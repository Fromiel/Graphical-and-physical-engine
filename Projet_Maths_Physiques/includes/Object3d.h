#ifndef OBJECT3D_H
#define OBJECT3D_H


#include <vector>
#include <ostream>
#include "Vertice.h"
#include "Vecteur3D.h"

/// <summary>
/// Classe représentant un object en 3D 
/// </summary>
class Object3D
{
	protected:
		std::vector<Vertice> vertices_; //Points composant l'objet
		std::vector<unsigned int> indices_; //Indices dans lequel les afficher

	public:

		std::vector<Vertice> getVertices() const { return vertices_; }
		std::vector<unsigned int> getIndices() const { return indices_; }


};



#endif