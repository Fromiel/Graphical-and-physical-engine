#ifndef OBJECT3D_H
#define OBJECT3D_H


#include <vector>
#include <ostream>
#include "Vertice.h"


enum ObjectTypeEnum {SphereMesh, CubeMesh, CylinderMesh};

/// <summary>
/// Classe représentant les arêtes d'un objet en 3D 
/// </summary>
class Object3D
{
	protected:
		std::vector<Vertice> vertices_; //Points composant l'objet
		std::vector<unsigned int> indices_; //Indices dans lequel les afficher
		ObjectTypeEnum objectType_;//Type de l'objet (Sphere, cube, ...)

	public:

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
		/// <returns>Le type de l'objet</returns>
		ObjectTypeEnum getType() const { return objectType_; }


};



#endif