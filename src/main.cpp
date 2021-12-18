#include <iostream>
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

char keyPressed[512];

typedef struct vertex_t {

	int id;
	glm::vec4 pos;
	glm::vec4 color;

}vertex_t;


typedef struct triangle_t {

	int id;
	vertex_t vertices[3];
}triangle_t;


typedef struct entity_t {
	int id;
	glm::vec3 posicion;
	glm::vec3 rotacion;
	glm::vec3 escalado;

	std::vector<triangle_t*>* mesh;

	glm::mat4 modelMatrix;
};



triangle_t* createDefaultTrangle()
{

	triangle_t* t = new triangle_t;

	t->id = 0;
	t->vertices[0].id = 0;
	t->vertices[0].color = glm::vec4(0.0, 1.0f, 0.0f, 1.0);
	t->vertices[0].pos = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);

	t->vertices[1].id = 1;
	t->vertices[1].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0);
	t->vertices[1].pos = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);

	t->vertices[2].id = 2;
	t->vertices[2].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0);
	t->vertices[2].pos = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	return t;
}

entity_t* createDefaultEntity() {

	entity_t* e = new entity_t;

	e->posicion = glm::vec3(0);
	e->rotacion = glm::vec3(0);
	e->escalado = glm::vec3(1.0f);

	e->mesh = new std::vector<triangle_t*>();
	e->mesh->push_back(createDefaultTrangle());

	e->modelMatrix = glm::mat4(1.0);

	return e;
}

void computeModelMatrix(entity_t* e)
{
	e->modelMatrix = glm::translate(glm::mat4(1.0), e->posicion);
	e->modelMatrix = glm::rotate(e->modelMatrix, e->rotacion.x, glm::vec3(1.0f, 0.0f, 0.0f));
	e->modelMatrix = glm::rotate(e->modelMatrix, e->rotacion.y, glm::vec3(0.0f, 1.0f, 0.0f));
	e->modelMatrix = glm::rotate(e->modelMatrix, e->rotacion.z, glm::vec3(0.0f, 0.0f, 1.0f));
	e->modelMatrix = glm::scale(e->modelMatrix, e->escalado);

}

void drawTriangle(triangle_t* t, glm::mat4 MVP)
{
	glBegin(GL_TRIANGLES);
	{
		for (int i = 0; i < 3; i++)
		{
			glColor3f(t->vertices[i].color.r, t->vertices[i].color.g, t->vertices[i].color.b);
			glm::vec4 transfPos = MVP * t->vertices[i].pos;
			glVertex3f(transfPos.x, transfPos.y, transfPos.z);
		}
	}
	glEnd();
}

void drawEntity(entity_t* e)
{
	computeModelMatrix(e);
	for (auto it = e->mesh->begin(); it != e->mesh->end(); it++)
	{
		drawTriangle(*it, e->modelMatrix);

	}
}

void entityStep(entity_t* e)
{
	if (keyPressed[GLFW_KEY_D])
		e->posicion.x += 0.0001f;
	if (keyPressed[GLFW_KEY_A])
		e->posicion.x -= 0.0001f;

	if (e->posicion.x > 2.0f)
		e->posicion.x = -2.0f;

	e->rotacion.y += 0.001f;
}


void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods) {

	switch (action)
	{
	case GLFW_PRESS:
		keyPressed[key] = 1;
		break;

	case GLFW_RELEASE:
		keyPressed[key] = 0;
		break;


	}

}


int main(int argc, char** argv)
{
	int glewState = glewInit();
	if (!glewState)
		std::cout << "ERROR iniciando glew\n";
	int glfwState = glfwInit();
	if (!glfwState)
		std::cout << "ERROR iniciando glfw\n";

	GLFWwindow* window = glfwCreateWindow(640, 480, "APIS 3D", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	memset(keyPressed, 0, sizeof(char) * 512);

	glfwSetKeyCallback(window, updateKeys);

	entity_t* e = createDefaultEntity();
	while (!glfwWindowShouldClose(window))
	{
		entityStep(e);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawEntity(e);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;

}