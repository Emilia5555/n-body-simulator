#pragma once
#include "body.h"


class Simulation {
public:
	std::vector<Body> bodies;
	double gravity = 1.0;
	// timestep
	double dt = 0.0001;
	double softening = 0.2;
	double simulationTime;

	double initialEnergy;
	double currentEnergy;

	// advances the simulation by one frame
	void stepForward();

	// reloads current preset
	// presetIndex: which preset to re-load
	void reset(int presetIndex);

	// calculates the total mechanical energy of the system
	// returns total energy
	double computeEnergy();

	// clears the bodies vector and fills it with the starting info for the given preset
	// presetIndex: which preset to load
	void loadPreset(int presetIndex);
	
	// array for colors 
	std::vector<glm::vec3> colors = {
		glm::vec3(0.365f, 0.976f, 1.0f),
		glm::vec3(0.478f, 1.0f, 0.69f),
		glm::vec3(1.0f, 0.243f, 0.243f),
		glm::vec3(0.761, 0.447, 1.0),
		glm::vec3(1.0, 0.325, 0.898),
		glm::vec3(0.329, 1, 0.439),
		glm::vec3(1, 0.976, 0.329),
		glm::vec3(1, 0.624, 0.329)
	};

};