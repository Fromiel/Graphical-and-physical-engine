#include <gtest/gtest.h>
#include "Matrix3D.h"

TEST(addition, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }) + Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	Matrix3D expected = Matrix3D({ 2, 4, 6, 8, 10, 12, 14, 16, 18 });
	EXPECT_TRUE(result == expected);
}


TEST(substraction, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }) - Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	Matrix3D expected = Matrix3D({ 0, 0, 0, 0, 0, 0, 0, 0,0 });
	EXPECT_TRUE(result == expected);
}

TEST(multiplicationScalar, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }) * 2;
	Matrix3D expected = Matrix3D({ 2, 4, 6, 8, 10, 12, 14, 16, 18 });
	EXPECT_TRUE(result == expected);
}

TEST(multiplicationMatrix, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }) * Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	Matrix3D expected = Matrix3D({ 30, 36, 42, 66, 81, 96, 102, 126, 150 });
	EXPECT_TRUE(result == expected);
}

TEST(determinant, TestMatrix3D_1)
{
	double result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }).determinant();
	double expected = 0;
	EXPECT_TRUE(result == expected);
}

TEST(transpose, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }).transpose();
	Matrix3D expected = Matrix3D({ 1, 4, 7, 2, 5, 8, 3, 6, 9 });
	EXPECT_TRUE(result == expected);
}

TEST(adjugate, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }).adjugate();
	Matrix3D expected = Matrix3D({ -3, 6, -3, 6, -12, 6, -3, 6, -3 });
	EXPECT_TRUE(result == expected);
}


TEST(invert, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 8 }).invert();
	Matrix3D expected = Matrix3D({ (double)-8 / 3, (double)8 / 3, -1, (double)10 / 3, (double)-13 / 3, 2, -1, 2, -1 });
	EXPECT_TRUE(result == expected);
}

TEST(identity, TestMatrix3D_1)
{
	Matrix3D result = Matrix3D::identity();
	Matrix3D expected = Matrix3D({ 1, 0, 0, 0, 1, 0, 0, 0, 1 });
	EXPECT_TRUE(result == expected);
}

