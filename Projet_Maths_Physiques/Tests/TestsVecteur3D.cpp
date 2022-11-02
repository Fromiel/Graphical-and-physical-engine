#include <gtest/gtest.h>
#include "Maths/Vecteur3D.h"

TEST(norm, TestVecteur3D_1) {
    double result = Vecteur3D(1, 2, 3).norm();
    double expected = sqrt(14);
    EXPECT_TRUE(result == expected);
}

TEST(norm_squared, TestVecteur3D_1) {
    double result = Vecteur3D(1, 2, 3).norm_squared();
    double expected = 14;
    EXPECT_TRUE(result == expected);
}

TEST(normalized, TestVecteur3D_1) {
    Vecteur3D result = Vecteur3D(14, 7, 14).normalized();
    Vecteur3D expected = Vecteur3D(2.0f/3.0f, 1.0f/3.0f, 2.0f/3.0f);

    bool testPass = true;

    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(scalar_multiplication, TestVecteur3D_1) {
    Vecteur3D result = Vecteur3D(1, 2, 3).scalar_multiplication(2);
    Vecteur3D expected = Vecteur3D(2, 4, 6);

    bool testPass = true;

    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(addition, TestVecteur3D_1) {
    Vecteur3D result = Vecteur3D(1, 2, 3) + Vecteur3D(1, 2, 3);
    Vecteur3D expected = Vecteur3D(2, 4, 6);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;
    
    EXPECT_TRUE(testPass);
}

TEST(substraction, TestVecteur3D_1) {
    Vecteur3D result = Vecteur3D(1, 2, 3) - Vecteur3D(1, 2, 3);
    Vecteur3D expected = Vecteur3D(0, 0, 0);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(scalarProduct, TestVecteur3D_1) {
    double result = scalar_product(Vecteur3D(1, 2, 3), Vecteur3D(4, 5, 6));
    double expected = 32;
    EXPECT_TRUE(result == expected);
}

TEST(vectorialProduct, TestVecteur3D_1) {
    Vecteur3D result = vectorial_product(Vecteur3D(1, 2, 3), Vecteur3D(4, 5, 6));
    Vecteur3D expected = Vecteur3D(-3, 6, -3);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}