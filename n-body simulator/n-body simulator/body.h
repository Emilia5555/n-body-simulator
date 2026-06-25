#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Body 
{
	// double precision vector
	glm::dvec3 position;
	glm::dvec3 velocity;
	glm::dvec3 acceleration;
	double mass;
	glm::vec3 color;
	std::vector<glm::vec3> prevPositions;

};