#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <QtGui>
#include <QApplication>
#include <QWidget>
//#include "TextureWidget.h"
#include "displaywidget.h"
//#include "main.h"


/*#ifdef __APPLE__
   #include <GLUT/glut.h>
#else
   #include <GL/glut.h>
#endif*/

using namespace std;
/*
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);
    if(argc == 1){
        cout<<"Usage: Please give a filename."<<endl;
        return 0;
    }
    TextureWidget* myTextureWidget = new TextureWidget(argv[1]);
    //myTextureWidget->show();
    DisplayWidget* disp = new DisplayWidget(myTextureWidget);
    disp->show();
   /*glutDisplayFunc(display); //  Uses function to redisplay
   glutMainLoop(); //  Prevents program from closing
   To display stuff, OpenGL needs something called a "context." Qt has a class that handles this, called QOpenGLContext.
   */
   //The equivalent of glutMainLoop is returning app.exec(), since that won't return until the user closes the application in the normal ways.
/*
   return app.exec();
}


/*
 *  Converts image[] array into RGB texture
 */
/*
void generateTexture() {
   //  Create texture location
   glGenTextures(1,&texture);
   //  Bind texture (state change - all texture calls now refer to this one specifically)
   glBindTexture(GL_TEXTURE_2D,texture);

   //  Copy image
   glTexImage2D(GL_TEXTURE_2D,0,3,DX,DY,0,GL_RGB,GL_UNSIGNED_BYTE,image);

   //  Scale linearly when image size doesn't match
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
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
*/

