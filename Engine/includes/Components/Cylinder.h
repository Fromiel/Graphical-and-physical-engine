#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object3D.h"

class Cylinder : public Object3D
{
	private:
		float radius_; //rayon du cylindre
		float height_; //hauteur du cylindre
		int sectorCount_;                        // # of slices
		int stackCount_;                         // # of stacks
		unsigned int baseIndex_;                 // starting index of base
		unsigned int topIndex_;                  // starting index of top

		std::vector<float> unitCircleVertices_;

		void buildUnitCircleVertices();

		void buildCylinder();

		std::vector<float> getSideNormals();

		std::vector<float> computeFaceNormal(float x1, float y1, float z1,  // v1
			float x2, float y2, float z2,  // v2
			float x3, float y3, float z3);  // v3





	public:
		/// <summary>
		/// Constructeur du cylindre calculant les points (vertices) et leur indice (indices)
		/// </summary>
		/// <param name="sectorCount"></param>
		Cylinder(unsigned int sectorCount = 36);


};

#endif 
