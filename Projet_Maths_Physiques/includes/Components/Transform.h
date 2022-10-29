#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Maths/Vecteur3D.h"
#include "Maths/Matrix4D.h"

class Transform
{
	private:
		Vecteur3D position_;
		Vecteur3D rotation_;
		Vecteur3D scale_;

		Matrix4D modelMatrix_;

	public:

		/// <summary>
		/// Constructeur placant l'entité à la position mise en argument et mettant le scale au scale mis en argument et une rotation nulle (0,0,0)
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scaling"></param>
		Transform(Vecteur3D position = Vecteur3D(0, 0, 0), Vecteur3D scaling = Vecteur3D(1, 1, 1));

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La position de l'objet</returns>
		Vecteur3D getPosition() const { return position_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>L'aggrandissement de l'objet</returns>
		Vecteur3D getScaling() const { return scale_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La model matrix</returns>
		Matrix4D getModelMatrix() { return modelMatrix_; }

		/// <summary>
		/// Permet de changer la position de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="Position">nouvelle position</param>
		void setPosition(const Vecteur3D& position);

		/// <summary>
		/// Permet de changer l'aggrandissement de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="position">position nouvelle position</param>
		void setScaling(const Vecteur3D& scale);

		/// <summary>
		/// Bouge l'objet du vecteur mis en argument dans ses coordonnées (on modifie la modelMatrix)
		/// </summary>
		/// <param name="vect"></param>
		void move(const Vecteur3D& vect);

		/// <summary>
		/// Effectue la rotation de l'objet dans ses coordonnées (on modifie la modelMatrix)
		/// </summary>
		/// <param name="angle"></param>
		/// <param name="pivot"></param>
		void rotate(float angle, const Vecteur3D& pivot);

};


#endif