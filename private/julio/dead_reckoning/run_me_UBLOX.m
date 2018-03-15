%% Read data
clc
clear all
% IDA_40KMPH_1
%Initial_index=0;
%Final_index=13699;
%n_output_data_hardware = 120;
% IDA_40KMPH_2
%Initial_index=0;
%Final_index=16509;
% REGRESO_40KMPH_1
%Initial_index=0;
%Final_index=14209;
% REGRESO_40KMPH_2
%Initial_index=0;
%Final_index=14769;
% IDA_50KMPH_1
%Initial_index=0;
%Final_index=15769;
% IDA_50KMPH_2
%Initial_index=0;
%Final_index=11889;
% REGRESO_50KMPH_1
% REGRESO_50KMPH_2
%Initial_index=0;
%Final_index=13749;
% IDA_60KMPH_1
%Initial_index=0;
%Final_index=9829;
% IDA_60KMPH_2
%Initial_index=0;
%Final_index=12089;
% REGRESO_60KMPH_1
%Initial_index=0;
%Final_index=11909;
% REGRESO_60KMPH_2
%Initial_index=0;
%Final_index=10509;
% IDA_70KMPH_1
Initial_index=0;
Final_index=7699;
n_output_data_hardware = 120;
% IDA_70KMPH_2
%Initial_index=0;
%Final_index=8769;
% REGRESO_70KMPH_1
%Initial_index=0;
%Final_index=8999;
% REGRESO_70KMPH_2
%Initial_index=0;
%Final_index=9399;
% IDA_80KMPH_1
%Initial_index=0;
%Final_index=6109;
% IDA_80KMPH_2
%Initial_index=0;
%Final_index=8639;
% REGRESO_80KMPH_1
%Initial_index=0;
%Final_index=6649;
% REGRESO_80KMPH_2
%Initial_index=0;
%Final_index=7839;
% IDA_90KMPH_1
%Initial_index=0;
%Final_index=11559;
% REGRESO_90KMPH_1
%Initial_index=0;
%Final_index=15249;

n_input_raw_data = Final_index-Initial_index+1;
n_input_aligned_data = n_input_raw_data;
%n_output_data=11030;
n_output_data=n_input_aligned_data;

raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, n_input_raw_data);
raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, n_input_raw_data);
rotated_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/rotated_raw_gyro.dat', 1, n_input_raw_data);
rotated_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/rotated_raw_accelerations.dat', 1, n_input_raw_data);
filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, n_input_raw_data);
filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, n_input_raw_data);
aligned_gyro = importfile_TelitSL869DR_3columns('RESLT/aligned_gyro.dat', 1, n_input_aligned_data);
aligned_acc = importfile_TelitSL869DR_3columns('RESLT/aligned_acc.dat', 1, n_input_aligned_data);

euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, n_output_data);
euler_angles_from_gyro = importfile_TelitSL869DR_3columns('RESLT/euler_angles_from_gyro.dat', 1, n_output_data);
euler_angles_from_accelerometer = importfile_TelitSL869DR_3columns('RESLT/euler_angles_from_accelerometer.dat', 1, n_output_data);
roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, n_output_data);
gravity_in_body_frame = importfile_TelitSL869DR_3columns('RESLT/gravity_in_body_frame.dat', 1, n_output_data);
body_acceleration = importfile_TelitSL869DR_3columns('RESLT/body_accelerations.dat', 1, n_output_data);
linear_acceleration = importfile_TelitSL869DR_3columns('RESLT/linear_accelerations.dat', 1, n_output_data);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, n_output_data);
velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, n_output_data);
velocity_north_east_down = importfile_TelitSL869DR_4columns('RESLT/velocity_north_east.dat', 1, n_output_data);

navigation_data = importfile_GEOFOG3D_8columns('RESLT/navigation_data_for_evaluation.dat', 1, n_output_data);
latitude_and_longitude = importfile_TelitSL869DR_3columns('RESLT/latitude_and_longitude.dat', 1, n_output_data);


latitude_and_longitude_hardware = importfile_TelitSL869DR_3columns('RESLT/40KMPH_IDA1_HW.dat', 1, n_output_data_hardware);

initial_raw_time = raw_gyro(1,1);
final_raw_time = raw_gyro(size(raw_gyro,1),1);
initial_time = aligned_gyro(1,1);
final_time = aligned_gyro(size(aligned_gyro,1),1);

%% RAW DATA
% Raw and aligned
% Gyro
figure
subplot(2,3,1)
plot(raw_gyro(:, 1), raw_gyro(:, 2)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 2)*180.0/pi, 'r')
title('[X] Gyro (Raw vs Filtered)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

subplot(2,3,2)
plot(raw_gyro(:, 1), raw_gyro(:, 3)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 3)*180.0/pi, 'r')
title('[Y] Gyro (Raw vs Filtered)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on
 
subplot(2,3,3)
plot(raw_gyro(:, 1), raw_gyro(:, 4)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 4)*180.0/pi, 'r')
title('[Z] Gyro (Raw vs Filtered)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

diff_rotated_raw_gyro = rotated_raw_gyro - raw_gyro;
max_diff_rotated_raw_gyro = max(diff_rotated_raw_gyro)

diff_filtered_raw_gyro = filtered_gyro - raw_gyro;
max_diff_filtered_raw_gyro = max(diff_filtered_raw_gyro)

diff_aligned_raw_gyro = aligned_gyro - raw_gyro;
max_diff_aligned_raw_gyro = max(diff_aligned_raw_gyro)

% Acceleration
subplot(2,3,4)
plot(raw_accelerations(:, 1), raw_accelerations(:, 2), 'b', aligned_acc(:, 1), aligned_acc(:, 2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Raw vs Filtered)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(raw_accelerations(:, 1), raw_accelerations(:, 3), 'b', aligned_acc(:, 1), aligned_acc(:, 3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Raw vs Filtered)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on
 
subplot(2,3,6)
plot(raw_accelerations(:, 1), raw_accelerations(:, 4), 'b', aligned_acc(:, 1), aligned_acc(:, 4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Raw vs Filtered)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

diff_rotated_raw_acc = rotated_raw_accelerations - raw_accelerations;
max_diff_rotated_raw_acc = max(diff_rotated_raw_acc)

diff_filtered_raw_acc = filtered_acc - raw_accelerations;
max_diff_filtered_raw_acc = max(diff_filtered_raw_acc)

diff_aligned_raw_acc = aligned_acc - raw_accelerations;
max_diff_aligned_raw_acc = max(diff_aligned_raw_acc)

% %% Compare Euler angles rates from MORE_DATA and computed by algorithm
% % MORE_DATA
% figure
% subplot(2,3,1)
% plot(second_gyro_from_table(:, 1), second_gyro_from_table(:, 2)*180.0/pi, 'b')
% title('MORE_DATA [X] Gyro (Second)')
% xlabel('Time (s)')
% ylabel('d/s')
% grid on
% 
% subplot(2,3,2)
% plot(second_gyro_from_table(:, 1), second_gyro_from_table(:, 3)*180.0/pi, 'b')
% title('MORE_DATA [Y] Gyro (Second)')
% xlabel('Time (s)')
% ylabel('d/s')
% grid on
%  
% subplot(2,3,3)
% plot(second_gyro_from_table(:, 1), second_gyro_from_table(:, 4)*180.0/pi, 'b')
% title('MORE_DATA [Z] Gyro (Second)')%% Read data
% xlabel('Time (s)')
% ylabel('d/s')
% grid on
% 
% % Euler angle rates from algorithm
% subplot(2,3,4)
% plot(euler_angles_rates(:, 1), euler_angles_rates(:, 2)*180.0/pi, 'r')
% title('[X] Gyro (Second)')
% xlabel('Time (s)')
% ylabel('d/s')
% grid on
% 
% subplot(2,3,5)
% plot(euler_angles_rates(:, 1), euler_angles_rates(:, 3)*180.0/pi, 'r')
% title('[Y] Gyro (Second)')
% xlabel('Time (s)')
% ylabel('d/s')
% grid on
%  
% subplot(2,3,6)
% plot(euler_angles_rates(:, 1), euler_angles_rates(:, 4)*180.0/pi, 'r')
% title('[Z] Gyro (Second)')
% xlabel('Time (s)')
% ylabel('d/s')
% grid on
% 
% interpolated_euler_angles_rates_roll = interp1(euler_angles_rates(:,1), euler_angles_rates(:,2), second_gyro_from_table(:,1));
% interpolated_euler_angles_rates_pitch = interp1(euler_angles_rates(:,1), euler_angles_rates(:,3), second_gyro_from_table(:,1));
% interpolated_euler_angles_rates_yaw = interp1(euler_angles_rates(:,1), euler_angles_rates(:,4), second_gyro_from_table(:,1));
% diff_euler_angles_rates_roll_from_algorithm_vs_GEOFOG3D = abs(interpolated_euler_angles_rates_roll - second_gyro_from_table(:,2));
% diff_euler_angles_rates_pitch_from_algorithm_vs_GEOFOG3D = abs(interpolated_euler_angles_rates_pitch - second_gyro_from_table(:,3));
% diff_euler_angles_rates_yaw_from_algorithm_vs_GEOFOG3D = abs(interpolated_euler_angles_rates_yaw - second_gyro_from_table(:,4));
% max_diff_euler_angles_rates_roll_from_algorithm_vs_GEOFOG3D = max(diff_euler_angles_rates_roll_from_algorithm_vs_GEOFOG3D)
% max_diff_euler_angles_rates_pitch_from_algorithm_vs_GEOFOG3D = max(diff_euler_angles_rates_pitch_from_algorithm_vs_GEOFOG3D)
% max_diff_euler_angles_rates_yaw_from_algorithm_vs_GEOFOG3D = max(diff_euler_angles_rates_yaw_from_algorithm_vs_GEOFOG3D)
% figure()
% plot(second_gyro_from_table(:,1), diff_euler_angles_rates_roll_from_algorithm_vs_GEOFOG3D*180.0/pi, 'r', ...
%      second_gyro_from_table(:,1), diff_euler_angles_rates_pitch_from_algorithm_vs_GEOFOG3D*180.0/pi, 'g', ...
%      second_gyro_from_table(:,1), diff_euler_angles_rates_yaw_from_algorithm_vs_GEOFOG3D*180.0/pi, 'b')
% title('[ERROR] Euler angles rates')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Roll', 'Pitch', 'Yaw', 'NorthWest')
% grid on

%% Euler angles from gyro and accelerometer
% % Euler angles from gyro
% figure
% subplot(2,3,1)
% plot(euler_angles_from_gyro(:,1), euler_angles_from_gyro(:,2)*180.0/pi, 'b')
% axis([initial_raw_time final_raw_time -180 180])
% title('Euler angle from gyro [roll]')
% xlabel('Time (s)')
% ylabel('\phi (degrees)')
% grid on
% 
% subplot(2,3,2)
% plot(euler_angles_from_gyro(:,1), euler_angles_from_gyro(:,3)*180.0/pi, 'b')
% axis([initial_raw_time final_raw_time -180 180])
% title('Euler angle from gyro [pitch]')
% xlabel('Time(s)')
% ylabel('\theta (degrees)')
% grid on
% 
% subplot(2,3,3)
% plot(euler_angles_from_gyro(:,1), euler_angles_from_gyro(:,4)*180.0/pi, 'b')
% axis([initial_raw_time final_raw_time -180 180])
% title('Euler angle from gyro [yaw]')
% xlabel('Time(s)')
% ylabel('\theta (degrees)')
% grid on
% 
% % Euler angles from accelerometers
% subplot(2,3,4)
% plot(euler_angles_from_accelerometer(:,1), euler_angles_from_accelerometer(:,2)*180.0/pi, 'r')
% axis([initial_raw_time final_raw_time -180 180])
% title('Euler angle from accelerometer [roll]')
% xlabel('Time (s)')
% ylabel('\phi (degrees)')
% grid on
% 
% subplot(2,3,5)
% plot(euler_angles_from_accelerometer(:,1), euler_angles_from_accelerometer(:,3)*180.0/pi, 'r')
% axis([initial_raw_time final_raw_time -180 180])
% title('Euler angle from accelerometer [pitch]')
% xlabel('Time(s)')
% ylabel('\theta (degrees)')
% grid on
% 
% subplot(2,3,6)
% plot(euler_angles_from_accelerometer(:,1), euler_angles_from_accelerometer(:,4)*180.0/pi, 'r')
% axis([initial_raw_time final_raw_time -180 180])
% title('Euler angle from accelerometer [yaw]')
% xlabel('Time(s)')
% ylabel('\theta (degrees)')
% grid on

%% Roll, pitch, yaw and body acceleration vs gravity in body frame
% Roll, pitch and yaw
% Processed roll
figure
subplot(2,3,1)
plot(roll_pitch_yaw(:,1), roll_pitch_yaw(:,2)*180.0/pi, 'b')
axis([initial_raw_time final_raw_time -180 180])
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
grid on

% Processed pitch
subplot(2,3,2)
plot(roll_pitch_yaw(:,1), roll_pitch_yaw(:,3)*180.0/pi, 'b')
axis([initial_raw_time final_raw_time -180 180])
title('Euler angle [pitch]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
grid on

% Processed yaw
subplot(2,3,3)
plot(roll_pitch_yaw(:,1), roll_pitch_yaw(:,4)*180.0/pi, 'b')
axis([initial_raw_time final_raw_time -180 180])
title('Euler angle [yaw]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
grid on

% Body acceleration vs Gravity in body frame
subplot(2,3,4)
plot(body_acceleration(:, 1), body_acceleration(:, 2), 'b', gravity_in_body_frame(:,1), gravity_in_body_frame(:,2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Body vs Gravity in body frame)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Gravity body frame', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(body_acceleration(:, 1), body_acceleration(:, 3), 'b', gravity_in_body_frame(:,1), gravity_in_body_frame(:,3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Body vs Gravity in body frame)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Gravity body frame', 'Location', 'NorthWest')
grid on

subplot(2,3,6)
plot(body_acceleration(:, 1), body_acceleration(:, 4), 'b', gravity_in_body_frame(:,1), gravity_in_body_frame(:,4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Body vs Gravity in body frame)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Gravity body frame', 'Location', 'NorthWest')
grid on

%% Body acceleration vs Linear acceleration AND Linear accelerartion vs Inertial accelerartion 
% Body acceleration vs Linear acceleration
figure
subplot(2,3,1)
plot(body_acceleration(:, 1), body_acceleration(:, 2), 'b', linear_acceleration(:,1), linear_acceleration(:,2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Body vs Linear)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-acceleration', 'Linear-acceleration', 'Location', 'NorthWest')
grid on

subplot(2,3,2)
plot(body_acceleration(:, 1), body_acceleration(:, 3), 'b', linear_acceleration(:,1), linear_acceleration(:,3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Body vs Linear)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-acceleration', 'Linear-acceleration', 'Location', 'NorthWest')
grid on
 
subplot(2,3,3)
plot(body_acceleration(:, 1), body_acceleration(:, 4), 'b', linear_acceleration(:,1), linear_acceleration(:,4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Body vs Linear)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-acceleration', 'Linear-acceleration', 'Location', 'NorthWest')
grid on

% Linear accelerartion vs Inertial accelerartion
subplot(2,3,4)
plot(linear_acceleration(:, 1), linear_acceleration(:, 2), 'r', inertial_acceleration(:,1), inertial_acceleration(:,2), 'g')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Linear vs Inertial)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Linear', 'Inertial', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(linear_acceleration(:, 1), linear_acceleration(:, 3), 'r', inertial_acceleration(:,1), inertial_acceleration(:,3), 'g')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Linear vs Inertial)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Linear', 'Inertial', 'Location', 'NorthWest')
grid on
 
subplot(2,3,6)
plot(linear_acceleration(:, 1), linear_acceleration(:, 4), 'r', inertial_acceleration(:,1), inertial_acceleration(:,4), 'g')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Linear vs Inertial)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Linear', 'Inertial', 'Location', 'NorthWest')
grid on

%% Velocity
m_per_sec_to_km_per_h = 3.6;
% % Plot velocity
figure
plot(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'b', velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 'r')
title('Velocity')
xlabel('Time (s)')
ylabel('Velocity km/h')
%legend('x-velocity', 'y-velocity', 'z-velocity', 'Location', 'NorthWest')
legend('x-velocity', 'y-velocity', 'Location', 'NorthWest')
grid on

diff_velocity = back_velocity - velocity

back_velocity = velocity;

%hold
%plot(velocity(:, 1), velocity(:, 1)*coefficients_x_velocity(1)+coefficients_x_velocity(2), 'g')
%plot(velocity(:, 1), velocity(:, 1)*coefficients_y_velocity(1)+coefficients_y_velocity(2), 'm')

%% Frontal accelerations and velocities
m_per_sec_to_km_per_h = 3.6;
figure
yyaxis left
plot(linear_acceleration(:, 1), linear_acceleration(:, 2), 'r')
title('[Front] Accelerations and Velocities')
axis([initial_raw_time final_raw_time -5.0 5.0])
xlabel('Time(s)')
ylabel('m/s^2')
yyaxis right
plot(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'm')
%axis([initial_raw_time final_raw_time -80.0 80.0])
ylabel('km/h')
legend('Acceleration from accelerometers', 'Velocity from computations', 'Location', 'NorthWest')
grid on

% Lateral accelerations and velocities
m_per_sec_to_km_per_h = 3.6;
figure
yyaxis left
plot(linear_acceleration(:, 1), linear_acceleration(:, 3), 'r')
title('[Lateral] Accelerations and Velocities')
axis([initial_raw_time final_raw_time -5.0 5.0])
xlabel('Time(s)')
ylabel('m/s^2')
yyaxis right
plot(velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 'm')
%axis([initial_raw_time final_raw_time -80.0 80.0])
ylabel('km/h')
legend('Acceleration from accelerometers', 'Velocity from computations', 'Location', 'NorthWest')
grid on

%% Google-maps stuff
t   =  navigation_data(:,1);          % estampa de tiempo (seg)

lon = navigation_data(:,2);          % longitud(decimales) 

lat =  navigation_data(:,3);          % latitud(decimales) 

distancia= navigation_data(:,7);      % distancia relativa entre puntos (m)
var_rumbo= navigation_data(:,8);     % rumbo del vehiculo ()
%var_rumbo= navigation_data(:,8)-37;     % rumbo del vehiculo ()
                        % correccion de signo 
%% CALCULO
%rumbo_inicial=37;  %Rumbo inicial(�) desde el cual comienza la nevegaci�n
rumbo_inicial=0;  %Rumbo inicial(�) desde el cual comienza la nevegaci�n
[new_lat,new_lon,Error]=calc_nav(lat,lon,distancia,rumbo_inicial,var_rumbo);

figure
plot(lon, lat, 'r', new_lon, new_lat, 'g', latitude_and_longitude(:,3), latitude_and_longitude(:,2), 'b')
hold on
title('Position')
xlabel('Longitude')
ylabel('Latitude')
legend('Reference trajectory', 'Our algorithm trajectory', 'Location', 'NorthWest')
plot_google_map2('Refresh','1','maptype','terrain','AutoAxis','1','FigureResizeUpdate','1')
hold off

figure
plot(lon, lat, 'r', new_lon, new_lat, 'g', 'LineWidth', 3)
hold on
title('Position')
xlabel('Longitude')
ylabel('Latitude')
legend('Reference trajectory', 'Our algorithm trajectory', 'Location', 'NorthWest')
plot_google_map2('Refresh','1','maptype','terrain','AutoAxis','1','FigureResizeUpdate','1')
hold off

figure
plot(lon, lat, 'r', new_lon, new_lat, 'g', latitude_and_longitude_hardware(:,3), latitude_and_longitude_hardware(:,2), 'b', 'LineWidth', 3)
hold on
title('Position')
xlabel('Longitude')
ylabel('Latitude')
legend('Reference trajectory', 'Offline algorithm', 'Hardware algorithm', 'Location', 'NorthWest')
plot_google_map2('Refresh','1','maptype','terrain','AutoAxis','1','FigureResizeUpdate','1')
hold off

figure
plot(t,Error)
title('Position error')
xlabel('Time (s)')
ylabel('Error (m)')
grid on

max(Error)

%% Plot lat-lon imported to show full trajectory
figure
plot(latlon(:,2), latlon(:,1), 'r')
hold on
title('Position')
xlabel('Longitude')
ylabel('Latitude')
plot_google_map2('Refresh','1','maptype','terrain','AutoAxis','1','FigureResizeUpdate','1')
hold off

%% POSITION
% This method uses XPOS and YPOS from the file which are computes from the
% X and Y velocities times the cos/sin, respectively, of the course angle
delay = 0.0005; % Delay in seconds in every loop
n_loop = size(navigation_data, 1);
% Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(navigation_data(1,5), navigation_data(1,6), 'b*'); % Get the plot hanlder
title('Position from velocity from GPS')
axis([min(navigation_data(:,5)) max(navigation_data(:,5)) min(navigation_data(:,6)) max(navigation_data(:,6))])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (x=%.2f, y=%.2f a=%2.f)', navigation_data(i,1), navigation_data(i,5), navigation_data(i,6), navigation_data(i,8));
    p.XData(i) = navigation_data(i,5);
    p.YData(i) = navigation_data(i,6);
    %drawnow();
    pause(delay);
end

diff_navigation_data = navigation_data - back_navigation_data;
max_diff_navigation_data = max(diff_navigation_data(:,8))
mean_diff_navigation_data = mean(diff_navigation_data(:,8))

figure
plot(navigation_data(:,1), diff_navigation_data(:,8)*180.0/pi, 'r')
title('[ERROR] Euler Yaw (degrees)')
xlabel('Time (s)')
ylabel('d')
grid on

back_navigation_data = navigation_data;

%% Here for velocity from acc
n_data = size(velocity, 1)
n_seconds_of_test = n_data;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
% Get the data at the specific times [1:n_data] seconds
seconds = [1:n_data];
for i=2:n_data
    x(i) = x(i-1) + velocity(i, 2) * cos(roll_pitch_yaw(i,4));
    y(i) = y(i-1) + velocity(i, 3) * sin(roll_pitch_yaw(i,4));
end
% Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(x(1), y(1), 'b*'); % Get the plot hanlder
title('Position from velocity')
axis([min(x(:)) max(x(:)) min(y(:)) max(y(:))])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

for i = 1:n_data
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', velocity(i,1), x(i), y(i));
    p.XData(i) = x(i);
    p.YData(i) = y(i);
    %drawnow();
    pause(delay);
end