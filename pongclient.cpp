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
    m_x = 10;
    m_y = 10;
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

void PongClient::on_btnConnectServer_clicked()
{
    QByteArray baReception;
    m_socket.connectToHost(ui->txtIpServeur->text(),60123, QIODevice::ReadWrite);
    m_socket.write("#");
    while (m_socket.waitForReadyRead(1000)) // Attente des données pendant 0.1 sec maximum
    {
        baReception.append(m_socket.read(m_socket.bytesAvailable()));
        m_joueur = baReception.toInt(0,10);
    }

}
