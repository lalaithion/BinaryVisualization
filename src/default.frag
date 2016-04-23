#version 430 core

//  Textures
uniform sampler2D texture;
//uniform sampler1D gradient;

uniform vec3 gradient[256];

//  Input from previous shader
in vec2 fragment_texture_coordinates;

//  Fragment color
layout (location=0) out vec4 Fragcolor;

void main()
{

   float frequency = texture2D(texture, fragment_texture_coordinates).r;
   //vec4  grad = texture1D(gradient, frequency);
   Fragcolor = vec4(gradient[int(frequency * 256)], 1.0);
   //else

   //Fragcolor = vec4(frequency, 0.0, 1.0, 1.0);
}
