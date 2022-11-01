#include <stdlib.h>  
#include <stdio.h> 
#include <time.h>  
#include "Components.h"
#include "Systems/KeyInput.h"

void Start(Entity entity)
{

}

void Update(float dt, Entity entity)
{
	float speed = 5.0f;
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];
	Camera &camera = coordinator->getComponent<Camera>(entity);
	if (keyInput->getIsKeyDown(GLFW_KEY_UP))
	{
		camera.movePosition(dt * speed * Vecteur3D(0, 1, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_DOWN))
	{
		camera.movePosition(dt * speed * Vecteur3D(0, -1, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_LEFT))
	{
		camera.movePosition(dt * speed * Vecteur3D(-1, 0, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_RIGHT))
	{
		camera.movePosition(dt * speed * Vecteur3D(1, 0, 0));
	}
	else if (KeyInput::_instances[0]->getIsKeyDown(GLFW_KEY_ESCAPE))
	{
		InputsManager::setEndGame(true);
	}
}

class MoveCamera : public LogicBehaviour
{
private:

public:
	MoveCamera(Entity entity) : LogicBehaviour(entity)
	{
		update_ = [this](float dt) {Update(dt, entity_); };
		start_ = [this]() {Start(entity_); };
	}
};