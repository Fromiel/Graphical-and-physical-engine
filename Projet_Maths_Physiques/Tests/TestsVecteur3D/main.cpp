#include <iostream>
#include "TestsVecteur3D.h"

int main(int argc, char **argv) {
    std::cout << "\nStarting tests for Vecteur3D\n" << std::endl;

    std::cout << "Norm :                    " << (TestsVecteur3D::norm()                     ? "ok" : "fail") << std::endl;
    std::cout << "Norm Squared :            " << (TestsVecteur3D::norm_squared()             ? "ok" : "fail") << std::endl;
    std::cout << "Normalized :              " << (TestsVecteur3D::normalized()               ? "ok" : "fail") << std::endl;
    std::cout << "Scalar Multiplication :   " << (TestsVecteur3D::scalar_multiplication()    ? "ok" : "fail") << std::endl;
    std::cout << "Addition :                " << (TestsVecteur3D::addition()                 ? "ok" : "fail") << std::endl;
    std::cout << "Substraction :            " << (TestsVecteur3D::substraction()             ? "ok" : "fail") << std::endl;
    std::cout << "Scalar Product :          " << (TestsVecteur3D::scalar_product()           ? "ok" : "fail") << std::endl;
    std::cout << "Vectorial Product :       " << (TestsVecteur3D::vectorial_product()        ? "ok" : "fail") << std::endl;

    std::cout << "\nEnding tests for Vecteur3D\n" << std::endl;
    return EXIT_SUCCESS;
}
