#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "CoreECS/Coordinator.h"
#include "Maths/Quaternion.h"
#include "Components/Particule.h"
#include "Components/Rigidbody.h"

class GameObject
{
	private:
		Coordinator* coordinator_;
		Entity entity_;

	public:
		/// <summary>
		/// Constructeur de gameobject prenant l'orientation du gameobject avec un quaternion
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scale"></param>
		/// <param name="orientation"></param>
		GameObject(Vector3D position = Vector3D(), Vector3D scale = Vector3D(1, 1, 1), Quaternion orientation = Quaternion());


		/// <summary>
		/// Constructeur de gameobject prenant l'orientation du gameobject avec un vecteur3d
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scale"></param>
		/// <param name="orientation"></param>
		GameObject(Vector3D position, Vector3D scale, Vector3D orientation);

		/// <summary>
		/// Detruit le gameobject
		/// </summary>
		void destroy() { coordinator_->destroyEntity(entity_); }

		/// <summary>
		/// Getter de entity
		/// </summary>
		/// <returns></returns>
		Entity getEntity() const { return entity_; }

		/// <summary>
		/// Ajoute un component T pour une entité donnée
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <param name="component"></param>
		template<typename T>
		void addComponent(T component){ coordinator_->addComponent(entity_, component); }

		/// <summary>
		/// Enlève un component T pour une entité donnée
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		template<typename T>
		void removeComponent(){ coordinator_->removeComponent<T>(entity_); }

		/// <summary>
		/// Retourne une référence vers un component T du gameobject
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<typename T>
		T& getComponent() { return coordinator_->getComponent<T>(entity_); }

		/// <summary>
		/// Retourne un pointeur vers un component T du gameobject
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <returns></returns>
		template<typename T>
		T* getComponentPtr() { return coordinator_->getComponentPtr<T>(entity_); }

		/// <summary>
		/// Permet de savoir si le gameobject possède un component de type T
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="entity"></param>
		/// <returns>True si le gameobject possède ce component, false sinon</returns>
		template<typename T>
		bool hasComponent() { return coordinator_->hasComponent<T>(entity_); }



		//Methodes pour ajouter des forces si le gameobject possede une particule

		/// <summary>
		/// Methode pour créer puis ajouter une particule comme composant du gameobject (si il y a deja une aprticule, on la remplace par la nouvelle)
		/// </summary>
		/// <param name="vel_initiale"></param>
		/// <param name="r"></param>
		/// <param name="m"></param>
		void createParticule(Vector3D vel_initiale, float r, float m);

		/// <summary>
		/// Methode pour savoir si le gameobject est une particule
		/// </summary>
		/// <returns>True si c'est une particule, false sinon</returns>
		bool hasParticule() { return coordinator_->hasComponent<Particule>(entity_); }

		/// <summary>
		/// Methode pour ajouter une force de gravite à la particule
		/// </summary>
		/// <param name="g"></param>
		void addGravity(float g);

		/// <summary>
		/// Methode pour ajouter une force bungee à la particule
		/// </summary>
		/// <param name="kElasticite"></param>
		/// <param name="attache"></param>
		/// <param name="l0"></param>
		void addBungee(float kElasticite, Vector3D attache, float l0);

		/// <summary>
		/// Methode pour ajouter une force de ressort avec un point fixe à la particule
		/// </summary>
		/// <param name="kElasticite"></param>
		/// <param name="attache"></param>
		/// <param name="l0"></param>
		void addRessortPtFixe(float kElasticite, Vector3D attache, float l0);

		/// <summary>
		/// Methode pour ajouter une force de ressort entre deux particules
		/// </summary>
		/// <param name="kElasticite"></param>
		/// <param name="p1"></param>
		/// <param name="p2"></param>
		/// <param name="l0"></param>
		static void addRessortPtPt(float kElasticite, GameObject& g1, GameObject& g2, float l0);

		/// <summary>
		/// Ajoute un cable à la particule du gameObject relié au gameObject en argument
		/// </summary>
		/// <param name="ml"></param>
		/// <param name="r"></param>
		/// <param name="g"></param>
		void addCable(float ml, float r, GameObject& g);

		/// <summary>
		/// Ajoute un rod à la particule du gameObject relié au gameObject en argument
		/// </summary>
		/// <param name="ml"></param>
		/// <param name="r"></param>
		/// <param name="g"></param>
		void addRod(float l, GameObject& g);


		// ------------------------------------------------------------------------------------//
		// ------- Methodes pour ajouter des forces si le gameobject possede un rigidbody -----//
		// ------------------------------------------------------------------------------------//

		/// <summary>
		/// Methode pour créer puis ajouter un rb comme composant du gameobject (si il y a deja un rb, on le remplace)
		/// </summary>
		/// <param name="vel_initiale"></param>
		/// <param name="r"></param>
		/// <param name="m"></param>
		void createRigidbody(float angularDamping, float invmasse, float linearDamping, ObjectTypeEnum type_objet, Vector3D initialSpeed = Vector3D(), Vector3D angularSpeed = Vector3D());

		/// <summary>
		/// Methode pour savoir si le gameobject est un rb
		/// </summary>
		/// <returns>True si c'est un rb, false sinon</returns>
		bool hasRigidbody() { return coordinator_->hasComponent<Rigidbody>(entity_); }

		/// <summary>
		/// Methode pour ajouter une force de gravite
		/// </summary>
		/// <param name="g"></param>
		void addGravityRigidbody(float g);

		/// <summary>
		/// Methode pour ajouter une force de ressort avec un point fixe
		/// </summary>
		/// <param name="kElasticite"></param>
		/// <param name="attache"></param>
		/// <param name="l0"></param>
		void addRessortPtPtRigidbody(const Vector3D& bodyAnchor, const Vector3D otherAnchor, float kElasticite, GameObject& g1, GameObject& g2, float l0);


		// ------------------------------------------------------------------------------------//
		// ------- Methodes pour ajouter des colliders au gameobject --------------------------//
		// ------------------------------------------------------------------------------------//


		/// <summary>
		/// Methode pour ajouter un sphere collider au gameobject
		/// </summary>
		/// <param name="radius">rayon du collider</param>
		/// <param name="position">Position par rapport au gameobject du centre du collider</param>
		void addSphereCollider(float radius, Vector3D position = Vector3D());

		/// <summary>
		/// Methode pour ajouter un planeCollider au gameobject
		/// </summary>
		/// <param name="offset"></param>
		/// <param name="normal"></param>
		/// <param name="position"></param>
		void addPlaneCollider(float halfSizeX = 1.0f, float halfSizeY = 1.0f);

		/// <summary>
		/// Methode pour ajouter un boxCollider au gameobject
		/// </summary>
		/// <param name="halfsize"></param>
		/// <param name="position"></param>
		void addBoxCollider(Vector3D halfsize = Vector3D(1, 1, 1), Vector3D position = Vector3D(), Vector3D orientation = Vector3D());
};



#endif
