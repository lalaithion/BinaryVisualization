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
   QComboBox* test_dropdown = new QComboBox();
   for(int i = 0; i < gradls.size(); i++) {
       test_dropdown->addItem(QString::fromStdString(gradls[i].getName()));
   }

   ogl->SetGradients(gradls);

   test_slider = new QSlider(Qt::Horizontal);
   test_slider->setRange(0,360);

   //  View angle and zoom
   QLabel* test_label = new QLabel();

   //  Pause/resume button
   test_button = new QPushButton("Load");

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->setContentsMargins(0,0,0,0);
   layout->addWidget(ogl,0,0,-1,1);
   layout->addWidget(new QLabel("Load"),0,1);
   layout->addWidget(test_button,0,2);
   layout->addWidget(new QLabel("Color"),1,1);
   layout->addWidget(test_dropdown,1,2);
   //layout->addWidget(new QLabel("Test slider"),2,1);
   //layout->addWidget(test_slider,2,2);
   //layout->addWidget(new QLabel("Test label"),3,1);
   //layout->addWidget(test_label,3,2);
   layout->addWidget(quit,8,1);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,800);
   layout->setRowStretch(7,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(test_dropdown, SIGNAL(currentIndexChanged(int)), ogl,        SLOT(set_dropdown(int)));
   connect(test_slider,   SIGNAL(valueChanged(int)),        ogl,        SLOT(set_slider(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,           SIGNAL(test_label(QString)),      test_label, SLOT(setText(QString)));
   //  Connect reset() and test_button() signals
   connect(test_button,   SIGNAL(pressed()),                ogl,        SLOT(button_pressed()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,          SIGNAL(pressed()),                qApp,       SLOT(quit()));
}
