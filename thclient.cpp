#include "thclient.h"
#include <QtGui>

ThClient::ThClient(QString Adresse)
{
    m_IpAdresse = Adresse;
}

void ThClient::run()
{
    m_sockClient.connectToHost(m_IpAdresse, 60123);
    m_sockClient.waitForConnected();
    //QByteArray a;
    //a.append("#.100.100.40.10.780.0.10.1");
    m_sockClient.write("&");
    while(m_sockClient.waitForReadyRead(100000))
    {
        m_baRecevoir.append(m_sockClient.read(m_sockClient.bytesAvailable())); // Lecture des données
        emit(siMAJjeux(m_baRecevoir));// Envoi des données pour la mise à jour de la fenêtre principale
        ThClient::sleep(1);
        m_sockClient.write(m_baRecevoir);
        m_baRecevoir.clear();
    }
    m_sockClient.disconnectFromHost();
    m_sockClient.close();
}

void ThClient::slInfo(QByteArray ba)
{
    m_baRecevoir= ba;
}
