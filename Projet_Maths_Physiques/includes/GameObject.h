#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object3D.h"
#include <optional>

class GameObject
{

	private:
		Object3D mesh_;
		std::optional<Particule> particule_;

	public:
		/// <summary>
		/// Constructeur du gameobject
		/// </summary>
		/// <param name="mesh"></param>
		/// <param name="particule"></param>
		GameObject(Object3D mesh, std::optional<Particule> particule = std::nullopt);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Les points représentant le gameobject</returns>
		Object3D getMesh() const { return mesh_; }

		/// <summary>
		/// Applique les forces exercées sur l'objet en fonction du frame rate
		/// </summary>
		/// <param name="frameRate"></param>
		void applyForces(double frameRate);






};

#endif 
