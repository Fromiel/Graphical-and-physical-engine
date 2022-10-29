
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


	//Register components
	coordinator->registerComponent<Transform>();
	coordinator->registerComponent<Object3D>();
	coordinator->registerComponent<Light>();
	coordinator->registerComponent<Camera>();
	coordinator->registerComponent<NoEntity>();
	coordinator->registerComponent<Particule>();
	coordinator->registerComponent<LogicBehaviour>();

	//initialisation des systèmes
	auto time = coordinator->registerSystem<Time>();
	auto render = coordinator->registerSystem<Render>();
	auto inputsManager = coordinator->registerSystem<InputsManager>();
	auto physics = coordinator->registerSystem<Physics>();
	auto logic = coordinator->registerSystem<Logic>();

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

	//set shader
	Shader shader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	render->setShader(&shader);

	//set les inputs
	inputsManager->setupKeyInputs(render->getWindow());
	KeyInput keyInput(std::vector<int>({ GLFW_KEY_ESCAPE, GLFW_KEY_S }));


	//initialisation des entités
	//Sphere
	Transform sphereTransform(Vecteur3D(0, 30, 0));
	Sphere sphere(1);
	Entity sphereEntity = coordinator->createEntity();
	Particule p(Vecteur3D(0, 30, 0), Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphereEntity, (Object3D)sphere);
	coordinator->addComponent(sphereEntity, sphereTransform);
	coordinator->addComponent(sphereEntity, p);

	//Cube fixe pour centre ressort
	Transform cubeTransform(Vecteur3D(0, 40, 0));
	Cube cube(0.5);
	Entity cubeEntity = coordinator->createEntity();
	coordinator->addComponent(cubeEntity, cubeTransform);
	coordinator->addComponent(cubeEntity, (Object3D)cube);


	//Sol en y = 0
	Transform solTransform(Vecteur3D(0, 0, 0), Vecteur3D(100,0.01,100));
	Cube sol(1);
	Entity solEntity = coordinator->createEntity();
	coordinator->addComponent(solEntity, solTransform);
	coordinator->addComponent(solEntity, (Object3D)sol);


	//camera
	Entity cameraEntity = coordinator->createEntity();
	Transform cameraTransform(Vecteur3D(0, 35, 20));
	coordinator->addComponent(cameraEntity, cameraTransform);
	Camera camera(cameraEntity, 0.1, 10000, 90);
	coordinator->addComponent(cameraEntity, camera);

	//light
	Transform lightTransform(Vecteur3D(0, 30, 10));
	Sphere sun(0.5);
	Light light(Vecteur3D(1,1,1));
	Entity lightEntity = coordinator->createEntity();
	coordinator->addComponent(lightEntity, lightTransform);
	coordinator->addComponent(lightEntity, light);
	coordinator->addComponent(lightEntity, (Object3D) sun);

	//Create random spheres
	Entity logicEntity = coordinator->createEntity();
	CreateSphere createRandomSpheres(logicEntity);
	coordinator->addComponent(logicEntity, (LogicBehaviour)createRandomSpheres);



	auto registreForce = ParticuleForceRegistry();
	ParticuleRessortPtFixe* ptr_forceRessort = new ParticuleRessortPtFixe(1, Vecteur3D(0, 40, 0), coordinator->getComponent<Particule>(sphereEntity), -10);
	ParticuleGravity* ptr_forceGravite = new ParticuleGravity(-9.81);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceRessort);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceGravite);

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