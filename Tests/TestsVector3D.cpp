#include <gtest/gtest.h>
#include "Maths/Vector3D.h"

const double epsilon = 0.0001;

TEST(norm, TestVector3D_1) {
    double result = Vector3D(1, 2, 3).norm();
    double expected = 14;
    EXPECT_TRUE(abs((result * result) - expected) < epsilon);
}

TEST(norm_squared, TestVector3D_1) {
    double result = Vector3D(1, 2, 3).norm_squared();
    double expected = 14;
    EXPECT_TRUE(abs(result - expected) < epsilon);
}

TEST(normalized, TestVector3D_1) {
    Vector3D result = Vector3D(14, 7, 14).normalized();
    Vector3D expected = Vector3D(2.0f/3.0f, 1.0f/3.0f, 2.0f/3.0f);

    bool testPass = true;

    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(scalar_multiplication, TestVector3D_1) {
    Vector3D result = Vector3D(1, 2, 3) * 2;
    Vector3D expected = Vector3D(2, 4, 6);

    bool testPass = true;

    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(addition, TestVector3D_1) {
    Vector3D result = Vector3D(1, 2, 3) + Vector3D(1, 2, 3);
    Vector3D expected = Vector3D(2, 4, 6);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;
    
    EXPECT_TRUE(testPass);
}

TEST(substraction, TestVector3D_1) {
    Vector3D result = Vector3D(1, 2, 3) - Vector3D(1, 2, 3);
    Vector3D expected = Vector3D(0, 0, 0);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(scalarProduct, TestVector3D_1) {
    double result = Vector3D::scalar_product(Vector3D(1, 2, 3), Vector3D(4, 5, 6));
    double expected = 32;
    EXPECT_TRUE(result == expected);
}

TEST(vectorialProduct, TestVector3D_1) {
    Vector3D result = Vector3D::vectorial_product(Vector3D(1, 2, 3), Vector3D(4, 5, 6));
    Vector3D expected = Vector3D(-3, 6, -3);

    bool testPass = true;
    
    if (result.get_x() != expected.get_x()) testPass = false;
    if (result.get_y() != expected.get_y()) testPass = false;
    if (result.get_z() != expected.get_z()) testPass = false;

    EXPECT_TRUE(testPass);
}

TEST(distance, TestVector3D_1)
{
	double result = Vector3D::distance(Vector3D(1, 2, 3), Vector3D(1, 2, 4));
	double expected = 1;
	EXPECT_TRUE(abs(result - expected) < epsilon);
}