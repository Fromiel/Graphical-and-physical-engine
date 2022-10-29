//#include "OpenGLManager.h"

#include <cstdio>
#include <ostream>
#include "CoreECS/Coordinator.h"
#include "Components.h"
#include "Systems.h"

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

	//initialisation des syst�mes
	auto time = coordinator->registerSystem<Time>();
	auto render = coordinator->registerSystem<Render>();
	auto inputsManager = coordinator->registerSystem<InputsManager>();
	auto physics = coordinator->registerSystem<Physics>();

	Signature noEntity;
	noEntity.set(coordinator->getComponentType<NoEntity>());

	Signature renderSignature;
	renderSignature.set(coordinator->getComponentType<Transform>());

	Signature physicsSignature;
	physicsSignature.set(coordinator->getComponentType<Transform>());
	physicsSignature.set(coordinator->getComponentType<Particule>());

	coordinator->setSystemSignature<Time>(noEntity);
	coordinator->setSystemSignature<InputsManager>(noEntity);
	coordinator->setSystemSignature<Render>(renderSignature);
	coordinator->setSystemSignature<Physics>(physicsSignature);

	//set shader
	Shader shader("./src/Shaders/shader.vert", "./src/Shaders/shader.frag");
	render->setShader(&shader);


	//initialisation des entit�s
	//Sphere
	Transform sphereTransform(Vecteur3D(0, 50, 0));
	Sphere sphere(1);
	Entity sphereEntity = coordinator->createEntity();
	Particule p(Vecteur3D(0, 50, 0), Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphereEntity, (Object3D)sphere);
	coordinator->addComponent(sphereEntity, sphereTransform);
	coordinator->addComponent(sphereEntity, p);

	//camera
	Entity cameraEntity = coordinator->createEntity();
	Transform cameraTransform(Vecteur3D(0, 0, 50));
	coordinator->addComponent(cameraEntity, cameraTransform);
	Camera camera(cameraEntity, 0.1, 10000, 90);
	coordinator->addComponent(cameraEntity, camera);

	//light
	Transform lightTransform(Vecteur3D(0, 0, 1000));
	Light light;
	Entity lightEntity = coordinator->createEntity();
	coordinator->addComponent(lightEntity, lightTransform);
	coordinator->addComponent(lightEntity, light);

	
	//set les inputs
	inputsManager->setWindow(render->getWindow());
	inputsManager->setInputCallBacks();


	while (!inputsManager->endGame()) //rajouter condition de fin
	{
		//update clock
		time->update();
		//Physical simulation
		physics->update(time->deltaTime());
		
		//Motion
		
		//render
		render->update(time->deltaTime());
		//process events
		inputsManager->pollEvents();


	}

	return 0;
}