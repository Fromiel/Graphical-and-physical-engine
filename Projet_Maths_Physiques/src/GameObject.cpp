#include "GameObject.h"
#include "Forces/ParticuleBungee.h"
#include "Forces/ParticuleGravity.h"
#include "Forces/ParticuleRessortPtFixe.h"
#include "Forces/ParticuleRessortPtPt.h"
#include "Engine.h"

GameObject::GameObject(Vecteur3D position, Vecteur3D scale, Quaternion orientation) : coordinator_(Coordinator::getInstance()), entity_(coordinator_->createEntity())
{
	Transform transform(position, scale, orientation);
	coordinator_->addComponent(entity_, transform);
}


void GameObject::createParticule(Vecteur3D vel_initiale, float r, float m)
{ 
	if (hasParticule())
		removeComponent<Particule>();

	addComponent(Particule(entity_, vel_initiale, r, m));
}

void GameObject::addGravity(float g)
{
	if (!hasParticule()) return;

	ParticuleGravity* ptr_forceGravite = new ParticuleGravity(g);
	Engine::getInstance()->getPhysicalEngine()->addForce(coordinator_->getComponentPtr<Particule>(entity_), ptr_forceGravite);
}

void GameObject::addBungee(float kElasticite, Vecteur3D attache, float l0)
{
	if (!hasParticule()) return;

	auto particule = coordinator_->getComponentPtr<Particule>(entity_);
	ParticuleBungee* ptr_bungee = new ParticuleBungee(kElasticite, attache, particule, l0);
	Engine::getInstance()->getPhysicalEngine()->addForce(particule, ptr_bungee);
}

void GameObject::addRessortPtFixe(float kElasticite, Vecteur3D attache, float l0)
{
	if (!hasParticule()) return;

	auto particule = coordinator_->getComponentPtr<Particule>(entity_);
	ParticuleRessortPtFixe* ptr_forceRessort = new ParticuleRessortPtFixe(kElasticite, attache, *particule, l0);
	Engine::getInstance()->getPhysicalEngine()->addForce(particule, ptr_forceRessort);
}

void GameObject::addRessortPtPt(float kElasticite, GameObject& g1, GameObject& g2, float l0)
{
	if (!g1.hasParticule() || !g2.hasParticule()) return;

	auto particule1 = g1.coordinator_->getComponentPtr<Particule>(g1.entity_);
	auto particule2 = g1.coordinator_->getComponentPtr<Particule>(g2.entity_);
	ParticuleRessortPtPt* ptr_forceRessort1 = new ParticuleRessortPtPt(kElasticite, particule1, particule2, l0);
	ParticuleRessortPtPt* ptr_forceRessort2 = new ParticuleRessortPtPt(kElasticite, particule2, particule1, l0);
	Engine::getInstance()->getPhysicalEngine()->addForce(particule1, ptr_forceRessort1);
	Engine::getInstance()->getPhysicalEngine()->addForce(particule2, ptr_forceRessort2);
}

void GameObject::addCable(float ml, float r, GameObject& g)
{
	if (!hasParticule() || !g.hasParticule()) return;
	
	ParticuleCable pCable(ml, r, coordinator_->getComponentPtr<Particule>(entity_), coordinator_->getComponentPtr<Particule>(g.entity_));
	Engine::getInstance()->getPhysicalEngine()->addCable(pCable);
}


void GameObject::addRod(float l, GameObject& g)
{
	if (!hasParticule() || !g.hasParticule()) return;

	ParticuleRod pRod(l, coordinator_->getComponentPtr<Particule>(entity_), coordinator_->getComponentPtr<Particule>(g.entity_));
	Engine::getInstance()->getPhysicalEngine()->addRod(pRod);
}