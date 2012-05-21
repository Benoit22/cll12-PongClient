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

    ui->txtIpServeur->setText("127.0.0.1");
    m_joueur = 0;
    m_Gagnant = false;
    m_Pret = false;
    /*
    m_scoreJ1 =2;
    m_Joueur1x = 40;
    m_Joueur1y = 10;
    m_Joueur2x = 780;
    m_Joueur2y = 10;
    m_Ballex = 100;
    m_Balley = 200;
    */
    //int x = this->width();
    //m_Ballex = x -20;
    /*
    QByteArray baTest;
    baTest += QByteArray::number(m_Ballex);
    baTest.append(".");
    baTest += QByteArray::number(m_Balley);
    baTest += QByteArray::number(m_Joueur1x);
    baTest += QByteArray::number(m_Joueur1x);
    baTest += QByteArray::number(m_Joueur2x);
    baTest += QByteArray::number(m_Joueur2x);
    baTest += QByteArray::number(1);
    baTest += QByteArray::number(2);
    */
    m_Ballex = -1;
    ui->lblScoreJ1->backgroundRole();
    ui->lblScoreJ2->backgroundRole();
    update();
}
void PongClient::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    if(m_joueur != 0 && m_Ballex == -1)
    {
        painter.drawRect(m_Joueur1x,m_Joueur1y,10,40);
        painter.drawRect(m_Joueur2x,m_Joueur2y,10,40);
    }
    else
        if(m_joueur != 0 && m_Ballex != -1)
        {
            painter.drawRect(m_Joueur1x,m_Joueur1y,10,40);
            painter.drawRect(m_Joueur2x,m_Joueur2y,10,40);
            painter.drawRect(m_Ballex,m_Balley,10,10);
        }
}

void PongClient::keyPressEvent ( QKeyEvent * event )
{
    QByteArray baEnvoye;
    if(m_Gagnant == false)
    {
        switch(event->key())
        {
        case Qt::Key_Down:
            if(m_Joueur1y < 260 && m_joueur == 1 && m_Pret ==true)
            {
                m_Joueur1y += 5;
                baEnvoye.append("#.");
                baEnvoye += QByteArray::number(m_Joueur1x);
                baEnvoye.append(".");
                baEnvoye += QByteArray::number(m_Joueur1y);
            }
            else
                if(m_Joueur2y < 260 && m_joueur == 2&& m_Pret ==true)
                {
                    m_Joueur2y += 5;
                    baEnvoye.append("#.");
                    baEnvoye += QByteArray::number(m_Joueur2x);
                    baEnvoye.append(".");
                    baEnvoye += QByteArray::number(m_Joueur2y);
                }
            emit(siInfos(baEnvoye));
            update();
            break;

        case Qt::Key_Up:
            if(m_Joueur1y > 0 && m_joueur == 1 && m_Pret ==true)
            {
                m_Joueur1y -= 5;
                baEnvoye.append("#.");
                baEnvoye += QByteArray::number(m_Joueur1x);
                baEnvoye.append(".");
                baEnvoye += QByteArray::number(m_Joueur1y);
            }
            else
                if(m_Joueur2y > 0 && m_joueur == 2 && m_Pret ==true)
                {
                    m_Joueur2y -= 5;
                    baEnvoye.append("#.");
                    baEnvoye += QByteArray::number(m_Joueur2x);
                    baEnvoye.append(".");
                    baEnvoye += QByteArray::number(m_Joueur2y);
                }
            emit(siInfos(baEnvoye));
            update();
            break;

        case Qt::Key_Space:
            if(m_Service == 1 && m_joueur == 1)
            {
                m_Pret = true;
                baEnvoye.append("#.");
                baEnvoye += QByteArray::number(m_Joueur1x);
                baEnvoye.append(".");
                baEnvoye += QByteArray::number(m_Joueur1y);
            }
            if(m_Service == 2 && m_joueur == 2)
            {
                m_Pret = true;
                baEnvoye.append("#.");
                baEnvoye += QByteArray::number(m_Joueur2x);
                baEnvoye.append(".");
                baEnvoye += QByteArray::number(m_Joueur2y);
            }
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
    m_Thcli = new ThClient(ui->txtIpServeur->text());
    connect(m_Thcli,SIGNAL(siMAJjeux(QByteArray)),this,SLOT(slMAJjeux(QByteArray)));
    connect(this,SIGNAL(siInfos(QByteArray)),m_Thcli,SLOT(slInfo(QByteArray)));
    m_Thcli->start();
}
void PongClient::slMAJjeux(QByteArray ba)
{
    QString Separe;
    QStringList Point;
    Separe = ba;
    Point = Separe.split(".");
    switch(ba[0])
    {
        case '#'://Trame normal
            m_Ballex = Point.at(1).toInt();
            m_Balley = Point.at(2).toInt();
            m_scoreJ1 = Point.at(7).toInt();
            m_scoreJ2 = Point.at(8).toInt();
            ui->lblScoreJ1->setText(QString::number(m_scoreJ1));
            ui->lblScoreJ2->setText(QString::number(m_scoreJ2));
            switch(m_joueur)
            {
                case 1:
                    m_Joueur2x = Point.at(5).toInt();
                    m_Joueur2y = Point.at(6).toInt();
                    break;
                case 2:

                    m_Joueur1x = Point.at(3).toInt();
                    m_Joueur1y = Point.at(4).toInt();
                    break;
            }
            update();
            break;
         case '%'://trame de service
            m_Pret = false;
            m_Ballex = Point.at(1).toInt();
            if(m_Ballex < 100)
                 m_Service = 1;
            else
                m_Service = 2;
            break;
         case '$'://Trame de gagnant
            m_Gagnant = true;
            m_scoreJ1 = Point.at(7).toInt();
            m_scoreJ2 = Point.at(8).toInt();
            ui->lblScoreJ1->setText(QString::number(m_scoreJ1));
            ui->lblScoreJ2->setText(QString::number(m_scoreJ2));
            break;
         case '&'://Trame de départ
            m_Pret = true;
            m_Ballex = Point.at(1).toInt();
            m_Balley = Point.at(2).toInt();
            m_Joueur1x = Point.at(3).toInt();
            m_Joueur1y = Point.at(4).toInt();
            m_Joueur2x = Point.at(5).toInt();
            m_Joueur2y = Point.at(6).toInt();
            m_scoreJ1 = Point.at(7).toInt();
            m_scoreJ2 = Point.at(8).toInt();
            ui->lblScoreJ1->setText(QString::number(m_scoreJ1));
            ui->lblScoreJ2->setText(QString::number(m_scoreJ2));
            update();
            break;
         default :
            m_joueur = ba.toInt(0,10);
            break;
    }
}

