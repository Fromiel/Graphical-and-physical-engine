
#include <cstdio>
#include <ostream>
#include "CoreECS/Coordinator.h"
#include "Components.h"
#include "Systems.h"
#include "ParticuleForceRegistry.h"
#include "Forces/ParticuleRessortPtFixe.h"
#include "Forces/ParticuleGravity.h"
#include "Scripts/CreateSphere.h"

struct NoEntity {};

int main(void)
{
	Coordinator* coordinator = Coordinator::getInstance();

	//initialisation des systèmes
	auto time = coordinator->registerSystem<Time>();
	auto render = coordinator->registerSystem<Render>();
	auto inputsManager = coordinator->registerSystem<InputsManager>();
	auto physics = coordinator->registerSystem<Physics>();
	auto logic = coordinator->registerSystem<Logic>();

	//Register components
	coordinator->registerComponent<Transform>();
	coordinator->registerComponent<Object3D>();
	coordinator->registerComponent<Light>();
	coordinator->registerComponent<Camera>();
	coordinator->registerComponent<NoEntity>();
	coordinator->registerComponent<Particule>();
	coordinator->registerComponent<LogicBehaviour>();
	coordinator->registerComponent<Material>();


	//Ajoute les signatures des systèmes
	Signature noEntity;
	noEntity.set(coordinator->getComponentType<NoEntity>());

	Signature renderSignature;
	renderSignature.set(coordinator->getComponentType<Transform>());

	Signature physicsSignature;
	physicsSignature.set(coordinator->getComponentType<Transform>());
	physicsSignature.set(coordinator->getComponentType<Particule>());

	Signature logicSignature;
	logicSignature.set(coordinator->getComponentType<LogicBehaviour>());

	coordinator->setSystemSignature<Time>(noEntity);
	coordinator->setSystemSignature<InputsManager>(noEntity);
	coordinator->setSystemSignature<Render>(renderSignature);
	coordinator->setSystemSignature<Physics>(physicsSignature);
	coordinator->setSystemSignature<Logic>(logicSignature);

	//set shaders
	Shader materialShader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	Shader lightShader("./src/Shaders/lightShader.vert", "./src/Shaders/lightShader.frag");


	//set les inputs
	inputsManager->setupKeyInputs(render->getWindow());
	KeyInput keyInput(std::vector<int>({ GLFW_KEY_ESCAPE, GLFW_KEY_S }));


	//initialisation des entités
	//Sphere
	Transform sphereTransform(Vecteur3D(0, 30, 0));
	Sphere sphere(1);
	Entity sphereEntity = coordinator->createEntity();
	Material sphereMat(materialShader, Vecteur3D(0.8, 0.5, 0.2), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));
	coordinator->addComponent(sphereEntity, (Object3D)sphere);
	coordinator->addComponent(sphereEntity, sphereTransform);
	Particule p(sphereEntity, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphereEntity, p);
	coordinator->addComponent(sphereEntity, sphereMat);

	//Cube fixe pour centre ressort
	Transform cubeTransform(Vecteur3D(0, 40, 0));
	Cube cube(0.5);
	Entity cubeEntity = coordinator->createEntity();
	coordinator->addComponent(cubeEntity, cubeTransform);
	coordinator->addComponent(cubeEntity, (Object3D)cube);
	coordinator->addComponent(cubeEntity, sphereMat);


	//Sol en y = 0
	Transform solTransform(Vecteur3D(0, 0, 0), Vecteur3D(100,0.01,100));
	Cube sol(1);
	Entity solEntity = coordinator->createEntity();
	coordinator->addComponent(solEntity, solTransform);
	coordinator->addComponent(solEntity, (Object3D)sol);
	coordinator->addComponent(solEntity, sphereMat);

	//Autre ressort
	Transform sphere2Transform(Vecteur3D(0, 30, 0));
	Sphere s2;
	Cube c2(0.5);
	Entity sphere2Entity = coordinator->createEntity();
	Entity cube2Entity = coordinator->createEntity();

	coordinator->addComponent(sphere2Entity, sphere2Transform);
	Particule p2(sphere2Entity, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphere2Entity, p2);
	coordinator->addComponent(sphere2Entity, (Object3D)s2);
	coordinator->addComponent(sphere2Entity, sphereMat);

	Transform c2t(sphere2Transform);
	coordinator->addComponent(cube2Entity, c2t);
	coordinator->addComponent(cube2Entity, (Object3D)c2);
	coordinator->addComponent(cube2Entity, sphereMat);

	//camera
	Entity cameraEntity = coordinator->createEntity();
	Transform cameraTransform(Vecteur3D(0, 35, 20));
	coordinator->addComponent(cameraEntity, cameraTransform);
	Camera camera(cameraEntity, 0.1, 10000, 90);
	coordinator->addComponent(cameraEntity, camera);

	//light
	Transform lightTransform(Vecteur3D(0, 30, 10));
	Sphere sun(0.5);
	Light light(Vecteur3D(0.8,0.8,0.8));
	Entity lightEntity = coordinator->createEntity();
	coordinator->addComponent(lightEntity, lightTransform);
	coordinator->addComponent(lightEntity, light);
	coordinator->addComponent(lightEntity, (Object3D) sun);
	coordinator->addComponent(lightEntity, Material(lightShader));

	//Create random spheres
	Entity logicEntity = coordinator->createEntity();
	CreateSphere createRandomSpheres(logicEntity);
	coordinator->addComponent(logicEntity, (LogicBehaviour)createRandomSpheres);



	auto registreForce = ParticuleForceRegistry();
	ParticuleRessortPtFixe* ptr_forceRessort = new ParticuleRessortPtFixe(1, Vecteur3D(0, 40, 0), coordinator->getComponent<Particule>(sphereEntity), -10);
	ParticuleGravity* ptr_forceGravite = new ParticuleGravity(-9.81);
	ParticuleRessortPtFixe* ptr_forceRessort2 = new ParticuleRessortPtFixe(1, Vecteur3D(0, 40, 0), coordinator->getComponent<Particule>(sphere2Entity), 20);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceRessort);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceGravite);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphere2Entity), ptr_forceRessort2);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphere2Entity), ptr_forceGravite);

	//Start des LogicBehaviours
	logic->start();

	while (!inputsManager->endGame()) //rajouter condition de fin
	{
		//update clock
		time->update();
		//Logic
		logic->update(time->deltaTime());
		//Physical simulation
		registreForce.updateForces(time->deltaTime());
		physics->update(time->deltaTime());
		
		//Motion
		
		//render
		render->update(time->deltaTime());
		//process events
		inputsManager->pollEvents();


	}

	
	return 0;
}