//
// Created by jules on 07/09/2022.
//

#include "Vecteur3D.h"
using namespace std;

Vecteur3D::Vecteur3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{}

Vecteur3D::Vecteur3D(const Vecteur3D &vect) _x(vect.get_x()), _y(vect.get_y()), _z(vect.get_z())
{}

Vecteur3D::norm(){
    return sqrt(_x*_x+_y*_y+_z*_z);
}





