#ifndef PONGCLIENT_H
#define PONGCLIENT_H
#include "thclient.h"
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

signals:
    void siInfos(QByteArray);
    void siThread();
private slots:
    void on_btnConnectServer_clicked();
    void slMAJjeux(QByteArray);

private:
    Ui::PongClient *ui;
    int m_Ballex;
    int m_Balley;
    int m_Joueur1x;
    int m_Joueur1y;
    int m_Joueur2x;
    int m_Joueur2y;
    int m_scoreJ1;
    int m_Service;
    int m_scoreJ2;
    bool m_Pret;
    bool m_Gagnant;
    int m_JoueurService;
    ThClient *m_Thcli;
    int m_joueur;
    //QByteArray
};

#endif // PONGCLIENT_H
