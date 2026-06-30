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


};