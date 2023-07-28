#include <gtest/gtest.h>
#include "Maths/Matrix34.h"

const float epsilon = 0.0001f;

TEST(defaultConstructor, TestMatrix34_1)
{
	Matrix34 matrix = Matrix34();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++) {
			ASSERT_EQ(matrix(i, j), 0) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << 0;
		}
	}
}

TEST(constructorWithVector, TestMatrix34_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Matrix34 matrix = Matrix34(content);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++) {
			ASSERT_EQ(matrix(i, j), content[i * 4 + j]) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << i * 3 + j + 1;
		}
	}
}

TEST(getter, TestMatrix34_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Matrix34 matrix = Matrix34(content);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++) {
			ASSERT_EQ(matrix(i, j), content[i * 4 + j]) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << content[i * 3 + j];
		}
	}
}

TEST(setter, TestMatrix34_1)
{
	Matrix34 matrix = Matrix34();
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(0, 2) = 3;
	matrix(1, 0) = 4;

	ASSERT_EQ(matrix(0, 0), 1) << "Test failed at index (0,0), value : " << matrix(0, 0) << " expected : " << 1;
	ASSERT_EQ(matrix(0, 1), 2) << "Test failed at index (0,1), value : " << matrix(0, 1) << " expected : " << 2;
	ASSERT_EQ(matrix(0, 2), 3) << "Test failed at index (0,2), value : " << matrix(0, 2) << " expected : " << 3;
	ASSERT_EQ(matrix(1, 0), 4) << "Test failed at index (1,0), value : " << matrix(1, 0) << " expected : " << 4;
}

TEST(getContentAsStdVector, TestMatrix34_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Matrix34 matrix = Matrix34(content);
	std::vector<double> result = matrix.getContentAsStdVector();
	for (size_t i = 0; i < 12; i++)
	{
		ASSERT_EQ(content[i], result[i]) << "Test failed at index " << i << ", value : " << result[i] << " expected : " << content[i];
	}
}
TEST(toFloatArray, TestMatrix34_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Matrix34 matrix = Matrix34(content);
	float result[16];
	matrix.toFloatArray(result);

	std::vector<double> expected = {1, 5, 9, 0, 2, 6, 10, 0, 3, 7, 11, 0, 4, 8, 12, 1};
	for (size_t i = 0; i < 16; i++)
	{
		ASSERT_FLOAT_EQ(expected[i], result[i], epsilon) << "Test failed at index " << i << ", value : " << result[i] << " expected : " << content[i];
	}
}

TEST(operatorAssign, TestMatrix34_1)
{
	Matrix34 matrix = Matrix34();
	Matrix34 matrix2 = Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
	matrix = matrix2;
	for (size_t i = 0; i < 12; i++)
	{
		ASSERT_EQ(matrix(i / 4, i % 4), matrix2(i / 4, i % 4)) << "Test failed at index (" << i / 4 << "," << i % 4 << "), value : " << matrix(i / 4, i % 4) << " expected : " << matrix2(i / 4, i % 4);
	}
}

TEST(addition, TestMatrix34_1)
{
	Matrix34 result = Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }) + Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
	Matrix34 expected = Matrix34({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 });
	EXPECT_TRUE(result == expected);
}


TEST(substraction, TestMatrix34_1)
{
	Matrix34 result = Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }) - Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
	Matrix34 expected = Matrix34();
	EXPECT_TRUE(result == expected);
}

TEST(multiplicationScalar, TestMatrix34_1)
{
	Matrix34 result = Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }) * 2;
	Matrix34 expected = Matrix34({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 });
	EXPECT_TRUE(result == expected);
}

TEST(multiplicationMatrix, TestMatrix34_1)
{
	Matrix34 result = Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }) * Matrix34({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
	Matrix34 expected = Matrix34({ 38, 44, 50, 60, 98, 116, 134, 160, 158, 188, 218, 260 });

	EXPECT_TRUE(result == expected);
}

TEST(invert, TestMatrix34_1)
{
	Matrix34 result = Matrix34({ 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 8, 0 }).invert();
	Matrix34 expected = Matrix34({ 
		(double)-8 / 3, (double)8 / 3, -1, 0,
		(double)10 / 3, (double)-13 / 3, 2, 0,
		-1, 2, -1, 0
	});
	EXPECT_TRUE(result == expected) << "Value of the invert : \n" << result << "Value expected : \n" << expected << std::endl;
}

TEST(Matrix34FoisMatrix3D, TestMatrix34_1)
{
	Matrix3D result = Matrix34({ 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 8, 0 }) * Matrix3D({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	Matrix3D expected = Matrix3D({ 30, 36, 42, 66, 81, 96, 95, 118, 141 });
	EXPECT_TRUE(result == expected) << "Value of the result : \n" << result << "Value expected : \n" << expected << std::endl;
}

TEST(Matrix34FoisVector3D, TestMatrix34_1)
{
	Vector3D result = Matrix34({ 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 8, 0 }) * Vector3D(1, 2, 3);
	Vector3D expected = Vector3D(14, 32, 47);
	EXPECT_TRUE(result == expected) << "Value of the result : \n" << result << "Value expected : \n" << expected << std::endl;
}

TEST(Matrix34FoisMatrix4D, TestMatrix34_1)
{
	Matrix4D result = Matrix34({ 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 8, 0 }) * Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
	Matrix4D expected = Matrix4D({ 38, 44, 50, 56, 83, 98, 113, 128, 119, 142, 165, 188, 13, 14, 15, 16 });
	EXPECT_TRUE(result == expected) << "Value of the result : \n" << result << "Value expected : \n" << expected << std::endl;
}