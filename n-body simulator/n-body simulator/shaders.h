#pragma once

// vertex shader
// R prefix for raw string literal
const char* vertexShaderSource = R"(
// use version 3.3 core
#version 330 core
// creates input varialbe aPos (vec3) at location 0
layout (location = 0) in vec3 aPos;
// creates input varialbe color (vec3) at location 1
layout (location = 1) in vec3 inColor;
out vec3 vertexColor;


// hold the view and projection matrixes i create in camera.h
uniform mat4 view;
uniform mat4 projection;

// main function, runs for every vertex
void main(){
	// matricex mutiplication applies left to right
	// first view makes the world space into camera space
	// then projection makes camera space clip space
	// mutiplying by a matrix is applying a linear transformation
	gl_Position = projection * view * vec4(aPos, 1.0);
	// set output color equal to the input color
	vertexColor = inColor; 
};
)";

// fragmagment shaders
const char* bodyFragmentShaderSource = R"(
	// use version 3.3 core
	#version 330 core
	// creates a vec4 output varaible called FragColor
	out vec4 FragColor;
	uniform vec3 vertexColor;

	void main(){
		// dont render anything outside 0.5 from the point center
		if (distance(gl_PointCoord,vec2(0.5,0.5)) > 0.5)
		{
			discard;
		}
		// sets FragColor color 
		FragColor = vec4(vertexColor,1.0);
	}

)";

const char* lineFragmentShaderSource = R"(
	// use version 3.3 core
	#version 330 core
	// creates a vec4 output varaible called FragColor
	out vec4 FragColor;
	uniform vec3 lineColor;

	void main(){
	
		// sets FragColor color 
		FragColor = vec4(lineColor, 1.0);
	}

)";

