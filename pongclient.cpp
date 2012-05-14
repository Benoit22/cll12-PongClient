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
    m_joueur = 1;
    m_Pret = false;
    m_scoreJ1 =2;
    m_socket.connectToHost(ui->txtIpServeur->text(),60123, QIODevice::ReadWrite);
    m_x = 40;
    m_y = 10;
    m_x1 = 780;
    m_y1 = 10;
    m_x2 = 100;
    m_y2 = 200;
    //int x = this->width();
    //m_x2 = x -20;
    /*
    QByteArray baTest;
    baTest += QByteArray::number(m_x2);
    baTest.append(".");
    baTest += QByteArray::number(m_y2);
    baTest += QByteArray::number(m_x);
    baTest += QByteArray::number(m_x);
    baTest += QByteArray::number(m_x1);
    baTest += QByteArray::number(m_x1);
    baTest += QByteArray::number(1);
    baTest += QByteArray::number(2);
    */
    ui->lblScoreJ1->backgroundRole();
    ui->lblScoreJ2->backgroundRole();
    update();
}
void PongClient::paintEvent(QPaintEvent *)
{
    if(m_joueur != 0)
    {
        QPainter painter(this);
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawRect(m_x,m_y,10,40);
        painter.drawRect(m_x1,m_y1,10,40);
        painter.drawRect(m_x2,m_y2,10,10);
    }
}

void PongClient::keyPressEvent ( QKeyEvent * event )
{
    QByteArray baEnvoye;
    switch (event->key())
    {
    case Qt::Key_Down:
        if(m_y < 260 && m_joueur == 1)
        {
            m_y += 5;
            baEnvoye += QByteArray::number(m_x);
            baEnvoye.append(".");
            baEnvoye += QByteArray::number(m_y);
        }
        else
            if(m_y1 < 260 && m_joueur == 2)
            {
                m_y1 += 5;
                baEnvoye += QByteArray::number(m_x1);
                baEnvoye.append(".");
                baEnvoye += QByteArray::number(m_y1);
            }
        m_socket.write(baEnvoye);
        update();
        break;

    case Qt::Key_Up:
        if(m_y > 0 && m_joueur == 1)
        {
            m_y -= 5;
            baEnvoye += QByteArray::number(m_x);
            baEnvoye.append(".");
            baEnvoye += QByteArray::number(m_y);
        }
        else
            if(m_y1 > 0 && m_joueur == 2)
            {
                m_y1 -= 5;
                baEnvoye += QByteArray::number(m_x1);
                baEnvoye.append(".");
                baEnvoye += QByteArray::number(m_y1);
            }
        m_socket.write(baEnvoye);
        update();
        break;

    case Qt::Key_Space:
        m_Pret = true;
        break;
    }
}

PongClient::~PongClient()
{
    delete ui;
}

void PongClient::on_btnConnectServer_clicked()
{
    QByteArray baInfo;
    QString Separe;
    QStringList Point;
    m_socket.write("#");
    while (m_socket.waitForReadyRead(30000)) // Attente des données pendant 30 sec maximum
    {
        switch(m_joueur)
        {
            case 0:
                baInfo.append(m_socket.read(m_socket.bytesAvailable()));
                m_joueur = baInfo.toInt(0,10);
                if(m_joueur == 1)
                {
                    m_x = 40;
                    m_y = 10;
                    update();
                }
                else
                {
                    m_x1 = 780;
                    m_y1 = 10;
                    update();
                }
                break;
            case 1:
                baInfo.append(m_socket.read(m_socket.bytesAvailable()));
                Separe = baInfo;
                Point = Separe.split(".");
                m_x2 = Point.at(0).toInt();
                m_y2 = Point.at(1).toInt();
                m_x1 = Point.at(4).toInt();
                m_y1 = Point.at(5).toInt();
                m_scoreJ1 = Point.at(6).toInt();
                m_scoreJ2 = Point.at(7).toInt();
                ui->lblScoreJ1->setText(QString::number(m_scoreJ1));
                ui->lblScoreJ2->setText(QString::number(m_scoreJ2));
                update();
                break;
            case 2:
                baInfo.append(m_socket.read(m_socket.bytesAvailable()));
                Separe = baInfo;
                Point = Separe.split(".");
                m_x2 = Point.at(0).toInt();
                m_y2 = Point.at(1).toInt();
                m_x = Point.at(2).toInt();
                m_y = Point.at(3).toInt();
                m_scoreJ1 = Point.at(6).toInt();
                m_scoreJ2 = Point.at(7).toInt();
                ui->lblScoreJ1->setText(QString::number(m_scoreJ1));
                ui->lblScoreJ2->setText(QString::number(m_scoreJ2));
                break;
        }
    }
}
