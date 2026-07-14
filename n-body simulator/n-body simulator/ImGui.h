#pragma once
#include "body.h"
#include "simulation.h"
// imgui controls
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void ImGuiControls(Simulation& simulation, int& currentPreset,
	bool& isPaused, glm::dvec3& newPosition, glm::dvec3& newVelocity,
	double& newMass, glm::vec3& newColor, Camera& camera, int& simulationSpeed)
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
	for (int i = 0; i < simulation.bodies.size();i++)
	{
		// string to hold title of collapsable header
		std::string label = "body ";
		label += std::to_string(i);
		//controls for pos and vel for individual bodies
		// label the header with the string label converted to a c string
		if (ImGui::CollapsingHeader(label.c_str()))
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


		// set bodies color to next color in color array based on how many bodies currently exsist
		int colorIndex = simulation.bodies.size();
		// if there are more bodies in the sim than colors in the array
		if (colorIndex >= simulation.colors.size())
		{
			// prevent color index from exceeding colors.size()
			colorIndex = simulation.bodies.size() % simulation.colors.size();
		}
		newColor = simulation.colors[colorIndex];

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

	// control speed of simulation
	ImGui::Text("speed: ");
	ImGui::SameLine();
	ImGui::SliderInt("##speed", &simulationSpeed, 1, 1000);

	// energy
	ImGui::Text("total energy: %f", simulation.currentEnergy);
	double drift = abs(simulation.initialEnergy - simulation.currentEnergy)
		/ abs(simulation.initialEnergy) * 100;
	ImGui::Text("energy drift: %f", drift);

	// reset sim if this button is pressed
	if (ImGui::Button("reset"))
	{
		simulation.loadPreset(currentPreset);
		camera.yaw = 0.0f;
		camera.pitch = 0.0f;
		camera.updateOrbit();
		simulationSpeed = 60;
	}

	//end the ImGui window
	ImGui::End();
}