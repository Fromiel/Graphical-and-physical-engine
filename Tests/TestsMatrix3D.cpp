#include <gtest/gtest.h>
#include "Maths/Matrix3D.h"

const float epsilon = 0.0001f;

TEST(defaultConstructor, TestMatrix3D_1)
{
	Matrix3D matrix = Matrix3D();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++) {
			ASSERT_EQ(matrix(i, j), 0) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << 0;
		}
	}
}

TEST(constructorWithVector, TestMatrix3D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix3D matrix = Matrix3D(content);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++) {
			ASSERT_EQ(matrix(i, j), content[i * 3 + j]) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << i * 3 + j + 1;
		}
	}
}

TEST(getter, TestMatrix3D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix3D matrix = Matrix3D(content);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++) {
			ASSERT_EQ(matrix(i, j), content[i * 3 + j]) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << content[i * 3 + j];
		}
	}
}

TEST(setter, TestMatrix3D_1)
{
	Matrix3D matrix = Matrix3D();
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(0, 2) = 3;
	matrix(1, 0) = 4;

	ASSERT_EQ(matrix(0, 0), 1) << "Test failed at index (0,0), value : " << matrix(0, 0) << " expected : " << 1;
	ASSERT_EQ(matrix(0, 1), 2) << "Test failed at index (0,1), value : " << matrix(0, 1) << " expected : " << 2;
	ASSERT_EQ(matrix(0, 2), 3) << "Test failed at index (0,2), value : " << matrix(0, 2) << " expected : " << 3;
	ASSERT_EQ(matrix(1, 0), 4) << "Test failed at index (1,0), value : " << matrix(1, 0) << " expected : " << 4;
}

TEST(getContentAsStdVector, TestMatrix3D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix3D matrix = Matrix3D(content);
	std::vector<double> result = matrix.getContentAsStdVector();
	for (size_t i = 0; i < 9; i++)
	{
		ASSERT_EQ(content[i], result[i]) << "Test failed at index " << i << ", value : " << result[i] << " expected : " << content[i];
	}
}
TEST(toFloatArray, TestMatrix3D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Matrix3D matrix = Matrix3D(content);
	float result[9];
	matrix.toFloatArray(result);

	auto expected = matrix.transpose().getContentAsStdVector();
	for (size_t i = 0; i < 9; i++)
	{
		ASSERT_FLOAT_EQ(expected[i], result[i], epsilon) << "Test failed at index " << i << ", value : " << result[i] << " expected : " << content[i];
	}
}

TEST(operatorAssign, TestMatrix3D_1)
{
	Matrix3D matrix = Matrix3D();
	Matrix3D matrix2 = Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	matrix = matrix2;
	for (size_t i = 0; i < 9; i++)
	{
		ASSERT_EQ(matrix(i / 3, i % 3), matrix2(i / 3, i % 3)) << "Test failed at index (" << i / 3 << "," << i % 3 << "), value : " << matrix(i / 3, i % 3) << " expected : " << matrix2(i / 3, i % 3);
	}
}

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

