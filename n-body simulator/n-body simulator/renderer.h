#pragma once
#include <glad/glad.h>
#include <vector>


// creates and configures VAO and VBO for bodies
// deletes anything in buffer objects before creating new ones
// VAO: int to hold vertex array object ID
// VBO: int to hold vertex buffer object ID
// positionAndColor: vector of floats, used to allocate GPU memory to hold position and color of bodies
void setupBuffersBody(unsigned int& VAO, unsigned int& VBO, std::vector<float>& positionAndColor)
{
	// clear anything that was in the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// generates ID for vertex array object and stores in VAO
	glGenVertexArrays(1, &VAO);
	// generates ID for vertex buffer object and stores in VBO
	glGenBuffers(1, &VBO);

	// makes our VAO currently active
	glBindVertexArray(VAO);
	// makes VBO the current active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// upload planet data into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionAndColor.size(), positionAndColor.data(), GL_DYNAMIC_DRAW);

	// tells openGL that VBO has position data at location 0, which is the 3 floats with no offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	// enables input slot 0
	glEnableVertexAttribArray(0);
	// enables input slot 1
	glEnableVertexAttribArray(1);

	// unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// creates and configures VAO and VBO for tails
// deletes anything in buffer objects before creating new ones
// VAO: int to hold vertex array object ID
// VBO: int to hold vertex buffer object ID
// tailPositionsAndColor: float vector with position and color data of tails
void setupBuffersTail(unsigned int& VAO, unsigned int& VBO, std::vector<float> tailPositionsAndColor)
{
	// clear anything that was in the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// generates ID for vertex array object and stores in VAO
	glGenVertexArrays(1, &VAO);
	// generates ID for vertex buffer object and stores in VBO
	glGenBuffers(1, &VBO);

	// makes our VAO currently active
	glBindVertexArray(VAO);
	// makes VBO the current active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// allocates space for tail position vector
	glBufferData(GL_ARRAY_BUFFER, tailPositionsAndColor.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	// tells openGL that VBO has position data at location 0, which is the 3 floats with no offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// enables input slot 0
	glEnableVertexAttribArray(0);
	
	// enables input slot 1
	glEnableVertexAttribArray(1);

	// unbind VAO and VBO 
	// binding 0 is unbinding
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// creates and configures VAO and VBO for tails
// deletes anything in buffer objects before creating new ones
// VAO: int to hold vertex array object ID
// VBO: int to hold vertex buffer object ID
// axisPosAndColor: float vector with position and color data of axis
void setupBuffersAxis(unsigned int& VAO, unsigned int& VBO, std::vector<float> axisPosAndColor) {
	// clear anything that was in the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// generates ID for vertex array object and stores in VAO
	glGenVertexArrays(1, &VAO);
	// generates ID for vertex buffer object and stores in VBO
	glGenBuffers(1, &VBO);

	// makes our VAO currently active
	glBindVertexArray(VAO);
	// makes VBO the current active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// allocates space for tail position vector
	glBufferData(GL_ARRAY_BUFFER, axisPosAndColor.size() * sizeof(float), axisPosAndColor.data(), GL_STATIC_DRAW);

	// tells openGL that VBO has position data at location 0, which is the 3 floats with no offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// enables input slot 0
	glEnableVertexAttribArray(0);

	// enables input slot 1
	glEnableVertexAttribArray(1);

	// unbind VAO and VBO 
	// binding 0 is unbinding
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}