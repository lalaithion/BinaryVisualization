#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "BV_Viewer.h"
#include "colors.h"
#include "gradient.h"

//
//  Constructor
//
BV_Viewer::BV_Viewer()
{
   //  Set window title
   setWindowTitle(tr("Ex06:  OpenGL 4"));

   //  Create new Triangle widget
   ogl = new BV_OpenGL;

   for(int i = 0; i < colors.size(); i++) {
       gradls.push_back(Gradient(colors[i]));
   }

   //  Select shader
   QComboBox* dropdown = new QComboBox();
   for(int i = 0; i < gradls.size(); i++) {
       dropdown->addItem(QString::fromStdString(gradls[i].getName()));
   }

   ogl->SetGradients(gradls);

   slider = new QSlider(Qt::Horizontal);
   slider->setRange(0,360);

   //  View angle and zoom
   QLabel* label = new QLabel();

   //  Pause/resume button
   button = new QPushButton("Load");

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->setContentsMargins(0,0,0,0);
   layout->addWidget(ogl,0,0,-1,1);
   layout->addWidget(button,0,1,1,2);
   layout->addWidget(new QLabel("Color"),1,1);
   layout->addWidget(dropdown,1,2);
   //layout->addWidget(new QLabel("slider"),2,1);
   //layout->addWidget(slider,2,2);
   //layout->addWidget(new QLabel("label"),3,1);
   //layout->addWidget(label,3,2);
   layout->addWidget(quit,8,1,1,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,800);
   layout->setRowStretch(7,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(dropdown, SIGNAL(currentIndexChanged(int)), ogl,        SLOT(set_dropdown(int)));
   connect(slider,   SIGNAL(valueChanged(int)),        ogl,        SLOT(set_slider(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,           SIGNAL(label(QString)),      label, SLOT(setText(QString)));
   //  Connect reset() and button() signals
   connect(button,   SIGNAL(pressed()),                ogl,        SLOT(button_pressed()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,          SIGNAL(pressed()),                qApp,       SLOT(quit()));
}
