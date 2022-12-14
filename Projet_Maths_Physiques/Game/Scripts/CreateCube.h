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

void UpdateC(float dt, Entity entity, GameObject camera)
{
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];

	if (keyInput->getIsKeyPressed(GLFW_KEY_F) || MouseInputs::IsLeftMouseDown())
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
	/*else if (MouseInputs::IsLeftMouseDown())
	{
		Shader materialShader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");

		Material sMaterial(materialShader, Vecteur3D(0.3f, 0.8f, 0.2f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));

		float randX = rand() % 20 - 10;
		float randY = rand() % 20 - 10;
		float randZ = rand() % 20 - 10;

		Vecteur3D randomSpeed(randX, randY, randZ);

		Transform cameraTransform = camera.getComponent<Transform>();
		GameObject sphere(cameraTransform.getPosition(), Vecteur3D(0.3, 0.3, 0.3));
		sphere.addComponent((Object3D)Sphere());
		sphere.addComponent(sMaterial);

		Matrix34 mat;
		mat.setOrientationAndPosition(cameraTransform.getOrientation(), Vecteur3D());
		Vecteur3D speed = mat * Vecteur3D(0, 0, -15);
		sphere.createRigidbody(1, 1, 1, SphereMesh, speed);
		sphere.addGravityRigidbody(-3);
		sphere.addSphereCollider(0.3f);

	}*/
}

class CreateCube : public LogicBehaviour
{
private:
	GameObject camera_;

public:
	CreateCube(Entity entity, GameObject camera) : LogicBehaviour(entity)
	{
		camera_ = camera;
		update_ = [this](float dt) {UpdateC(dt, entity_, camera_); };
		start_ = [this]() {StartC(entity_); };
	}
};