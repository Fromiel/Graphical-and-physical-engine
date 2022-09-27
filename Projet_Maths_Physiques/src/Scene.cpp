#include "Scene.h"

Scene::Scene(Camera camera, Light light, std::vector<GameObject> gameObjects) : camera_(camera), light_(light), gameObjects_(gameObjects)
{

}

void Scene::applyForces(double frameRate)
{
	for (int i = 0; i < gameObjects_.size(); i++)
	{
		gameObjects_[i].applyForces(frameRate);
	}
}