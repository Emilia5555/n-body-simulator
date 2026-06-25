#pragma once
#include "body.h"

class Simulation {
public:
	std::vector<Body> bodies;
	double gravity = 1.0;
	// timestep
	double dt = 0.0001;
	double softening = 0.01;
	double simulationTime;

	double initialEnergy;
	double currentEnergy;

	void stepForward() {
		simulationTime++;
	}

	void loadPreset(int presentIndex) {

	}


};