#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // ------------------------------------------------------
    // List of plots for each widget
    QStringList Plots_options;

    // ------------------------------------------------------
    // Plot methods (each widget calls one of these to plot its data)
    void plot_raw_gyro_x();
    void plot_raw_gyro_y();
    void plot_raw_gyro_z();
    void plot_raw_acc_x();
    void plot_raw_acc_y();
    void plot_raw_acc_z();
    void plot_rotated_gyro_x();
    void plot_rotated_gyro_y();
    void plot_rotated_gyro_z();
    void plot_rotated_acc_x();
    void plot_rotated_acc_y();
    void plot_rotated_acc_z();
    void plot_filtered_gyro_x();
    void plot_filtered_gyro_y();
    void plot_filtered_gyro_z();
    void plot_filtered_acc_x();
    void plot_filtered_acc_y();
    void plot_filtered_acc_z();
    void plot_aligned_gyro_x();
    void plot_aligned_gyro_y();
    void plot_aligned_gyro_z();
    void plot_aligned_acc_x();
    void plot_aligned_acc_y();
    void plot_aligned_acc_z();
    void plot_euler_angle_phi_gyro();
    void plot_euler_angle_theta_gyro();
    void plot_euler_angle_psi_gyro();
    void plot_euler_angle_phi_acc();
    void plot_euler_angle_theta_acc();
    void plot_euler_angle_phi_fused();
    void plot_euler_angle_theta_fused();
    void plot_euler_angle_psi_fused();
    void plot_gravity_x_body_frame();
    void plot_gravity_y_body_frame();
    void plot_gravity_z_body_frame();
    void plot_linear_acc_x();
    void plot_linear_acc_y();
    void plot_linear_acc_z();
    void plot_inertial_acc_x();
    void plot_inertial_acc_y();
    void plot_inertial_acc_z();
    void plot_velocity_x();
    void plot_velocity_y();
    void plot_velocity_north();
    void plot_velocity_east();
    void plot_position_x_body_frame();
    void plot_position_y_body_frame();
    void plot_position_x_inertial_frame();
    void plot_position_y_inertial_frame();

    // ------------------------------------------------------
    // Data structures to store the computed values
    QVector<double> Time;
    QVector<double> Raw_gyro_x;
    QVector<double> Raw_gyro_y;
    QVector<double> Raw_gyro_z;
    QVector<double> Raw_acc_x;
    QVector<double> Raw_acc_y;
    QVector<double> Raw_acc_z;
    QVector<double> Rotated_gyro_x;
    QVector<double> Rotated_gyro_y;
    QVector<double> Rotated_gyro_z;
    QVector<double> Rotated_acc_x;
    QVector<double> Rotated_acc_y;
    QVector<double> Rotated_acc_z;
    QVector<double> Filtered_gyro_x;
    QVector<double> Filtered_gyro_y;
    QVector<double> Filtered_gyro_z;
    QVector<double> Filtered_acc_x;
    QVector<double> Filtered_acc_y;
    QVector<double> Filtered_acc_z;
    QVector<double> Aligned_gyro_x;
    QVector<double> Aligned_gyro_y;
    QVector<double> Aligned_gyro_z;
    QVector<double> Aligned_acc_x;
    QVector<double> Aligned_acc_y;
    QVector<double> Aligned_acc_z;
    QVector<double> Euler_angle_phi_gyro;
    QVector<double> Euler_angle_theta_gyro;
    QVector<double> Euler_angle_psi_gyro;
    QVector<double> Euler_angle_phi_acc;
    QVector<double> Euler_angle_theta_acc;
    QVector<double> Euler_angle_phi_fused;
    QVector<double> Euler_angle_theta_fused;
    QVector<double> Euler_angle_psi_fused;
    QVector<double> Gravity_x_body_frame;
    QVector<double> Gravity_y_body_frame;
    QVector<double> Gravity_z_body_frame;
    QVector<double> Linear_acc_x;
    QVector<double> Linear_acc_y;
    QVector<double> Linear_acc_z;
    QVector<double> Inertial_acc_x;
    QVector<double> Inertial_acc_y;
    QVector<double> Inertial_acc_z;
    QVector<double> Velocity_x;
    QVector<double> Velocity_y;
    QVector<double> Velocity_north;
    QVector<double> Velocity_east;
    QVector<double> Position_x_body_frame;
    QVector<double> Position_y_body_frame;
    QVector<double> Position_x_inertial_frame;
    QVector<double> Position_y_inertial_frame;

};

#endif // MAINWINDOW_H
