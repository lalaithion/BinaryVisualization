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
   setWindowTitle(tr("He1mdall"));

   //  Create new Triangle widget
   ogl = new BV_OpenGL;

   for(int i = 0; i < colors.size(); i++) {
       gradls.push_back(Gradient(colors[i]));
   }

   //  Select shader
   QComboBox* grad_dropdown = new QComboBox();
   for(int i = 0; i < gradls.size(); i++) {
       grad_dropdown->addItem(QString::fromStdString(gradls[i].getName()));
   }

   ogl->SetGradients(gradls);

   //  Load new file button
   button = new QPushButton("Load");

   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->setContentsMargins(0,0,0,0);
   layout->addWidget(ogl,0,0,1,-1);
   layout->addWidget(grad_dropdown,1,0);
   layout->addWidget(quit,1,1);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(grad_dropdown, SIGNAL(currentIndexChanged(int)), ogl,        SLOT(set_dropdown(int)) );
   //  Connect reset() and button() signals
   //connect(button,   SIGNAL(pressed()),                     this,       SLOT(remake_window()) );
   //  Connect quit() signal to qApp::quit()
   connect(quit,          SIGNAL(pressed()),                qApp,       SLOT(quit()) );
}

