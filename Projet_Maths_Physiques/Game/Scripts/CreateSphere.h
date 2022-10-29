#include <stdlib.h>  
#include <stdio.h> 
#include <time.h>  
#include "Components.h"
#include "Systems/KeyInput.h"

void Start()
{
	srand(time(NULL));
}

void Update(float dt)
{
	Coordinator* coordinator = Coordinator::getInstance();
	if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_S))
	{
		Vecteur3D position((rand() % 100) / 5.0f, (rand() % 100) / 5.0f + 25, (rand() % 100) / 5.0f);
		int x = rand() % 10 + 1;
		Entity newSphere = coordinator->createEntity();
		Transform newTransform(position);
		Object3D newMeshes = Sphere(2);
		coordinator->addComponent(newSphere, newTransform);
		coordinator->addComponent(newSphere, newMeshes);
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_ESCAPE))
	{
		InputsManager::setEndGame(true);
	}
}

class CreateSphere : public LogicBehaviour
{
	private:

	public:
		CreateSphere(Entity entity) : LogicBehaviour(entity)
		{
			update_ = Update;
			start_ = Start;
		}


};