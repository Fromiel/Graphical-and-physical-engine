#ifndef SPHERE_H
#define SPHERE_H
#define _USE_MATH_DEFINES

#include "Object3d.h"
#include <math.h>

/// <summary>
/// Classe représantant une sphère
/// </summary>
class Sphere : public Object3D
{
	private:
		float radius_; //rayon
		Vecteur3D center_; //centre
		unsigned int sectorCount_, stackCount_; //Subdivisions en longitudes (sectors) et latitudes (stacks)


	public:
		/// <summary>
		/// Constructeur de la sphère calculant les points (vertices) et leur indice (indices)
		/// </summary>
		/// <param name="radius"></param>
		/// <param name="center"></param>
		/// <param name="sectorCount"></param>
		/// <param name="stackCount"></param>
		Sphere(float radius, Vecteur3D center, unsigned int sectorCount, unsigned int stackCount);


};




#endif