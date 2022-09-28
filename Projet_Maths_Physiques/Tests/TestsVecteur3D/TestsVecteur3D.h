#ifndef TESTS_VECTEUR3D_H
#define TESTS_VECTEUR3D_H

#include "../../includes/Vecteur3D.h"

class TestsVecteur3D {
    public:
        static bool norm();
        static bool norm_squared();
        static bool normalized();
        static bool scalar_multiplication();
        static bool addition();
        static bool substraction();
        static bool scalar_product();
        static bool vectorial_product();
};

#endif
