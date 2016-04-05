#include "openglwindow.h"
#include "readfile.h"

#include <QtGui/QGuiApplication>
#include <QApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QPushButton>
#include <QGridLayout>
#include <QtWidgets>

#include <QtCore/qmath.h>

char* filename;
unsigned char* publicImage;

class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    GLuint m_posAttr;
    GLuint m_texAttr;
    GLuint m_textureUniform;


    QOpenGLShaderProgram *m_program;
    int m_frame;
};

TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
{
    QComboBox* shader = new QComboBox();
    shader->addItem("Fixed Pipeline");
    shader->addItem("Programmable Pipeline");

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(new QLabel("Projection"),1,1);
    layout->addWidget(shader,1,2);
    //setLayout(layout);

}

/*int readFile(char* filename) {
    #define BLOCK_SIZE 32
    if(filename == NULL) {
        cout<<"Please input a file."<<endl;
        exit(0);
    }
    //FILE* fp = fopen(filename, "rb" ); // "rb" is "read binary"
    ifstream fp;
    fp.open(filename);
    if(!fp) {
        cout<<"File not valid: "<<strerror(errno)<<" "<<filename<<endl;
        exit(0);
    }

    int length = 0; //  Used to prevent reading from beyond the end of the file
    while(!fp.eof()) {
        char* buf = new(nothrow) char[BLOCK_SIZE];
        if(buf == NULL) {
            cout<<"Buffer allocation failed in readFile"<<endl;
            exit(0);
        }
        fp.read(buf, BLOCK_SIZE);
        length += BLOCK_SIZE;
        cout<<"Squid"<<endl;

       for (int i = 0; i < sizeof(buf)/sizeof(unsigned char); i++) {
          //  Converts from 1D character array to 3D RGB array
           cout<<buf[i]<<endl;
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
       delete(buf);
    }
    fp.close();

    return 0;
}*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    char* filename = argv[1];
    fileReader reader;
    reader.readFile(filename);
    publicImage = reader.getImage();
    //QSurfaceFormat format;
    //format.setSamples(16);

    TriangleWindow window;
    //window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(false);
    /*QWidget window2;

       QLabel *queryLabel = new QLabel(
           QApplication::translate("Input Binary", "Binary:"));
       QLineEdit *queryEdit = new QLineEdit();


       QHBoxLayout *queryLayout = new QHBoxLayout();
       queryLayout->addWidget(queryLabel);
       queryLayout->addWidget(queryEdit);

       QVBoxLayout *mainLayout = new QVBoxLayout();
       mainLayout->addLayout(queryLayout);
       window2.setLayout(mainLayout);

       // Set up the model and configure the view...
       window2.setWindowTitle(
           QApplication::translate("Input", "Input Binary"));
       window2.show();*/
    return app.exec();
}

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute highp vec4 texAttr;\n"
    "varying lowp vec2 texCoord;\n"
    "void main() {\n"
    "   texCoord = texAttr.xy;\n"
    "   gl_Position = posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec2 texCoord;\n"
    "uniform lowp sampler2D tex;\n"
    "void main() {\n"
    "   gl_FragColor = texture2D(tex, texCoord);\n"
    "}\n";

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_texAttr = m_program->attributeLocation("texAttr");
    m_textureUniform = m_program->uniformLocation("tex");

    GLuint texture;
    glGenTextures(1,&texture);
    //  Bind texture (state change - all texture calls now refer to this one specifically)
    glBindTexture(GL_TEXTURE_2D,texture);

    //  MAKE EVERYTHING POWERS OF TWO BECAUSE RASONS (or raisins, possibly. Probably not reasons. -Audrey)
    /*unsigned char image[16*3] = {

        0,0,255,255,255,255,255,255,255,0,255,0,
        255,255,255,255,255,255,255,255,255,0,0,0,
        255,255,255,0,0,0,255,255,255,255,255,255,
        255,255,255,255,0,0,255,255,255,255,255,255,


        //255,0,  0,    0  ,255,0  ,  0  ,0  ,255,
        //255,255,255,  0  ,0  ,0  ,  255,255,255,
        //255,0  ,0  ,  0,  255,0  ,  0,  0  ,255,
    };*/
    //  Copy image
    glTexImage2D(GL_TEXTURE_2D,0,3,DX,DY,0,GL_RGB,GL_UNSIGNED_BYTE,publicImage);

    //  Scale linearly when image size doesn't match
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    /*QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);
    */
    GLfloat vertices[] = {
        -1.0f, -1.0f,
        -1.0f, +1.0f,
        +1.0f, -1.0f,
        +1.0f, +1.0f,
        +1.0f, -1.0f,
        -1.0f, +1.0f,
    };

    GLfloat textureCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
    };

    m_program->setUniformValue(m_textureUniform, 0);
    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_texAttr, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;
}
