#ifndef TESTS_MATRIX3D_H
#define TESTS_MATRIX3D_H

#include "../../includes/Matrix3D.h"

class TestsMatrix3D {
    public:
        static bool addition();
        static bool substraction();
        static bool multiplicationScalar();
        static bool multiplicationMatrix();
        static bool determinant();
        static bool transpose();
        static bool adjugate();
        static bool invert();
        static bool identity();
};

#endif
