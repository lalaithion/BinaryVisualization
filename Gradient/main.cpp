#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "CSCIx239.h"
#include "interpolate.h"
#include "gradient.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define GL_GLEXT_PROTOTYPES

#define DX 256 //  X dimension
#define DY 256 //  Y dimension

int asp = 1;                        //  Aspect ratio
char* filename;    //  Filename in
unsigned int  texture;              //  32-bit location of texture representing the final graph
unsigned char image[DX * DY * 3];   //  Buffer holding the final image
int shader = 0; //  Shader program

void generateTexture(); //  Convert image[] into a texture
void display(); //  Draws the object the texture is rendered onto
int readFile(); //  reads the file in and converts it into image[]

int main(int argc,char* argv[])
{
    Gradient test ("test3.gradient");

    glutInit(&argc,argv);
    //  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //  Not nessessary right now, but leaving it here in case it becomes nessessary later
    glutInitWindowSize(512, 512);
    glutCreateWindow(test.getName().c_str());

    glEnable(GL_TEXTURE_2D); //  Allows for textures to be used
    glOrtho(-asp,+asp,-1,1,-1,1); //  Orthographic projection (as opposed to perspective)
    //  sets the size of the camera

    shader = CreateShaderProg("basic.vert","basic.frag"); 
    glUseProgram(shader);
    int id = glGetUniformLocation(shader,"texture");
    if (id>=0) glUniform1f(id,0);

    float array[256*3];

    test.getTexture(array);

    int gradloc = glGetUniformLocation(shader, "gradient");
    glUniform1fv(gradloc, 256*3, array);

    memset(image,0,DX * DY * 3); //  Clear buffer

    glutDisplayFunc(display); //  Uses function to redisplay
    glutMainLoop(); //  Prevents program from closing

    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); //  Refreshes colors
    glColor3f(1,1,1); //  Colored white so that texture will show up


    //  Draws a square in front of the camera
    glBegin(GL_QUADS);

    glTexCoord2d(1,0);
    glVertex2f( 1,-1);

    glTexCoord2d(1,1);
    glVertex2f( 1, 1);

    glTexCoord2d(0,1);
    glVertex2f(-1, 1);

    glTexCoord2d(0,0);
    glVertex2f(-1,-1);

    glEnd();


    glFlush(); //  Outputs to screen
}
