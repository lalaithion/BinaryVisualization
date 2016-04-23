#version 430 core

//  Transformation matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec2 TextureCoords;

//  Output to next shader
out vec2 fragment_texture_coordinates;

void main()
{
   //  Set transformed vertex location
   fragment_texture_coordinates = TextureCoords;
   gl_Position =  ProjectionMatrix * ModelViewMatrix * Vertex;
}
