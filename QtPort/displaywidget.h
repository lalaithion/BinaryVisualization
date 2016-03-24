#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QDoubleSpinBox>
#include "TextureWidget.h"

class DisplayWidget : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   //TextureWidget*  screenTexture;
public:
    DisplayWidget(TextureWidget *screenTexture);
    DisplayWidget();
};

#endif // DISPLAYWIDGET_H
