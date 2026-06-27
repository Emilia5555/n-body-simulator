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
	
	// binary plus orbiter
	if (presetIndex == 0){
		bodies.clear();
		Body body1(
			// position
			glm::dvec3(-0.5, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, -0.5, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			glm::vec3(0.0, 0.0, 1.0)
		);
		Body body2(
			// position
			glm::dvec3(0.5, 0.0, 0.0),
			// velocity
			glm::dvec3(0.0, 0.5, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			1.0,
			// color
			glm::vec3(0.0, 1.0, 0.0)
		);

		Body body3(
			// position
			glm::dvec3(0.0, 0.8, 0.0),
			// velocity
			glm::dvec3(0.0, -0.0, 0.0),
			// acceleration
			glm::dvec3(0.0, 0.0, 0.0),
			// mass
			0.1,
			// color
			glm::vec3(1.0, 0.0, 0.0)
		);

		bodies.push_back(body1);
		bodies.push_back(body2);
		bodies.push_back(body3);
	}


}