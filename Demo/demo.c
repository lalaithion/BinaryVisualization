#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
   #include <GLUT/glut.h>
#else
   #include <GL/glut.h>
#endif

#define GL_GLEXT_PROTOTYPES

#define DX 16 //  X dimension
#define DY 16 //  Y dimension

int asp = 1;                        //  Aspect ratio
char* filename = "testFile.txt";    //  Filename in
unsigned int  texture;              //  32-bit location of texture representing the final graph
unsigned char image[DX * DY * 3];   //  Buffer holding the final image

void generateTexture(); //  Convert image[] into a texture
void display();
int readFile();

int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   //  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //  Not nessessary right now, but leaving it here in case it becomes nessessary later
   glutInitWindowSize(300, 300);
   glutCreateWindow("Texture Demo");
   
   glEnable(GL_TEXTURE_2D); //  Allows for textures to be used
   glOrtho(-asp,+asp,-1,1,-1,1); //  Orthographic projection - sets the size of the camera
   
   memset(image,0,DX * DY); //  Clear buffer
   
   readFile();
   generateTexture();
   
   glutDisplayFunc(display); //  Uses function to redisplay
   glutMainLoop(); //  Prevents program from closing
   
   return 0;
}

int readFile() {
   #define BLOCK_SIZE 32
   FILE* fp = fopen( filename, "rb" ); // "rb" is "read binary"
   
   /*
   //  Find size of file - probably useful later
   fseek(fp, 0, SEEK_END); //  Limited at 2GB
   int size = ftell(fp);   
   rewind(fp)              //  Set filestream back to start
   */
   
   int length = 0; //  Used to prevent reading from beyond the end of the file
   unsigned char* buf = malloc(BLOCK_SIZE);
   while( (length = fread(buf, 1, BLOCK_SIZE, fp)) ) { //  fread( destination, element size, bytes, filestream ) returns the number of bytes read
      int i;
      for (i = 0; i < length - 1; i++) {
         //  Converts from 1D character array to 3D RGB array
         int x = buf[i] % DX;
         int y = (buf[i + 1] % DY) * DY;
         int color = 2; //  Each location has a RGB componenet: R=0, G=1, B=2
         image[(x + y) * 3 + color] = 255; //  Currently only colors any hit at all to be pure blue, instead of drawing gradients based on frequency
      }
   }
   free(buf);
   fclose( fp );
   
   return 0;
}

/*
 *  Converts image[] array into RGB texture
 */
void generateTexture() {
   //  Create texture location
   glGenTextures(1,&texture);
   //  Bind texture (state change - all texture calls now refer to this one specifically)
   glBindTexture(GL_TEXTURE_2D,texture);
   
   //  Copy image
   glTexImage2D(GL_TEXTURE_2D,0,3,DX,DY,0,GL_RGB,GL_UNSIGNED_BYTE,image);
   
   //  Scale linearly when image size doesn't match
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
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