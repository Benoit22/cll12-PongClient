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
    m_joueur = 0;
    m_socket.connectToHost(ui->txtIpServeur->text(),60123, QIODevice::ReadWrite);
    m_x = 10;
    m_y = 10;
    m_x1 = 0;
    m_x2 = 0;
    m_x2 = 100;
    m_y2 = 200;
    update();
}
void PongClient::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawRect(m_x,m_y,10,40);
    painter.drawRect(m_x2,m_y2,10,10);
}

void PongClient::keyPressEvent ( QKeyEvent * event )
{
    {
        switch (event->key())
        {
            case Qt::Key_Down:
                if(m_y <= 245 && m_joueur=1)
                {
                    m_y += 5;
                    QString trame;
                    trame = QString::number(m_x2);
                    trame += ",";
                    trame += QString::number(m_y2);
                    trame += ".";
                    trame = QString::number(m_x);
                    trame += ",";
                    trame += QString::number(m_y);
                    trame += ".";
                    trame = QString::number(m_x1);
                    trame += ",";
                    trame += QString::number(m_y1);
                    trame += ".";
                    trame = QString::number(10);
                    trame += ",";
                    trame += QString::number(14);

                    m_socket.write(trame);
                }
                else
                {
                    m_y1 += 5;
                    QString trame;
                    trame = QString::number(m_x2);
                    trame += ",";
                    trame += QString::number(m_y2);
                    trame += ".";
                    trame = QString::number(m_x);
                    trame += ",";
                    trame += QString::number(m_y);
                    trame += ".";
                    trame = QString::number(m_x1);
                    trame += ",";
                    trame += QString::number(m_y1);
                    trame += ".";
                    trame = QString::number(10);
                    trame += ",";
                    trame += QString::number(14);
                    m_socket.write(trame);
                }
                update();
                break;
            case Qt::Key_Up:
                if(m_y >= 5 && m_joueur=1)
                {
                    m_y -= 5;
                    QString trame;
                    trame = QString::number(m_x2);
                    trame += ",";
                    trame += QString::number(m_y2);
                    trame += ".";
                    trame = QString::number(m_x);
                    trame += ",";
                    trame += QString::number(m_y);
                    trame += ".";
                    trame = QString::number(m_x1);
                    trame += ",";
                    trame += QString::number(m_y1);
                    trame += ".";
                    trame = QString::number(10);
                    trame += ",";
                    trame += QString::number(14);
                    m_socket.write(trame);
                }
                else
                {
                    m_y1 -= 5;
                    QString trame;
                    trame = QString::number(m_x2);
                    trame += ",";
                    trame += QString::number(m_y2);
                    trame += ".";
                    trame = QString::number(m_x);
                    trame += ",";
                    trame += QString::number(m_y);
                    trame += ".";
                    trame = QString::number(m_x1);
                    trame += ",";
                    trame += QString::number(m_y1);
                    trame += ".";
                    trame = QString::number(10);
                    trame += ",";
                    trame += QString::number(14);
                    m_socket.write(trame);
                }
                update();
                break;
        }
    }
}

PongClient::~PongClient()
{
    delete ui;
}

void PongClient::on_btnConnectServer_clicked()
{
    QString test;
    QStringList test2;
    QByteArray baInfo;
    baInfo.append("400");
    baInfo.append(".");
    baInfo.append("200");
    test = baInfo;
    test2 = test.split('.');
    m_joueur =  test2.at(0).toInt();
    //= baInfo.right(2);
    m_socket.write("#");
    while (m_socket.waitForReadyRead(10000)) // Attente des données pendant 10 sec maximum
    {
        switch(m_joueur)
        {
            case 0:
                baInfo.append(m_socket.read(m_socket.bytesAvailable()));
                m_joueur = baInfo.toInt(0,10);
                break;
            case 1:
                baInfo.append(m_socket.read(m_socket.bytesAvailable()));
        }
    }
}
