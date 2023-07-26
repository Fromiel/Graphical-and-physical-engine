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
	float speed = 10.0f;
	float rotationSpeed = 0.2f;
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];
	Camera &camera = coordinator->getComponent<Camera>(entity);

	Matrix34 viewMatrixInv = camera.getViewMatrix();
	std::vector<double> content = viewMatrixInv.getContentAsStdVector();
	std::vector<double> matrix3dContent = { content[0], content[1], content[2], content[4], content[5], content[6], content[8], content[9], content[10] };
	Matrix3D m3d(matrix3dContent);

	/*float dt = dT;
	if (dT == 0)
		dt = 0.05f;*/

	if (keyInput->getIsKeyDown(GLFW_KEY_W))
	{
		camera.move(dt * speed * Vecteur3D(0, 0, -1));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_S))
	{
		camera.move(dt * speed * Vecteur3D(0, 0, 1));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_A))
	{
		camera.move(dt * speed * Vecteur3D(-1, 0, 0));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_D))
	{
		camera.move(dt * speed * Vecteur3D(1, 0, 0));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_SPACE))
	{
		camera.move(dt * speed * Vecteur3D(0, 1, 0));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_Q))
	{
		camera.move(dt * speed * Vecteur3D(0, -1, 0));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_UP))
	{
		camera.rotate(rotationSpeed * dt, Vecteur3D(1, 0, 0));
	}
	else if (keyInput->getIsKeyDown(GLFW_KEY_LEFT))
	{
		camera.rotate(rotationSpeed * dt, Vecteur3D(0, 1, 0));
	}
	else if (keyInput->getIsKeyDown(GLFW_KEY_DOWN))
	{
		camera.rotate(rotationSpeed * dt, Vecteur3D(-1, 0, 0));
	}
	else if (keyInput->getIsKeyDown(GLFW_KEY_RIGHT))
	{
		camera.rotate(rotationSpeed * dt, Vecteur3D(0, -1, 0));
	}
	if (keyInput->getIsKeyDown(GLFW_KEY_ESCAPE))
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