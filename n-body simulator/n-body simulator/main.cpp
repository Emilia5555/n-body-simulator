#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_utils.h"
#include "shaders.h"

int main() {

	// if window doesnt initialize correctly, print error and exit
	if (glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// tell GLFW to use version 3.3 (major.minor) 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tell GLFW to use the core profile, which means we only have access to modern OpenGL functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// consts for window size
	const float WINDOW_HEIGHT = 1200;
	const float WINDOW_WIDTH = 1000;

	// creates the window (width px, height px, title, monitor for fullscreen, share context)
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "n-body gravity simulator", nullptr, nullptr);
	// if window doesn't get created, print error, terminate window, and exit
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		// avoid memory leak by terminating GLFW before exiting
		glfwTerminate();
		return -1;
	}



	return 0;
}