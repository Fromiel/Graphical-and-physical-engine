#include "TestsMatrix3D.h"

bool TestsMatrix3D::addition() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}) + Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix3D expected = Matrix3D({2, 4, 6, 8, 10, 12, 14, 16, 18});
    return result == expected;
}

bool TestsMatrix3D::substraction() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}) - Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix3D expected = Matrix3D({0, 0, 0, 0, 0, 0, 0, 0,0});
    return result == expected;
}

bool TestsMatrix3D::multiplicationScalar() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}) * 2;
    Matrix3D expected = Matrix3D({2, 4, 6, 8, 10, 12, 14, 16, 18});
    return result == expected;
}

bool TestsMatrix3D::multiplicationMatrix() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}) * Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix3D expected = Matrix3D({30, 36, 42, 66, 81, 96, 102, 126, 150});
    return result == expected;
}

bool TestsMatrix3D::determinant() {
    double result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}).determinant();
    double expected = 0;
    return result == expected;
}

bool TestsMatrix3D::transpose() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}).transpose();
    Matrix3D expected = Matrix3D({1, 4, 7, 2, 5, 8, 3, 6, 9});
    return result == expected;
}

bool TestsMatrix3D::adjugate() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 9}).adjugate();
    Matrix3D expected = Matrix3D({-3, 6, -3, 6, -12, 6, -3, 6, -3});
    return result == expected;
}

bool TestsMatrix3D::invert() {
    Matrix3D result = Matrix3D({1, 2, 3, 4, 5, 6, 7, 8, 8}).invert();
    Matrix3D expected = Matrix3D({(double)-8/3, (double)8/3, -1, (double)10/3, (double)-13/3, 2, -1, 2, -1});
    return result == expected;
}

bool TestsMatrix3D::identity() {
    Matrix3D result = Matrix3D::identity();
    Matrix3D expected = Matrix3D({1, 0, 0, 0, 1, 0, 0, 0, 1});
    return result == expected;
}
