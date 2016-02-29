//  Basic fragment shader

uniform sampler2D texture;
varying vec2 texpos;

void main()
{
    vec4 color = texture2D(texture,texpos);
    gl_FragColor = color;
}
