#ifndef SCENE_H
#define SCENE_H

/*#include "Components/Object3D.h"
#include "CompoCamera.h"
#include "Light.h"
#include "GameObject.h"


class Scene
{
	private:
		std::vector<GameObject> gameObjects_;
		Camera camera_;
		Light light_;

	public:
		/// <summary>
		/// Constructeur de la scene
		/// </summary>
		/// <param name="camera">Caméra de la scène</param>
		/// <param name="light">Lumière de la scène</param>
		/// <param name="gameObjects">Les objets de la scène</param>
		Scene(Camera camera = Camera(), Light light = Light(), std::vector<GameObject> gameObjects = std::vector<GameObject>());

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La caméra de la scène</returns>
		Camera getCamera() const { return camera_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La lumière de la scène</returns>
		Light getLight() const { return light_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Les objets de la scène</returns>
		std::vector<GameObject> getGameObjects() const { return gameObjects_; }

		
		void setGameObject(int index, GameObject object) { gameObjects_[index] = object; }

		/// <summary>
		/// Ajoute un GameObjectbjet à la scène­
		/// </summary>
		/// <param name="object">L'objet à ajouter</param>
		void addGameObject(const GameObject& object) { gameObjects_.push_back(object); }

		/// <summary>
		/// Applique les forces exercées sur les objets de la scène en fonction du frame rate
		/// </summary>
		/// <param name="frameRate"></param>
		void applyForces(double frameRate);


};
*/

#endif