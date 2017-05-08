#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "../../../../../../chapchom/external_src/qcustomplot/qcustomplot/qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ---------------------------------------------------
    // Add options to plot options
    Plots_options.append("Raw Gyro X");
    Plots_options.append("Raw Gyro Y");
    Plots_options.append("Raw Gyro Z");
    Plots_options.append("Raw Acc X");
    Plots_options.append("Raw Acc Y");
    Plots_options.append("Raw Acc Z");
    Plots_options.append("Rotated Gyro X");
    Plots_options.append("Rotated Gyro Y");
    Plots_options.append("Rotated Gyro Z");
    Plots_options.append("Rotated Acc X");
    Plots_options.append("Rotated Acc Y");
    Plots_options.append("Rotated Acc Z");
    Plots_options.append("Filtered Gyro X");
    Plots_options.append("Filtered Gyro Y");
    Plots_options.append("Filtered Gyro Z");
    Plots_options.append("Filtered Acc X");
    Plots_options.append("Filtered Acc Y");
    Plots_options.append("Filtered Acc Z");
    Plots_options.append("Aligned Gyro X (in time)");
    Plots_options.append("Aligned Gyro Y (in time)");
    Plots_options.append("Aligned Gyro Z (in time)");
    Plots_options.append("Aligned Acc X (in time)");
    Plots_options.append("Aligned Acc Y (in time)");
    Plots_options.append("Aligned Acc Z (in time)");
    Plots_options.append("Euler angle PHI from Gyro");
    Plots_options.append("Euler angle THETA from Gyro");
    Plots_options.append("Euler angle PSI from Gyro");
    Plots_options.append("Euler angle PHI from Acc");
    Plots_options.append("Euler angle THETA from Acc");
    Plots_options.append("Euler angle PHI (fused)");
    Plots_options.append("Euler angle THETA (fused)");
    Plots_options.append("Euler angle PSI (fused)");
    Plots_options.append("Gravity (in X-body frame)");
    Plots_options.append("Gravity (in Y-body frame)");
    Plots_options.append("Gravity (in Z-body frame)");
    Plots_options.append("Linear Acc X (in body frame)");
    Plots_options.append("Linear Acc Y (in body frame)");
    Plots_options.append("Linear Acc Z (in body frame)");
    Plots_options.append("Inertial Acc X (in inertial frame)");
    Plots_options.append("Inertial Acc Y (in inertial frame)");
    Plots_options.append("Inertial Acc Z (in inertial frame)");
    Plots_options.append("Velocity X (in body frame)");
    Plots_options.append("Velocity Y (in body frame)");
    Plots_options.append("Velocity North (in inertial frame)");
    Plots_options.append("Velocity East (in inertial frame)");
    Plots_options.append("Position X (in body frame)");
    Plots_options.append("Position Y (in body frame)");
    Plots_options.append("Position X (in inertial frame)");
    Plots_options.append("Position Y (in inertial frame)");

    // Add options to combo boxs
    ui->cmb1->addItems(Plots_options);
    ui->cmb2->addItems(Plots_options);
    ui->cmb3->addItems(Plots_options);
    ui->cmb4->addItems(Plots_options);
    ui->cmb5->addItems(Plots_options);
    ui->cmb6->addItems(Plots_options);
    ui->cmb7->addItems(Plots_options);
    ui->cmb8->addItems(Plots_options);
    ui->cmb9->addItems(Plots_options);
    ui->cmb10->addItems(Plots_options);
    ui->cmb11->addItems(Plots_options);
    ui->cmb12->addItems(Plots_options);

    // ---------------------------------------------------



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot_raw_gyro_x(const double gyro_x)
{
    const unsigned range_in_x = 10000;

    // Increase the global counter
    Global_counter_for_plot++;

    // Add the current mouse coordinates to the data to plot
    Trajectory_coordinates[0].push_back(X_trajectory);
    Trajectory_coordinates[1].push_back(Y_trajectory);

    // Add the current Kalman coordinate to the data to plot
    Kalman_coordinates[0].push_back(X_Kalman);
    Kalman_coordinates[1].push_back(Y_Kalman);

    QVector<double> time_data(Global_counter_for_plot);

    for (unsigned i = 0; i < Global_counter_for_plot; i++)
    {time_data[i] = i;}

    // ---------------------------------------------------------------
    // X PLOT
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    // Mouse (GREEN)
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->wdg_plot_x->graph(0)->setPen(QPen(QColor(0,255,0)));
    ui->wdg_plot_x->graph(0)->setData(time_data, Trajectory_coordinates[0]);
    // ---------------------------------------------------------------
    // Kalman (BLUE)
    ui->wdg_plot_x->graph(1)->setPen(QPen(QColor(0,0,255)));
    ui->wdg_plot_x->graph(1)->setData(time_data, Kalman_coordinates[0]);

    // Assign labels to axis    ui->wdg_plot_x->xAxis->setLabel("time");
    ui->wdg_plot_x->yAxis->setLabel("x-position");

    // Set range
    ui->wdg_plot_x->xAxis->setRange(0, range_in_x);
    ui->wdg_plot_x->yAxis->setRange(0, x_max);

    ui->wdg_plot_x->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->wdg_plot_x->replot();

}
