#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_utils.h"
#include "shaders.h"
#include <vector>
#include <cmath>
#include "body.h"
#include "simulation.h"
#include "camera.h"
#include "renderer.h"
// matrix
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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


	// simulation object
	Simulation simulation;
	

	simulation.loadPreset(0);

	// holds positions of bodies
	// cast to a float becasue openGL does not nativley have doubles
	std::vector<float> positionAndColor;
	for (Body& body : simulation.bodies) {
		positionAndColor.push_back(body.position.x);
		positionAndColor.push_back(body.position.y);
		positionAndColor.push_back(body.position.z);
		positionAndColor.push_back(body.color.x);
		positionAndColor.push_back(body.color.y);
		positionAndColor.push_back(body.color.z);
	}



	// buffer setup
	// holds ID for vertex array object
	unsigned int bodyVAO = 0;
	// holds ID for vertex buffer object
	unsigned int bodyVBO = 0;

	// holds ID for vertex array object
	unsigned int tailVAO = 0;
	// holds ID for vertex buffer object
	unsigned int tailVBO = 0;

	setupBuffersBody(bodyVAO, bodyVBO,positionAndColor);

	setupBuffersTail(tailVAO,tailVBO);

	// create camera
	Camera camera(
		// set position to (0,0,3)
		glm::vec3(0.0f, 0.0f, 3.0f),
		// set target to (0,0,0)
		glm::vec3(0.0f, 0.0f, 0.0f),
		// set (0,1,0) as the direction of "up"
		glm::vec3(0.0f, 1.0f, 0.0f),
		// set field of view to 45 degrees
		45.0f,
		// set the aspect ratio as the window width/height
		(WINDOW_WIDTH / WINDOW_HEIGHT),
		// set the near plane to 0.1 world units
		0.1f,
		// set the far plane to 100 world units
		100.0f
	);

	// store camera pointer on glfw window so callbacks can access it
	glfwSetWindowUserPointer(window, &camera);
	// set glfw callback functions to my callback functions for mouse events
	// these get called if the event is detected by glfwPollEvents
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);
	glfwSetCursorPosCallback(window, mouseMoveCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// update camera positions
	camera.updateOrbit();

	// while the user has not closed the window 
	while (!glfwWindowShouldClose(window))
	{
		// indicates color to set background (red,green, blue, alpha) uses 0-1 scale, expects float values
		glClearColor(0.067f, 0.071f, 0.102f, 1.0f);
		// sets the color 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// makes the draw call use the correct shader program
		glUseProgram(shaderProgram);


		// get view and projection matrix every frame
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = camera.getProjectionMatrix();

		// send camera matrices to the GPU
		// glGetUniformLocation() gets view uniform from shader and returns int ID for that variables slot 
		// glUniformMatrix4fv uploads a 4x4 float matrix to that slot on the GPU
		// requires the raw float data of the matrix
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


		glBindVertexArray(bodyVAO);
		glPointSize(25.0f);

		// repeat step forward 5 times per frame
		for (int i = 0; i < 6; i++) {
			simulation.stepForward();
		}
		// for all bodies
		for (Body& body : simulation.bodies) {
			// if tail vector is too big start deleting the from front element
			if (body.prevPositions.size() >= 500) {
				body.prevPositions.erase(body.prevPositions.begin());
			}
			// add position to prevPostitions to create tail
			body.prevPositions.push_back(body.position);
		}

		// get rid of old positions
		positionAndColor.clear();
		// holds positions and color of bodies
		for (Body& body : simulation.bodies) {
			positionAndColor.push_back(body.position.x);
			positionAndColor.push_back(body.position.y);
			positionAndColor.push_back(body.position.z);
			positionAndColor.push_back(body.color.x);
			positionAndColor.push_back(body.color.y);
			positionAndColor.push_back(body.color.z);
		}

		// holds positions of tails
		std::vector<float> tailPositions;
		for (Body& body : simulation.bodies) 
		{
			// clear before re-using
			tailPositions.clear();
			// loop through prevPositions
			for (glm::vec3 pos : body.prevPositions) 
			{
				// create a tail positions flat float vector for each body
				tailPositions.push_back(pos.x);
				tailPositions.push_back(pos.y);
				tailPositions.push_back(pos.z);
			}
			
			// upload this trail info with glVertexAtribPointer
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tailPositions.size(), tailPositions.data(), GL_DYNAMIC_DRAW);
			// draw the tail
			glDrawArrays(GL_LINE_STRIP, 0, tailPositions.size());
		}

		// makes our VAO currently active
		glBindVertexArray(bodyVAO);
		// makes VBO the current active GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, bodyVBO);

		// upload body data into VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* positionAndColor.size(), positionAndColor.data(), GL_DYNAMIC_DRAW);
		
		glEnable(GL_PROGRAM_POINT_SIZE);
		glDrawArrays(GL_POINTS, 0, simulation.bodies.size());

		// prevents screen from flickering by drawing to a back buffer and then swapping it to the front
		glfwSwapBuffers(window);
		// detects input events, without this line the program wouldnt respond to any input
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}