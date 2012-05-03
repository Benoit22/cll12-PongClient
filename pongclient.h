#ifndef PONGCLIENT_H
#define PONGCLIENT_H

#include <QMainWindow>
#include <QWidget>
    #include <QKeyEvent>

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
private:
    Ui::PongClient *ui;
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_x1;
    int m_y1;
    int m_w1;
    int m_h1;
    int m_x2;
    int m_y2;
    int m_w2;
    int m_h2;
};

#endif // PONGCLIENT_H
