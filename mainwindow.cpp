#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::about);
    connect(ui->actionWaveViewer,&QAction::triggered,this,&MainWindow::showGraph);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGraph()
{
    Plot* plot = new Plot(this);
    plot->setWindowModality(Qt::WindowModality::ApplicationModal);
    plot->show();
}

void MainWindow::about()
{
    AboutDialog* aboutDlg = new AboutDialog(this);
    aboutDlg->setModal(true);
    aboutDlg->show();
}

