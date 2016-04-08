//  Basic vertex shader

varying vec2 texpos;

void main()
{
    //  Set vertex coordinates
    texpos = gl_MultiTexCoord0.st; //get first two elements
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
