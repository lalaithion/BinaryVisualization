#include "TextureWidget.h"
#include <errno.h>
#include <QPushButton>
#include <iostream>
#include <QGridLayout>

using namespace std;

TextureWidget::TextureWidget(char* file){
    /*glutInit(&argc,argv);
    //  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //  Not necessary right now, but leaving it here in case it becomes necessary later
    glutInitWindowSize(512, 512);
    glutCreateWindow(filename);*/
    asp = 1;
    filename = file;
    /*QWidget window;
    window.resize(512, 512);
    window.show();
    window.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));*/

    glEnable(GL_TEXTURE_2D); //  Allows for textures to be used
    glOrtho(-asp,+asp,-1,1,-1,1); //  Orthographic projection (as opposed to perspective)
                                  //  sets the size of the camera

    memset(image,0,DX * DY * 3); //  Clear buffer
    //readFile();
    //generateTexture();
    //display();
}

void TextureWidget::generateTexture() {
   cout<<"Blaaah"<<endl;
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

void TextureWidget::display()
{
   cout<<"Blaaah"<<endl;
   glClear(GL_COLOR_BUFFER_BIT); //  Refreshes colors
   glColor3f(0,0,0); //  Colored white so that texture will show up

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

int TextureWidget::readFile() {
   #define BLOCK_SIZE 32
    cout<<"Blaaah"<<endl;
    if(filename == NULL) {
     printf("Please input a file\n");
     return 0;
    }
   FILE* fp = fopen(filename, "rb" ); // "rb" is "read binary"
   if(!fp) {
    printf("File not valid: %s %s\n", strerror(errno), filename);
    exit(0);
   }
   /*
   //  Find size of file - probably useful later
   fseek(fp, 0, SEEK_END); //  Limited at 2GB
   int size = ftell(fp);
   rewind(fp)              //  Set filestream back to start
   */

   int length = 0; //  Used to prevent reading from beyond the end of the file
   unsigned char* buf = (unsigned char*)(malloc(BLOCK_SIZE));
   while( (length = fread(buf, 1, BLOCK_SIZE, fp)) ) { //  fread( destination, element size, bytes, filestream ) returns the number of bytes read
      int i;
      for (i = 0; i < length - 1; i++) {
         //  Converts from 1D character array to 3D RGB array
         int x = buf[i];
         int y = (buf[i + 1]) * DY ;

         if(image[(x + y ) * 3 + 2] == 0) {
            image[(x + y) * 3 + 2] = 255;
         }
         else if(image[(x + y) * 3 + 1] == 0) {
            image[(x + y) * 3 + 1] = 255;
         }
         else if(image[(x + y) * 3 + 0] == 0) {
            image[(x + y) * 3 + 0] = 255;
         }
         //int color = 2; //  Each location has a RGB componenet: R=0, G=1, B=2
         //image[(x + y) * 3 + color] = 255; //  This is the only blue mode coloring
      }
   }
   free(buf);
   fclose( fp );

   return 0;
}

