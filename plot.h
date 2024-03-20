#ifndef PLOT_H
#define PLOT_H

#include <QMainWindow>
#include <QNetworkDatagram>
#include <QUdpSocket>

namespace Ui {
class Plot;
}

class Plot : public QMainWindow
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    ~Plot();
    void resizeEvent(QResizeEvent* e);

public slots:
    void loadDataToPlot();

private:
    Ui::Plot *ui;

    QUdpSocket* socket;

};

#endif // PLOT_H
