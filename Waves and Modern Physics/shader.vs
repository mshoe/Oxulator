#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;	// The color variable has attribute position 1
  
out vec3 ourColor; // Output a color to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float xPos;

void main()
{
    gl_Position = projection * view * model * vec4(position.x + xPos, position.y, position.z, 1.0);
    ourColor = color; // Set ourColor to the input color we got from the vertex data
}       