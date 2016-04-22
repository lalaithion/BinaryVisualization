#include "openglwindow.h"
#include "image.h"
#include "gradient.h"

#include <QtGui/QGuiApplication>
#include <QApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QPushButton>
#include <QGridLayout>
#include <QtWidgets>

#include <QFileDialog>

#include <QtCore/qmath.h>

#include <string.h>

float image[256*256];
float grad_image[256*3];

std::string rainbow =
        "\"Rainbow\"\n"
        "usehsv\n"
        "0.0->#000000\n"
        "0.25->#000099\n"
        "0.5->#009900\n"
        "0.75->#EE0000\n"
        "1.0->#FFFFFF\n";

std::string red2green =
        "\"RedtoGreen\"\n"
        "usehsv\n"
        "0.0->#000001\n"
        "1.0->#00FF00\n";

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
        "uniform lowp sampler1D grad;\n"
        "void main() {\n"
        "   vec4 color = texture2D(tex,texCoord);\n"
        "   vec4 newcolor = texture1D(grad, color.r);\n"
        "   gl_FragColor = vec4(newcolor.r, newcolor.b, newcolor.g, 1.0);\n"
        "}\n";

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
    GLuint m_gradientUniform;


    QOpenGLShaderProgram *m_program;
    int m_frame;
};

void generateTexture(unsigned int* image);

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    //  Throws warnings in Windows 10

    QString filename = QFileDialog::getOpenFileName(0, "Select file");//, QDir::homePath());

    Image testFile(filename.toUtf8().data());

    Gradient gradient(rainbow);
    gradient.getTexture(grad_image);

    //Choose a normalization
    testFile.getLogNormalizedBuffer(image);

    //Gradient Stuff

    //Display our image
    TriangleWindow window;
    window.resize(640, 640);
    window.show();

    app.exec();
}

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

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_texAttr = m_program->attributeLocation("texAttr");
    m_textureUniform = m_program->uniformLocation("tex");
    m_gradientUniform = m_program->uniformLocation("grad");

    GLuint texture;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1,&texture);

    //  Bind texture (state change - all texture calls now refer to this one specifically)
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0,1,256,256,0,GL_LUMINANCE,GL_FLOAT,image);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    GLuint gradient;
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1,&gradient);

    //  Bind texture (state change - all texture calls now refer to this one specifically)
    glBindTexture(GL_TEXTURE_1D,gradient);
    glTexImage1D(GL_TEXTURE_1D,0,3,256,0,GL_RGB,GL_FLOAT,grad_image);

    glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    GLfloat vertices[] = {
        -1.0f, -1.0f,
        -1.0f, +1.0f,
        +1.0f, -1.0f,
        +1.0f, +1.0f,
        +1.0f, -1.0f,
        -1.0f, +1.0f,
    };

    GLfloat textureCoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
    };
    m_program->bind();

    m_program->setUniformValue(m_textureUniform, 0);
    m_program->setUniformValue(m_gradientUniform, 1);

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
