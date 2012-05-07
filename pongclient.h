#ifndef PONGCLIENT_H
#define PONGCLIENT_H
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QtGui>

namespace Ui {
class PongClient;
}

class PongClient : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PongClient(QWidget *parent = 0);
    ~PongClient();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
private slots:
    void on_btnConnectServer_clicked();

private:
    Ui::PongClient *ui;
    int m_x;//Joueur1
    int m_y;//Joueur1
    int m_x1;//Joueur2
    int m_y1;//Joueur2
    int m_x2;//Balle
    int m_y2;//Balle
    QTcpSocket m_socket;
    int m_joueur;
    //QByteArray
};

#endif // PONGCLIENT_H
