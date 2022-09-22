//
// Created by jules on 07/09/2022.
//

#ifndef VECTEUR3D_H
#define VECTEUR3D_H

#include <iostream>
#include <cmath>

class Vecteur3D{

    private :
        double _x;
        double _y;
        double _z;

    public:

        Vecteur3D(double x=0, double y=0, double z=0);

        Vecteur3D(const Vecteur3D & vect);

        double get_x() const {return _x;}

        double get_y() const {return _y;}

        double get_z() const {return _z;}

        double norm();

        double norm_squared();

        Vecteur3D normalized();

        Vecteur3D scalar_multiplication(double scalar);

};

std::ostream & operator<<(std::ostream & out, const Vecteur3D & vect);

Vecteur3D operator+(const Vecteur3D &vect1, const Vecteur3D &vect2);

Vecteur3D operator-(const Vecteur3D &vect1, const Vecteur3D &vect2);

Vecteur3D operator*(const Vecteur3D &vect1, const Vecteur3D &vect2);

Vecteur3D operator*(const double d, const Vecteur3D& v);
Vecteur3D operator*(const Vecteur3D& v, const double d);

double scalar_product(const Vecteur3D &vect1, const Vecteur3D &vect2);

Vecteur3D vectorial_product(const Vecteur3D &vect1, const Vecteur3D &vect2);

#endif //VECTEUR3D_H
