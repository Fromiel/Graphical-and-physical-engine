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
	// Find the distance from the plane. 
	float ballDistance = scalar_product(Vecteur3D(0, 1, 0) * Plan->getPosition(), position) - Sphere->radius;
	if (ballDistance >= 0 || ballDistance < -Sphere->radius) {
		return 0;
	}
	// Create the contact; it has a normal in the plane direction. 
	CollisionData newData;
	newData.normalContact = Vecteur3D(0, 1, 0);
	newData.penetration = -ballDistance; 
	newData.ptContact = position - Vecteur3D(0, 1, 0) * (ballDistance + Sphere->radius);
	data->push_back(newData);

	return 1;
}

int CollisionsSystem::generateContactsBoxPlane(const BoxCollider* Box, const PlaneCollider* Plan, std::vector<CollisionData>* data) {
	Vecteur3D halfSize = Box->halfsize;
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
	Matrix34 boxToWorld = Box->getWorldPositionOrientation();
	Matrix34 planToWorldPosition = Plan->getWorldPositionOrientation();
	Matrix34 boxToPlan = planToWorldPosition.inverse() * boxToWorld;

	for (unsigned i = 0; i < 8; i++) { 
		vertices[i] = boxToPlan * vertices[i];
	}
	
	int nbContact = 0;
	Vecteur3D normal = planToWorldPosition.transformDirection(Vecteur3D(0, 1, 0));

	for(auto vertexPos : vertices) {
		// Calculate the distance from the plane. 
		float vertexDistance = scalar_product(vertexPos,Vecteur3D(0, 1, 0));
		// Compare this to the planes distance. 
		if ((vertexPos.get_x() < Plan->halfSizeX && vertexPos.get_x() > -Plan->halfSizeX) && (vertexPos.get_z() < Plan->halfSizeY && vertexPos.get_z() > -Plan->halfSizeY) && vertexDistance < 0) {
			// Create the contact data. 
			// The contact point is halfway between the vertex and the plane. We multiply the direction by half the separation distance and add the vertex location. 
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
	// Transform the center of the sphere into box coordinates. 
	Vecteur3D center = Sphere->getPosition();
	Matrix34 mat = std::vector<double>{ 1,0,0,0,0,1,0,0,0,0,1,0};
	mat.setOrientationAndPosition(Quaternion(), Box->getPosition());
	mat = mat.inverse();
	Vecteur3D relCenter = mat * center;

	
	// Early out check to see if we can exclude the contact. 
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
	if (dist < Box->halfsize.get_y()) dist = -Box->halfsize.get_y();
	closestPt = Vecteur3D(closestPt.get_x(), dist, closestPt.get_z());

	dist = relCenter.get_z();
	if (dist > Box->halfsize.get_z()) dist = Box->halfsize.get_z();
	if (dist < -Box->halfsize.get_z()) dist = -Box->halfsize.get_z();
	closestPt = Vecteur3D(closestPt.get_x(), closestPt.get_y(), dist);

	// Check to see if we�re in contact. 
	dist = (closestPt - relCenter).norm_squared(); 
	if (dist > Sphere->radius * Sphere->radius) {
		return 0;
	}
	// Compile the contact. 
	mat = Matrix34(std::vector<double>{ 1,0,0,0,0,1,0,0,0,0,1,0 });
	mat.setOrientationAndPosition(Quaternion(), Box->getPosition());
	Vecteur3D closestPtWorld = mat * closestPt;

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