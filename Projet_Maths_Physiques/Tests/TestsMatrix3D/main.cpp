#include <iostream>
#include "TestsMatrix3D.h"

int main(int argc, char **argv) {
    std::cout << "\nStarting tests for Matrix3D\n" << std::endl;

    std::cout << "Addition :                " << (TestsMatrix3D::addition()             ? "ok" : "fail") << std::endl;
    std::cout << "Substraction :            " << (TestsMatrix3D::substraction()         ? "ok" : "fail") << std::endl;
    std::cout << "MultiplicationScalar :    " << (TestsMatrix3D::multiplicationScalar() ? "ok" : "fail") << std::endl;
    std::cout << "MultiplicationMatrix :    " << (TestsMatrix3D::multiplicationMatrix() ? "ok" : "fail") << std::endl;
    std::cout << "Determinant :             " << (TestsMatrix3D::determinant()          ? "ok" : "fail") << std::endl;
    std::cout << "Transpose :               " << (TestsMatrix3D::transpose()            ? "ok" : "fail") << std::endl;
    std::cout << "Adjugate :                " << (TestsMatrix3D::adjugate()             ? "ok" : "fail") << std::endl;
    std::cout << "Invert :                  " << (TestsMatrix3D::invert()               ? "ok" : "fail") << std::endl;
    std::cout << "Identity :                " << (TestsMatrix3D::identity()             ? "ok" : "fail") << std::endl;

    std::cout << "\nEnding tests for Matrix3D\n" << std::endl;
    return EXIT_SUCCESS;
}
