#ifndef BV_V_H
#define BV_V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "BV_OpenGL.h"
#include "gradient.h"

class BV_Viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*                 slider;
   QPushButton*             button;
   BV_OpenGL*               ogl;
   std::vector<Gradient>    gradls;
private slots:
   //void                     remake_window();
public:
    BV_Viewer();
};

#endif
