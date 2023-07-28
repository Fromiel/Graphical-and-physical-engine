#ifndef COLLIDER_H
#define COLLIDER_H

#include "Components/Rigidbody.h"
#include "CollisionData.h"


enum typeColliderEnum
{
	PlanC,
	SphereC,
	BoxC
};
/// <summary>
/// Composant de base représentant un collider pour détecter les collisions entre deux objets
/// </summary>
class Collider
{
	protected:
		Entity entity_;
		Rigidbody *rigidbody_;
		Matrix34 offset_;
		typeColliderEnum type_;

	public:
		/// <summary>
		/// Constructeur non valué
		/// </summary>
		Collider() {}

		/// <summary>
		/// Constructeur de collider
		/// </summary>
		/// <param name="entity"></param>
		/// <param name="position"></param>
		/// <param name="orientation"></param>
		/// <param name="rigidbody"></param>
		Collider(Entity entity, Vector3D position = Vector3D(), Vector3D orientation = Vector3D(), Rigidbody* rigidbody = NULL);

		void onCollision(const CollisionData& data) const;

		Rigidbody* getRigidbody() { return rigidbody_; }

		Entity getEntity() const { return entity_; }

		Matrix34 getOffset() const { return offset_; }

		/// <summary>
		/// Retourne la matrice permettant de passer des coordonnées du collider vers le monde
		/// </summary>
		/// <returns></returns>
		Matrix34 getWorldPositionOrientation() const;

		/// <summary>
		/// Retourne la moitie de la taille d'un cote de la boite englobante
		/// </summary>
		/// <returns></returns>
		virtual float getMaxSize() const = 0;

		/// <summary>
		/// Retourne la position du centre du collider dans les coordonnees du monde
		/// </summary>
		/// <returns></returns>
		Vector3D getPosition() const;

		/// <summary>
		/// Retourne le type du collider (Sphere, box, plan, ...)
		/// </summary>
		/// <returns></returns>
		typeColliderEnum getType() const { return type_; }

};

#endif