#ifndef PHYSICPARTICLE_H
#define PHYSICPARTICLE_H

#include "CoreECS/Coordinator.h"
#include "ParticuleForceRegistry.h"
#include "Collisions/ParticuleContact.h"
#include "Collisions/ParticuleContactResolver.h"
#include "Collisions/Liens/ParticuleCable.h"
#include "Collisions/Liens/ParticuleRod.h"

/// <summary>
/// Système gérant la physique des particules
/// </summary>
class PhysicParticle : public System
{
	private:
		ParticuleForceRegistry forceRegistry_; //Pour les forces

		//Pour les collisions
		ParticuleContact* particleContact_;
		ParticuleContactResolver contactResolver_;
		std::vector<ParticuleContact*> allContactsInScene_;
		std::vector<ParticuleCable> cables_;
		std::vector<ParticuleRod> rods_;


	public:
		/// <summary>
		/// Constructeur de physic particle qui va initialiser le forceRegistry de particule
		/// </summary>
		PhysicParticle();

		/// <summary>
		/// Met à jour la physique de tous 
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

		/// <summary>
		/// Ajoute une force au forceRegistry
		/// </summary>
		/// <returns></returns>
		void addForce(Particule* p, ParticuleForceGenerator *pfg) { forceRegistry_.add(p, pfg); }

		/// <summary>
		/// Ajoute un cable à cables
		/// </summary>
		/// <returns></returns>
		void addCables(ParticuleCable& pc) { cables_.push_back(pc); }

		/// <summary>
		/// Ajoute un rod à rods
		/// </summary>
		/// <returns></returns>
		void addRods(ParticuleRod& pr) { rods_.push_back(pr); }

};


#endif