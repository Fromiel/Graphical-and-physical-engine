
#include <cstdio>
#include <ostream>
#include "CoreECS/Coordinator.h"
#include "Components.h"
#include "Systems.h"
#include "ParticuleForceRegistry.h"
#include "Forces/ParticuleRessortPtFixe.h"
#include "Forces/ParticuleGravity.h"
#include "Forces/ParticuleRessortPtPt.h"
#include "Forces/ParticuleBungee.h"
#include "Scripts/MoveCamera.h"
#include "Collisions/ParticuleContactResolver.h"
#include "Collisions/Liens/ParticuleCable.h"
#include "Collisions/Liens/ParticuleRod.h"
#include "Scripts/Blob.h"
#include "Scripts/BlobRod.h"

struct NoEntity {};

int main(void)
{
	Coordinator* coordinator = Coordinator::getInstance();

	//initialisation des syst�mes
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


	//Ajoute les signatures des syst�mes
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
	KeyInput keyInput(std::vector<int>({ GLFW_KEY_ESCAPE, GLFW_KEY_S, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_SPACE, GLFW_KEY_Q, GLFW_KEY_H , GLFW_KEY_G , GLFW_KEY_F , GLFW_KEY_T }));


	//initialisation des entit�s
	//Sphere
	Transform sphereTransform(Vecteur3D(-10, 40	, 0));
	Sphere sphere;
	Entity sphereEntity = coordinator->createEntity();
	Material sphereMat(materialShader, Vecteur3D(0.8f, 0.5f, 0.2f), Vecteur3D(1.0f, 0.5f, 0.31f), Vecteur3D(0.5f, 0.5f, 0.5f));
	coordinator->addComponent(sphereEntity, (Object3D)sphere);
	coordinator->addComponent(sphereEntity, sphereTransform);
	Particule p(sphereEntity, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphereEntity, p);
	coordinator->addComponent(sphereEntity, sphereMat);

	//Cube fixe pour centre ressort
	/*Transform cubeTransform(Vecteur3D(0, 50, 0));
	Cube cube;
	Entity cubeEntity = coordinator->createEntity();
	coordinator->addComponent(cubeEntity, cubeTransform);
	coordinator->addComponent(cubeEntity, (Object3D)cube);
	coordinator->addComponent(cubeEntity, sphereMat);*/


	//Sol en y = 0
	Transform solTransform(Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(100.0f, 0.01f, 100.0f));
	Cube sol;
	Entity solEntity = coordinator->createEntity();
	coordinator->addComponent(solEntity, solTransform);
	coordinator->addComponent(solEntity, (Object3D)sol);
	coordinator->addComponent(solEntity, sphereMat);

	//Autre ressort
	Transform sphere2Transform(Vecteur3D(10, 40, 0));
	Sphere s2;
	//Cube c2(0.5);
	Entity sphere2Entity = coordinator->createEntity();
	//Entity cube2Entity = coordinator->createEntity();

	coordinator->addComponent(sphere2Entity, sphere2Transform);
	Particule p2(sphere2Entity, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphere2Entity, p2);
	coordinator->addComponent(sphere2Entity, (Object3D)s2);
	coordinator->addComponent(sphere2Entity, sphereMat);

	//Transform c2t(Vecteur3D(-10, 50, 0));
	//coordinator->addComponent(cube2Entity, c2t);
	//coordinator->addComponent(cube2Entity, (Object3D)c2);
	//coordinator->addComponent(cube2Entity, sphereMat);*/

	//Test Collisions
	Transform sphere3Transform(Vecteur3D(-20, 50, 0));
	Sphere s3;
	Entity sphere3Entity = coordinator->createEntity();
	coordinator->addComponent(sphere3Entity, sphere3Transform);
	Particule p3(sphere3Entity, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphere3Entity, p3);
	coordinator->addComponent(sphere3Entity, (Object3D)s3);
	coordinator->addComponent(sphere3Entity, sphereMat);

	Transform sphere4Transform(Vecteur3D(-20, 55, 0));
	Sphere s4;
	Entity sphere4Entity = coordinator->createEntity();
	coordinator->addComponent(sphere4Entity, sphere4Transform);
	Particule p4(sphere4Entity, Vecteur3D(0, 0, 0), 1, 1);
	coordinator->addComponent(sphere4Entity, p4);
	coordinator->addComponent(sphere4Entity, (Object3D)s4);
	coordinator->addComponent(sphere4Entity, sphereMat);


	ParticuleContactResolver contact_resolver;
	ParticuleContact* pc2 = new ParticuleContact();
	//ParticuleRod pr(10, coordinator->getComponentPtr<Particule>(sphere4Entity), coordinator->getComponentPtr<Particule>(sphere3Entity));
	ParticuleCable pcable(10,0.5, coordinator->getComponentPtr<Particule>(sphere4Entity), coordinator->getComponentPtr<Particule>(sphere3Entity));
	std::vector<ParticuleContact*> all_contacts_in_scene;



	//camera
	Entity cameraEntity = coordinator->createEntity();
	Transform cameraTransform(Vecteur3D(0, 35, 20));
	coordinator->addComponent(cameraEntity, cameraTransform);
	Camera camera(cameraEntity, 0.1f, 10000.0f, 90.0f);
	coordinator->addComponent(cameraEntity, camera);
	MoveCamera moveCamera(cameraEntity);
	coordinator->addComponent(cameraEntity, (LogicBehaviour)moveCamera);

	//light
	Transform lightTransform(Vecteur3D(0, 30, -10));
	Sphere sun;
	Light light(Vecteur3D(0.8f, 0.8f, 0.8f));
	Entity lightEntity = coordinator->createEntity();
	coordinator->addComponent(lightEntity, lightTransform);
	coordinator->addComponent(lightEntity, light);
	coordinator->addComponent(lightEntity, (Object3D) sun);
	coordinator->addComponent(lightEntity, Material(lightShader));



	//Create blobs
	ParticuleContact* pc = new ParticuleContact();
	ParticuleForceRegistry* registry = new ParticuleForceRegistry();

	Entity blob = coordinator->createEntity();
	Blob blobScript(blob, registry, pc);
	coordinator->addComponent(blob, (LogicBehaviour)blobScript);

	Entity blobRod = coordinator->createEntity();
	BlobRod blobRodScript(blob, registry, pc);
	coordinator->addComponent(blobRod, (LogicBehaviour)blobRodScript);



	auto registreForce = ParticuleForceRegistry();
	ParticuleGravity* ptr_forceGravite = new ParticuleGravity(-9.81f);
	ParticuleGravity* ptr_lowGravity = new ParticuleGravity(-1.0);
	//ParticuleBungee* ptr_bungee = new ParticuleBungee(5, Vecteur3D(0, 50, 0), coordinator->getComponentPtr<Particule>(sphereEntity), -10);
	ParticuleRessortPtPt* ptr_forceRessort2 = new ParticuleRessortPtPt(1, coordinator->getComponentPtr<Particule>(sphereEntity), coordinator->getComponentPtr<Particule>(sphere2Entity), 10);
	ParticuleRessortPtPt* ptr_forceRessort3 = new ParticuleRessortPtPt(1, coordinator->getComponentPtr<Particule>(sphere2Entity), coordinator->getComponentPtr<Particule>(sphereEntity), 10);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceRessort2);
	registreForce.add(coordinator->getComponentPtr<Particule>(sphere2Entity), ptr_forceRessort3);

	//ParticuleRessortPtFixe* ptr_forceRessort = new ParticuleRessortPtFixe(1, Vecteur3D(0, 40, 0), coordinator->getComponent<Particule>(sphereEntity), -10);
	//registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceRessort);
	//registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_forceGravite);
	//registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_bungee);
	//registreForce.add(coordinator->getComponentPtr<Particule>(sphere2Entity), ptr_forceGravite);
	//ParticuleRessortPtFixe* ptr_ressort = new ParticuleRessortPtFixe(5, coordinator->getComponent<Transform>(cubeEntity).getPosition(), coordinator->getComponent<Particule>(sphereEntity), 15);
	//registreForce.add(coordinator->getComponentPtr<Particule>(sphere2Entity), ptr_forceGravite);
	//registreForce.add(coordinator->getComponentPtr<Particule>(sphereEntity), ptr_ressort);

	//SPhere 3
	registreForce.add(coordinator->getComponentPtr<Particule>(sphere3Entity), ptr_lowGravity);


	//Start des LogicBehaviours
	logic->start();


	//Boucle de jeu
	while (!inputsManager->endGame())
	{
		all_contacts_in_scene.clear();
		//update clock
		time->update();
		//Logic
		logic->update(time->deltaTime());
		//Physical simulation
		registreForce.updateForces(time->deltaTime());
		registry->updateForces(time->deltaTime());
		physics->update(time->deltaTime());

		
		//Pour le test, on d�coupera mieux par la suite
		pc2->clear();
		pcable.addContact(pc2, 0);
		all_contacts_in_scene.push_back(pc2);

		contact_resolver.SetIterations(1 + static_cast<unsigned int>(all_contacts_in_scene.size()) * 2);
		contact_resolver.resolveContacts(all_contacts_in_scene, 1, time->deltaTime());

		//render
		render->update(time->deltaTime());
		//process events
		inputsManager->pollEvents();


	}

	
	return 0;
}