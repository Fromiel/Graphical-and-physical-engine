#include <stdlib.h>  
#include <stdio.h> 
#include <time.h>  
#include "Components.h"
#include "Systems/KeyInput.h"
#include "Forces/ParticuleRessortPtPt.h"
#include "ParticuleForceRegistry.h"
#include "Collisions/Liens/ParticuleRod.h"


void addParticuleRod(std::vector<Entity>& blob, Vecteur3D position, ParticuleForceRegistry* registry, std::vector<ParticuleRod>& rods)
{
	//On cree la nouvelle particule
	Coordinator* coordinator = Coordinator::getInstance();
	Entity newParticule = coordinator->createEntity();
	Transform transform(position);
	Sphere sphere(0.5);
	Shader materialShader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	Material sphereMat(materialShader, Vecteur3D(0.15, 0.15, 0.9), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));
	coordinator->addComponent(newParticule, transform);
	Particule particule(newParticule, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(newParticule, (Object3D) sphere);
	coordinator->addComponent(newParticule, particule);
	coordinator->addComponent(newParticule, sphereMat);

	//Fait le lien entre la nouvelle particule et toutes les autres
	for (auto particule : blob)
	{
		//ressorts
		ParticuleRessortPtPt* ptr_forceRessort_particule = new ParticuleRessortPtPt(1, coordinator->getComponentPtr<Particule>(particule), coordinator->getComponentPtr<Particule>(newParticule), 1.5);
		ParticuleRessortPtPt* ptr_forceRessort_newParticule = new ParticuleRessortPtPt(1, coordinator->getComponentPtr<Particule>(newParticule), coordinator->getComponentPtr<Particule>(particule), 1.5);

		registry->add(coordinator->getComponentPtr<Particule>(particule), ptr_forceRessort_particule);
		registry->add(coordinator->getComponentPtr<Particule>(newParticule), ptr_forceRessort_newParticule);

		//colliders
		ParticuleRod cable(5, coordinator->getComponentPtr<Particule>(particule), coordinator->getComponentPtr<Particule>(newParticule));
		rods.push_back(cable);
	}

	blob.push_back(newParticule);


	
}


void moveBlobRod(std::vector<Entity>& blob, Vecteur3D move)
{
	Coordinator* coordinator = Coordinator::getInstance();
	for (auto particule : blob)
	{
		Transform& transform = coordinator->getComponent<Transform>(particule);
		Vecteur3D newPosition = transform.getPosition() + move;
		transform.setPosition(newPosition);
	}
}


void StartBlobRod(Entity entity, std::vector<Entity>& blob, ParticuleForceRegistry* registry, std::vector<ParticuleRod>& rods)
{
	srand(time(NULL));
	int nbParticules = 8;
	for (int i = 0; i < nbParticules; i++)
	{
		Vecteur3D position((rand() % 100) / 10.0f, (rand() % 100) / 10.0f + 40, 0);
		addParticuleRod(blob, position, registry, rods);
	}

}


void addContactsRod(std::vector<ParticuleRod> rods, ParticuleContact* pc)
{
	for (auto& rod : rods)
	{
		rod.addContact(pc, 0);
	}
}


void UpdateBlobRod(float dt, Entity entity, std::vector<Entity>& blob, ParticuleForceRegistry* registry, std::vector<ParticuleContact*> all_contacts_in_scene, ParticuleContact* pc, ParticuleContactResolver contact_resolver, std::vector<ParticuleRod> rods)
{
	all_contacts_in_scene.clear();

	pc->clear();
	addContactsRod(rods, pc);
	
	all_contacts_in_scene.push_back(pc);


	contact_resolver.SetIterations(1 + all_contacts_in_scene.size() * 2);
	contact_resolver.resolveContacts(all_contacts_in_scene, 1, dt);

	float speed = 5.0f;
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];

	if (keyInput->getIsKeyDown(GLFW_KEY_T))
	{
		moveBlobRod(blob, dt * speed * Vecteur3D(0, 1, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_G))
	{
		moveBlobRod(blob, dt * speed * Vecteur3D(0, -1, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_F))
	{
		moveBlobRod(blob, dt * speed * Vecteur3D(-1, 0, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_H))
	{
		moveBlobRod(blob, dt * speed * Vecteur3D(1, 0, 0));
	}
}

class BlobRod : public LogicBehaviour
{
private:
	std::vector<Entity> blob_;
	ParticuleForceRegistry* registry_;
	std::vector<ParticuleContact*> all_contacts_in_scene_;
	ParticuleContact* pc_;
	ParticuleContactResolver contact_resolver_;
	std::vector<ParticuleRod> rods_;

public:
	BlobRod(Entity entity, ParticuleForceRegistry* registry, ParticuleContact* pc) : LogicBehaviour(entity), registry_(registry), blob_(), pc_(pc)
	{
		update_ = [this](float dt) {UpdateBlobRod(dt, entity_, blob_, registry_, all_contacts_in_scene_, pc_, contact_resolver_, rods_); };
		start_ = [this]() {StartBlobRod(entity_, blob_, registry_, rods_); };
	}
};