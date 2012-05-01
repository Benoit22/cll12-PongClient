#ifndef PONGCLIENT_H
#define PONGCLIENT_H

#include <QMainWindow>

namespace Ui {
class PongClient;
}

class PongClient : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PongClient(QWidget *parent = 0);
    ~PongClient();
    
private:
    Ui::PongClient *ui;
};

#endif // PONGCLIENT_H
