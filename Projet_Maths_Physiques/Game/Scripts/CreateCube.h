#include <stdlib.h>  
#include <stdio.h> 
#include <time.h>  
#include "Components.h"
#include "Systems/KeyInput.h"
#include "GameObject.h"

void StartC(Entity entity)
{
	srand(time(NULL));
	//iSecret = rand() % 10 + 1; entre 1 et 10
}

void UpdateC(float dt, Entity entity)
{
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];

	if (keyInput->getIsKeyDown(GLFW_KEY_F))
	{
		Shader materialShader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");

		Material sMaterial(materialShader, Vecteur3D(0.3f, 0.8f, 0.2f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));

		float randX = rand() % 20 - 10;
		float randY = rand() % 20 - 10;
		float randZ = rand() % 20 - 10;

		Vecteur3D randomSpeed(randX, randY, randZ);

		GameObject cube(Vecteur3D(0, 15, 0));
		cube.addComponent((Object3D)Cube());
		cube.addComponent(sMaterial);
		cube.createRigidbody(1, 1, 1, CubeMesh,randomSpeed );
		cube.addGravityRigidbody(0);
		cube.addBoxCollider(Vecteur3D(0.5, 0.5, 0.5));

	}
}

class CreateCube : public LogicBehaviour
{
private:

public:
	CreateCube(Entity entity) : LogicBehaviour(entity)
	{
		update_ = [this](float dt) {UpdateC(dt, entity_); };
		start_ = [this]() {StartC(entity_); };
	}
};