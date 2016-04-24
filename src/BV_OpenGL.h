#ifndef BV_OPENGL_H
#define BV_OPENGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include <QMatrix4x4>
#include <gradient.h>

class BV_OpenGL : public QGLWidget
{
Q_OBJECT
private:
   bool    init;      //  Initialized
   bool    move;      //  Light animation
   int     obj;       //  Object
   float   zh;        //  Light position
   float   x0,y0;     //  Object center
   float   z0;        //  Zoom
   int     mode;      //  Display mode
   int     th,ph;     //  Display angles
   bool    mouse;     //  Mouse pressed
   QPoint  pos;       //  Mouse position
   int     fov;       //  Field of view
   double  dim;       //  Display size
   double  asp;       //  Sceen aspect ratio
   unsigned int tex;  //  Textures
   QGLBuffer cube_buffer;     //  Vertex buffer
   QMatrix4x4       proj;     //  Projection matrix
   QGLShaderProgram shader;   //  Shader
   QTimer           timer;    //  Timer for animations
   QElapsedTimer    time;     //  Track elapsed time
   GLuint texture;
   QVector3D gradient[256];
   std::vector<Gradient> gradls;
public:
   BV_OpenGL(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
   void SetGradients(std::vector<Gradient>);
public slots:
    void set_dropdown(int sel);               //  Slot to set shader
    void set_slider(int z);                   //  Slot to light elevation (%)
    void button_pressed();            //  Slot to set light movement
    void reset();                          //  Reset view
signals:
    void test_label(QString text);             //  Signal for view angles
    void light(int);                       //  Light position
protected:
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
    void mousePressEvent(QMouseEvent*);    //  Mouse pressed
    void mouseReleaseEvent(QMouseEvent*);  //  Mouse released
    void mouseMoveEvent(QMouseEvent*);     //  Mouse moved
    void wheelEvent(QWheelEvent*);         //  Mouse wheel
private:
   void Fatal(QString message);            //  Error handler
   void Projection();                      //  Update projection
   void Shader(QGLShaderProgram& shader,QString vert,QString frag);  //  Create shader
};

#endif
