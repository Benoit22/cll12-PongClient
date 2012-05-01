#include "pongclient.h"
#include "ui_pongclient.h"

PongClient::PongClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PongClient)
{
    ui->setupUi(this);
}

PongClient::~PongClient()
{
    delete ui;
}
