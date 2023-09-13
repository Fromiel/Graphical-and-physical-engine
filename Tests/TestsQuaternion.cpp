#include <gtest/gtest.h>
#include "Maths/Quaternion.h"

const float epsilon = 0.01f;
const double pi = 3.14159265358979323846;

float toRadians(float degrees)
{
	return degrees * pi / 180;
}


TEST(constructorEuler, TestQuaternion_1)
{
	Quaternion q(Vector3D(toRadians(135), toRadians(90), 0));

	EXPECT_NEAR(q.getW(), 0.271f, epsilon);
	EXPECT_NEAR(q.getX(), 0.653f, epsilon);
	EXPECT_NEAR(q.getY(), 0.271f, epsilon);
	EXPECT_NEAR(q.getZ(), 0.653f, epsilon);
}

TEST(normalize, TestQuaternion_1)
{
	Quaternion q(1, 2, 3, 4, false);

	q.normalize();

	EXPECT_NEAR(q.getW(), 0.183f, epsilon);
	EXPECT_NEAR(q.getX(), 0.365f, epsilon);
	EXPECT_NEAR(q.getY(), 0.548f, epsilon);
	EXPECT_NEAR(q.getZ(), 0.730f, epsilon);
}