#include "pongclient.h"
#include "ui_pongclient.h"
#include <QtGui>
#include <qdrawutil.h>

PongClient::PongClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PongClient)
{
    this->grabKeyboard();
    ui->setupUi(this);
    m_x = 10;
    m_y = 10;
   // QRect r1(100, 200, 11, 16);
    //QPaintEvent eve;
    //eve.rect(r1);
    //QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    //QPainter painter;
    //painter.setPen(Qt::blue);
    //painter.setFont(QFont("Arial", 30));
    //painter.begin(ui->lblJeux);
    //painter.drawRect(rectangle);
    //QPainter Palette(this);
    //Palette.drawRect(10,10,10,10);
    //Palette.save();
    //Palette.fillRect(10,10,5,8,Qt::SolidPattern);
    //ui->label->set;

    //QColor *couleur;
    //couleur = new QColor(255,255,255);
    //qDrawPlainRect(&Palette,100,100,10,10,*couleur, 1,0);
    //ui->lblJeux->
    update();
}
void PongClient::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawRect(m_x,m_y,10,40);
    painter.drawRect(100,200,10,10);
}

void PongClient::keyPressEvent ( QKeyEvent * event )
{
    {
        switch (event->key())
        {
            case Qt::Key_Down:
                if(m_y <= 245)
                    m_y += 5;
                update();
                break;
            case Qt::Key_Up:
                if(m_y >= 5)
                    m_y -= 5;
                update();
                break;
        }
    }
}

PongClient::~PongClient()
{
    delete ui;
}
