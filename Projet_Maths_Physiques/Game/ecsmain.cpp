#include <cstdio>
#include <ostream>
#include "Components.h"
#include "Systems.h"
#include "ParticuleForceRegistry.h"
#include "Scripts/MoveCamera.h"
#include "Engine.h"
#include "GameObject.h"
#include "Scripts/InstantiateCylindre.h"
#include "Bounding/BVHNode.h"
#include "Bounding/BoundingSphere.h"

int main(void)
{
	Engine *engine = Engine::getInstance();

	//set shaders
	Shader materialShader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	Shader lightShader("./src/Shaders/lightShader.vert", "./src/Shaders/lightShader.frag");

	Material sMaterial(materialShader, Vecteur3D(0.8f, 0.5f, 0.2f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));

	//---------TODO--------------------
	//set les inputs
	KeyInput keyInput(std::vector<int>({ GLFW_KEY_ESCAPE, GLFW_KEY_S, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_SPACE, GLFW_KEY_Q, GLFW_KEY_H , GLFW_KEY_G , GLFW_KEY_F , GLFW_KEY_T, GLFW_KEY_SPACE }));
	//-----------------------------------

	//initialisation des entites
	/*
	//Sphere
	GameObject sphere(Vecteur3D(-10, 40, 0));
	sphere.addComponent((Object3D)Sphere());
	sphere.addComponent(sMaterial);
	sphere.createParticule(Vecteur3D(0, 0, 0), 1, 1);
	*/
	//Sol en y = 0
	GameObject sol(Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(100.0f, 0.01f, 100.0f));
	sol.addComponent((Object3D)Cube());
	sol.addComponent(sMaterial);
	/*
	//Autre ressort
	GameObject sphere2(Vecteur3D(10, 40, 0));
	sphere2.addComponent((Object3D)Sphere());
	sphere2.createParticule(Vecteur3D(0, 0, 0), 1, 1);
	sphere2.addComponent(sMaterial);
	
	//Test Collisions
	GameObject sphere3(Vecteur3D(-20, 50, 0));
	sphere3.addComponent((Object3D)Sphere());
	sphere3.createParticule(Vecteur3D(0, 0, 0), 1, 1);
	sphere3.addComponent(sMaterial);

	GameObject sphere4(Vecteur3D(-20, 55, 0));
	sphere4.addComponent((Object3D)Sphere());
	sphere4.createParticule(Vecteur3D(0, 0, 0), 1, 1);
	sphere4.addComponent(sMaterial);
	*/
	//camera
	GameObject camera(Vecteur3D(0, 35, 20), Vecteur3D(1, 1, 1), Vecteur3D(0, 0, 0));
	camera.addComponent(Camera(camera.getEntity(), 0.1f, 10000.0f, 90.0f));
	camera.addComponent((LogicBehaviour) MoveCamera(camera.getEntity()));

	//light
	GameObject light(Vecteur3D(0, 30, -10));
	light.addComponent((Object3D)Sphere());
	light.addComponent(Light(Vecteur3D(0.8f, 0.8f, 0.8f)));
	light.addComponent(Material(lightShader));
	/*
	GameObject::addRessortPtPt(1, sphere, sphere2, 10);
	sphere3.addGravity(-1.0);

	//Cylindre
	GameObject cylindre(Vecteur3D(0, 10, -5), Vecteur3D(3, 3, 20), Vecteur3D(1.57, 0, 0));
	cylindre.addComponent((Object3D)Cylinder());
	cylindre.addComponent(sMaterial);

	sphere4.addCable(10, 0.5, sphere3);
	*/
	//Rigidbodies

	
	GameObject cube(Vecteur3D(-10, 30, 0), Vecteur3D(5,5,5));
	cube.addComponent((Object3D)Cube());
	cube.addComponent(sMaterial);
	cube.createRigidbody(1, 1, 1, CubeMesh);
	
	/*
	GameObject sphere_rb(Vecteur3D(0, 0, 0));
	sphere_rb.addComponent((Object3D)Sphere());
	sphere_rb.createRigidbody(0, 1, 0, SphereMesh);
	sphere_rb.addComponent(sMaterial);
	*/
	

	//Forces � tester pour quand on aura r�gl� le pb du GetComponent

	
	//Gravity
	GameObject cylindre(Vecteur3D(-10, 40, -5), Vecteur3D(3, 3, 20), Vecteur3D(1.57, 0, 0));
	cylindre.addComponent((Object3D)Cylinder());
	cylindre.addComponent(sMaterial);
	cylindre.createRigidbody(1,1,1,CylinderMesh);
	cylindre.addGravityRigidbody(-1.0);


	//Script instantiate camera
	GameObject instantiateCylindre;
	instantiateCylindre.addComponent((LogicBehaviour)InstantiateCylindre(instantiateCylindre.getEntity()));

	
	//Cube 2
	GameObject cube2(Vecteur3D(10, 30, 0), Vecteur3D(5,5,5));
	cube2.addComponent((Object3D)Cube());
	cube2.addComponent(sMaterial);
	cube2.createRigidbody(1, 1, 1, CubeMesh);

	//Ressort
	Vecteur3D center(0, 0, 0);
	Vecteur3D kessoku(0, 2.5, 0);
	cube2.addRessortPtPtRigidbody(center, kessoku, 0.5, cube, cube2, 25);

	//Bounding 
	BoundingSphere bSphere2(Vecteur3D(10, 30, 0), 5);
	Rigidbody* cube2_rb = cube2.getComponentPtr<Rigidbody>();
	BVHNode<BoundingSphere> node2(cube2_rb, nullptr, nullptr, bSphere2);

	BoundingSphere bSphere(Vecteur3D(-10, 30, 0), 5);
	Rigidbody* cube_rb = cube.getComponentPtr<Rigidbody>();
	BVHNode<BoundingSphere> node(cube_rb, nullptr, nullptr, bSphere);

	node.insert(cube2_rb, bSphere2);
	node.display();
	node.children[0]->display();
	node.children[1]->display();

	engine->loop();

	
	return 0;
}