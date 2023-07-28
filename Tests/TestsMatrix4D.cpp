#include <gtest/gtest.h>
#include "Maths/Matrix4D.h"

const float epsilon = 0.0001f;

TEST(defaultConstructor, TestMatrix4D_1)
{
	Matrix4D matrix = Matrix4D();
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++) {
			ASSERT_EQ(matrix(i, j), 0) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << 0;
		}
	}
}

TEST(constructorWithVector, TestMatrix4D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	Matrix4D matrix = Matrix4D(content);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++) {
			ASSERT_EQ(matrix(i, j), content[i * 4 + j]) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << i * 3 + j + 1;
		}
	}
}

TEST(getter, TestMatrix4D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	Matrix4D matrix = Matrix4D(content);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++) {
			ASSERT_EQ(matrix(i, j), content[i * 4 + j]) << "Test failed at index (" << i << "," << j << "), value : " << matrix(i, j) << " expected : " << content[i * 3 + j];
		}
	}
}

TEST(setter, TestMatrix4D_1)
{
	Matrix4D matrix = Matrix4D();
	matrix(0, 0) = 1;
	matrix(0, 1) = 2;
	matrix(0, 2) = 3;
	matrix(1, 0) = 4;

	ASSERT_EQ(matrix(0, 0), 1) << "Test failed at index (0,0), value : " << matrix(0, 0) << " expected : " << 1;
	ASSERT_EQ(matrix(0, 1), 2) << "Test failed at index (0,1), value : " << matrix(0, 1) << " expected : " << 2;
	ASSERT_EQ(matrix(0, 2), 3) << "Test failed at index (0,2), value : " << matrix(0, 2) << " expected : " << 3;
	ASSERT_EQ(matrix(1, 0), 4) << "Test failed at index (1,0), value : " << matrix(1, 0) << " expected : " << 4;
}

TEST(getContentAsStdVector, TestMatrix4D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	Matrix4D matrix = Matrix4D(content);
	std::vector<double> result = matrix.getContentAsStdVector();
	for (size_t i = 0; i < 16; i++)
	{
		ASSERT_EQ(content[i], result[i]) << "Test failed at index " << i << ", value : " << result[i] << " expected : " << content[i];
	}
}
TEST(toFloatArray, TestMatrix4D_1)
{
	std::vector<double> content = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	Matrix4D matrix = Matrix4D(content);
	float result[16];
	matrix.toFloatArray(result);

	auto expected = matrix.transpose().getContentAsStdVector();
	for (size_t i = 0; i < 16; i++)
	{
		ASSERT_FLOAT_EQ(expected[i], result[i], epsilon) << "Test failed at index " << i << ", value : " << result[i] << " expected : " << content[i];
	}
}

TEST(operatorAssign, TestMatrix4D_1)
{
	Matrix4D matrix = Matrix4D();
	Matrix4D matrix2 = Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
	matrix = matrix2;
	for (size_t i = 0; i < 16; i++)
	{
		ASSERT_EQ(matrix(i / 4, i % 4), matrix2(i / 4, i % 4)) << "Test failed at index (" << i / 4 << "," << i % 4 << "), value : " << matrix(i / 4, i % 4) << " expected : " << matrix2(i / 4, i % 4);
	}
}

TEST(addition, TestMatrix4D_1)
{
	Matrix4D result = Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }) + Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
	Matrix4D expected = Matrix4D({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 });
	EXPECT_TRUE(result == expected);
}


TEST(substraction, TestMatrix4D_1)
{
	Matrix4D result = Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }) - Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
	Matrix4D expected = Matrix4D();
	EXPECT_TRUE(result == expected);
}

TEST(multiplicationScalar, TestMatrix4D_1)
{
	Matrix4D result = Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }) * 2;
	Matrix4D expected = Matrix4D({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 });
	EXPECT_TRUE(result == expected);
}

TEST(multiplicationMatrix, TestMatrix4D_1)
{
	Matrix4D result = Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }) * Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
	Matrix4D expected = Matrix4D({ 90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600 });
	EXPECT_TRUE(result == expected);
}

TEST(transpose, TestMatrix4D_1)
{
	Matrix4D result = Matrix4D({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }).transpose();
	Matrix4D expected = Matrix4D({ 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16 });
	EXPECT_TRUE(result == expected);
}

TEST(invert, TestMatrix4D_1)
{
	Matrix4D result = Matrix4D({ 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4 }).invert();
	Matrix4D expected = Matrix4D({ (double)17 / 6, -1, (double) -1 / 2, (double)-1 / 3,
									-1, 1, 0, 0, 
								(double)-1 / 2, 0, (double) 1 / 2, 0,
								(double)-1 / 3, 0, 0, (double)1 / 3 }
								);
	EXPECT_TRUE(result == expected) << "Value of the invert : \n" << result << "Value expected : \n" << expected << std::endl;
}