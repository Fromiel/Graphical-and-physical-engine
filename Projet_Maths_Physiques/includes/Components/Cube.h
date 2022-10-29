#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"

/// <summary>
/// Classe représentant un cube
/// </summary>
class Cube : public Object3D
{
	private:
		//Longueur d'une arrête du cube
		float length_;

	public:
		/// <summary>
		/// Constructeur de cube
		/// </summary>
		/// <param name="length_">longueur d'un cote du cube</param>
		/// <param name="position"></param>
		/// <param name="scale"></param>
		Cube(float length = 1.0f);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La longueur d'un coté du cube</returns>
		float getLength() const { return length_; }

};

#endif 
