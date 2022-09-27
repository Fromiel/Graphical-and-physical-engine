#include "Cube.h"

Cube::Cube(float length, Vecteur3D position, Vecteur3D scale) : Object3D(position, scale), length_(length)
{
	float l = length / 2;
	vertices_ = std::vector<Vertice>(
		{
			{-l, -l, -l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5},
			{-l, l, -l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 },
			{l, l, -l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 },
			{l, -l, -l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 },
			{l, -l, l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 },
			{l, l, l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 },
			{-l, l, l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 },
			{-l, -l, l, 0.5, 0.5, 0.5, 0, 1, 0, 0.5, 0.5 }
		}
	);

	indices_ = std::vector<unsigned int>(
		{
			0, 1, 2,
			0, 2, 3,
			2, 5, 3,
			5, 3, 4,
			5, 6, 7,
			5, 7, 4,
			0, 1, 6,
			6, 7, 0,
			0, 3, 4,
			0, 4, 7,
			1, 2, 5,
			1, 5, 6
		}
	);
}