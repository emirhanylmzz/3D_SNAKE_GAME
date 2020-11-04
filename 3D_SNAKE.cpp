﻿//Emirhan Yılmaz
//3D snake game
//5.11.2020

#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Snake.h"
using namespace std;

void key_callback(GLFWwindow* window, Snake& snake);
string readFile(const char* filePath);

int main()
{
	if (!glfwInit())
	{
		cerr << "GLFW initialisation failed!" << endl;
		glfwTerminate();
		return -1;
	}
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/
	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "3D SNAKE", NULL, NULL);
	if (!mainWindow)
	{
		cerr << "GLFW window creatin failed!" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW ınitialisation failed!" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return -1;
	}
	{
		GLfloat positions[] =
		{
			-0.5, -0.5, -0.5,   -0.5, -0.5,  0.5,   -0.5,  0.5,  0.5,   -0.5,  0.5, -0.5,
			 0.5, -0.5, -0.5,    0.5, -0.5,  0.5,    0.5,  0.5,  0.5,    0.5,  0.5, -0.5,
			-0.5, -0.5, -0.5,   -0.5, -0.5,  0.5,    0.5, -0.5,  0.5,    0.5, -0.5, -0.5,
			-0.5,  0.5, -0.5,   -0.5,  0.5,  0.5,    0.5,  0.5,  0.5,    0.5,  0.5, -0.5,
			-0.5, -0.5, -0.5,   -0.5,  0.5, -0.5,    0.5,  0.5, -0.5,    0.5, -0.5, -0.5,
			-0.5, -0.5,  0.5,   -0.5,  0.5,  0.5,    0.5,  0.5,  0.5,    0.5, -0.5,  0.5
		};
		//GRID
		VertexArray vao;
		VertexBuffer vbgrid(positions, sizeof(positions));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		vao.AddBuffer(vbgrid, layout);

		//SNAKE
		VertexArray vaS;
		VertexBuffer vbS(positions, sizeof(positions));
		VertexBufferLayout layoutS;
		layoutS.Push<float>(3);
		vaS.AddBuffer(vbS, layoutS);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = 
			glm::lookAt(glm::vec3(0.0f, 10.0f, 25.0f),
			glm::vec3(0.0f, -5.0f, 0.0f),
			glm::vec3(0.0f, 1.0f,0.0f));

		glm::mat4 pv = proj * view;

		string vertexShader = readFile("vertex.shader");
		string fragmentShader = readFile("fragment.shader");
		Shader shader(vertexShader, fragmentShader);
		
		//Creating grid coordinats
		float x = -10;
		float z = 10;
		glm::vec3 pos[20][20];
		for (unsigned int i = 0; i < 20; ++i)
		{
			for (unsigned int j = 0; j < 20; ++j)
			{
				pos[i][j] = glm::vec3(x, -5.0f, z);
				x = x + 1;
			}
			x = -10;
			z = z - 1;
		}
		
		Snake snake(glm::vec3(5.0f, -5.0f, 0.0f));
		Bait bait(glm::vec3(2.0f, -5.0f, 0.0f));

		vao.UnBind();
		vbgrid.UnBind();
		vaS.UnBind();
		vbS.UnBind();
		shader.UnBind();
		Renderer renderer;
		while (!glfwWindowShouldClose(mainWindow) && snake.isGameOver())
		{
			renderer.clear();
			renderer.drawGrid(vao, shader, pos, pv);
			renderer.drawSnake(vaS, shader, snake, pv, bait);
			int direction = snake.getDirection();
			if (direction == 1)
				snake.moveLeft();
			if (direction == 2)
				snake.moveDown();
			if (direction == 3)
				snake.moveRight();
			if (direction == 5)
				snake.moveUp();
			snake.snakegrow(bait);
			key_callback(mainWindow, snake);
			glfwSwapBuffers(mainWindow);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return (0);
}


string readFile(const char* filePath) {
	string content;
	ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		cerr << "Could not read file!\n" << filePath << ". File does not exist!\n" << endl;
		return "";
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void key_callback(GLFWwindow* window, Snake& snake)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		snake.setDirection(5);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		snake.setDirection(1);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		snake.setDirection(3);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		snake.setDirection(2);
}