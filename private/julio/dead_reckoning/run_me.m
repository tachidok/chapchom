%% Read data
% putty_9_car_ride_tona_acatepec_inaoe_wait_large.log
n_input_raw_data = 7961;
n_input_aligned_data = 7901;
%n_output_data=7370;
n_output_data=7350;
raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, n_input_raw_data);
raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, n_input_raw_data);
rotated_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/rotated_raw_gyro.dat', 1, n_input_raw_data);
rotated_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/rotated_raw_accelerations.dat', 1, n_input_raw_data);
filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, n_input_raw_data);
filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, n_input_raw_data);
aligned_gyro = importfile_TelitSL869DR_3columns('RESLT/aligned_gyro.dat', 1, n_input_aligned_data);
aligned_acc = importfile_TelitSL869DR_3columns('RESLT/aligned_acc.dat', 1, n_input_aligned_data);

euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, n_output_data);
roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, n_output_data);
gravity_in_body_frame = importfile_TelitSL869DR_3columns('RESLT/gravity_in_body_frame.dat', 1, n_output_data);
body_acceleration = importfile_TelitSL869DR_3columns('RESLT/body_accelerations.dat', 1, n_output_data);
body_acceleration_without_gravity = importfile_TelitSL869DR_3columns('RESLT/body_accelerations_without_gravity.dat', 1, n_output_data);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, n_output_data);
linear_acceleration = importfile_TelitSL869DR_3columns('RESLT/linear_accelerations.dat', 1, n_output_data);
velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, n_output_data);

speed_in_m_per_sec_from_gps = importfile_TelitSL869DR_2columns('RESLT/speed_in_m_per_sec_from_GPS.dat', 1, 531);
acc_in_m_per_sec_from_speed_from_gps = importfile_TelitSL869DR_2columns('RESLT/acc_in_m_per_sec_from_speed_from_GPS.dat', 1, 531);
error_acc_in_m_per_sec_between_gps_and_sensor = importfile_TelitSL869DR_3columns('RESLT/error_acc_in_m_per_sec.dat', 1, 531);

initial_raw_time = raw_gyro(1,1);
final_raw_time = raw_gyro(size(raw_gyro,1),1);
initial_time = aligned_gyro(1,1);
final_time = aligned_gyro(size(aligned_gyro,1),1);

%% Filtered and aligned
% Gyro
figure
subplot(2,3,1)
plot(filtered_gyro(:, 1), filtered_gyro(:, 2)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 2)*180.0/pi, 'r')
title('[X] Gyro (Filtered vs Aligned Time Stamp)')
xlabel('Time (s)')
ylabel('d/s')
legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
grid on

subplot(2,3,2)
plot(filtered_gyro(:, 1), filtered_gyro(:, 3)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 3)*180.0/pi, 'r')
title('[Y] Gyro (Filtered vs Aligned Time Stamp)')
xlabel('Time (s)')
ylabel('d/s')
legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
grid on
 
subplot(2,3,3)
plot(filtered_gyro(:, 1), filtered_gyro(:, 4)*180.0/pi, 'b', aligned_gyro(:, 1), aligned_gyro(:, 4)*180.0/pi, 'r')
title('[Z] Gyro (Filtered vs Aligned Time Stamp)')
xlabel('Time (s)')
ylabel('d/s')
legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
grid on

% Acceleration
subplot(2,3,4)
plot(filtered_acc(:, 1), filtered_acc(:, 2), 'b', aligned_acc(:, 1), aligned_acc(:, 2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Filtered vs Aligned Time Stamp)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(filtered_acc(:, 1), filtered_acc(:, 3), 'b', aligned_acc(:, 1), aligned_acc(:, 3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Filtered vs Aligned Time Stamp)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
grid on
 
subplot(2,3,6)
plot(filtered_acc(:, 1), filtered_acc(:, 4), 'b', aligned_acc(:, 1), aligned_acc(:, 4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Filtered vs Aligned Time Stamp)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Filtered', 'Aligned Time Stamp', 'Location', 'NorthWest')
grid on

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

%% Body acceleration vs Body acceleration without gravity
% Body acceleration vs Body acceleration without gravity
figure
subplot(2,3,1)
plot(body_acceleration(:, 1), body_acceleration(:, 2), 'b', body_acceleration_without_gravity(:,1), body_acceleration_without_gravity(:,2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Body vs Body w/o gravity)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Body-frame acceleration w/o gravity', 'Location', 'NorthWest')
grid on

subplot(2,3,2)
plot(body_acceleration(:, 1), body_acceleration(:, 3), 'b', body_acceleration_without_gravity(:,1), body_acceleration_without_gravity(:,3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Body vs Body w/o gravity)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Body-frame acceleration w/o gravity', 'Location', 'NorthWest')
grid on
 
subplot(2,3,3)
plot(body_acceleration(:, 1), body_acceleration(:, 4), 'b', body_acceleration_without_gravity(:,1), body_acceleration_without_gravity(:,4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Body vs Body w/o gravity)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Body-frame acceleration w/o gravity', 'Location', 'NorthWest')
grid on

%% Body accelerartion w/o gravity vs Inertial accelerartion vs Linear accelerartion
% Body accelerartion w/o gravity vs Inertial accelerartion vs Linear accelerartion
subplot(2,3,4)
plot(body_acceleration_without_gravity(:, 1), body_acceleration_without_gravity(:, 2), 'b', inertial_acceleration(:,1), inertial_acceleration(:,2), 'r', linear_acceleration(:,1), linear_acceleration(:,2), 'g')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Body w/o gravity vs Inertial vs Linear)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body w/o gravity', 'Inertial', 'Linear', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(body_acceleration_without_gravity(:, 1), body_acceleration_without_gravity(:, 3), 'b', inertial_acceleration(:,1), inertial_acceleration(:,3), 'r', linear_acceleration(:,1), linear_acceleration(:,3), 'g')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Body w/o gravity vs Inertial vs Linear)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body w/o gravity', 'Inertial', 'Linear', 'Location', 'NorthWest')
grid on
 
subplot(2,3,6)
plot(body_acceleration_without_gravity(:, 1), body_acceleration_without_gravity(:, 4), 'b', inertial_acceleration(:,1), inertial_acceleration(:,4), 'r', linear_acceleration(:,1), linear_acceleration(:,4), 'g')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Body w/o gravity vs Inertial vs Linear)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body w/o gravity', 'Inertial', 'Linear', 'Location', 'NorthWest')
grid on

%% Velocity
m_per_sec_to_km_per_h = 3.6;
% % Plot velocity
figure
%plot(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'b', velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 'r', velocity(:, 1), velocity(:, 4)*m_per_sec_to_km_per_h, 'g')
plot(velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'b', velocity(:, 1), velocity(:, 3)*m_per_sec_to_km_per_h, 'r')
title('Velocity')
xlabel('Time (s)')
ylabel('Velocity km/h')
%legend('x-velocity', 'y-velocity', 'z-velocity', 'Location', 'NorthWest')
legend('x-velocity', 'y-velocity', 'Location', 'NorthWest')
grid on

%% Frontal accelerations and velocities
figure
plotyy(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b', ...
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
xlabel('Time(s)')
ylabel('m/s^2')
yyaxis right
plot(speed_in_m_per_sec_from_gps(:,1), speed_in_m_per_sec_from_gps(:,2)*m_per_sec_to_km_per_h, 'b.', ...
     velocity(:, 1), velocity(:, 2)*m_per_sec_to_km_per_h, 'r.')
ylabel('km/h')
legend('Acceleration from GPS', 'Acceleration from accelerometers', 'Velocity from GPS', 'Velocity from computations', 'Location', 'NorthWest')
grid on

%% Frontal accleration from GPS vs frontal acceleration from accelerometers
% Acceleration in m/s^2 from speed from GPS vs frontal acceleration in m/s^2 from accelerometers
figure
%subplot(1,2,2)
plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b',  body_acceleration(:, 1), body_acceleration(:, 2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Acceleration from GPS vs acceleration from accelerometers')
xlabel('Time(s)')
ylabel('m/s^2')
legend('Acceleration from GPS', 'Acceleration from accelerometers', 'Location', 'NorthWest')
grid on

% Error
figure
subplot(1,2,1)
plot(error_acc_in_m_per_sec_between_gps_and_sensor(:,1), error_acc_in_m_per_sec_between_gps_and_sensor(:,2), 'b')
%axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Absolute error between acceleration from velocity from GPS and accelerometer lecture')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

% Error
subplot(1,2,2)
plot(error_acc_in_m_per_sec_between_gps_and_sensor(:,1), error_acc_in_m_per_sec_between_gps_and_sensor(:,3), 'b')
%axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Relative error between acceleration from velocity from GPS and accelerometer lecture')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

average_abs_error = mean(error_acc_in_m_per_sec_between_gps_and_sensor(:,2),1)
average_relative_error = mean(error_acc_in_m_per_sec_between_gps_and_sensor(:,3),1)
