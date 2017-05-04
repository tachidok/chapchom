#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "../../../../../../chapchom/external_src/qcustomplot/qcustomplot/qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
