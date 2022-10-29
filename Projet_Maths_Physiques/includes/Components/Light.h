#ifndef LIGHT_H
#define LIGHT_H

#include "Maths/Vecteur3D.h"
#include "Camera.h"
/// <summary>
/// Classe repr�sentant la lumiere de la sc�ne
/// </summary>
class Light 
{
	private:
		//Couleur de la lumi�re
		Vecteur3D color_;

	public:
		/// <summary>
		/// Constructeur de Light
		/// </summary>
		/// <param name="position_">Position de la lumiere</param>
		Light(Vecteur3D color = Vecteur3D(1, 1, 1));

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La couleur de la lumi�re</returns>
		Vecteur3D getColor() const { return color_; }

		/// <summary>
		/// Permet de changer la couleur de la lumi�re
		/// </summary>
		/// <param name="color">Nouvelle couleur</param>
		void setColor(const Vecteur3D& color, bool IsBetweenOAnd1 = true);

};


#endif 
