#ifndef LIGHT_H
#define LIGHT_H

#include "Maths/Vector3D.h"
#include "Camera.h"
/// <summary>
/// Classe représentant la lumiere de la scène
/// </summary>
class Light 
{
	private:
		//Couleur de la lumière
		Vector3D color_;
		//Specular de la lumiere
		Vector3D specular_;

	public:
		/// <summary>
		/// Constructeur de Light
		/// </summary>
		/// <param name="position_">Position de la lumiere</param>
		Light(Vector3D color = Vector3D(1, 1, 1), Vector3D specular = Vector3D(1, 1, 1));

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La couleur de la lumière</returns>
		Vector3D getColor() const { return color_; }

		/// <summary>
		/// Permet de changer la couleur de la lumière
		/// </summary>
		/// <param name="color">Nouvelle couleur</param>
		void setColor(const Vector3D& color, bool IsBetweenOAnd1 = true);

		/// <summary>
		/// Getter de specular
		/// </summary>
		/// <returns></returns>
		Vector3D getSpecular() const { return specular_; }

		/// <summary>
		/// Setter de specular (les valeurs doivent etre entre 0 et 1)
		/// </summary>
		/// <param name="specular"></param>
		void setSpecular(const Vector3D& specular) { specular_ = specular; };

};


#endif 
