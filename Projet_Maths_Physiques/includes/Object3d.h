#ifndef OBJECT3D_H
#define OBJECT3D_H


#include <vector>
#include <ostream>
#include "Vertice.h"
#include "Matrix4D.h"
#include "Particule.h"

/// <summary>
/// Classe représentant un object en 3D 
/// </summary>
class Object3D
{
	protected:
		std::vector<Vertice> vertices_; //Points composant l'objet
		std::vector<unsigned int> indices_; //Indices dans lequel les afficher
		Vecteur3D position_; 
		Vecteur3D scaling_;
		Matrix4D modelMatrix_;

	public:

		/// <summary>
		/// Constructeur de Object3d ou l'on specifie une particule
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scaling"></param>
		Object3D(Vecteur3D position, Vecteur3D scaling);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>les points de l'objet</returns>
		std::vector<Vertice> getVertices() const { return vertices_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>les indices de l'objet</returns>
		std::vector<unsigned int> getIndices() const { return indices_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>la position de l'objet</returns>
		Vecteur3D getPosition() const { return position_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>l'aggrandissement de l'objet</returns>
		Vecteur3D getScaling() const { return scaling_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>la model matrix</returns>
		Matrix4D getModelMatrix() { return modelMatrix_; }


		/// <summary>
		/// Permet de changer la position de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="position">nouvelle position</param>
		void setPosition(const Vecteur3D &position);

		/// <summary>
		/// Permet de changer l'aggrandissement de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="position">position nouvelle position</param>
		void setScaling(const Vecteur3D &scale);

		/// <summary>
		/// Bouge l'objet du vecteur mis en argument dans ses coordonnées (on modifie la modelMatrix)
		/// </summary>
		/// <param name="vect"></param>
		void move(const Vecteur3D &vect);

		/// <summary>
		/// Effectue la rotation de l'objet dans ses coordonnées (on modifie la modelMatrix)
		/// </summary>
		/// <param name="angle"></param>
		/// <param name="pivot"></param>
		void rotate(float angle, const Vecteur3D &pivot);

		


};



#endif