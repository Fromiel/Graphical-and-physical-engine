#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Maths/Vector3D.h"
#include "Maths/Matrix34.h"
#include "Maths/Quaternion.h"

/// <summary>
/// Classe g�rant les valeurs de l'objet dans le monde en 3d (position, orientation, scale)
/// </summary>
class Transform
{
	private:
		Vector3D position_;
		Vector3D scale_;
		Quaternion orientation_;

		Matrix34 modelMatrix_;
		Matrix34 toWorldMatrix_;

		//booleens permettant de recalculer les matrices seulement quand cela est necessaire (optimisation)
		bool modelChanged_;
		bool worldChanged_;

		/// <summary>
		/// Method pour recalculer la modelMatrix � partir de la position, de l'orientation et du scale du transform
		/// </summary>
		void computeModelMatrix();

		/// <summary>
		/// Method pour recalculer la modelMatrix � partir de la position, de l'orientation et du scale du transform
		/// </summary>
		void computeWorldMatrix();

	public:

		/// <summary>
		/// Constructeur placant l'entit� � la position mise en argument et mettant le scale au scale mis en argument et une orientation au quaternion pass� en argument
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scaling"></param>
		/// <param name="rotation"></param>
		Transform(Vector3D position = Vector3D(0, 0, 0), Vector3D scaling = Vector3D(1, 1, 1), Quaternion orientation = Quaternion());

		/// <summary>
		/// Constructeur placant l'entit� � la position mise en argument et mettant le scale au scale mis en argument et une rotation au vecteur3d pass� en argument
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scaling"></param>
		/// <param name="orientation"></param>
		Transform(Vector3D position, Vector3D scaling, Vector3D orientation);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La position de l'objet</returns>
		Vector3D getPosition() const { return position_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>L'aggrandissement de l'objet</returns>
		Vector3D getScaling() const { return scale_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>L'orientation de l'objet</returns>
		Quaternion getOrientation() const { return orientation_; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La model matrix</returns>
		Matrix34 getModelMatrix();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La matrice de changement de coordonn�es vers les coordonn�es du monde</returns>
		Matrix34 getWorldMatrix();


		/// <summary>
		/// Permet de changer la position de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="Position">nouvelle position</param>
		void setPosition(const Vector3D& position);

		/// <summary>
		/// Permet de changer l'aggrandissement de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="position">position nouvelle position</param>
		void setScaling(const Vector3D& scale);

		/// <summary>
		/// Permet de changer l'orientation de l'objet (on modifie la modelMatrix)
		/// </summary>
		/// <param name="orientation"></param>
		void setOrientation(const Quaternion& orientation);

		/// <summary>
		/// Bouge l'objet du vecteur mis en argument dans ses coordonn�es (on modifie la modelMatrix)
		/// </summary>
		/// <param name="vect"></param>
		void move(const Vector3D& vect);

		/// <summary>
		/// Effectue la rotation de l'objet dans ses coordonn�es (on modifie la modelMatrix)
		/// </summary>
		/// <param name="angle"></param>
		/// <param name="pivot"></param>
		void rotate(float angle, const Vector3D& pivot);

};


#endif