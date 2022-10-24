#include <gtest/gtest.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sphere.h"


glm::vec3 toVec3(Vecteur3D vect)
{
	return glm::vec3(vect.get_x(), vect.get_y(), vect.get_z());
}

bool compareGlmMatrixWithMatrix(Matrix4D result, glm::mat4 expected)
{
	float result_[16];
	result.toFloatArray(result_);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (result_[i * 4 + j] != expected[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool compareGlmMatrixWithMatrix(Matrix3D result, glm::mat3 expected)
{
	float result_[9];
	result.toFloatArray(result_);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result_[i * 3 + j] != expected[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

TEST(viewMatrix, TestsTransformMatrix_1)
{
	Vecteur3D position(0.0f, 0.0f, 27.0f);
	Camera camera(0.1, 100, position);

	//Create a camera which looks at the center of the world (0, 0, 0)
	
	glm::vec3 pos = toVec3(position);

	//Expected result with glm
	glm::mat4 view;
	view = glm::lookAt(pos,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	EXPECT_TRUE(compareGlmMatrixWithMatrix(camera.getViewMatrix(), view));
}

TEST(translationMatrix, TestsTransformMatrix_1)
{
	Vecteur3D positon(1, 24, -57);
	Matrix4D translation = Matrix4D::translation(positon);

	glm::vec3 pos = toVec3(positon);
	glm::mat4 expected = glm::translate(glm::mat4(1.0), pos);

	EXPECT_TRUE(compareGlmMatrixWithMatrix(translation, expected));
}

TEST(rotationMatrix, TestsTransformMatrix_1)
{
	//pas implementer pour l'instant
	EXPECT_TRUE(true);
}

TEST(scalingMatrix, TestsTransformMatrix_1)
{
	Vecteur3D scale(1, 0.5, 5.5);
	Matrix4D scaling = Matrix4D::scaling(scale);

	glm::vec3 sc = toVec3(scale);
	glm::mat4 expected = glm::scale(glm::mat4(1.0), sc);

	EXPECT_TRUE(compareGlmMatrixWithMatrix(scaling, expected));
}

TEST(projectionMatrix, TestsTransformMatrix_1)
{
	Vecteur3D position(0.0f, 0.0f, 27.0f);
	Camera camera(0.1, 100, position, 110);

	Matrix4D projection = Matrix4D::projectionMatrix(camera.getFov(), camera.getRatio(), camera.getNear(), camera.getFar());

	glm::mat4 expected = glm::perspective(camera.getFov(), camera.getRatio(), camera.getNear(), camera.getFar());

	EXPECT_TRUE(compareGlmMatrixWithMatrix(projection, expected));
}

TEST(normalMatrix, TestsTransformMatrix_1)
{
	Vecteur3D position(0.0f, 0.0f, 27.0f);
	Camera camera(0.1, 100, position, 110);

	Sphere s(2, Vecteur3D(0.0f, 5.0f, 25.0f));
	s.setScaling(Vecteur3D(0.5f, 0.45f, 1.0f));

	Matrix3D normal = camera.getNormalMatrix(s.getModelMatrix());


	glm::mat4 view;
	view = glm::lookAt(toVec3(position),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), toVec3(s.getPosition())) * glm::scale(glm::mat4(1.0f), toVec3(s.getScaling()));
	glm::mat4 modelViewMatrix = view * model;

	glm::mat3 modelViewMatrix3(modelViewMatrix);
	glm::mat3 expected = glm::inverse(glm::transpose(modelViewMatrix3));

	EXPECT_TRUE(compareGlmMatrixWithMatrix(normal, expected));
}

