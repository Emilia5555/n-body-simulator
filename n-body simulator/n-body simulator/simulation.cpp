#include "simulation.h"
#include "body.h"

// adjusts each bodies position by calculating the forces acting it 
void Simulation::stepForward()
{

	for (Body& body : bodies)
	{
		// update position based on current data
		glm::dvec3 newPosition = body.position + body.velocity * dt
			+ 0.5 * body.acceleration * dt * dt;
		body.position = newPosition;
		// update half velocity based on current data
		glm::dvec3 newVelocity = body.velocity + dt * 0.5 * body.acceleration;
		body.velocity = newVelocity;
		// make acceleration 0
		body.acceleration = glm::dvec3(0.0, 0.0, 0.0);
	}
	// loop through 0 to n bodies (i)
	for (int i = 0; i < bodies.size(); i++) {
		// loop through 1 to n bodies (j)
		for (int j = i + 1; j < bodies.size(); j++) {
			// get distance between two bodies
			// position of body2 - position of body1
			glm::dvec3 distance = bodies[j].position - bodies[i].position;
			// get magnitude of distance
			double magnitude = glm::length(distance);
			// get direction of distance
			glm::dvec3 direction = distance / magnitude;

			// calculate force between i and j
			// F = G * m1 * m2 / (radius * radius + softening)
			double force = gravity * bodies[i].mass * bodies[j].mass /
				(magnitude * magnitude + softening);

			// calculate acceleration for i and j
			// apply acceleration to i and j
			bodies[i].acceleration += direction * (force / bodies[i].mass);
			bodies[j].acceleration += -direction * (force / bodies[j].mass);


		}
	}

	for (Body& body : bodies)
	{
		// calculate new velocity with info from forces
		// update half velocity and with new data
		glm::dvec3 newVelocity = body.velocity + dt * 0.5 * body.acceleration;
		body.velocity = newVelocity;
	}
}

void Simulation::loadPreset(int presetIndex) {

	// test preset
	if (presetIndex == 0) {
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(-4.0, -4.0, 0.0),
			// velocity
			glm::dvec3(0.05, -0.05, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[0]

		);
		Body body2(
			// position
			glm::dvec3(4.0, 4.0, 0.0),
			// velocity
			glm::dvec3(-0.05, 0.05, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[1]
		);

		Body body3(
			// position
			glm::dvec3(-2.0, 2.0, 0.0),
			// velocity
			glm::dvec3(-0.05, 0.05, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[2]

		);
		Body body4(
			// position
			glm::dvec3(2.0, -2.0, 0.0),
			// velocity
			glm::dvec3(0.05, -0.05, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[3]
		);

		Body body5(
			// position
			glm::dvec3(0.0, -1.0, 0.0),
			// velocity
			glm::dvec3(0.0, 0.0, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[4]
		);
		Body body6(
			// position
			glm::dvec3(0.0, 1.0, 0.0),
			// velocity
			glm::dvec3(0.0, 0.0, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[5]
		);

		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
		bodies.push_back(body4);
		//bodies.push_back(body5);
		//bodies.push_back(body6);
	}

	// figure 8 preset 
	if (presetIndex == 1) {
		softening = 0.0;
		dt = 0.00005;
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(0.97000436, -0.24308753, 0.0),
			// velocity
			glm::dvec3(0.466203685, 0.43236573, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[0]
		);
		Body body2(
			// position
			glm::dvec3(-0.97000436, 0.24308753, 0.0),
			// velocity
			glm::dvec3(0.466203685, 0.43236573, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[1]
		);

		Body body3(
			// position
			glm::dvec3(0.0, 0.0, 0.0),
			// velocity
			glm::dvec3(-0.93240737, -0.86473146, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[2]

		);

		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
	}

	// lagrange
	if (presetIndex == 2) {
		softening = 0.1;
		dt = 0.0005;
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(3.0, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, 0.5, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[0]
		);
		Body body2(
			// position
			glm::dvec3(-1.5, 2.598076211353316, 0.0),
			// velocity
			glm::dvec3(-0.43301270189221935, -0.25, 0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[1]
		);

		Body body3(
			// position
			glm::dvec3(-1.5, -2.598076211353316, 0.0),
			// velocity
			glm::dvec3(0.43301270189221935, -0.25, 0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[2]

		);

		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
	}
	// Broucke
	if (presetIndex == 3) {
		softening = 0.0;
		dt = 0.000075;
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(0.0132604844, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, 1.054151921, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[0]
		);
		Body body2(
			// position
			glm::dvec3(1.4157286016, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, -0.8440052572, 0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[1]
		);

		Body body3(
			// position
			glm::dvec3(-1.4157286016, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, -0.2101466639, 0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[2]

		);

		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
	}
	// O2(1.2)
	if (presetIndex == 4) {
		softening = 0.0;
		dt = 0.000075;
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(-1.0, 0.0, 0.0),
			// velocity
			glm::dvec3(-0.272600007460296, -0.432093711947155, 0.629473407171139),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[0]
		);
		Body body2(
			// position
			glm::dvec3(1.0, 0.0, 0.0),
			// velocity
			glm::dvec3(-0.272600007460296, -0.432093711947155, -0.629473407171139),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[1]
		);

		Body body3(
			// position
			glm::dvec3(0.0, 0.0, 1.02200578272669),
			// velocity
			glm::dvec3(0.45433334576716, 0.7201561865785917, 0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.2,
			// color
			colors[2]

		);

		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
	}
	// pentagon
	if (presetIndex == 5) {
		softening = 0.0;
		dt = 0.0001;
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(3.0, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, 0.45, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[0]
		);
		Body body2(
			// position
			glm::dvec3(0.9270509831248424, 2.8531695488854605, 0.0),
			// velocity
			glm::dvec3(-0.4279754323328191, 0.13905764746872637, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[1]
		);

		Body body3(
			// position
			glm::dvec3(-2.427050983124842, 1.7633557568774196, 0.0),
			// velocity
			glm::dvec3(-0.26450336353161297, -0.3640576474687263, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[2]
		);

		Body body4(
			// position
			glm::dvec3(-2.427050983124843, -1.7633557568774196, 0.0),
			// velocity
			glm::dvec3(0.26450336353161297, -0.3640576474687263, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[3]
		);

		Body body5(
			// position
			glm::dvec3(0.9270509831248417, -2.853169548885461, 0.0),
			// velocity
			glm::dvec3(0.42797543233281915, 0.13905764746872626, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			colors[4]
		);
		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
		bodies.push_back(body4);
		bodies.push_back(body5);
	}

	initialEnergy = computeEnergy();
}

double Simulation::computeEnergy()
{
	double totalKE = 0;
	double totalPE = 0;
	// loop over all bodies to add up all the KE
	for (Body body : bodies)
	{
		// 1/2 * mass * velocity^2
		// dot product for velocity to multiply vectors correctly
		totalKE += (0.5) * body.mass * glm::dot(body.velocity, body.velocity);
	}
	// loop over all bodies in pairs to calculate PE
	for (int i = 0; i < bodies.size(); i++)
	{
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body body1 = bodies[i];
			Body body2 = bodies[j];
			// -g*m1*m2 / r
			totalPE += ((-gravity * body1.mass * body2.mass)
				/ glm::distance(body1.position, body2.position));
		}

	}

	return totalKE + totalPE;
}