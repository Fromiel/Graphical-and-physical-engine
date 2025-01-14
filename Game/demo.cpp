#include <cstdio>
#include <ostream>
#include "Components.h"
#include "Systems.h"
#include "Scripts/MoveCamera.h"
#include "Engine.h"
#include "GameObject.h"
#include "Scripts/CreateCube.h"
#include "Bounding/BVHNode.h"
#include "Bounding/BoundingSphere.h"

int main(void)
{
	Engine* engine = Engine::getInstance();

	//set shaders
	Shader materialShader("./Shaders/shader.vert", "./Shaders/shader.frag");
	Shader lightShader("./Shaders/lightShader.vert", "./Shaders/lightShader.frag");

	Material sMaterial(materialShader, Vector3D(0.8f, 0.5f, 0.2f), Vector3D(1.0f, 0.5f, 0.31f), Vector3D(0.5f, 0.5f, 0.5f), 200);
	Material greenMaterial(materialShader, Vector3D(0.4f, 0.9f, 0.1f), Vector3D(1.0f, 0.5f, 0.31f), Vector3D(0.5f, 0.5f, 0.5f));
	Material transparentMaterial(materialShader, Vector3D(0.8f, 0.5f, 0.2f), Vector3D(1.0f, 0.5f, 0.31f), Vector3D(0.5f, 0.5f, 0.5f), 200, 0.2);
	Material centerMaterial(materialShader, Vector3D(0.9f, 0.1f, 0.1f), Vector3D(1.0f, 0.5f, 0.31f), Vector3D(0.5f, 0.5f, 0.5f), 200);
	Material middleMaterial(materialShader, Vector3D(0.9f, 0.9f, 0.9f), Vector3D(1.0f, 0.5f, 0.31f), Vector3D(0.5f, 0.5f, 0.5f), 200);

	//---------TODO--------------------
	//set les inputs
	KeyInput keyInput(std::vector<int>({GLFW_KEY_ESCAPE, GLFW_KEY_S, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_SPACE, GLFW_KEY_Q, GLFW_KEY_H , GLFW_KEY_G , GLFW_KEY_F , GLFW_KEY_T, GLFW_KEY_SPACE }));
	//-----------------------------------

	//camera
	GameObject camera(Vector3D(0, 15, 10), Vector3D(1, 1, 1), Vector3D(0, 0, 0));
	camera.addComponent(Camera(camera.getEntity(), 0.1f, 10000.0f, 90.0f));
	camera.addComponent((LogicBehaviour)MoveCamera(camera.getEntity()));

	//light
	GameObject light(Vector3D(0, 36, 45));
	light.addComponent((Object3D)Sphere());
	light.addComponent(Light(Vector3D(0.8f, 0.8f, 0.8f)));
	light.addComponent(Material(lightShader));

	//Test collider

	//Creation cible

	GameObject center(Vector3D(0, 15, -10), Vector3D(1, 1, 0.1));
	center.addComponent((Object3D)Cube());
	center.addComponent(centerMaterial);
	center.addBoxCollider(Vector3D(0.5, 0.5, 0.05));

	GameObject middle(Vector3D(0, 15, -10.15), Vector3D(3, 3, 0.1));
	middle.addComponent((Object3D)Cube());
	middle.addComponent(middleMaterial);
	middle.addBoxCollider(Vector3D(1.5, 1.5, 0.05));

	GameObject center2(Vector3D(0, 15, -10.30), Vector3D(4.5, 4.5, 0.1));
	center2.addComponent((Object3D)Cube());
	center2.addComponent(centerMaterial);
	center2.addBoxCollider(Vector3D(2.25, 2.25, 0.05));







	GameObject createCubeHolder;
	createCubeHolder.addComponent((LogicBehaviour)CreateCube(createCubeHolder.getEntity(), camera));


	//Loop
	engine->loop();


	return 0;
}