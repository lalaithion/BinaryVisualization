#include "BV_OpenGL.h"
#include <QtOpenGL>
#include <QMessageBox>
#include <math.h>
#include "image.h"
#include "gradient.h"
#include <typeinfo>

#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

//
///  Constructor with default settings
//
BV_OpenGL::BV_OpenGL(QWidget* parent)
    : QGLWidget(parent)
{
   mode = 0;
   obj  = 0;
   init  = false;
   mouse = false;
   asp = 1;
   dim = 1;
   fov = 0;//55;
   th = ph = 0;
   x0 = y0 = 0;
   z0 = 1;
   zh = 0;
}

//
///  This function sets the vector of gradients to the value passed in
//

void BV_OpenGL::SetGradients(std::vector<Gradient> grads)
{
    gradls = grads;
}

//
///  Reset view
//
void BV_OpenGL::reset()
{
   th = ph = 0;
   dim = 3;
   Projection();
   ///  Request redisplay
   updateGL();
}


//
/// \brief  Set shader
//
void BV_OpenGL::set_dropdown(int sel)
{
    /// initalize array
    float grad_image[256*3];
    /// load selected gradient
    Gradient r = gradls[sel];
    /// get it's texture
    r.getTexture(grad_image);
    /// loop through it, and set the gradient array to have the right values
    for (int k = 0; k < 256; k++) {
         gradient[k] = QVector3D(grad_image[k*3], grad_image[k*3+2], grad_image[k*3+1]);
    }
    mode = sel;
    ///  Request redisplay
    updateGL();
}

//
/// \brief  Set light elevation
//
void BV_OpenGL::set_slider(int Z)
{
   z0 = 0.02*Z;
   ///  Request redisplay
   updateGL();
}

void BV_OpenGL::button_pressed() {
    /// initialize array
    /*
    float image[4*4] = {
        0.5, 0.0, 0.5, 0.0,
        0.0, 0.5, 0.0, 0.5,
        0.5, 0.0, 0.5, 0.0,
        0.0, 0.5, 0.0, 0.5,
    }; */
    float image[256*256];
    //for(int i = 0; i < 256*256; i++) {image[i] = 0;}
    /// get filename with dialog
    QString filename = QFileDialog::getOpenFileName(0, "Select file");//, QDir::homePath());
    /// get image from Image object using a logarithmic normalization
    Image File(filename.toUtf8().data());
    File.getLogNormalizedBuffer(image);
    //glGenTextures(1, &texture);
    //Bind texture (state change - all texture calls now refer to this one specifically)
    glBindTexture(texture,GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D,0,1,256,256,0,GL_LUMINANCE,GL_FLOAT,image);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}

//
/// \brief  Cube Vertexes
//
const int plane_size=6;
const float plane_data[] =  // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B   s t
   //  Front
   +1,+1,0,+1,   0, 0,+1,   1,0,0,  1,1,
   -1,+1,0,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,0,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,+1,0,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,0,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,-1,0,+1,   0, 0,+1,   1,0,0,  0,0,
};

//
///  Initialize
//
void BV_OpenGL::initializeGL()
{
   if (init) return;
   init = true;

   //
   /*float image[256*256];
   QString filename = QFileDialog::getOpenFileName(0, "Select file");//, QDir::homePath());
   Image File(filename.toUtf8().data());
   File.getLogNormalizedBuffer(image);

   glGenTextures(1,&texture);
   //  Bind texture (state change - all texture calls now refer to this one specifically)
   glBindTexture(texture,GL_TEXTURE_2D);
   glTexImage2D(GL_TEXTURE_2D,0,1,256,256,0,GL_LUMINANCE,GL_FLOAT,image);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
*/
   button_pressed();

   float grad_image[256*3];
   Gradient r = gradls[0];
   r.getTexture(grad_image);
   for (int k = 0; k < 256; k++) {
        gradient[k] = QVector3D(grad_image[k*3], grad_image[k*3+2], grad_image[k*3+1]);
   }
   ///  Load shaders
   Shader(shader,":/default.vert",":/default.frag");

   ///  Start 100 fps timer connected to updateGL
   move = true;
   timer.setInterval(10);
   connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
   timer.start();
   time.start();

   ///  Cube vertex buffer object
   ///  Copy data to vertex buffer object
   cube_buffer.create();
   cube_buffer.bind();
   cube_buffer.setUsagePattern(QGLBuffer::StaticDraw);
   cube_buffer.allocate(sizeof(plane_data));
   cube_buffer.write(0,plane_data,sizeof(plane_data));
   ///  Unbind this buffer
   cube_buffer.release();
}

//
/// \brief  Set projection when window is resized
//
void BV_OpenGL::resizeGL(int width, int height)
{
   ///  Window aspect ration
   asp = height ? width / (float)height : 1;
   ///  Viewport is whole screen
   glViewport(0,0,width,height);
   ///  Set projection
   Projection();
}

//
///  \brief Draw the window
//
void BV_OpenGL::paintGL()
{
   ///  Wall time (seconds)
   float t = 0.001*time.elapsed();
   if (move) zh = fmod(90*t,360);

   ///  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   ///  Set view
   glLoadIdentity();
   if (fov) glTranslated(0,0,-2*dim);

   //glRotated(ph,1,0,0);
   //glRotated(th,0,1,0);

   ///  Create Modelview matrix

   QMatrix4x4 mv;
   if (fov) mv.translate(0,0,-2*dim);

   //mv.rotate(ph,1,0,0);
   //mv.rotate(th,0,1,0);


   /// Enable shader
   shader.bind();
   ///  Set Modelview and Projection Matrix
   shader.setUniformValue("ProjectionMatrix",proj);
   shader.setUniformValue("ModelViewMatrix",mv);
   shader.setUniformValue("texture",texture);
   shader.setUniformValueArray("gradient",gradient, 255*3);

   ///  Select cube buffer
   cube_buffer.bind();
   //   Attribute 0: vertex coordinate (vec4) at offset 0
   shader.enableAttributeArray(0);
   //shader.setAttributeArray(shader.attributeLocation("Vertex"));
   //shader.setAttributeArray(shader.attributeLocation("TextureCoords"));
   shader.setAttributeBuffer(shader.attributeLocation("Vertex"),GL_FLOAT,0,4,12*sizeof(float));
   //   Attribute 1:  vertex texture coordinates (vec2) offset 10 floats
   shader.enableAttributeArray(1);
   shader.setAttributeBuffer(shader.attributeLocation("TextureCoords"),GL_FLOAT,10*sizeof(float),2,12*sizeof(float));

   /// Draw the plane
   glDrawArrays(GL_TRIANGLES,0,plane_size);

   /// Disable vertex arrays
   shader.disableAttributeArray(0);
   shader.disableAttributeArray(1);

   ///  Unbind this buffer
   cube_buffer.release();

   /// Back to fixed pipeline
   shader.release();
   
   ///  Emit angles to display
   emit label(QString::number(th));
   ///  Emit light angle
   //emit light((int)zh);
}

//
///  \brief Throw a fatal error and die
//
void BV_OpenGL::Fatal(QString message)
{
   QMessageBox::critical(this,"BV_OpenGL",message);
   QApplication::quit();
}

//
/// \brief  Set OpenGL projection
//
void BV_OpenGL::Projection()
{
   ///  Set fixed pipeline transformation
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fov)
   {
      float zmin = dim/4;
      float zmax = 4*dim;
      float ydim = zmin*tan(fov*M_PI/360);
      float xdim = ydim*asp;
      glFrustum(-xdim,+xdim,-ydim,+ydim,zmin,zmax);
   }
   else
      glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   ///  Set GL4 transformation
   proj.setToIdentity();
   if (fov)
      proj.perspective(fov,asp,dim/4,4*dim);
   else
      proj.ortho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
}

/******************************************************************/
/*************************  Mouse Events  *************************/
/******************************************************************/
//
//  Mouse pressed
//
void BV_OpenGL::mousePressEvent(QMouseEvent* e)
{
   mouse = true;
   pos = e->pos();  //  Remember mouse location
}

//
//  Mouse released
//
void BV_OpenGL::mouseReleaseEvent(QMouseEvent*)
{
    mouse = false;
}

//
//  Mouse moved
//
void BV_OpenGL::mouseMoveEvent(QMouseEvent* e)
{
   if (mouse)
   {
      QPoint d = e->pos()-pos;  //  Change in mouse location
      th = (th+d.x())%360;      //  Translate x movement to azimuth
      ph = (ph+d.y())%360;      //  Translate y movement to elevation
      pos = e->pos();           //  Remember new location
      updateGL();               //  Request redisplay
   }
}

//
//  Mouse wheel
//
void BV_OpenGL::wheelEvent(QWheelEvent* e)
{
   //  Zoom out
   if (e->delta()<0)
      dim += 0.1;
   //  Zoom in
   else if (dim>1)
      dim -= 0.1;
   //  Request redisplay
   Projection();
   updateGL();
}

//
/// \briefLoad shader
//
void BV_OpenGL::Shader(QGLShaderProgram& shader,QString vert,QString frag)
{
   //  Vertex shader
   if (vert.length() && !shader.addShaderFromSourceFile(QGLShader::Vertex,vert))
      Fatal("Error compiling "+vert+"\n"+shader.log());
   //  Fragment shader
   if (frag.length() && !shader.addShaderFromSourceFile(QGLShader::Fragment,frag))
      Fatal("Error compiling "+frag+"\n"+shader.log());
   //  Link
   if (!shader.link())
      Fatal("Error linking shader\n"+shader.log());
}
