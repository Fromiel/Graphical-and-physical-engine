#include "Forces/ParticuleRessortPtFixe.h"

ParticuleRessortPtFixe::ParticuleRessortPtFixe(float kElasticite, Vecteur3D attache, const Particule& particule, float l0) {
	_kElasticite = kElasticite;
	_attache = attache;
	_l0 = l0;
}

ParticuleRessortPtFixe::~ParticuleRessortPtFixe() {
	
}

void ParticuleRessortPtFixe::updateForce(Particule* particule, float duration) {
	std::cout << "On débute update force ressort" << std::endl;
	Vecteur3D direction = _attache - particule->getPos();
	std::cout << "Direction : " << direction << std::endl;
	direction = direction.normalized();
	std::cout << "Direction : " << direction << std::endl;
	float l = distance(particule->getPos(), _attache);
	std::cout << "Distance entre les deux particules : " << l << std::endl;
	std::cout << "Paramètre du add force : " << (-_kElasticite * (l - _l0)) * direction << std::endl;
	particule->addForce((-_kElasticite * (l - _l0))*direction);
	std::cout << "On a fini d'update force ressort" << std::endl;
};