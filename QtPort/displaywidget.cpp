
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "displaywidget.h"

//
//  Constructor
//
DisplayWidget::DisplayWidget(TextureWidget *screenTexture)
{
    QPushButton* rst = new QPushButton("Reset");
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(rst,8,1);
    layout->addWidget(screenTexture, 0, 0, 8, 1);
    setLayout(layout);
}

DisplayWidget::DisplayWidget()
{
    QPushButton* rst = new QPushButton("Reset");
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(rst,8,1);
    //layout->addWidget(screenTexture, 0, 0, 8, 1);
    setLayout(layout);
}
