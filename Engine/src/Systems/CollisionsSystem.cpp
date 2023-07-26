#include "Systems/CollisionsSystem.h"
#include "Bounding/Octree.h"
#include "Bounding/BVHNode.h"
#include "Bounding/BoundingSphere.h"
#include "Components/Transform.h"
#include "Systems/InputsManager.h"
#include "Systems/Time.h"

// Helper structure for octree
typedef struct Item {
	std::shared_ptr<Collider> collider;
	Element<Collider> element;
	Transform transform;
	float x;
	float y;
	float z;
	float maxWidth;
} Item;

void CollisionsSystem::update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();

	//On stocke les infos utiles dans des vectors
	//Colliders
	std::vector<std::shared_ptr<Collider>> colliders;
	std::vector<Element<Collider>> elements;
	std::vector<Transform> transforms;
	for (auto gameObject : entities_)
	{
		auto collider = coordinator->getComponent<std::shared_ptr<Collider>>(gameObject);
		colliders.push_back(collider);
		transforms.push_back(coordinator->getComponent<Transform>(gameObject));
		elements.push_back({ collider.get() });
	}

	// Construire Octree
	Octree<Item>* octree = new Octree<Item>(-15.0f, -15.0f, -15.0f, 30.0f, 2);
	for (int i = 0; i < colliders.size(); i++) {
		octree->insertItem({
			colliders[i],
			elements[i],
			transforms[i],
			transforms[i].getPosition().get_x(),
			transforms[i].getPosition().get_y(),
			transforms[i].getPosition().get_z(),
			colliders[i]->getMaxSize()
		});
	}

	// Affiner le calcul pour valider les collision
	std::vector<CollisionData> datas;
	for (auto element : octree->gatherCollisions()) {
		generateContacts(&(*element.first.collider), &(*element.second.collider), &datas);
		generateContacts(&(*element.second.collider), &(*element.first.collider), &datas);
	}

	// Resoudre les collisions
	if (datas.size() != 0) {
		std::cout << "Nombre de contacts : " << datas.size() << std::endl;
		for (int i = 0; i < datas.size(); i++) std::cout << datas[i] << std::endl;
		Time::setTimeScale(0.0f);
	}

	delete octree;
}

int CollisionsSystem::generateContactsSphereSphere(const SphereCollider* Sphere1, const SphereCollider* Sphere2, std::vector<CollisionData>* data) {
	Coordinator* coord = Coordinator::getInstance();
	Vecteur3D pos1 = Sphere1->getPosition();
	Vecteur3D pos2 = Sphere2->getPosition();
	float diffPose = distance(pos1, pos2);
	if (diffPose >= Sphere1->radius + Sphere2->radius) {
		return 0;
	}

	Vecteur3D normal = (pos1 - pos2).normalized();
	CollisionData newData;
	newData.normalContact = normal;
	newData.ptContact = pos1 - (normal * Sphere2->radius);
	newData.penetration = (Sphere1->radius + Sphere2->radius - diffPose);
	//newData.setBodyData(Sphere1.rigidbody_, Sphere2.rigidbody_, data->friction, data->restitution);
	data->push_back(newData);

	return 1;
}

int CollisionsSystem::generateContactsSpherePlane(const SphereCollider* Sphere, const PlaneCollider* Plan, std::vector<CollisionData>* data) {
	// Cache the sphere position. 
	Vecteur3D position = Sphere->getPosition();

	//Position de la sphere dans les coordonnées du plan
	Matrix34 planToWorldPosition = Plan->getWorldPositionOrientation();
	Matrix34 sphereToPlan = planToWorldPosition.inverse();

	Vecteur3D positionInPlaneCoord = sphereToPlan * position;

	// Trouve la distance au plan
	float ballDistance = scalar_product(Vecteur3D(0, 1, 0), positionInPlaneCoord) - Sphere->radius;

	if (ballDistance >= 0 
		|| (positionInPlaneCoord.get_x() > Plan->halfSizeX && distance(positionInPlaneCoord, Vecteur3D(Plan->halfSizeX, 0, positionInPlaneCoord.get_z())) > 0)
		|| (positionInPlaneCoord.get_z() > Plan->halfSizeZ && distance(positionInPlaneCoord, Vecteur3D(positionInPlaneCoord.get_x(), 0, Plan->halfSizeZ)) > 0)
		)
	{
		return 0;
	}

	// Creer le contact 
	CollisionData newData;
	newData.normalContact = planToWorldPosition.transformDirection(Vecteur3D(0, 1, 0));
	newData.penetration = -ballDistance; 
	newData.ptContact = planToWorldPosition * (positionInPlaneCoord - newData.normalContact * (ballDistance - Sphere->radius));
	data->push_back(newData);

	return 1;
}

int CollisionsSystem::generateContactsBoxPlane(const BoxCollider* Box, const PlaneCollider* Plan, std::vector<CollisionData>* data) {
	Vecteur3D halfSize = Box->halfsize;
	//On cree les points de la boite
	Vecteur3D vertices[8] = { 
		Vecteur3D(-halfSize.get_x(), - halfSize.get_y(), - halfSize.get_z()), 
		Vecteur3D(-halfSize.get_x(), - halfSize.get_y(), + halfSize.get_z()),
		Vecteur3D(-halfSize.get_x(), + halfSize.get_y(), - halfSize.get_z()),
		Vecteur3D(-halfSize.get_x(), + halfSize.get_y(), + halfSize.get_z()),
		Vecteur3D(+halfSize.get_x(), - halfSize.get_y(), - halfSize.get_z()),
		Vecteur3D(+halfSize.get_x(), - halfSize.get_y(), + halfSize.get_z()),
		Vecteur3D(+halfSize.get_x(), + halfSize.get_y(), - halfSize.get_z()),
		Vecteur3D(+halfSize.get_x(), + halfSize.get_y(), + halfSize.get_z())
	};

	//On va passer les points dans les coordonnees du plan
	Matrix34 boxToWorld = Box->getWorldPositionOrientation();
	Matrix34 planToWorldPosition = Plan->getWorldPositionOrientation();
	Matrix34 boxToPlan = planToWorldPosition.inverse() * boxToWorld;

	for (unsigned i = 0; i < 8; i++) { 
		vertices[i] = boxToPlan * vertices[i];
	}
	
	int nbContact = 0;
	Vecteur3D normal = planToWorldPosition.transformDirection(Vecteur3D(0, 1, 0)); //Normale du plan dans les coordonnees du monde (par defaut un plan a sa normale = (0, 1, 0))

	for(auto vertexPos : vertices) {
		// Calcule la distance au plan
		float vertexDistance = scalar_product(vertexPos,Vecteur3D(0, 1, 0));
		// On regarde si le point coupe la plan
		if ((vertexPos.get_x() < Plan->halfSizeX && vertexPos.get_x() > -Plan->halfSizeX) && (vertexPos.get_z() < Plan->halfSizeZ && vertexPos.get_z() > -Plan->halfSizeZ) && vertexDistance < 0) {
			// Create the contact data. 
			CollisionData newData;
			newData.ptContact = planToWorldPosition * (vertexPos - normal * vertexDistance);
			newData.normalContact = normal;
			newData.penetration = -vertexDistance;
			data->push_back(newData);

			nbContact++;
		}
	}
	return nbContact;
}

int CollisionsSystem::generateContactsBoxSphere(const BoxCollider* Box, const SphereCollider* Sphere, std::vector<CollisionData>* data) {
	// Transforme le centre de la sphere dans les coordonnées de la boite 
	Vecteur3D center = Sphere->getPosition();
	Matrix34 boxToWorld = Box->getWorldPositionOrientation();
	Vecteur3D relCenter = boxToWorld.inverse() * center;

	
	// On regarde si on peut exclure le contact
	if (abs(relCenter.get_x()) - Sphere->radius > Box->halfsize.get_x() || abs(relCenter.get_y()) - Sphere->radius > Box->halfsize.get_y() || abs(relCenter.get_z()) - Sphere->radius > Box->halfsize.get_z()) {
		return 0;
	}  

	Vecteur3D closestPt(0,0,0); 
	float dist; 
	// Clamp each coordinate to the box. 
	dist = relCenter.get_x();
	if (dist > Box->halfsize.get_x()) dist = Box->halfsize.get_x();
	if (dist < -Box->halfsize.get_x()) dist = -Box->halfsize.get_x();
	closestPt = Vecteur3D(dist, closestPt.get_y(), closestPt.get_z());

	dist = relCenter.get_y();
	if (dist > Box->halfsize.get_y()) dist = Box->halfsize.get_y();
	if (dist < -Box->halfsize.get_y()) dist = -Box->halfsize.get_y();
	closestPt = Vecteur3D(closestPt.get_x(), dist, closestPt.get_z());

	dist = relCenter.get_z();
	if (dist > Box->halfsize.get_z()) dist = Box->halfsize.get_z();
	if (dist < -Box->halfsize.get_z()) dist = -Box->halfsize.get_z();
	closestPt = Vecteur3D(closestPt.get_x(), closestPt.get_y(), dist);

	// Check to see if were in contact. 
	dist = (closestPt - relCenter).norm_squared(); 
	if (dist > Sphere->radius * Sphere->radius) {
		return 0;
	}
	// Compile the contact. 
	Vecteur3D closestPtWorld = boxToWorld * closestPt;

	CollisionData newData;
	newData.normalContact = (closestPtWorld - center);
	newData.normalContact.normalized(); 
	newData.ptContact = closestPtWorld; 
	newData.penetration = Sphere->radius - sqrt(dist);
	data->push_back(newData);

	return 1;
}

int CollisionsSystem::generateContacts(Collider* firstCollider,  Collider* secondCollider, std::vector<CollisionData>* data) {
	if (firstCollider->getType() == SphereC && secondCollider->getType() == SphereC) {
		return generateContactsSphereSphere(static_cast<SphereCollider*>(firstCollider), static_cast<SphereCollider*>(secondCollider), data);
	}
	if (firstCollider->getType() == SphereC && secondCollider->getType() == PlanC) {
		return generateContactsSpherePlane(static_cast<SphereCollider*>(firstCollider), static_cast<PlaneCollider*>(secondCollider), data);
	}
	if (firstCollider->getType() == BoxC && secondCollider->getType() == PlanC) {
		return generateContactsBoxPlane(static_cast<BoxCollider*>(firstCollider), static_cast<PlaneCollider*>(secondCollider), data);
	}
	if (firstCollider->getType() == BoxC && secondCollider->getType() == SphereC) {
		return generateContactsBoxSphere(static_cast<BoxCollider*>(firstCollider), static_cast<SphereCollider*>(secondCollider), data);
	}
	return 0;
}