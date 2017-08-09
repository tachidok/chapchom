#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "../../../../../../chapchom/external_src/qcustomplot/qcustomplot/qcustomplot.h"

void plot_raw_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_raw_gyro, mw->Raw_gyro_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_raw_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_raw_gyro[0], mw->Time_raw_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_raw_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_raw_gyro, mw->Raw_gyro_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_raw_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_raw_gyro[0], mw->Time_raw_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_raw_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_raw_gyro, mw->Raw_gyro_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_raw_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_raw_gyro[0], mw->Time_raw_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_raw_acc_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_raw_acc, mw->Raw_acc_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_raw_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_raw_acc[0], mw->Time_raw_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_raw_acc_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_raw_acc, mw->Raw_acc_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_raw_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_raw_acc[0], mw->Time_raw_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_raw_acc_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_raw_acc, mw->Raw_acc_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_raw_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_raw_acc[0], mw->Time_raw_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_rotated_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_rotated_gyro, mw->Rotated_gyro_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_rotated_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_rotated_gyro[0], mw->Time_rotated_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_rotated_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_rotated_gyro, mw->Rotated_gyro_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_rotated_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_rotated_gyro[0], mw->Time_rotated_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_rotated_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_rotated_gyro, mw->Rotated_gyro_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_rotated_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_rotated_gyro[0], mw->Time_rotated_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_rotated_acc_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_rotated_acc, mw->Rotated_acc_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_rotated_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_rotated_acc[0], mw->Time_rotated_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_rotated_acc_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_rotated_acc, mw->Rotated_acc_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_rotated_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_rotated_acc[0], mw->Time_rotated_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_rotated_acc_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_rotated_acc, mw->Rotated_acc_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_rotated_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_rotated_acc[0], mw->Time_rotated_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_filtered_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_filtered_gyro, mw->Filtered_gyro_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_filtered_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_filtered_gyro[0], mw->Time_filtered_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_filtered_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_filtered_gyro, mw->Filtered_gyro_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_filtered_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_filtered_gyro[0], mw->Time_filtered_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_filtered_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_filtered_gyro, mw->Filtered_gyro_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_filtered_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_filtered_gyro[0], mw->Time_filtered_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_filtered_acc_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_filtered_acc, mw->Filtered_acc_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_filtered_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_filtered_acc[0], mw->Time_filtered_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_filtered_acc_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_filtered_acc, mw->Filtered_acc_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_filtered_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_filtered_acc[0], mw->Time_filtered_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_filtered_acc_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_filtered_acc, mw->Filtered_acc_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_filtered_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_filtered_acc[0], mw->Time_filtered_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_aligned_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_aligned_gyro, mw->Aligned_gyro_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_aligned_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_aligned_gyro[0], mw->Time_aligned_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_aligned_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_aligned_gyro, mw->Aligned_gyro_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_aligned_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_aligned_gyro[0], mw->Time_aligned_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_aligned_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_aligned_gyro, mw->Aligned_gyro_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_aligned_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_aligned_gyro[0], mw->Time_aligned_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_GYRO, MAX_RAW_GYRO);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_aligned_acc_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_aligned_acc, mw->Aligned_acc_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_aligned_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_aligned_acc[0], mw->Time_aligned_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_aligned_acc_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_aligned_acc, mw->Aligned_acc_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_aligned_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_aligned_acc[0], mw->Time_aligned_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_aligned_acc_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_aligned_acc, mw->Aligned_acc_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_aligned_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_aligned_acc[0], mw->Time_aligned_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_phi_gyro(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_gyro, mw->Euler_angle_phi_gyro);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_gyro[0], mw->Time_euler_angle_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_theta_gyro(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_gyro, mw->Euler_angle_theta_gyro);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_gyro[0], mw->Time_euler_angle_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_psi_gyro(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,255,0)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_gyro, mw->Euler_angle_psi_gyro);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_gyro.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_gyro[0], mw->Time_euler_angle_gyro[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_phi_acc(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_acc, mw->Euler_angle_phi_acc);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_acc[0], mw->Time_euler_angle_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_theta_acc(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(255,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_acc, mw->Euler_angle_theta_acc);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_acc[0], mw->Time_euler_angle_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_phi_fused(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,0,255)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_fused, mw->Euler_angle_phi_fused);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_fused.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_fused[0], mw->Time_euler_angle_fused[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_theta_fused(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,0,255)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_fused, mw->Euler_angle_theta_fused);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_fused.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_fused[0], mw->Time_euler_angle_fused[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_euler_angle_psi_fused(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,0,255)));
    wdg_plot->graph(0)->setData(mw->Time_euler_angle_fused, mw->Euler_angle_psi_fused);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("deg");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_euler_angle_fused.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_euler_angle_fused[0], mw->Time_euler_angle_fused[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_EULER_ANGLE, MAX_EULER_ANGLE);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_gravity_x_body_frame(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_gravity_body_frame, mw->Gravity_x_body_frame);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_gravity_body_frame.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_gravity_body_frame[0], mw->Time_gravity_body_frame[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_gravity_y_body_frame(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_gravity_body_frame, mw->Gravity_y_body_frame);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_gravity_body_frame.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_gravity_body_frame[0], mw->Time_gravity_body_frame[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_gravity_z_body_frame(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,0,0)));
    wdg_plot->graph(0)->setData(mw->Time_gravity_body_frame, mw->Gravity_z_body_frame);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_gravity_body_frame.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_gravity_body_frame[0], mw->Time_gravity_body_frame[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_linear_acc_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(64,128,64)));
    wdg_plot->graph(0)->setData(mw->Time_linear_acc, mw->Linear_acc_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_linear_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_linear_acc[0], mw->Time_linear_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_linear_acc_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(64,128,64)));
    wdg_plot->graph(0)->setData(mw->Time_linear_acc, mw->Linear_acc_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_linear_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_linear_acc[0], mw->Time_linear_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_linear_acc_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(64,128,64)));
    wdg_plot->graph(0)->setData(mw->Time_linear_acc, mw->Linear_acc_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_linear_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_linear_acc[0], mw->Time_linear_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_inertial_acc_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,128,0)));
    wdg_plot->graph(0)->setData(mw->Time_inertial_acc, mw->Inertial_acc_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_inertial_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_inertial_acc[0], mw->Time_inertial_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_inertial_acc_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,128,0)));
    wdg_plot->graph(0)->setData(mw->Time_inertial_acc, mw->Inertial_acc_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_inertial_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_inertial_acc[0], mw->Time_inertial_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_inertial_acc_z(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,128,0)));
    wdg_plot->graph(0)->setData(mw->Time_inertial_acc, mw->Inertial_acc_z);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s^2");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_inertial_acc.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_inertial_acc[0], mw->Time_inertial_acc[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_RAW_ACC, MAX_RAW_ACC);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_velocity_x(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,192,255)));
    wdg_plot->graph(0)->setData(mw->Time_velocity_body, mw->Velocity_x);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_velocity_body.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_velocity_body[0], mw->Time_velocity_body[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_VELOCITY, MAX_VELOCITY);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_velocity_y(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,192,255)));
    wdg_plot->graph(0)->setData(mw->Time_velocity_body, mw->Velocity_y);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_velocity_body.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_velocity_body[0], mw->Time_velocity_body[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_VELOCITY, MAX_VELOCITY);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_velocity_north(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,128,255)));
    wdg_plot->graph(0)->setData(mw->Time_velocity_inertial, mw->Velocity_north);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_velocity_inertial.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_velocity_inertial[0], mw->Time_velocity_inertial[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_VELOCITY, MAX_VELOCITY);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_velocity_east(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(0,128,255)));
    wdg_plot->graph(0)->setData(mw->Time_velocity_inertial, mw->Velocity_east);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("Time (s)");
    wdg_plot->yAxis->setLabel("m/s");

    // Get the number of data in Time
    const unsigned n_time = mw->Time_velocity_inertial.size();

    // Set range
    wdg_plot->xAxis->setRange(mw->Time_velocity_inertial[0], mw->Time_velocity_inertial[n_time-1]);
    wdg_plot->yAxis->setRange(MIN_VELOCITY, MAX_VELOCITY);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_position_body_frame(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,64,255)));
    wdg_plot->graph(0)->setData(mw->Position_x_body_frame,
                                mw->Position_y_body_frame);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("meters");
    wdg_plot->yAxis->setLabel("meters");

    // Set range
    wdg_plot->xAxis->setRange(MIN_POSITION, MAX_POSITION);
    wdg_plot->yAxis->setRange(MIN_POSITION, MAX_POSITION);

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

void plot_position_inertial_frame(MainWindow *mw, QCustomPlot *wdg_plot)
{
    // ---------------------------------------------------------------
    // Assign data to plot
    // ---------------------------------------------------------------
    //ui->wdg_plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    wdg_plot->graph(0)->setPen(QPen(QColor(128,64,255)));
    wdg_plot->graph(0)->setData(mw->Position_x_inertial_frame,
                                mw->Position_y_inertial_frame);

    // Assign labels to axis
    wdg_plot->xAxis->setLabel("longitude");
    wdg_plot->yAxis->setLabel("latitude");

    // Get the maximum and minimum of each vector
    std::pair<const double*, const double*> longitude_range =
            std::minmax_element(mw->Position_x_inertial_frame.constBegin(),
                                mw->Position_x_inertial_frame.constEnd());

    std::pair<const double*, const double*> latitude_range =
            std::minmax_element(mw->Position_y_inertial_frame.constBegin(),
                                mw->Position_y_inertial_frame.constEnd());

    // Set range
    wdg_plot->xAxis->setRange(*(longitude_range.first),
                              *(longitude_range.second));
    wdg_plot->yAxis->setRange(*(latitude_range.first),
                              *(latitude_range.second));

    // Set interactions with the plot and replot (redraw)
    wdg_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    wdg_plot->replot();
}

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
    Plots_options.append("Position (in body frame)");
    Plots_options.append("Position (in inertial frame)");

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
    // Compute the number of data to keep in history based on the
    // number of data per second and the number of seconds to keep
    // in history
    N_data_in_history = N_DATA_PER_SECOND*N_SECONDS_IN_HISTORY;

    // Initialise vector of functions pointers (if we require to
    // add a new function be carefull with the index of the function
    // pointer such that it matches with the index of the item in the
    // combo box -Plots_options-)
    Plot_function_pt.push_back(&(plot_raw_gyro_x));
    Plot_function_pt.push_back(&(plot_raw_gyro_y));
    Plot_function_pt.push_back(&(plot_raw_gyro_z));
    Plot_function_pt.push_back(&(plot_raw_acc_x));
    Plot_function_pt.push_back(&(plot_raw_acc_y));
    Plot_function_pt.push_back(&(plot_raw_acc_z));
    Plot_function_pt.push_back(&(plot_rotated_gyro_x));
    Plot_function_pt.push_back(&(plot_rotated_gyro_y));
    Plot_function_pt.push_back(&(plot_rotated_gyro_z));
    Plot_function_pt.push_back(&(plot_rotated_acc_x));
    Plot_function_pt.push_back(&(plot_rotated_acc_y));
    Plot_function_pt.push_back(&(plot_rotated_acc_z));
    Plot_function_pt.push_back(&(plot_filtered_gyro_x));
    Plot_function_pt.push_back(&(plot_filtered_gyro_y));
    Plot_function_pt.push_back(&(plot_filtered_gyro_z));
    Plot_function_pt.push_back(&(plot_filtered_acc_x));
    Plot_function_pt.push_back(&(plot_filtered_acc_y));
    Plot_function_pt.push_back(&(plot_filtered_acc_z));
    Plot_function_pt.push_back(&(plot_aligned_gyro_x));
    Plot_function_pt.push_back(&(plot_aligned_gyro_y));
    Plot_function_pt.push_back(&(plot_aligned_gyro_z));
    Plot_function_pt.push_back(&(plot_aligned_acc_x));
    Plot_function_pt.push_back(&(plot_aligned_acc_y));
    Plot_function_pt.push_back(&(plot_aligned_acc_z));
    Plot_function_pt.push_back(&(plot_euler_angle_phi_gyro));
    Plot_function_pt.push_back(&(plot_euler_angle_theta_gyro));
    Plot_function_pt.push_back(&(plot_euler_angle_psi_gyro));
    Plot_function_pt.push_back(&(plot_euler_angle_phi_acc));
    Plot_function_pt.push_back(&(plot_euler_angle_theta_acc));
    Plot_function_pt.push_back(&(plot_euler_angle_phi_fused));
    Plot_function_pt.push_back(&(plot_euler_angle_theta_fused));
    Plot_function_pt.push_back(&(plot_euler_angle_psi_fused));
    Plot_function_pt.push_back(&(plot_gravity_x_body_frame));
    Plot_function_pt.push_back(&(plot_gravity_y_body_frame));
    Plot_function_pt.push_back(&(plot_gravity_z_body_frame));
    Plot_function_pt.push_back(&(plot_linear_acc_x));
    Plot_function_pt.push_back(&(plot_linear_acc_y));
    Plot_function_pt.push_back(&(plot_linear_acc_z));
    Plot_function_pt.push_back(&(plot_inertial_acc_x));
    Plot_function_pt.push_back(&(plot_inertial_acc_y));
    Plot_function_pt.push_back(&(plot_inertial_acc_z));
    Plot_function_pt.push_back(&(plot_velocity_x));
    Plot_function_pt.push_back(&(plot_velocity_y));
    Plot_function_pt.push_back(&(plot_velocity_north));
    Plot_function_pt.push_back(&(plot_velocity_east));
    Plot_function_pt.push_back(&(plot_position_body_frame));
    Plot_function_pt.push_back(&(plot_position_inertial_frame));

    // Read data from external application via ethernet/serial communication
    Read_data_thread.setup(Original_read_data_thread);
    // Start thread
    Read_data_thread.moveToThread(&Original_read_data_thread);

    // Initialise thread
    Original_read_data_thread.start();

    // -------------------------------------------------------------
    // Time stuff
    // -------------------------------------------------------------
    // Create timer
    Plot_timer = new QTimer(this);

    // Connect timer signal and slot to plot
    connect(Plot_timer, SIGNAL(timeout()), this, SLOT(slot_plot()));

    Plot_timer->start(TIMER_TIMEOUT_MS);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===================================================================
// In charge of filling data into the data structures
// ===================================================================
void MainWindow::fill_data(const double time_raw_gyro,
                           const double raw_gyro_x,
                           const double raw_gyro_y,
                           const double raw_gyro_z,
                           const double time_raw_acc,
                           const double raw_acc_x,
                           const double raw_acc_y,
                           const double raw_acc_z,
                           const double time_rotated_gyro,
                           const double rotated_gyro_x,
                           const double rotated_gyro_y,
                           const double rotated_gyro_z,
                           const double time_rotated_acc,
                           const double rotated_acc_x,
                           const double rotated_acc_y,
                           const double rotated_acc_z,
                           const double time_filtered_gyro,
                           const double filtered_gyro_x,
                           const double filtered_gyro_y,
                           const double filtered_gyro_z,
                           const double time_filtered_acc,
                           const double filtered_acc_x,
                           const double filtered_acc_y,
                           const double filtered_acc_z,
                           const double time_aligned_gyro,
                           const double aligned_gyro_x,
                           const double aligned_gyro_y,
                           const double aligned_gyro_z,
                           const double time_aligned_acc,
                           const double aligned_acc_x,
                           const double aligned_acc_y,
                           const double aligned_acc_z,
                           const double time_euler_angle_gyro,
                           const double euler_angle_phi_gyro,
                           const double euler_angle_theta_gyro,
                           const double euler_angle_psi_gyro,
                           const double time_euler_angle_acc,
                           const double euler_angle_phi_acc,
                           const double euler_angle_theta_acc,
                           const double time_euler_angle_fused,
                           const double euler_angle_phi_fused,
                           const double euler_angle_theta_fused,
                           const double euler_angle_psi_fused,
                           const double time_gravity_body_frame,
                           const double gravity_x_body_frame,
                           const double gravity_y_body_frame,
                           const double gravity_z_body_frame,
                           const double time_linear_acc,
                           const double linear_acc_x,
                           const double linear_acc_y,
                           const double linear_acc_z,
                           const double time_inertial_acc,
                           const double inertial_acc_x,
                           const double inertial_acc_y,
                           const double inertial_acc_z,
                           const double time_velocity_body,
                           const double velocity_x,
                           const double velocity_y,
                           const double time_velocity_inertial,
                           const double velocity_north,
                           const double velocity_east,
                           const double time_position_body,
                           const double position_x_body_frame,
                           const double position_y_body_frame,
                           const double time_position_inertial,
                           const double position_x_inertial_frame,
                           const double position_y_inertial_frame)
{

    // Add new elements to the data structures
    Time_raw_gyro.push_back(time_raw_gyro);
    Raw_gyro_x.push_back(raw_gyro_x);
    Raw_gyro_y.push_back(raw_gyro_y);
    Raw_gyro_z.push_back(raw_gyro_z);
    Time_raw_acc.push_back(time_raw_acc);
    Raw_acc_x.push_back(raw_acc_x);
    Raw_acc_y.push_back(raw_acc_y);
    Raw_acc_z.push_back(raw_acc_z);
    Time_rotated_gyro.push_back(time_rotated_gyro);
    Rotated_gyro_x.push_back(rotated_gyro_x);
    Rotated_gyro_y.push_back(rotated_gyro_y);
    Rotated_gyro_z.push_back(rotated_gyro_z);
    Time_rotated_acc.push_back(time_rotated_acc);
    Rotated_acc_x.push_back(rotated_acc_x);
    Rotated_acc_y.push_back(rotated_acc_y);
    Rotated_acc_z.push_back(rotated_acc_z);
    Time_filtered_gyro.push_back(time_filtered_gyro);
    Filtered_gyro_x.push_back(filtered_gyro_x);
    Filtered_gyro_y.push_back(filtered_gyro_y);
    Filtered_gyro_z.push_back(filtered_gyro_z);
    Time_filtered_acc.push_back(time_filtered_acc);
    Filtered_acc_x.push_back(filtered_acc_x);
    Filtered_acc_y.push_back(filtered_acc_y);
    Filtered_acc_z.push_back(filtered_acc_z);
    Time_aligned_gyro.push_back(time_aligned_gyro);
    Aligned_gyro_x.push_back(aligned_gyro_x);
    Aligned_gyro_y.push_back(aligned_gyro_y);
    Aligned_gyro_z.push_back(aligned_gyro_z);
    Time_aligned_acc.push_back(time_aligned_acc);
    Aligned_acc_x.push_back(aligned_acc_x);
    Aligned_acc_y.push_back(aligned_acc_y);
    Aligned_acc_z.push_back(aligned_acc_z);
    Time_euler_angle_gyro.push_back(time_euler_angle_gyro);
    Euler_angle_phi_gyro.push_back(euler_angle_phi_gyro);
    Euler_angle_theta_gyro.push_back(euler_angle_theta_gyro);
    Euler_angle_psi_gyro.push_back(euler_angle_psi_gyro);
    Time_euler_angle_acc.push_back(time_euler_angle_acc);
    Euler_angle_phi_acc.push_back(euler_angle_phi_acc);
    Euler_angle_theta_acc.push_back(euler_angle_theta_acc);
    Time_euler_angle_fused.push_back(time_euler_angle_fused);
    Euler_angle_phi_fused.push_back(euler_angle_phi_fused);
    Euler_angle_theta_fused.push_back(euler_angle_theta_fused);
    Euler_angle_psi_fused.push_back(euler_angle_psi_fused);
    Time_gravity_body_frame.push_back(time_gravity_body_frame);
    Gravity_x_body_frame.push_back(gravity_x_body_frame);
    Gravity_y_body_frame.push_back(gravity_y_body_frame);
    Gravity_z_body_frame.push_back(gravity_z_body_frame);
    Time_linear_acc.push_back(time_linear_acc);
    Linear_acc_x.push_back(linear_acc_x);
    Linear_acc_y.push_back(linear_acc_y);
    Linear_acc_z.push_back(linear_acc_z);
    Time_inertial_acc.push_back(time_inertial_acc);
    Inertial_acc_x.push_back(inertial_acc_x);
    Inertial_acc_y.push_back(inertial_acc_y);
    Inertial_acc_z.push_back(inertial_acc_z);
    Time_velocity_body.push_back(time_velocity_body);
    Velocity_x.push_back(velocity_x);
    Velocity_y.push_back(velocity_y);
    Time_velocity_inertial.push_back(time_velocity_inertial);
    Velocity_north.push_back(velocity_north);
    Velocity_east.push_back(velocity_east);
    Time_position_body.push_back(time_position_body);
    Position_x_body_frame.push_back(position_x_body_frame);
    Position_y_body_frame.push_back(position_y_body_frame);
    Time_position_inertial.push_back(time_position_inertial);
    Position_x_inertial_frame.push_back(position_x_inertial_frame);
    Position_y_inertial_frame.push_back(position_y_inertial_frame);

    if (!Time_raw_gyro.empty() && Time_raw_gyro.size() > N_data_in_history)
    {
        Time_raw_gyro.pop_front();
    }

    if (!Raw_gyro_x.empty() && Raw_gyro_x.size() > N_data_in_history)
    {
        Raw_gyro_x.pop_front();
    }

    if (!Raw_gyro_y.empty() && Raw_gyro_y.size() > N_data_in_history)
    {
        Raw_gyro_y.pop_front();
    }

    if (!Raw_gyro_z.empty() && Raw_gyro_z.size() > N_data_in_history)
    {
        Raw_gyro_z.pop_front();
    }

    if (!Time_raw_acc.empty() && Time_raw_acc.size() > N_data_in_history)
    {
        Time_raw_acc.pop_front();
    }

    if (!Raw_acc_x.empty() && Raw_acc_x.size() > N_data_in_history)
    {
        Raw_acc_x.pop_front();
    }

    if (!Raw_acc_y.empty() && Raw_acc_y.size() > N_data_in_history)
    {
        Raw_acc_y.pop_front();
    }

    if (!Raw_acc_z.empty() && Raw_acc_z.size() > N_data_in_history)
    {
        Raw_acc_z.pop_front();
    }

    if (!Time_rotated_gyro.empty() && Time_rotated_gyro.size() > N_data_in_history)
    {
        Time_rotated_gyro.pop_front();
    }

    if (!Rotated_gyro_x.empty() && Rotated_gyro_x.size() > N_data_in_history)
    {
        Rotated_gyro_x.pop_front();
    }

    if (!Rotated_gyro_y.empty() && Rotated_gyro_y.size() > N_data_in_history)
    {
        Rotated_gyro_y.pop_front();
    }

    if (!Rotated_gyro_z.empty() && Rotated_gyro_z.size() > N_data_in_history)
    {
        Rotated_gyro_z.pop_front();
    }

    if (!Time_rotated_acc.empty() && Time_rotated_acc.size() > N_data_in_history)
    {
        Time_rotated_acc.pop_front();
    }

    if (!Rotated_acc_x.empty() && Rotated_acc_x.size() > N_data_in_history)
    {
        Rotated_acc_x.pop_front();
    }

    if (!Rotated_acc_y.empty() && Rotated_acc_y.size() > N_data_in_history)
    {
        Rotated_acc_y.pop_front();
    }

    if (!Rotated_acc_z.empty() && Rotated_acc_z.size() > N_data_in_history)
    {
        Rotated_acc_z.pop_front();
    }

    if (!Time_filtered_gyro.empty() && Time_filtered_gyro.size() > N_data_in_history)
    {
        Time_filtered_gyro.pop_front();
    }

    if (!Filtered_gyro_x.empty() && Filtered_gyro_x.size() > N_data_in_history)
    {
        Filtered_gyro_x.pop_front();
    }

    if (!Filtered_gyro_y.empty() && Filtered_gyro_y.size() > N_data_in_history)
    {
        Filtered_gyro_y.pop_front();
    }

    if (!Filtered_gyro_z.empty() && Filtered_gyro_z.size() > N_data_in_history)
    {
        Filtered_gyro_z.pop_front();
    }

    if (!Time_filtered_acc.empty() && Time_filtered_acc.size() > N_data_in_history)
    {
        Time_filtered_acc.pop_front();
    }

    if (!Filtered_acc_x.empty() && Filtered_acc_x.size() > N_data_in_history)
    {
        Filtered_acc_x.pop_front();
    }

    if (!Filtered_acc_y.empty() && Filtered_acc_y.size() > N_data_in_history)
    {
        Filtered_acc_y.pop_front();
    }

    if (!Filtered_acc_z.empty() && Filtered_acc_z.size() > N_data_in_history)
    {
        Filtered_acc_z.pop_front();
    }

    if (!Time_aligned_gyro.empty() && Time_aligned_gyro.size() > N_data_in_history)
    {
        Time_aligned_gyro.pop_front();
    }

    if (!Aligned_gyro_x.empty() && Aligned_gyro_x.size() > N_data_in_history)
    {
        Aligned_gyro_x.pop_front();
    }

    if (!Aligned_gyro_y.empty() && Aligned_gyro_y.size() > N_data_in_history)
    {
        Aligned_gyro_y.pop_front();
    }

    if (!Aligned_gyro_z.empty() && Aligned_gyro_z.size() > N_data_in_history)
    {
        Aligned_gyro_z.pop_front();
    }

    if (!Time_aligned_acc.empty() && Time_aligned_acc.size() > N_data_in_history)
    {
        Time_aligned_acc.pop_front();
    }

    if (!Aligned_acc_x.empty() && Aligned_acc_x.size() > N_data_in_history)
    {
        Aligned_acc_x.pop_front();
    }

    if (!Aligned_acc_y.empty() && Aligned_acc_y.size() > N_data_in_history)
    {
        Aligned_acc_y.pop_front();
    }

    if (!Aligned_acc_z.empty() && Aligned_acc_z.size() > N_data_in_history)
    {
        Aligned_acc_z.pop_front();
    }

    if (!Time_euler_angle_gyro.empty() && Time_euler_angle_gyro.size() > N_data_in_history)
    {
        Time_euler_angle_gyro.pop_front();
    }

    if (!Euler_angle_phi_gyro.empty() && Euler_angle_phi_gyro.size() > N_data_in_history)
    {
        Euler_angle_phi_gyro.pop_front();
    }

    if (!Euler_angle_theta_gyro.empty() && Euler_angle_theta_gyro.size() > N_data_in_history)
    {
        Euler_angle_theta_gyro.pop_front();
    }

    if (!Euler_angle_psi_gyro.empty() && Euler_angle_psi_gyro.size() > N_data_in_history)
    {
        Euler_angle_psi_gyro.pop_front();
    }

    if (!Time_euler_angle_acc.empty() && Time_euler_angle_acc.size() > N_data_in_history)
    {
        Time_euler_angle_acc.pop_front();
    }

    if (!Euler_angle_phi_acc.empty() && Euler_angle_phi_acc.size() > N_data_in_history)
    {
        Euler_angle_phi_acc.pop_front();
    }

    if (!Euler_angle_theta_acc.empty() && Euler_angle_theta_acc.size() > N_data_in_history)
    {
        Euler_angle_theta_acc.pop_front();
    }

    if (!Time_euler_angle_fused.empty() && Time_euler_angle_fused.size() > N_data_in_history)
    {
        Time_euler_angle_fused.pop_front();
    }

    if (!Euler_angle_phi_fused.empty() && Euler_angle_phi_fused.size() > N_data_in_history)
    {
        Euler_angle_phi_fused.pop_front();
    }

    if (!Euler_angle_theta_fused.empty() && Euler_angle_theta_fused.size() > N_data_in_history)
    {
        Euler_angle_theta_fused.pop_front();
    }

    if (!Euler_angle_psi_fused.empty() && Euler_angle_psi_fused.size() > N_data_in_history)
    {
        Euler_angle_psi_fused.pop_front();
    }

    if (!Time_gravity_body_frame.empty() && Time_gravity_body_frame.size() > N_data_in_history)
    {
        Time_gravity_body_frame.pop_front();
    }

    if (!Gravity_x_body_frame.empty() && Gravity_x_body_frame.size() > N_data_in_history)
    {
        Gravity_x_body_frame.pop_front();
    }

    if (!Gravity_y_body_frame.empty() && Gravity_y_body_frame.size() > N_data_in_history)
    {
        Gravity_y_body_frame.pop_front();
    }

    if (!Gravity_z_body_frame.empty() && Gravity_z_body_frame.size() > N_data_in_history)
    {
        Gravity_z_body_frame.pop_front();
    }

    if (!Time_linear_acc.empty() && Time_linear_acc.size() > N_data_in_history)
    {
        Time_linear_acc.pop_front();
    }

    if (!Linear_acc_x.empty() && Linear_acc_x.size() > N_data_in_history)
    {
        Linear_acc_x.pop_front();
    }

    if (!Linear_acc_y.empty() && Linear_acc_y.size() > N_data_in_history)
    {
        Linear_acc_y.pop_front();
    }

    if (!Linear_acc_z.empty() && Linear_acc_z.size() > N_data_in_history)
    {
        Linear_acc_z.pop_front();
    }

    if (!Time_inertial_acc.empty() && Time_inertial_acc.size() > N_data_in_history)
    {
        Time_inertial_acc.pop_front();
    }

    if (!Inertial_acc_x.empty() && Inertial_acc_x.size() > N_data_in_history)
    {
        Inertial_acc_x.pop_front();
    }

    if (!Inertial_acc_y.empty() && Inertial_acc_y.size() > N_data_in_history)
    {
        Inertial_acc_y.pop_front();
    }

    if (!Inertial_acc_z.empty() && Inertial_acc_z.size() > N_data_in_history)
    {
        Inertial_acc_z.pop_front();
    }

    if (!Time_velocity_body.empty() && Time_velocity_body.size() > N_data_in_history)
    {
        Time_velocity_body.pop_front();
    }

    if (!Velocity_x.empty() && Velocity_x.size() > N_data_in_history)
    {
        Velocity_x.pop_front();
    }

    if (!Velocity_y.empty() && Velocity_y.size() > N_data_in_history)
    {
        Velocity_y.pop_front();
    }

    if (!Time_velocity_inertial.empty() && Time_velocity_inertial.size() > N_data_in_history)
    {
        Time_velocity_inertial.pop_front();
    }

    if (!Velocity_north.empty() && Velocity_north.size() > N_data_in_history)
    {
        Velocity_north.pop_front();
    }

    if (!Velocity_east.empty() && Velocity_east.size() > N_data_in_history)
    {
        Velocity_east.pop_front();
    }

    if (!Time_position_body.empty() && Time_position_body.size() > N_data_in_history)
    {
        Time_position_body.pop_front();
    }

    if (!Position_x_body_frame.empty() && Position_x_body_frame.size() > N_data_in_history)
    {
        Position_x_body_frame.pop_front();
    }

    if (!Position_y_body_frame.empty() && Position_y_body_frame.size() > N_data_in_history)
    {
        Position_y_body_frame.pop_front();
    }

    if (!Time_position_inertial.empty() && Time_position_inertial.size() > N_data_in_history)
    {
        Time_position_inertial.pop_front();
    }

    if (!Position_x_inertial_frame.empty() && Position_x_inertial_frame.size() > N_data_in_history)
    {
        Position_x_inertial_frame.pop_front();
    }

    if (!Position_y_inertial_frame.empty() && Position_y_inertial_frame.size() > N_data_in_history)
    {
        Position_y_inertial_frame.pop_front();
    }

}

// ===================================================================
// Method in charge of calling the corresponing plotting functions
// based on the combo box selection
// ===================================================================
void MainWindow::slot_plot()
{

    if (!Time_raw_gyro.empty() &&
        !Raw_gyro_x.empty() && !Raw_gyro_y.empty() && !Raw_gyro_z.empty() &&
        !Time_raw_acc.empty() &&
        !Raw_acc_x.empty() && !Raw_acc_y.empty() && !Raw_acc_z.empty() &&
        !Time_rotated_gyro.empty() &&
        !Rotated_gyro_x.empty() && !Rotated_gyro_y.empty() && !Rotated_gyro_z.empty() &&
        !Time_rotated_acc.empty() &&
        !Rotated_acc_x.empty() && !Rotated_acc_y.empty() && !Rotated_acc_z.empty() &&
        !Time_filtered_gyro.empty() &&
        !Filtered_gyro_x.empty() && !Filtered_gyro_y.empty() && !Filtered_gyro_z.empty() &&
        !Time_filtered_acc.empty() &&
        !Filtered_acc_x.empty() && !Filtered_acc_y.empty() && !Filtered_acc_z.empty() &&
        !Time_aligned_gyro.empty() &&
        !Aligned_gyro_x.empty() && !Aligned_gyro_y.empty() && !Aligned_gyro_z.empty() &&
        !Time_aligned_acc.empty() &&
        !Aligned_acc_x.empty() && !Aligned_acc_y.empty() && !Aligned_acc_z.empty() &&
        !Time_euler_angle_gyro.empty() &&
        !Euler_angle_phi_gyro.empty() && !Euler_angle_theta_gyro.empty() && !Euler_angle_psi_gyro.empty() &&
        !Time_euler_angle_acc.empty() &&
        !Euler_angle_phi_acc.empty() && !Euler_angle_theta_acc.empty() &&
        !Time_euler_angle_fused.empty() &&
        !Euler_angle_phi_fused.empty() && !Euler_angle_theta_fused.empty() && !Euler_angle_psi_fused.empty() &&
        !Time_gravity_body_frame.empty() &&
        !Gravity_x_body_frame.empty() && !Gravity_y_body_frame.empty() && !Gravity_z_body_frame.empty() &&
        !Time_linear_acc.empty() &&
        !Linear_acc_x.empty() && !Linear_acc_y.empty() && !Linear_acc_z.empty() &&
        !Time_inertial_acc.empty() &&
        !Inertial_acc_x.empty() && !Inertial_acc_y.empty() && !Inertial_acc_z.empty() &&
        !Time_velocity_body.empty() &&
        !Velocity_x.empty() && !Velocity_y.empty() &&
        !Time_velocity_inertial.empty() &&
        !Velocity_north.empty() && !Velocity_east.empty() &&
        !Time_position_body.empty() &&
        !Position_x_body_frame.empty() && !Position_y_body_frame.empty() &&
        !Time_position_inertial.empty() &&
        !Position_x_inertial_frame.empty() && !Position_y_inertial_frame.empty())
    {
        // Check the selected option in each combo box and call the
        // appropiate plot method
        Plot_function_pt[ui->cmb1->currentIndex()](this, ui->wdg1);
        Plot_function_pt[ui->cmb2->currentIndex()](this, ui->wdg2);
        Plot_function_pt[ui->cmb3->currentIndex()](this, ui->wdg3);
        Plot_function_pt[ui->cmb4->currentIndex()](this, ui->wdg4);
        Plot_function_pt[ui->cmb5->currentIndex()](this, ui->wdg5);
        Plot_function_pt[ui->cmb6->currentIndex()](this, ui->wdg6);
        Plot_function_pt[ui->cmb7->currentIndex()](this, ui->wdg7);
        Plot_function_pt[ui->cmb8->currentIndex()](this, ui->wdg8);
        Plot_function_pt[ui->cmb9->currentIndex()](this, ui->wdg9);
        Plot_function_pt[ui->cmb10->currentIndex()](this, ui->wdg10);
        Plot_function_pt[ui->cmb11->currentIndex()](this, ui->wdg11);
        Plot_function_pt[ui->cmb12->currentIndex()](this, ui->wdg12);
    }

}
