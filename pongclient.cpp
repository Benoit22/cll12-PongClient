#include "pongclient.h"
#include "ui_pongclient.h"
#include <QtGui>
#include <qdrawutil.h>

PongClient::PongClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PongClient)
{
    ui->setupUi(this);
    QPainter Palette;
    Palette.drawRect(10,10,10,10);
    //Palette.fillRect(10,10,5,8,Qt::SolidPattern);
    //ui->label->set;

    //QColor *couleur;
    //couleur = new QColor(255,255,255);
    //qDrawPlainRect(&Palette,100,100,10,10,*couleur, 1,0);
    //ui->lblJeux->
}

PongClient::~PongClient()
{
    delete ui;
}
