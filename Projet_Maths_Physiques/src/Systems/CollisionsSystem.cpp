#include "Systems/CollisionsSystem.h"
#include "Bounding/Octree.h"
#include "Bounding/BVHNode.h"
#include "Bounding/BoundingSphere.h"
#include "Components/Transform.h"
#include "Systems/InputsManager.h"
#include "Systems/Time.h"

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
	typedef struct Item {
		std::shared_ptr<Collider> collider;
		Element<Collider> element;
		Transform transform;
		float x;
		float y;
		float z;
		float maxWidth;
	} Item;
	Octree<Item>* octree = new Octree<Item>(-15.0f, -15.0f, -15.0f, 30.0f, 2);
	for (int i = 0; i < colliders.size(); i++) {
		octree->insertItem({
			colliders[i],
			elements[i],
			transforms[i],
			transforms[i].getPosition().get_x(),
			transforms[i].getPosition().get_y(),
			transforms[i].getPosition().get_z(),
			transforms[i].maxScale()
		});
	}

	// std::cout << "=============================== CYCLE ===============================" << octree->gatherCollisions().size() << std::endl;
	
	// Construire BVH pour chaque paire donnée par l'octree
	for (auto element : octree->gatherCollisions()) {
		// std::cout << "{(" << element.first.x << ";" << element.first.y << ";" << element.first.z << "), (" << element.second.x << ";" << element.second.y << ";" << element.second.z << ")" << std::endl;

		// Inserer les colliders dans le bvh
		BVHNode<BoundingSphere, Collider> bvh;
		bvh.insert(&element.first.element, BoundingSphere(element.first.transform.getPosition(), element.first.transform.maxScale()));
		bvh.insert(&element.second.element, BoundingSphere(element.second.transform.getPosition(), element.second.transform.maxScale()));

		// Determiner la possibilite de collision
		PotentialContact<Collider> potentialContact[10];
		int nbpc = bvh.getPotentialContacts(potentialContact, 10);

		// Affiner le calcul pour valider la collision
		if (!nbpc) continue;

		CollisionData datas[10000];
		CollisionData* currentData = datas;
		int nbDatas = 0;
		int n = generateContacts(potentialContact[0].body[0]->rb, potentialContact[0].body[1]->rb, currentData);
		n += generateContacts(potentialContact[0].body[1]->rb, potentialContact[0].body[0]->rb, currentData);
		nbDatas += n;
		currentData += n;

		// Resoudre la collision
		if (nbDatas == 0)continue;
		std::cout << "Nombre de contacts : " << nbDatas << std::endl;
		for (int i = 0; i < nbDatas; i++)std::cout << datas[i] << std::endl;
		Time::setTimeScale(0.0f);
	}

	delete octree;
}

int CollisionsSystem::generateContactsSphereSphere(const SphereCollider* Sphere1, const SphereCollider* Sphere2, CollisionData* data) {
	Coordinator* coord = Coordinator::getInstance();
	Vecteur3D pos1 = Sphere1->getPosition();
	Vecteur3D pos2 = Sphere2->getPosition();
	float diffPose = distance(pos1, pos2);
	if (diffPose >= Sphere1->radius + Sphere2->radius) {
		return 0;
	}

	Vecteur3D normal = (pos1 - pos2).normalized();
	data->normalContact = normal;
	data->ptContact = pos1 - (normal * Sphere2->radius);
	data->penetration = (Sphere1->radius + Sphere2->radius - diffPose);
	//data->setBodyData(Sphere1.rigidbody_, Sphere2.rigidbody_, data->friction, data->restitution);
	return 1;
}

int CollisionsSystem::generateContactsSpherePlane(const SphereCollider* Sphere, const PlaneCollider* Plan, CollisionData* data) {
	// Cache the sphere position. 
	Vecteur3D position = Sphere->getPosition();
	// Find the distance from the plane. 
	float ballDistance = scalar_product(Plan->normal, position) - Sphere->radius - Plan->offset;
	if (ballDistance >= 0) {
		return 0;
	}
	// Create the contact; it has a normal in the plane direction. 
	data->normalContact = Plan->normal;
	data->penetration = -ballDistance; 
	data->ptContact = position - Plan->normal * (ballDistance + Sphere->radius);
	return 1;
}

int CollisionsSystem::generateContactsBoxPlane(const BoxCollider* Box, const PlaneCollider* Plan, CollisionData* data) {
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
	Matrix34 toWorld, toPlane;
	toWorld.setOrientationAndPosition(Quaternion(), Box->getPosition());
	toPlane.setOrientationAndPosition(Quaternion(), Plan->getPosition());
	toPlane = toPlane.inverse();
	toPlane = toPlane * toWorld;

	for (unsigned i = 0; i < 8; i++) { 
		vertices[i] = toPlane * vertices[i];

	}
	
	int nbContact = 0;

	for(auto vertexPos : vertices) {

		// Calculate the distance from the plane. 
		float vertexDistance = scalar_product(vertexPos,Plan->normal) - Plan->offset;
		// Compare this to the plane�s distance. 
		if (vertexDistance < 0) {
			// Create the contact data. 
			// The contact point is halfway between the vertex and the plane. We multiply the direction by half the separation distance and add the vertex location. 
			data->ptContact = vertexPos - Plan->normal * vertexDistance;
			data->normalContact = Plan->normal;
			data->penetration = -vertexDistance;
			nbContact++;
			data++;
		}
	}
	return nbContact;
}

int CollisionsSystem::generateContactsBoxSphere(const BoxCollider* Box, const SphereCollider* Sphere, CollisionData* data) {
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
	data->normalContact = (closestPtWorld - center);
	data->normalContact.normalized(); 
	data->ptContact = closestPtWorld; 
	data->penetration = Sphere->radius - sqrt(dist);
	return 1;
}

int CollisionsSystem::generateContacts(Collider* firstCollider,  Collider* secondCollider, CollisionData* data) {
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