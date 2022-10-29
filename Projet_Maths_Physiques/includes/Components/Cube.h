#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"

/// <summary>
/// Classe repr�sentant un cube
/// </summary>
class Cube : public Object3D
{
	private:
		//Longueur d'une arr�te du cube
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
		/// <returns>La longueur d'un cot� du cube</returns>
		float getLength() const { return length_; }

};

#endif 
