#ifndef THCLIENT_H
#define THCLIENT_H

#include <QThread>
#include <QTcpSocket>

class ThClient : public QThread
{
    Q_OBJECT
public:
    explicit ThClient(QString);
    void run();

signals:
    void siMAJjeux(QByteArray);
private slots:
    void slInfo(QByteArray);
private:
    QString m_IpAdresse;
    QByteArray m_baRecevoir;        //trame pour recevoir
    QByteArray m_baTx;              //trame pour envoyer
    QTcpSocket m_sockClient;
};

#endif // THCLIENT_H
