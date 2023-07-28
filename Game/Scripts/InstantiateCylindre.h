#include <stdlib.h>  
#include <stdio.h> 
#include <time.h>  
#include "Components.h"
#include "Systems/KeyInput.h"
#include "GameObject.h"

void StartI(Entity entity)
{

}

void UpdateI(float dt, Entity entity)
{
	Coordinator* coordinator = Coordinator::getInstance();
	KeyInput* keyInput = KeyInput::_instances[0];

	if (keyInput->getIsKeyDown(GLFW_KEY_F))
	{
		Shader materialShader("./Shaders/shader.vert", "./Shaders/shader.frag");

		Material sMaterial(materialShader, Vector3D(0.3f, 0.8f, 0.2f), Vector3D(1.0f, 0.5f, 0.31f), Vector3D(0.5f, 0.5f, 0.5f));

		GameObject cylindre(Vector3D(-10, 40, -5), Vector3D(3, 3, 20), Vector3D(1.57, 0, 0));
		cylindre.addComponent((Object3D)Cylinder());
		cylindre.addComponent(sMaterial);
		cylindre.createRigidbody(1, 1, 1, CylinderMesh);
		cylindre.addGravityRigidbody(-1.0);

	}
}

class InstantiateCylindre : public LogicBehaviour
{
private:

public:
	InstantiateCylindre(Entity entity) : LogicBehaviour(entity)
	{
		update_ = [this](float dt) {UpdateI(dt, entity_); };
		start_ = [this]() {StartI(entity_); };
	}
};