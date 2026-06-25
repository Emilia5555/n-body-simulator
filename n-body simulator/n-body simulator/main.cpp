#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_utils.h"
#include "shaders.h"
#include <vector>
#include <cmath>

int main() {

	// GLFW setup
	// if window doesnt initialize correctly, print error and exit
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// tell GLFW to use version 3.3 (major.minor) 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tell GLFW to use the core profile, which means we only have access to modern OpenGL functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// consts for window size
	const float WINDOW_HEIGHT = 1000;
	const float WINDOW_WIDTH = 1200;

	// creates the window (width px, height px, title, monitor for fullscreen, share context)
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "n-body gravity simulator", nullptr, nullptr);
	// if window doesn't get created, print error, terminate window, and exit
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		// avoid memory leak by terminating GLFW before exiting
		glfwTerminate();
		return -1;
	}


	// adjusts where the window pops up on screen (px from top and left of screen)
	glfwSetWindowPos(window, 1200, 100);


	// applies the OpenGL context to the window, makes OpenGL work with the window we just made
	glfwMakeContextCurrent(window);

	// GLAD setup
	//initialize GLAD to make GLFW work with windows
	//use glfwGetProcAdress from GLFW to show GLAD where to get the functions we need 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialze GLAD" << std::endl;
		return -1;
	}

	// make objects appear infront or behind eachother
	glEnable(GL_DEPTH_TEST);

	// create shader program
	unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

	float planetParticle[] = { 0.0f, 0.0f, 0.0f };


	// buffer setup
	// holds ID for vertex array object
	unsigned int VAO = 0;
	// holds ID for vertex buffer object
	unsigned int VBO = 0;

	// clear anything that was in the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// generates ID for vertex array object and stores in VAO
	glGenVertexArrays(1, &VAO);
	// generates ID for vertex buffer object and stores in VBO
	glGenBuffers(1, &VBO);

	// makes our VAO currently active
	glBindVertexArray(VAO);
	// makes VBO the current active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// upload planet data into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(planetParticle), planetParticle, GL_STATIC_DRAW);

	// tells openGL that VBO has vertex data where each vertex is 3 floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// enables input slot 0
	glEnableVertexAttribArray(0);

	// unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// while the user has not closed the window 
	while (!glfwWindowShouldClose(window))
	{
		// indicates color to set background (red,green, blue, alpha) uses 0-1 scale, expects float values
		glClearColor(0.067f, 0.071f, 0.102f, 1.0f);
		// sets the color 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// makes the draw call use the correct shader program
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glPointSize(25.0f);
		glDrawArrays(GL_POINTS, 0, 1);

		// prevents screen from flickering by drawing to a back buffer and then swapping it to the front
		glfwSwapBuffers(window);
		// detects input events, without this line the program wouldnt respond to any input
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}