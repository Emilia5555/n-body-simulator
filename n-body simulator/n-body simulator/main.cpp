#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_utils.h"
#include "shaders.h"
#include <vector>
#include <cmath>
#include <string>
#include "body.h"
#include "simulation.h"
#include "camera.h"
#include "renderer.h"
// matrix
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// imgui controls
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
	const float WINDOW_WIDTH = 1600;

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
	glfwSetWindowPos(window, 900, 100);


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


	// ImGui setup
	// gotta have this
	IMGUI_CHECKVERSION();
	// creates context ill be working with
	ImGui::CreateContext();
	// stores ImGui input/output configuration
	ImGuiIO& io = ImGui::GetIO();
	// connects ImGui to windows
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	// conects ImGui to OpenGl 3.3 renderer
	ImGui_ImplOpenGL3_Init("#version 330");
	// dark theme for control panel
	ImGui::StyleColorsDark();



	// create shader programs
	unsigned int bodyShaderProgram = createShaderProgram(vertexShaderSource, bodyFragmentShaderSource);
	unsigned int lineShaderProgram = createShaderProgram(vertexShaderSource, lineFragmentShaderSource);

	// simulation object
	Simulation simulation;
	
	// int to store preset
	int currentPreset = 0;
	// set which orbit the bodies should move
	simulation.loadPreset(currentPreset);


	// buffer setup
	// holds ID for vertex array object
	unsigned int bodyVAO = 0;
	// holds ID for vertex buffer object
	unsigned int bodyVBO = 0;

	// holds ID for vertex array object
	unsigned int tailVAO = 0;
	// holds ID for vertex buffer object
	unsigned int tailVBO = 0;


	// holds positions of bodies
	// cast to a float becasue openGL does not nativley have doubles
	std::vector<float> bodyPosition;
	setupBuffersBody(bodyVAO, bodyVBO,bodyPosition);

	// holds positions of tails
	std::vector<float> tailPosition;
	setupBuffersTail(tailVAO,tailVBO, tailPosition);

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

	// set callback functions
	// store camera pointer on glfw window so callbacks can access it
	glfwSetWindowUserPointer(window, &camera);
	// set glfw callback functions to my callback functions for mouse events
	// these get called if the event is detected by glfwPollEvents
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);
	glfwSetCursorPosCallback(window, mouseMoveCallback);
	glfwSetScrollCallback(window, scrollCallback);
	// use ImGui callback function for keyboard
	glfwSetCharCallback(window,ImGui_ImplGlfw_CharCallback);
	glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
	// update camera positions
	camera.updateOrbit();

	// positions and color for axis
	std::vector<float> axisPos;
	// fill axisPos
	// loop through rows
	for (int j = 0; j < 6;j++) 
	{
		// loop through columns
		for (int i = 0; i < 3;i++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					axisPos.push_back(10.0);
				}
				else if (j == 1)
				{
					axisPos.push_back(-10.0);

				}
				else
				{
					axisPos.push_back(0.0);
				}
			}
			else if (i == 1)
			{
				if (j == 2)
				{
					axisPos.push_back(10.0);
				}
				else if (j == 3)
				{
					axisPos.push_back(-10.0);

				}
				else
				{
					axisPos.push_back(0.0);
				}
			}
			else if (i == 2)
			{
				if (j == 4)
				{
					axisPos.push_back(10.0);
				}
				else if (j == 5)
				{
					axisPos.push_back(-10.0);

				}
				else
				{
					axisPos.push_back(0.0);
				}
			}
			
		}
		
	}


	// buffer setup for axis
	// holds ID for vertex array object
	unsigned int axisVAO = 0;
	// holds ID for vertex buffer object
	unsigned int axisVBO = 0;

	setupBuffersAxis(axisVAO, axisVBO,axisPos);
	// bool to store wether or not simulator is paused
	bool isPaused = false;

	// variables for input to be stored in for add new body
	glm::dvec3 newPosition = glm::dvec3(0.0, 0.0, 0.0);
	glm::dvec3 newVelocity = glm::dvec3(0.0, 0.0, 0.0);
	double newMass = 0.1;
	glm::vec3 newColor;
	// while the user has not closed the window 
	while (!glfwWindowShouldClose(window))
	{
		 //tells ImGui a new frame is starting
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// set window width and height
		ImGui::SetNextWindowSize(ImVec2(300, 0));
		// start the imgui window
		ImGui::Begin("controls");

		// dropdown for select preset
		const char* presets[6] = { "default","figure 8","lagrange","Broucke","3D","pentagon" };
		// limit width of dropdown 
		ImGui::SetNextItemWidth(100);
		// if dropdown is changed, reload with new preset
		if (ImGui::Combo("select preset", &currentPreset, presets, 6)) 
		{
			simulation.loadPreset(currentPreset);
		}

		// make a collapsable header for each individual bodies controls
		for(int i = 0; i < simulation.bodies.size();i++)
		{
			// string to hold title of collapsable header
			std::string label = "body ";
			label += std::to_string(i);
			// label the header with the string label converted to a c string
			if(ImGui::CollapsingHeader(label.c_str())) 
			{
				// each ImGui widget needs a unique ID
				// create a unique ID for each component of each body by making the x0, x1.. etc
				std::string positionX = "##positionX";
				positionX += std::to_string(i);
				std::string positionY = "##positionY";
				positionY += std::to_string(i);
				std::string positionZ = "##positionZ";
				positionZ += std::to_string(i);

				std::string massLabel = "##mass";

				massLabel += std::to_string(i);
				std::string velocityX = "##velocityX";
				velocityX += std::to_string(i);
				std::string velocityY = "##velocityY";
				velocityY += std::to_string(i);
				std::string velocityZ = "##velocityZ";
				velocityZ += std::to_string(i);
				// text creates label
				// same line makes label appear on the left on the input box
				// input double connects input box to double to edit (component of position)
				// ## prevents label from being diplayed
			
				// controls for position components
				ImGui::Text("position: ");
				ImGui::Text("x: ");
				ImGui::SameLine();
				ImGui::InputDouble(positionX.c_str(), &simulation.bodies[i].position.x);
				ImGui::Text("y: ");
				ImGui::SameLine();
				ImGui::InputDouble(positionY.c_str(), &simulation.bodies[i].position.y);
				ImGui::Text("z: ");
				ImGui::SameLine();
				ImGui::InputDouble(positionZ.c_str(), &simulation.bodies[i].position.z);

				// controls for velocity components
				ImGui::NewLine();
				ImGui::Text("velocity: ");
				ImGui::Text("x: ");
				ImGui::SameLine();
				ImGui::InputDouble(velocityX.c_str(), &simulation.bodies[i].velocity.x);
				ImGui::Text("y: ");
				ImGui::SameLine();
				ImGui::InputDouble(velocityY.c_str(), &simulation.bodies[i].velocity.y);
				ImGui::Text("z: ");
				ImGui::SameLine();
				ImGui::InputDouble(velocityZ.c_str(), &simulation.bodies[i].velocity.z);
	
				// controls for mass
				ImGui::NewLine();
				ImGui::Text("mass: ");
				ImGui::SameLine();
				ImGui::InputDouble(massLabel.c_str(), &simulation.bodies[i].mass);
			
			}
			
		}
		// add body header
		std::string addBody = "add body ";
		if (ImGui::CollapsingHeader(addBody.c_str()))
		{

			

			// create labels for inputs 
			std::string newPositionX = "##newPositionX";
			std::string positionY = "##positionY";
			std::string positionZ = "##positionZ";

			std::string massLabel = "##mass";

			std::string velocityX = "##velocityX";
			std::string velocityY = "##velocityY";
			std::string velocityZ = "##velocityZ";

			// get values for new body
			// get and set newPosition
			ImGui::Text("position: ");
			ImGui::Text("x: ");
			ImGui::SameLine();
			ImGui::InputDouble(newPositionX.c_str(), &newPosition.x);
			ImGui::Text("y: ");
			ImGui::SameLine();
			ImGui::InputDouble(positionY.c_str(), &newPosition.y);
			ImGui::Text("z: ");
			ImGui::SameLine();
			ImGui::InputDouble(positionZ.c_str(), &newPosition.z);

			// get and set newVelocity
			ImGui::NewLine();
			ImGui::Text("velocity: ");
			ImGui::Text("x: ");
			ImGui::SameLine();
			ImGui::InputDouble(velocityX.c_str(), &newVelocity.x);
			ImGui::Text("y: ");
			ImGui::SameLine();
			ImGui::InputDouble(velocityY.c_str(), &newVelocity.y);
			ImGui::Text("z: ");
			ImGui::SameLine();
			ImGui::InputDouble(velocityZ.c_str(), &newVelocity.z);

			// get and set newMass
			ImGui::NewLine();
			ImGui::Text("mass: ");
			ImGui::SameLine();
			ImGui::InputDouble(massLabel.c_str(), &newMass);

			// logic for setting color 	
			// array for colors 
			std::vector<glm::vec3> colors;
			colors.push_back(glm::vec3(0.365f, 0.976f, 1.0f));
			colors.push_back(glm::vec3(0.478f, 1.0f, 0.69f));
			colors.push_back(glm::vec3(1.0f, 0.243f, 0.243f));
			colors.push_back(glm::vec3(0.761, 0.447, 1.0));
			colors.push_back(glm::vec3(1.0, 0.325, 0.898));
			colors.push_back(glm::vec3(0.329, 1, 0.439));
			colors.push_back(glm::vec3(1, 0.976, 0.329));
			colors.push_back(glm::vec3(1, 0.624, 0.329));

			// set bodies color to next color in color array based on how many bodies currently exsist
			int colorIndex = simulation.bodies.size();
			// if there are more bodies in the sim than colors in the array
			if (colorIndex >= colors.size()) 
			{
				// prevent color index from exceeding colors.size()
				colorIndex = simulation.bodies.size() % colors.size();
			}
			newColor = colors[colorIndex];

			// create new body with newPosition and newVelocity
			Body newBody(
				// position
				newPosition,
				// velocity
				newVelocity,
				// acceleration
				glm::dvec3(0.0, 0.0, 0.0),
				// mass
				newMass,
				// color
				newColor
			);
			
			if (ImGui::Button("add body")) 
			{
				// add newBody to sim
				simulation.bodies.push_back(newBody);
			}
			}


		// pause button
		ImGui::Checkbox("paused", &isPaused);
		// reset sim if this button is pressed
		if (ImGui::Button("reset"))
		{
			simulation.loadPreset(currentPreset);
		}

		//end the ImGui window
		ImGui::End();

		

		// indicates color to set background (red,green, blue, alpha) uses 0-1 scale, expects float values
		glClearColor(0.0f, 0.0f, 0.02f, 1.0f);
		// sets the color 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// get view and projection matrix every frame
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = camera.getProjectionMatrix();

		// send camera matrices to the GPU for all shaders
		// glGetUniformLocation() gets view uniform from shader and returns int ID for that variables slot 
		// glUniformMatrix4fv uploads a 4x4 float matrix to that slot on the GPU
		// requires the raw float data of the matrix
		// set shader program
		glUseProgram(bodyShaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(bodyShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(bodyShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// set shader program
		glUseProgram(lineShaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lineShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// draw axis
		// makes our axis VAO currently active
		glBindVertexArray(axisVAO);
		// makes VBO the current active GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
		// upload data
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * axisPos.size(), axisPos.data(), GL_STATIC_DRAW);
		// set axis color
		glUniform3f(glGetUniformLocation(lineShaderProgram, "lineColor"), 0.431, 0.431, 0.431);
		// draw the axis
		glDrawArrays(GL_LINES, 0, axisPos.size() / 3);


		// repeat step forward a few times per frame to control speed
		for (int i = 0; i < 46; i++) {
			if (!isPaused) 
			{
				simulation.stepForward();
			}
		}

		// holds positions and color of bodies
		for (Body& body : simulation.bodies) {
			// get rid of old positions
			bodyPosition.clear();
			// push back 3 floats for position
			bodyPosition.push_back(body.position.x);
			bodyPosition.push_back(body.position.y);
			bodyPosition.push_back(body.position.z);
			// push back 3 floats for color
			//bodyPosition.push_back(body.color.x);
			//bodyPosition.push_back(body.color.y);
			//bodyPosition.push_back(body.color.z);

			// draw bodies
			glUseProgram(bodyShaderProgram);
			// set buffers for body
			glBindVertexArray(bodyVAO);
			glBindBuffer(GL_ARRAY_BUFFER, bodyVBO);
			// set point size
			glPointSize(25.0f);
			glEnable(GL_PROGRAM_POINT_SIZE);
			//set color of body
			glUniform3f(glGetUniformLocation(bodyShaderProgram, "vertexColor"), body.color.x, body.color.y, body.color.z);
			// upload body data into VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bodyPosition.size(), bodyPosition.data(), GL_DYNAMIC_DRAW);
			glDrawArrays(GL_POINTS, 0, 1);

		}

		// make a float vector representing the prevPositions of the bodies
		for (Body& body : simulation.bodies) 
		{
			// if tail vector is too big start deleting the from front element
			// prevents tails from disappearing while paused
			if (body.prevPositions.size() >= 1600 && !isPaused) {
				body.prevPositions.erase(body.prevPositions.begin());
			}
			// add position to prevPostitions to create tail
			body.prevPositions.push_back(body.position);

			// clear before re-using
			tailPosition.clear();
			// loop through prevPositions

			for (glm::vec3 pos : body.prevPositions) 
			{
				// create a tail positions flat float vector for each body
				tailPosition.push_back(pos.x);
				tailPosition.push_back(pos.y);
				tailPosition.push_back(pos.z);
			}
			// set shader program
			glUseProgram(lineShaderProgram);
			// makes our tail VAO currently active
			glBindVertexArray(tailVAO);
			// makes VBO the current active GL_ARRAY_BUFFER
			glBindBuffer(GL_ARRAY_BUFFER, tailVBO);
			// upload this trail info with glVertexAtribPointer
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tailPosition.size(), tailPosition.data(), GL_DYNAMIC_DRAW);
			// set tail thickness
			glLineWidth(3.0f);
			// set color of tail
			glUniform3f(glGetUniformLocation(lineShaderProgram, "lineColor"), body.color.x, body.color.y, body.color.z );
			// draw the tail (tailPosition.size()/3 because its looking for vertices to draw)
			glDrawArrays(GL_LINE_STRIP, 0, tailPosition.size() / 3);
		}
		// render ImGui controls
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// prevents screen from flickering by drawing to a back buffer and then swapping it to the front
		glfwSwapBuffers(window);
		// detects input events, without this line the program wouldnt respond to any input
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}