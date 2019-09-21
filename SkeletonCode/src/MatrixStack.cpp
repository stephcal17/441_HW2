#include "MatrixStack.h"

#include <stdio.h>
#include <cassert>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

MatrixStack::MatrixStack()
{
	mstack = make_shared< stack<glm::mat4> >();
	mstack->push(glm::mat4(1.0));
}

MatrixStack::~MatrixStack()
{
}

void MatrixStack::pushMatrix()
{
	const glm::mat4 &top = mstack->top();
	mstack->push(top);
	assert(mstack->size() < 100);
}

void MatrixStack::popMatrix()
{
	assert(!mstack->empty());
	mstack->pop();
	// There should always be one matrix left.
	assert(!mstack->empty());
}

void MatrixStack::loadIdentity()
{
	glm::mat4 &top = mstack->top();
	top = glm::mat4(1.0);
}

void MatrixStack::translate(const glm::vec3 &t)
{
	glm::mat4 translationMatrix(1.0f);

	// Need to comment out the following line and write your own version
	//translationMatrix = glm::translate(glm::mat4(1.0f), t);
	translationMatrix[3][0] = t[0];
	translationMatrix[3][1] = t[1];
	translationMatrix[3][2] = t[2];

	multMatrix(translationMatrix);
}

void MatrixStack::scale(const glm::vec3 &s)
{
	glm::mat4 scaleMatrix(1.0f);

	// Need to comment out the following line and write your own version
	//scaleMatrix = glm::scale(glm::mat4(1.0f), s);
	scaleMatrix[0][0] = s[0];
	scaleMatrix[1][1] = s[1];
	scaleMatrix[2][2] = s[2];

	multMatrix(scaleMatrix);
}

void MatrixStack::rotateX(float angle)
{
	glm::mat4 rotationMatrix(1.0f);

	// Need to comment out the following line and write your own version
	//rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
	float sinx = sin(angle);
	float cosx = cos(angle);
	rotationMatrix[1][1] = cosx;
	rotationMatrix[1][2] = sinx;
	rotationMatrix[2][1] = -sinx;
	rotationMatrix[2][2] = cosx;

	multMatrix(rotationMatrix);
}

void MatrixStack::rotateY(float angle)
{
	glm::mat4 rotationMatrix(1.0f);

	// Need to comment out the following line and write your own version
	//rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	float siny = sin(angle);
	float cosy = cos(angle);
	rotationMatrix[0][0] = cosy;
	rotationMatrix[0][2] = -siny;
	rotationMatrix[2][0] = siny;
	rotationMatrix[2][2] = cosy;

	multMatrix(rotationMatrix);
}

void MatrixStack::rotateZ(float angle)
{
	glm::mat4 rotationMatrix(1.0f);

	// Need to comment out the following line and write your own version
	//rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
	float sinz = sin(angle);
	float cosz = cos(angle);
	rotationMatrix[0][0] = cosz;
	rotationMatrix[0][1] = sinz;
	rotationMatrix[1][0] = -sinz;
	rotationMatrix[1][1] = cosz;

	multMatrix(rotationMatrix);
}

void MatrixStack::multMatrix(glm::mat4 &matrix)
{
	glm::mat4 &top = mstack->top();

	// Need to comment out the following line and write your own version
	//top *= matrix;
	float tmp = 0.0;
	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			for (int g = 0; g < 4; g++) {
				tmp += top[g][i] * matrix[n][g];
			}
			top[n][i] = tmp;
			tmp = 0.0;
		}
	}

	// Getting a pointer to the glm::mat4 matrix
	float* topArray = glm::value_ptr(top);
	float* matrixArray = glm::value_ptr(matrix);
}

void MatrixStack::Perspective(float fovy, float aspect, float near, float far)
{
	glm::mat4 projectionMatrix(0.0f);

	// Need to comment out the following line and write your own version
	projectionMatrix = glm::perspective(fovy, aspect, near, far);

	multMatrix(projectionMatrix);
}

void MatrixStack::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	glm::mat4 viewMatrix(1.0f);

	// Need to comment out the following line and write your own version
	viewMatrix = glm::lookAt(eye, center, up);

	multMatrix(viewMatrix);
}


void MatrixStack::translate(float x, float y, float z)
{
	translate(glm::vec3(x, y, z));
}

void MatrixStack::scale(float x, float y, float z)
{
	scale(glm::vec3(x, y, z));
}

void MatrixStack::scale(float s)
{
	scale(glm::vec3(s, s, s));
}

glm::mat4 &MatrixStack::topMatrix()
{
	return mstack->top();
}

void MatrixStack::print(const glm::mat4 &mat, const char *name)
{
	if(name) {
		printf("%s = [\n", name);
	}
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			// mat[j] returns the jth column
			printf("%- 5.2f ", mat[j][i]);
		}
		printf("\n");
	}
	if(name) {
		printf("];");
	}
	printf("\n");
}

void MatrixStack::print(const char *name) const
{
	print(mstack->top(), name);
}
