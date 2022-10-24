#include <gtest/gtest.h>
#include "Matrix4D.h"

TEST(test, testtest)
{
    EXPECT_TRUE(true);
}


/*Test Matrix4D :

    Matrix4D test_mat_0;
    std::vector<double> content = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    Matrix4D test_mat_1(content);
    content = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
    Matrix4D test_mat_2(content);
    Matrix4D test_mat_copie(test_mat_1);

    std::cout << test_mat_0 << std::endl;
    std::cout << test_mat_1 << std::endl;
    std::cout << test_mat_2 << std::endl;
    std::cout << test_mat_copie << std::endl;

    std::vector<double> test_getter = test_mat_copie.getContentAsStdVector();
    for (double i : test_getter) {
        std::cout << i << std::endl;
    }
    std::cout << test_mat_1(1, 1) << std::endl;
    double test_get_elt = test_mat_1(2, 3);
    std::cout << test_get_elt << std::endl;
    Matrix4D test_mat_copie_2 = test_mat_copie;
    std::cout << test_mat_copie << std::endl;
    std::vector<double> test_1 = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    Matrix4D test_mat_plus(test_1);
    test_mat_plus += test_mat_plus;
    Matrix4D test_mat_moins(test_1);
    test_mat_moins -= test_mat_moins;
    std::cout << test_mat_plus << std::endl;
    std::cout << test_mat_moins << std::endl;

    Matrix4D test_transpose = test_mat_1.transpose();
    Matrix4D test_identity = Matrix4D::identity();
    Matrix4D test_invert = test_identity.invert();
    Vecteur3D vect_3(1, 2, 3);
    Matrix4D test_translate = Matrix4D::translation(vect_3);
    Matrix4D test_scaling = Matrix4D::scaling(vect_3);
    Matrix4D test_projection = Matrix4D::projectionMatrix(M_PI, 1, 1, 500);
    std::cout << test_transpose << std::endl;
    std::cout << test_invert << std::endl;
    std::cout << test_identity << std::endl;
    std::cout << test_translate << std::endl;
    std::cout << test_scaling << std::endl;
    std::cout << test_projection << std::endl;

    Matrix4D test_plus = test_mat_1 + test_mat_2;
    Matrix4D test_moins = test_mat_1 - test_mat_2;
    Matrix4D test_fois_1 = test_mat_1 * 4;
    Matrix4D test_fois_2 = 4 * test_mat_1;
    Matrix4D test_fois_3 = test_mat_1 * test_mat_2;

    bool test_egalite = (test_fois_1 == test_fois_2);
    std::cout << test_plus << std::endl;
    std::cout << test_moins << std::endl;
    std::cout << test_fois_1 << std::endl;
    std::cout << test_fois_2 << std::endl;
    std::cout << test_fois_3 << std::endl;
    std::cout << test_egalite << std::endl; */