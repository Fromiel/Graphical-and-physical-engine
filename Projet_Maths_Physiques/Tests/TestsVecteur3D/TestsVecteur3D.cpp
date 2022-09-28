#include "TestsVecteur3D.h"

bool TestsVecteur3D::norm() {
    double result = Vecteur3D(1, 2, 3).norm();
    double expected = sqrt(14);
    return result == expected;
}

bool TestsVecteur3D::norm_squared() {
    double result = Vecteur3D(1, 2, 3).norm_squared();
    double expected = 14;
    return result == expected;
}

bool TestsVecteur3D::normalized() {
    Vecteur3D result = Vecteur3D(14, 7, 14).normalized();
    Vecteur3D expected = Vecteur3D(2./3., 1./3., 2./3.);

    bool testPass = true;

    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    return testPass;
}

bool TestsVecteur3D::scalar_multiplication() {
    Vecteur3D result = Vecteur3D(1, 2, 3).scalar_multiplication(2);
    Vecteur3D expected = Vecteur3D(2, 4, 6);

    bool testPass = true;

    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    return testPass;
}

bool TestsVecteur3D::addition() {
    Vecteur3D result = Vecteur3D(1, 2, 3) + Vecteur3D(1, 2, 3);
    Vecteur3D expected = Vecteur3D(2, 4, 6);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;
    
    return testPass;
}

bool TestsVecteur3D::substraction() {
    Vecteur3D result = Vecteur3D(1, 2, 3) - Vecteur3D(1, 2, 3);
    Vecteur3D expected = Vecteur3D(0, 0, 0);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    return testPass;
}

bool TestsVecteur3D::scalar_product() {
    double result = ::scalar_product(Vecteur3D(1, 2, 3), Vecteur3D(4, 5, 6));
    double expected = 32;
    return result == expected;
}

bool TestsVecteur3D::vectorial_product() {
    Vecteur3D result = ::vectorial_product(Vecteur3D(1, 2, 3), Vecteur3D(4, 5, 6));
    Vecteur3D expected = Vecteur3D(-3, 6, -3);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    return testPass;
}