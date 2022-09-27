#include "GameObject.h"



GameObject::GameObject(Object3D mesh, std::optional<Particule> particule) : mesh_(mesh), particule_(particule)
{

}

void GameObject::applyForces(double frameRate)
{
	if (!particule_.has_value()) return;

	particule_.value().update(frameRate);
	mesh_.setPosition(particule_.value().getPos());
}