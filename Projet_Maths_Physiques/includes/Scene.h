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
		/// <param name="camera">Cam�ra de la sc�ne</param>
		/// <param name="light">Lumi�re de la sc�ne</param>
		/// <param name="gameObjects">Les objets de la sc�ne</param>
		Scene(Camera camera = Camera(), Light light = Light(), std::vector<GameObject> gameObjects = std::vector<GameObject>());

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La cam�ra de la sc�ne</returns>
		Camera getCamera() const { return camera_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La lumi�re de la sc�ne</returns>
		Light getLight() const { return light_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Les objets de la sc�ne</returns>
		std::vector<GameObject> getGameObjects() const { return gameObjects_; }

		
		void setGameObject(int index, GameObject object) { gameObjects_[index] = object; }

		/// <summary>
		/// Ajoute un GameObjectbjet � la sc�ne�
		/// </summary>
		/// <param name="object">L'objet � ajouter</param>
		void addGameObject(const GameObject& object) { gameObjects_.push_back(object); }

		/// <summary>
		/// Applique les forces exerc�es sur les objets de la sc�ne en fonction du frame rate
		/// </summary>
		/// <param name="frameRate"></param>
		void applyForces(double frameRate);


};
*/

#endif