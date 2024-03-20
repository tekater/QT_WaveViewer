#include "plot.h"
#include "ui_plot.h"

Plot::Plot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);

    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setRange(0,4500);
    ui->customPlot->yAxis->setRange(-500,4500);

    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost,10002);
    //connect(socket,&QUdpSocket::readyRead,this,&Plot::loadDataToPlot);
    connect(socket,SIGNAL(readyRead()),this,SLOT(loadDataToPlot()));

}

Plot::~Plot()
{
    delete socket;
    delete ui;
}

void Plot::resizeEvent(QResizeEvent* e)
{
    QMainWindow::resizeEvent(e);
    ui->customPlot->resize(QSize(this->geometry().width() - 10,this->geometry().height() - 30));
}

void Plot::loadDataToPlot()
{
    int size = socket->pendingDatagramSize();

    QNetworkDatagram datagram = socket->receiveDatagram(size);
    QByteArray buffer = datagram.data();

    QDataStream stream(buffer);
    qint16* values = new qint16[size / 2] {};

    for(int i = 0; i < size / 2; i++)
    {
        stream >> values[i];
    }

    int limit = size / 2;

    QVector<double> x(limit), y(limit);
    for(int i = 0; i < limit; i ++)
    {
        x[i] = i;
        y[i] = values[i];
    }
    delete[] values;

    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->replot();

    ui->statusbar->showMessage("Mediane:" + QString::number(y[size / 4]) + "\t\t\t"+ " Maxvalue: " + QString::number(y.last()));
}
