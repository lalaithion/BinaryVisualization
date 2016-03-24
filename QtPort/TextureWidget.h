#ifndef TEXTUREWIDGET_H
#define TEXTUREWIDGET_H

#include <QtGui>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QMatrix4x4>
//#include "main.h"
#define DX 512
#define DY 512

class TextureWidget : public QWidget
{
Q_OBJECT
public:
   int asp;                        //  Aspect ratio
   char* filename;    //  Filename in
   unsigned int  texture;              //  32-bit location of texture representing the final graph
   unsigned char image[DX * DY * 3];   //  Buffer holding the final image
   int gArgc; //Global variable storing argc
   char* gArgv[]; //Global variable storing argv
   TextureWidget(char *file);                  //  Constructor
protected:
   void generateTexture(); //  Convert image[] into a texture
   void display(); //  Draws the object the texture is rendered onto
   int readFile(); //  reads the file in and converts it into image[]
};

#endif
