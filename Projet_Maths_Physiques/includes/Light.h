#ifndef LIGHT_H
#define LIGHT_H

#include "Vecteur3D.h"

/// <summary>
/// Classe représentant la lumiere de la scène
/// </summary>
class Light 
{
	private:
		//Position de la lumiere
		Vecteur3D position_;
		//Couleur de la lumière
		Vecteur3D color_;

	public:
		/// <summary>
		/// Constructeur de Light
		/// </summary>
		/// <param name="position_">Position de la lumiere</param>
		Light(Vecteur3D position_ = Vecteur3D(), Vecteur3D color = Vecteur3D(1, 1, 1));

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La position de la lumiere</returns>
		Vecteur3D getPosition() const { return position_; }

		/// <summary>
		/// Permet de changer la position de la lumiere
		/// </summary>
		/// <param name="position">Nouvelle position de la lumiere</param>
		void setPosition(const Vecteur3D &position) { position_ = position; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La couleur de la lumière</returns>
		Vecteur3D getColor() const { return color_; }

		/// <summary>
		/// Permet de changer la couleur de la lumière
		/// </summary>
		/// <param name="color">Nouvelle couleur</param>
		void setColor(const Vecteur3D &color) { color_ = color; }

};


#endif 
