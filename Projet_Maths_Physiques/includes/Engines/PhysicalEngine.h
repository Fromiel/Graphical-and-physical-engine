#ifndef	PHYSICALENGINE_H
#define PHYSICALENGINE_H

#include "CoreECS/Coordinator.h"
#include "Systems/PhysicParticle.h"
#include "Systems/PhysicRigidBody.h"

/// <summary>
/// Classe g�rant la physique du jeu (d�placer les objets en fonction des forces qui leur sont appliqu�es)
/// </summary>
class PhysicalEngine
{
	private:
		Coordinator* coordinator_; //Pointeur vers Coordinator pour gerer l'architecture ECS

		std::shared_ptr<PhysicParticle> physicParticleSystem_; //Pointeur vers le systeme de gestion de la physique des particules
		std::shared_ptr<PhysicRigidBody> physicRigidBodySystem_; //Pointeur vers le systeme de gestion de la physique des rigidBody

	public:
		/// <summary>
		/// Constructeur qui va initialiser le moteur physique
		/// </summary>
		PhysicalEngine();

		/// <summary>
		/// Methode appelee pour mettre � jour le moteur physique en fonction du temps qui s'est �coul� avec la derni�re frame
		/// </summary>
		/// <param name="dt">Temps qui s'est �coul� avec la derni�re frame</param>
		void update(float dt);

		/// <summary>
		/// Getter de physicParticleSystem
		/// </summary>
		/// <returns></returns>
		void addForce(Particule* p, ParticuleForceGenerator* pfg) { physicParticleSystem_->addForce(p, pfg); }

		/// <summary>
		/// Ajoute un cable
		/// </summary>
		/// <param name="pc"></param>
		void addCable(ParticuleCable& pc) { physicParticleSystem_->addCables(pc); }

		/// <summary>
		/// Ajoute un rod
		/// </summary>
		/// <param name="pr"></param>
		void addRod(ParticuleRod& pr) { physicParticleSystem_->addRods(pr); }
};

#endif