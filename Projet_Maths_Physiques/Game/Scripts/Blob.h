#include <stdlib.h>  
#include <stdio.h> 
#include <time.h>  
#include "Components.h"
#include "Systems/KeyInput.h"
#include "Forces/ParticuleRessortPtPt.h"
#include "ParticuleForceRegistry.h"


void addParticule(std::vector<Entity>& blob, Vecteur3D position, ParticuleForceRegistry* registry)
{
	//On cree la nouvelle particule
	Coordinator* coordinator = Coordinator::getInstance();
	Entity newParticule = coordinator->createEntity();
	Transform transform(position);
	Sphere sphere(0.5);
	coordinator->addComponent(newParticule, transform);
	Particule particule(newParticule, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(newParticule, (Object3D) sphere);
	coordinator->addComponent(newParticule, particule);

	//Fait le lien entre la nouvelle particule et toutes les autres
	for (auto particule : blob)
	{
		ParticuleRessortPtPt* ptr_forceRessort_particule = new ParticuleRessortPtPt(1, coordinator->getComponentPtr<Particule>(particule), coordinator->getComponentPtr<Particule>(newParticule), 0.5);
		ParticuleRessortPtPt* ptr_forceRessort_newParticule = new ParticuleRessortPtPt(1, coordinator->getComponentPtr<Particule>(newParticule), coordinator->getComponentPtr<Particule>(particule), 0.5);

		registry->add(coordinator->getComponentPtr<Particule>(particule), ptr_forceRessort_particule);
		registry->add(coordinator->getComponentPtr<Particule>(newParticule), ptr_forceRessort_newParticule);

	}

	blob.push_back(newParticule);

	//Todo ajouter les colliders
	
}


void moveBlob(std::vector<Entity>& blob, Vecteur3D move)
{
	Coordinator* coordinator = Coordinator::getInstance();
	for (auto particule : blob)
	{
		Transform& transform = coordinator->getComponent<Transform>(particule);
		Vecteur3D newPosition = transform.getPosition() + move;
		transform.setPosition(newPosition);
	}
}


void StartBlob(Entity entity, std::vector<Entity>& blob, ParticuleForceRegistry* registry)
{
	srand(time(NULL));
	int nbParticules = 100;
	for (int i = 0; i < nbParticules; i++)
	{
		Vecteur3D position((rand() % 100) / 10.0f, (rand() % 100) / 10.0f + 15, 0);
		addParticule(blob, position, registry);
	}

}

void UpdateBlob(float dt, Entity entity, std::vector<Entity>& blob, ParticuleForceRegistry* registry)
{
	float speed = 5.0f;
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];

	if (keyInput->getIsKeyDown(GLFW_KEY_W))
	{
		moveBlob(blob, dt * speed * Vecteur3D(0, 1, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_S))
	{
		moveBlob(blob, dt * speed * Vecteur3D(0, -1, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_A))
	{
		moveBlob(blob, dt * speed * Vecteur3D(-1, 0, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_D))
	{
		moveBlob(blob, dt * speed * Vecteur3D(1, 0, 0));
	}
}

class Blob : public LogicBehaviour
{
private:
	std::vector<Entity> blob_;
	ParticuleForceRegistry* registry_;

public:
	Blob(Entity entity, ParticuleForceRegistry* registry) : LogicBehaviour(entity), registry_(registry), blob_()
	{
		update_ = [this](float dt) {UpdateBlob(dt, entity_, blob_, registry_); };
		start_ = [this]() {StartBlob(entity_, blob_, registry_); };
	}


};