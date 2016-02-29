//  Basic fragment shader

uniform sampler2D texture;
varying vec2 texpos;

void main()
{
    vec4 color = texture2D(texture,texpos);
    color.r = 1.0;
    gl_FragColor = color;
}
