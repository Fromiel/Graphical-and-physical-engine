#include "Systems/CollisionsSystem.h"
#include "Bounding/BVHNode.h"
#include "Bounding/BoundingSphere.h"
#include "Components/Transform.h"

void CollisionsSystem::update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();

	//Colliders
	std::vector<Collider> colliders;
	
	// 1) Construire BVH
	BVHNode<BoundingSphere> bvh;
	for (auto gameObject : entities_)
	{
		auto collider = coordinator->getComponent<Collider>(gameObject);
		colliders.push_back(collider);
		// Inserer ce collider dans le bvh
		Transform t = coordinator->getComponent<Transform>(gameObject);
		BoundingSphere bs(t.getPosition(), t.maxScale());
		bvh.insert(collider.getRigidbody(), bs);
	}

	// 2) Detecter les collisions possibles
	PotentialContact potentialContacts[100];

	int nbPotentialContact = bvh.getPotentialContacts(potentialContacts, 100);

	// 3) Calculer vrai collisions
	for (int i = 0; i < nbPotentialContact; i++)
	{
		//todo : generer tous les contacts pour tous les contacts potentiels
	}

	// 4) Resoudre les collisions




}

int generateContactsSphereSphere(const SphereCollider& Sphere1, const SphereCollider& Sphere2, CollisionData* data) {
	Coordinator* coord = Coordinator::getInstance();
	Vecteur3D pos1 = Sphere1.getPosition();
	Vecteur3D pos2 = Sphere2.getPosition();
	float diffPose = distance(pos1, pos2);
	if (diffPose >= Sphere1.radius + Sphere2.radius) {
		return 0;
	}
	Vecteur3D normal = (pos1 - pos2).normalized();
	data->normalContact = normal;
	data->ptContact = pos1 + (pos1 - pos2) * 0.5f;
	data->penetration = (Sphere1.radius + Sphere2.radius - diffPose); 
	//data->setBodyData(Sphere1.rigidbody_, Sphere2.rigidbody_, data->friction, data->restitution);
	return 1;
}

int generateContactsSpherePlane(const SphereCollider& Sphere, const PlaneCollider& Plan, CollisionData* data) {
	// Cache the sphere position. 
	Vecteur3D position = Sphere.getPosition();
	// Find the distance from the plane. 
	float ballDistance = scalar_product(Plan.normal, position) - Sphere.radius - Plan.offset; 
	if (ballDistance >= 0) {
		return 0;
	}
	// Create the contact; it has a normal in the plane direction. 
	data->normalContact = Plan.normal; 
	data->penetration = -ballDistance; 
	data->ptContact = position - Plan.normal * (ballDistance + Sphere.radius);
	return 1;
}

int generateContactsBoxPlane(const BoxCollider& Box, const PlaneCollider& Plan, CollisionData* data) {
	Vecteur3D halfSize = Box.halfsize;
	Vecteur3D vertices[8] = { 
		Vecteur3D(-halfSize.get_x() - halfSize.get_y() - halfSize.get_z()), 
		Vecteur3D(-halfSize.get_x() - halfSize.get_y() + halfSize.get_z()),
		Vecteur3D(-halfSize.get_x() + halfSize.get_y() - halfSize.get_z()),
		Vecteur3D(-halfSize.get_x() + halfSize.get_y() + halfSize.get_z()),
		Vecteur3D(+halfSize.get_x() - halfSize.get_y() - halfSize.get_z()),
		Vecteur3D(+halfSize.get_x() - halfSize.get_y() + halfSize.get_z()),
		Vecteur3D(+halfSize.get_x() + halfSize.get_y() - halfSize.get_z()),
		Vecteur3D(+halfSize.get_x() + halfSize.get_y() + halfSize.get_z())
	};
	for (unsigned i = 0; i < 8; i++) { 
		vertices[i] = Box.getOffset() * vertices[i];
	}
	
	int nbContact = 0;

	for(auto vertexPos : vertices) {

		// Calculate the distance from the plane. 
		float vertexDistance = scalar_product(vertexPos,Plan.normal);
		// Compare this to the plane’s distance. 
		if (vertexDistance <= Plan.offset) {
			// Create the contact data. 
			// The contact point is halfway between the vertex and the plane. We multiply the direction by half the separation distance and add the vertex location. 
			data->ptContact = Plan.normal * (vertexDistance - Plan.offset) + vertexPos;
			data->normalContact = Plan.normal;
			data->penetration = Plan.offset - vertexDistance;
			nbContact++;
			data++;
		}
	}
	return nbContact;
}

int generateContactsBoxSphere(const BoxCollider& Box, const SphereCollider& Sphere, CollisionData* data) {
	// Transform the center of the sphere into box coordinates. 
	Vecteur3D center = Sphere.getPosition();
	Matrix34 mat = std::vector<double>{ 1,0,0,0,0,1,0,0,0,0,1,0};
	mat.transformPosition(Box.getPosition());
	mat.inverse();
	Vecteur3D relCenter = mat * center;

	
	// Early out check to see if we can exclude the contact. 
	if (abs(relCenter.get_x()) - Sphere.radius > Box.halfsize.get_x() || abs(relCenter.get_y()) - Sphere.radius > Box.halfsize.get_y() || abs(relCenter.get_z()) - Sphere.radius > Box.halfsize.get_z()) {
		return 0;
	}  
	Vecteur3D closestPt(0,0,0); 
	float dist; 
	// Clamp each coordinate to the box. 
	dist = relCenter.get_x();
	if (dist > Box.halfsize.get_x()) dist = Box.halfsize.get_x();
	if (dist < -Box.halfsize.get_x()) dist = -Box.halfsize.get_x();
	closestPt = Vecteur3D(dist, closestPt.get_y(), closestPt.get_z());

	dist = relCenter.get_y();
	if (dist > Box.halfsize.get_y()) dist = Box.halfsize.get_y();
	if (dist < Box.halfsize.get_y()) dist = -Box.halfsize.get_y();
	closestPt = Vecteur3D(closestPt.get_x(), dist, closestPt.get_z());

	dist = relCenter.get_z();
	if (dist > Box.halfsize.get_z()) dist = Box.halfsize.get_z();
	if (dist < -Box.halfsize.get_z()) dist = -Box.halfsize.get_z();
	closestPt = Vecteur3D(closestPt.get_x(), closestPt.get_y(), dist);

	// Check to see if we’re in contact. 
	dist = (closestPt - relCenter).norm_squared(); 
	if (dist > Sphere.radius * Sphere.radius) {
		return 0;
	}
	// Compile the contact. 
	mat = Matrix34(std::vector<double>{ 1,0,0,0,0,1,0,0,0,0,1,0 });
	mat.transformPosition(Box.getPosition());
	Vecteur3D closestPtWorld = mat * closestPt;
	data->normalContact = (closestPtWorld - center);
	data->normalContact.normalized(); 
	data->ptContact = closestPtWorld; 
	data->penetration = Sphere.radius - sqrt(dist);
	return 1;
}

int generateContacts(const Collider& firstCollider, const Collider& secondCollider, CollisionData* data) {
	if (firstCollider.getType() == SphereC && secondCollider.getType() == SphereC) {
		return generateContactsSphereSphere((SphereCollider)firstCollider, (SphereCollider)secondCollider, data);
	}
	if (firstCollider.getType() == SphereC && secondCollider.getType() == PlanC) {
		return generateContactsSpherePlane((SphereCollider)firstCollider, (PlaneCollider)secondCollider, data);
	}
	if (firstCollider.getType() == BoxC && secondCollider.getType() == PlanC) {
		return generateContactsBoxPlane((BoxCollider)firstCollider, (PlaneCollider)secondCollider, data);
	}
	if (firstCollider.getType() == BoxC && secondCollider.getType() == SphereC) {
		return generateContactsBoxSphere((BoxCollider)firstCollider, (SphereCollider)secondCollider, data);
	}
}