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
	Engine *engine = Engine::getInstance();

	//set shaders
	Shader materialShader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	Shader lightShader("./src/Shaders/lightShader.vert", "./src/Shaders/lightShader.frag");

	Material sMaterial(materialShader, Vecteur3D(0.8f, 0.5f, 0.2f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f), 200);
	Material greenMaterial(materialShader, Vecteur3D(0.4f, 0.9f, 0.1f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));
	Material transparentMaterial(materialShader, Vecteur3D(0.8f, 0.5f, 0.2f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f), 200, 0.2);

	//---------TODO--------------------
	//set les inputs
	KeyInput keyInput(std::vector<int>({ GLFW_KEY_ESCAPE, GLFW_KEY_S, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_SPACE, GLFW_KEY_Q, GLFW_KEY_H , GLFW_KEY_G , GLFW_KEY_F , GLFW_KEY_T, GLFW_KEY_SPACE }));
	//-----------------------------------

	//Sol en y = 0
	//GameObject sol(Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(100.0f, 0.01f, 100.0f));
	//sol.addComponent((Object3D)Cube());
	//sol.addComponent(sMaterial);

	//camera
	GameObject camera(Vecteur3D(0, 15, 10), Vecteur3D(1, 1, 1), Vecteur3D(0, 0, 0));
	camera.addComponent(Camera(camera.getEntity(), 0.1f, 10000.0f, 90.0f));
	camera.addComponent((LogicBehaviour) MoveCamera(camera.getEntity()));

	//light
	GameObject light(Vecteur3D(0, 36, 45));
	light.addComponent((Object3D)Sphere());
	light.addComponent(Light(Vecteur3D(0.8f, 0.8f, 0.8f)));
	light.addComponent(Material(lightShader));

	//Test collider

	//Creation d'une boite avec 6 plans
	GameObject wall1(Vecteur3D(), Vecteur3D(30, 0.01, 30));
	wall1.addComponent((Object3D)Cube());
	wall1.addComponent(sMaterial);
	wall1.addPlaneCollider(0, Vecteur3D(0, 1, 0));

	GameObject wall2(Vecteur3D(0, 30, 0), Vecteur3D(30, 0.01, 30));
	wall2.addComponent((Object3D)Cube());
	wall2.addComponent(sMaterial);
	wall2.addPlaneCollider(0, Vecteur3D(0, -1, 0));

	GameObject wall3(Vecteur3D(-15, 15, 0), Vecteur3D(0.01, 30, 30));
	wall3.addComponent((Object3D)Cube());
	wall3.addComponent(sMaterial);
	wall3.addPlaneCollider(0, Vecteur3D(1, 0, 0));

	GameObject wall4(Vecteur3D(15, 15, 0), Vecteur3D(0.01, 30, 30));
	wall4.addComponent((Object3D)Cube());
	wall4.addComponent(sMaterial);
	wall4.addPlaneCollider(0, Vecteur3D(-1, 0, 0));

	GameObject wall5(Vecteur3D(0, 15, -15), Vecteur3D(30, 30, 0.01));
	wall5.addComponent((Object3D)Cube());
	wall5.addComponent(sMaterial);
	wall5.addPlaneCollider(0, Vecteur3D(0, 0, 1));

	GameObject wall6(Vecteur3D(0, 15, 15), Vecteur3D(30, 30, 0.01));
	wall6.addComponent((Object3D)Cube());
	wall6.addComponent(transparentMaterial);
	wall6.addPlaneCollider(0, Vecteur3D(0, 0, -1));


	GameObject createCubeHolder;
	createCubeHolder.addComponent((LogicBehaviour)CreateCube(createCubeHolder.getEntity()));


	//Loop
	engine->loop();

	
	return 0;
}