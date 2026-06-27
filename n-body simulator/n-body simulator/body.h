#pragma once
#include <glm/glm.hpp>
#include <vector>

class Body 
{
public:
	// double precision vector
	glm::dvec3 position;
	glm::dvec3 velocity;
	glm::dvec3 acceleration;
	double mass;
	glm::vec3 color;
	std::vector<glm::vec3> prevPositions;

	// default constructor
	Body()
	{
		position = glm::dvec3(0.0, 0.0, 0.0);
		velocity = glm::dvec3(0.0, 0.0, 0.0);
		acceleration = glm::dvec3(0.0, 0.0, 0.0);
		mass = 0.1;
		color = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	// constructor
	Body(glm::dvec3 pos, glm::dvec3 vel, glm::dvec3 acc, double iMass, glm::vec3 iColor) 
	{
		position = pos;
		velocity = vel;
		acceleration = acc;
		mass = iMass;
		color = iColor;
	}

};