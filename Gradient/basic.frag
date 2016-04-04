//  Basic fragment shader

uniform sampler2D texture;
uniform float gradient[256*3];
varying vec2 texpos;


void main()
{
    float color = texpos.x;
    int level = int(floor(color*255.0));
    vec4 newcolor;
    newcolor.r = gradient[level*3];
    newcolor.g = gradient[(level*3)+1];
    newcolor.b = gradient[(level*3)+2];
    gl_FragColor = newcolor;
}
