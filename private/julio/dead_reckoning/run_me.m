%% Read data
% putty_9_car_ride_tona_acatepec_inaoe_wait_large.log
n_input_raw_data = 7961;
%n_input_raw_data = 6826;
n_input_aligned_data = 7901;
%n_input_aligned_data = 6769;
n_output_data=7370;
%n_output_data=7350;
%n_output_data=6314;

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

speed_in_m_per_sec_from_gps = importfile_TelitSL869DR_2columns('RESLT/speed_in_m_per_sec_from_GPS.dat', 1, 531);
acc_in_m_per_sec_from_speed_from_gps = importfile_TelitSL869DR_2columns('RESLT/acc_in_m_per_sec_from_speed_from_GPS.dat', 1, 531);
error_acc_in_m_per_sec_between_gps_and_sensor = importfile_TelitSL869DR_3columns('RESLT/error_acc_in_m_per_sec.dat', 1, 531);

navigation_data_from_GPS = importfile_TelitSL869DR_7columns('RESLT/navigation_data_from_GPS.dat', 1, 531);

initial_raw_time = raw_gyro(1,1);
final_raw_time = raw_gyro(size(raw_gyro,1),1);
initial_time = aligned_gyro(1,1);
final_time = aligned_gyro(size(aligned_gyro,1),1);

%% Filtered and aligned
% % Gyro
% figure
% subplot(2,3,1)
% plot(filtered_gyro(:, 1), filtered_gyro(:, 2)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 2)*180.0/pi, 'r')
% title('[X] Gyro (Filtered vs Aligned Time Stamp)')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
% grid on
% 
% subplot(2,3,2)
% plot(filtered_gyro(:, 1), filtered_gyro(:, 3)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 3)*180.0/pi, 'r')
% title('[Y] Gyro (Filtered vs Aligned Time Stamp)')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
% grid on
%  
% subplot(2,3,3)
% plot(filtered_gyro(:, 1), filtered_gyro(:, 4)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 4)*180.0/pi, 'r')
% title('[Z] Gyro (Filtered vs Aligned Time Stamp)')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
% grid on
% 
% % Acceleration
% subplot(2,3,4)
% plot(filtered_acc(:, 1), filtered_acc(:, 2), 'b', aligned_acc(:, 1), aligned_acc(:, 2), 'r')
% axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
% title('x-acceleration (Filtered vs Aligned Time Stamp)')
% xlabel('Time (s)')
% ylabel('Acceleration (m/s^2)')
% legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
% grid on
% 
% subplot(2,3,5)
% plot(filtered_acc(:, 1), filtered_acc(:, 3), 'b', aligned_acc(:, 1), aligned_acc(:, 3), 'r')
% axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
% title('y-acceleration (Filtered vs Aligned Time Stamp)')
% xlabel('Time (s)')
% ylabel('Acceleration (m/s^2)')
% legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
% grid on
%  
% subplot(2,3,6)
% plot(filtered_acc(:, 1), filtered_acc(:, 4), 'b', aligned_acc(:, 1), aligned_acc(:, 4), 'r')
% axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
% title('z-acceleration (Filtered vs Aligned Time Stamp)')
% xlabel('Time (s)')
% ylabel('Acceleration (m/s^2)')
% legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
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
coefficients_x_velocity = polyfit(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 1)
coefficients_y_velocity = polyfit(velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 1)
% % Plot velocity
figure
%plot(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'b', velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 'r', velocity(:, 1), velocity(:, 4)*m_per_sec_to_km_per_h, 'g')
plot(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'b', velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 'r')
%plot(velocity(:, 1), velocity(:, 2), 'b', velocity(:, 1), velocity(:, 3), 'r')
%hold
%plot(velocity(:, 1), velocity(:, 2) - velocity(:, 1)*coefficients_x_velocity(1)+coefficients_x_velocity(2), 'b', ...
%     velocity(:, 1), velocity(:, 3) - velocity(:, 1)*coefficients_y_velocity(1)+coefficients_y_velocity(2), 'r')
title('Velocity')
xlabel('Time (s)')
ylabel('Velocity km/h')
%legend('x-velocity', 'y-velocity', 'z-velocity', 'Location', 'NorthWest')
legend('x-velocity', 'y-velocity', 'Location', 'NorthWest')
grid on

%velocity(:,2) = velocity(:, 2) - velocity(:, 1)*coefficients_x_velocity(1)+coefficients_x_velocity(2) + 45.0;

%hold
%plot(velocity(:, 1), velocity(:, 1)*coefficients_x_velocity(1)+coefficients_x_velocity(2), 'g')
%plot(velocity(:, 1), velocity(:, 1)*coefficients_y_velocity(1)+coefficients_y_velocity(2), 'm')

%% Frontal accelerations and velocities
figure
plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b', ...
    speed_in_m_per_sec_from_gps(:,1), speed_in_m_per_sec_from_gps(:,2)*m_per_sec_to_km_per_h*0.01, 'b.', ...
    linear_acceleration(:, 1), linear_acceleration(:, 2), 'r', ...
    velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h*0.01, 'r.')
title('[Front of car] Accelerations and Velocities')
xlabel('Time(s)')
ylabel('m/s^2 and km/h')
legend('Acceleration from GPS', 'Velocity from GPS', 'Acceleration from accelerometers', 'Velocity from computations', 'Location', 'NorthWest')
grid on

%% Frontal accelerations and velocities
figure
yyaxis left
plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b', ...
    linear_acceleration(:, 1), linear_acceleration(:, 2), 'r')
title('[Front of car] Accelerations and Velocities')
axis([initial_raw_time final_raw_time -5.0 5.0])
xlabel('Time(s)')
ylabel('m/s^2')
yyaxis right
plot(speed_in_m_per_sec_from_gps(:,1), speed_in_m_per_sec_from_gps(:,2)*m_per_sec_to_km_per_h, 'g.', ...
     velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'm.')
axis([initial_raw_time final_raw_time -80.0 80.0])
ylabel('km/h')
legend('Acceleration from GPS', 'Acceleration from accelerometers', 'Velocity from GPS', 'Velocity from computations', 'Location', 'NorthWest')
grid on

%% Frontal accleration from GPS vs frontal acceleration from accelerometers
% % Acceleration in m/s^2 from speed from GPS vs frontal acceleration in m/s^2 from accelerometers
% figure
% %subplot(1,2,2)
% plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b',  body_acceleration(:, 1), body_acceleration(:, 2), 'r')
% axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
% title('[Front of car] Acceleration from GPS vs acceleration from accelerometers')
% xlabel('Time(s)')
% ylabel('m/s^2')
% legend('Acceleration from GPS', 'Body-frame acceleration from accelerometers', 'Location', 'NorthWest')
% grid on

% Acceleration in m/s^2 from speed from GPS vs frontal acceleration in m/s^2 from accelerometers
figure
%subplot(1,2,2)
plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b',  linear_acceleration(:, 1), linear_acceleration(:, 2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Acceleration from GPS vs linear acceleration')
xlabel('Time(s)')
ylabel('m/s^2')
legend('Acceleration from GPS', 'Linear acceleration', 'Location', 'NorthWest')
grid on

% Error
figure
subplot(1,2,1)
plot(error_acc_in_m_per_sec_between_gps_and_sensor(:,1), error_acc_in_m_per_sec_between_gps_and_sensor(:,2), 'b')
%axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Absolute error - Acceleration from velocity from GPS vs Linear-acceleration in x')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

% Error
subplot(1,2,2)
plot(error_acc_in_m_per_sec_between_gps_and_sensor(:,1), error_acc_in_m_per_sec_between_gps_and_sensor(:,3), 'b')
%axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Relative error - Acceleration from velocity from GPS vs Linear-acceleration in x')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

average_abs_error = mean(error_acc_in_m_per_sec_between_gps_and_sensor(:,2),1)
average_relative_error = mean(error_acc_in_m_per_sec_between_gps_and_sensor(:,3),1)

%% DELETE
delay = 0.05; % Delay in seconds in every loop
n_loop = size(navigation_data_from_GPS, 1)
% Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(navigation_data_from_GPS(1,4), navigation_data_from_GPS(1,5), 'b*'); % Get the plot hanlder
title('Position from velocity from GPS')
axis([min(navigation_data_from_GPS(:,4)) max(navigation_data_from_GPS(:,4)) min(navigation_data_from_GPS(:,5)) max(navigation_data_from_GPS(:,5))])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', navigation_data_from_GPS(i,1), navigation_data_from_GPS(i,4), navigation_data_from_GPS(i,5));
    p.XData(i) = navigation_data_from_GPS(i,4);
    p.YData(i) = navigation_data_from_GPS(i,5);
    %drawnow();
    pause(delay);
end

plot(navigation_data_from_GPS(:,1), navigation_data_from_GPS(:,7),'r')
