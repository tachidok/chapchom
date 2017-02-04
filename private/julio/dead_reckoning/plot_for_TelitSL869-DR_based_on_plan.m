
%% Read data
% putty_8_car_ride_square_wait_large.log
initial_time = 0;
final_time = 478;
n_input_data = 6651;
%n_output_data = 7901;
n_output_data = 6839; % order 2
n_output_data = 5246; % order 4
n_output_data = 3122; % order 8
n_output_data = 1005; % order 12
n_output_data = 478; % order 14
%n_output_data = 14804; % order 14
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, n_input_data);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, n_input_data);
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, n_output_data);
my_true_course_in_degrees = importfile_TelitSL869DR_2columns('RESLT/true_course_in_degrees.dat', 1, n_output_data);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, n_output_data);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, n_output_data);
my_inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, n_output_data);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, n_output_data);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, n_output_data);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, n_output_data);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, n_output_data);

%% Read data
% putty_9_car_ride_tona_acatepec_inaoe_wait_large.log
n_input_raw_data = 7961;
n_input_aligned_data = 7901;
n_output_data=7370;
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
linear_acceleration = importfile_TelitSL869DR_3columns('RESLT/linear_accelerations.dat', 1, n_output_data);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, n_output_data);
velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, n_output_data);

speed_in_m_per_sec_from_gps = importfile_TelitSL869DR_2columns('RESLT/speed_in_m_per_sec_from_GPS.dat', 1, 531);
acc_in_m_per_sec_from_speed_from_gps = importfile_TelitSL869DR_2columns('RESLT/acc_in_m_per_sec_from_speed_from_GPS.dat', 1, 531);
error_acc_in_m_per_sec_between_gps_and_sensor = importfile_TelitSL869DR_3columns('RESLT/error_acc_in_m_per_sec.dat', 1, 531);

initial_raw_time = raw_gyro(1,1);
final_raw_time = raw_gyro(size(raw_gyro,1),1);
initial_time = aligned_gyro(1,1);
final_time = aligned_gyro(size(aligned_gyro,1),1);

%% Raw gyro and acceleration
figure
subplot(2,3,1)
plot(raw_gyro(:, 1), raw_gyro(:, 2)*180.0/pi, 'b')
title('[X] Gyro  (gyro system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
grid on

subplot(2,3,2)
plot(raw_gyro(:, 1), raw_gyro(:, 3)*180.0/pi, 'b')
title('[Y] Gyro  (gyro system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
grid on
 
subplot(2,3,3)
plot(raw_gyro(:, 1), raw_gyro(:, 4)*180.0/pi, 'b')
title('[Z] Gyro  (gyro system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
grid on

subplot(2,3,4)
plot(raw_accelerations(:, 1), raw_accelerations(:, 2), 'b')
axis([initial_raw_time final_raw_time -1.5 1.5])
%axis([initial_time final_time -5 15])
title('x-acceleration (acc system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
grid on

subplot(2,3,5)
plot(raw_accelerations(:, 1), raw_accelerations(:, 3), 'b')
axis([initial_raw_time final_raw_time -1.5 1.5])
%axis([initial_time final_time -5 15])
title('y-acceleration (acc system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
grid on
 
subplot(2,3,6)
plot(raw_accelerations(:, 1), raw_accelerations(:, 4), 'b')
axis([initial_raw_time final_raw_time -1.5 1.5])
%axis([initial_time final_time -5 15])
title('z-acceleration (acc system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
grid on

%% Rotated gyro and acceleration
figure
subplot(2,3,1)
plot(rotated_raw_gyro(:, 1), rotated_raw_gyro(:, 2)*180.0/pi, 'b')
title('[X] Gyro (ASIKIs system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
grid on

subplot(2,3,2)
plot(rotated_raw_gyro(:, 1), rotated_raw_gyro(:, 3)*180.0/pi, 'b')
title('[Y] Gyro (ASIKIs system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
grid on

subplot(2,3,3)
plot(rotated_raw_gyro(:, 1), rotated_raw_gyro(:, 4)*180.0/pi, 'b')
title('[Z] Gyro (ASIKIs system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
grid on

subplot(2,3,4)
plot(rotated_raw_accelerations(:, 1), rotated_raw_accelerations(:, 2), 'b')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (ASIKIs system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
grid on

subplot(2,3,5)
plot(rotated_raw_accelerations(:, 1), rotated_raw_accelerations(:, 3), 'b')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (ASIKIs system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
grid on
 
subplot(2,3,6)
plot(rotated_raw_accelerations(:, 1), rotated_raw_accelerations(:, 4), 'b')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (ASIKIs system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
grid on

%% Rotated raw and filtered
% Gyro
figure
subplot(2,3,1)
plot(rotated_raw_gyro(:, 1), rotated_raw_gyro(:, 2)*180.0/pi, 'b', filtered_gyro(:, 1), filtered_gyro(:, 2)*180.0/pi, 'r')
title('[X] Gyro (Raw vs filtered)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

subplot(2,3,2)
plot(rotated_raw_gyro(:, 1), rotated_raw_gyro(:, 3)*180.0/pi, 'b', filtered_gyro(:, 1), filtered_gyro(:, 3)*180.0/pi, 'r')
title('[Y] Gyro (Raw vs filtered)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on
 
subplot(2,3,3)
plot(rotated_raw_gyro(:, 1), rotated_raw_gyro(:, 4)*180.0/pi, 'b', filtered_gyro(:, 1), filtered_gyro(:, 4)*180.0/pi, 'r')
title('[Z] Gyro (Raw vs filtered)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

% Acceleration
subplot(2,3,4)
plot(rotated_raw_accelerations(:, 1), rotated_raw_accelerations(:, 2), 'b', filtered_acc(:, 1), filtered_acc(:, 2), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('x-acceleration (Raw vs filtered)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(rotated_raw_accelerations(:, 1), rotated_raw_accelerations(:, 3), 'b', filtered_acc(:, 1), filtered_acc(:, 3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Raw vs filtered)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on
 
subplot(2,3,6)
plot(rotated_raw_accelerations(:, 1), rotated_raw_accelerations(:, 4), 'b', filtered_acc(:, 1), filtered_acc(:, 4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Raw vs filtered)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw', 'Filtered', 'Location', 'NorthWest')
grid on

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

% %% Aligned gyro vs Euler angular rates
% figure
% plot(aligned_gyro(:, 1), aligned_gyro(:, 2)*180.0/pi, 'b', euler_angles_rates(:,1), euler_angles_rates(:,2)*180.0/pi, 'r')
% title('[X] Gyro (Aligned vs Euler anglular rate)')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Gyro aligned Time Stamp', 'Euler angular rate', 'Location', 'NorthWest')
% grid on
% 
% figure
% plot(aligned_gyro(:, 1), aligned_gyro(:, 3)*180.0/pi, 'b', euler_angles_rates(:,1), euler_angles_rates(:,3)*180.0/pi, 'r')
% title('[Y] Gyro (Aligned vs Euler anglular rate)')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Gyro aligned Time Stamp', 'Euler angular rate', 'Location', 'NorthWest')
% grid on
%  
% figure
% plot(aligned_gyro(:, 1), aligned_gyro(:, 4)*180.0/pi, 'b', euler_angles_rates(:,1), euler_angles_rates(:,4)*180.0/pi, 'r')
% title('[Z] Gyro (Aligned vs Euler anglular rate)')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Gyro aligned Time Stamp', 'Euler angular rate', 'Location', 'NorthWest')
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
legend('Body-frame acceleration', 'Gravity', 'Location', 'NorthWest')
grid on

subplot(2,3,5)
plot(body_acceleration(:, 1), body_acceleration(:, 3), 'b', gravity_in_body_frame(:,1), gravity_in_body_frame(:,3), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('y-acceleration (Body vs Gravity in body frame)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Gravity', 'Location', 'NorthWest')
grid on

subplot(2,3,6)
plot(body_acceleration(:, 1), body_acceleration(:, 4), 'b', gravity_in_body_frame(:,1), gravity_in_body_frame(:,4), 'r')
axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('z-acceleration (Body vs Gravity in body frame)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Body-frame acceleration', 'Gravity', 'Location', 'NorthWest')
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
meters_to_kilometers = 1/1000;
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

%% Position (Yo)
n_data = size(velocity,1);
n_seconds_of_test = -n_data / 14.0;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
for i=2:n_data
    x(i) = step_size * velocity(i, 2) * cos(roll_pitch_yaw(i,4)) + x(i-1);
    y(i) = step_size * velocity(i, 2) * sin(roll_pitch_yaw(i,4)) + y(i-1);
end
% % Plot position
figure();
plot(x, y, 'b')
axis([min(x) max(x) min(y) max(y)])
title('Position')
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

delay = 0.005; % Delay in seconds in every loop
n_loop = size(x, 1)
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(x(1), y(1), 'b'); % Get the plot hanlder
axis([min(x) max(x) min(y) max(y)])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', velocity(i, 1), x(i), y(i)); % Update title
    p.XData(i) = x(i);
    p.YData(i) = y(i);
    %drawnow();
    pause(delay);
end

%% Speed and accleration from GPS
% Speed in m/s from GPS
figure
%subplot(1,2,1)
plot(speed_in_m_per_sec_from_gps(:,1), speed_in_m_per_sec_from_gps(:,2), 'b')
title('[Front of car] Speed from GPS')
xlabel('Time(s)')
ylabel('km/h')
grid on

% Acceleration in m/s^2 from speed from GPS
figure
%subplot(1,2,2)
plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b')
title('[Front of car] Acceleration from GPS')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

%% Frontal accleration from GPS vs frontal acceleration from accelerometers
% Acceleration in m/s^2 from speed from GPS vs frontal acceleration in m/s^2 from accelerometers
figure
%subplot(1,2,2)
%plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b',  aligned_acc(:, 1), aligned_acc(:, 2)-0.2902, 'r')
plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b',  body_acceleration(:, 1), body_acceleration(:, 2), 'r')
%plot(acc_in_m_per_sec_from_speed_from_gps(:,1), acc_in_m_per_sec_from_speed_from_gps(:,2), 'b',  aligned_acc(:, 1), aligned_acc(:, 2)*0.8705, 'r')
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
title('[Front of car] Absolute error - Acceleration from velocity from GPS vs Body-acceleration in x')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

% Error
subplot(1,2,2)
plot(error_acc_in_m_per_sec_between_gps_and_sensor(:,1), error_acc_in_m_per_sec_between_gps_and_sensor(:,3), 'b')
%axis([initial_raw_time final_raw_time -9.8*1.5 9.8*1.5])
title('[Front of car] Relative error - Acceleration from velocity from GPS vs Body-acceleration in x')
xlabel('Time(s)')
ylabel('m/s^2')
grid on

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

%% Position (From velocity from GPS)
n_data = size(speed_in_m_per_sec_from_gps ,1);
n_seconds_of_test = n_data;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
% Get the data at the specific times [1:n_data] seconds
seconds = [1:n_data];
angle_at_specific_second = interp1(roll_pitch_yaw(:,1), roll_pitch_yaw(:,4), seconds);
for i=2:n_data
    x(i) = step_size * speed_in_m_per_sec_from_gps(i, 2) * cos(angle_at_specific_second(i)) + x(i-1);
    y(i) = step_size * speed_in_m_per_sec_from_gps(i, 2) * sin(angle_at_specific_second(i)) + y(i-1);
end
% % Plot position
figure();
plot(x, y, 'b')
axis([min(x) max(x) min(y) max(y)])
title('Position from velocity from GPS')
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

delay = 0.0005; % Delay in seconds in every loop
n_loop = size(x, 1)
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(x(1), y(1), 'b*'); % Get the plot hanlder
axis([min(x) max(x) min(y) max(y)])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')
grid on

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', seconds(i), x(i), y(i)); % Update title
    p.XData(i) = x(i);
    p.YData(i) = y(i);
    %drawnow();
    pause(delay);
end

% x-position vs time and y-position vs time
figure
plot(speed_in_m_per_sec_from_gps(:, 1), x * meters_to_kilometers, 'b', speed_in_m_per_sec_from_gps(:, 1), y * meters_to_kilometers, 'r')
title('x-displacement and y-displacement')
xlabel('time (s)')
ylabel('displ (km)')
legend('x-displacement', 'y-displacement', 'Location', 'NorthWest')


















%% Position (Luis Chico)
n_data = size(my_velocity,1);
n_seconds_of_test = n_data / 15.0;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = 1.0/14.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
for i=2:n_data
    %x(i) = my_velocity(i, 2)*m_per_sec_to_km_per_h * cos(my_true_course_in_degrees(i,2)*pi/180.0) + x(i-1);
    %y(i) = my_velocity(i, 2)*m_per_sec_to_km_per_h * sin(my_true_course_in_degrees(i,2)*pi/180.0) + y(i-1);
    x(i) = step_size * my_velocity(i, 2) * cos(my_true_course_in_degrees(i,2)*pi/180.0) + x(i-1);
    y(i) = step_size * my_velocity(i, 2) * sin(my_true_course_in_degrees(i,2)*pi/180.0) + y(i-1);
end
% % Plot position
figure();
plot(x, y, 'b*')
axis([min(x) max(x) min(y) max(y)])
title('Position')
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

delay = 0.005; % Delay in seconds in every loop
n_loop = size(x, 1)
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(x(1), y(1), 'b*'); % Get the plot hanlder
axis([min(x) max(x) min(y) max(y)])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', my_position(i, 1), x(i), y(i)); % Update title
    p.XData(i) = x(i);
    p.YData(i) = y(i);
    %drawnow();
    pause(delay);
end

%% Position (Yo)
n_data = size(my_velocity,1);
n_seconds_of_test = n_data / 14.0;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
for i=2:n_data
    x(i) = step_size * my_velocity(i, 2) * cos(my_roll_pitch_yaw(i,4)) + x(i-1);
    y(i) = step_size * my_velocity(i, 2) * sin(my_roll_pitch_yaw(i,4)) + y(i-1);
end
% % Plot position
figure();
plot(x, y, 'b')
axis([min(x) max(x) min(y) max(y)])
title('Position')
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

delay = 0.005; % Delay in seconds in every loop
n_loop = size(x, 1)
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(x(1), y(1), 'b*'); % Get the plot hanlder
axis([min(x) max(x) min(y) max(y)])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', my_position(i, 1), x(i), y(i)); % Update title
    p.XData(i) = x(i);
    p.YData(i) = y(i);
    %drawnow();
    pause(delay);
end

%% Position (From velocity from GPS)
n_data = size(my_speed_in_m_per_sec ,1);
n_seconds_of_test = n_data;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
% Get the data at the specific times [1:n_data] seconds
seconds = [1:n_data];
angle_at_specific_second = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4), seconds);
for i=2:n_data
    x(i) = step_size * my_speed_in_m_per_sec(i, 2) * cos(angle_at_specific_second(i)) + x(i-1);
    y(i) = step_size * my_speed_in_m_per_sec(i, 2) * sin(angle_at_specific_second(i)) + y(i-1);
end
% % Plot position
figure();
plot(x, y, 'b')
axis([min(x) max(x) min(y) max(y)])
title('Position from velocity from GPS')
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

delay = 0.005; % Delay in seconds in every loop
n_loop = size(x, 1)
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(x(1), y(1), 'b*'); % Get the plot hanlder
axis([min(x) max(x) min(y) max(y)])
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', seconds(i), x(i), y(i)); % Update title
    p.XData(i) = x(i);
    p.YData(i) = y(i);
    %drawnow();
    pause(delay);
end

% x-position vs time and y-position vs time
figure
plot(my_speed_in_m_per_sec(:, 1), x * meters_to_kilometers, 'b', my_speed_in_m_per_sec(:, 1), y * meters_to_kilometers, 'r')
title('x-displacement and y-displacement')
xlabel('time (s)')
ylabel('displ (km)')
legend('x-displacement', 'y-displacement', 'Location', 'NorthWest')

%% Latitude and longitude
% Data from GPS
%initial_latitude=19.017476;
%initial_longitude=-98.191140;
% Data from Google Earth
initial_latitude=19.0289399;
initial_longitude=-98.3178446;
lon = zeros(n_data, 1);
lat = zeros(n_data, 1);
lon(1)=initial_longitude;
lat(1)=initial_latitude;
cos_init_long = cos(initial_longitude*pi/180.0);
for i=2:n_data
    dx=-(x(i)-x(i-1));
    dy=(y(i)-y(i-1));
    lon(i) = lon(i-1) + (180.0/pi)*(dx/6378137)/cos_init_long;
    lat(i) = lat(i-1) + (180.0/pi/2)*(dy/6378137);
    %lon(i) = initial_longitude + (180.0/pi)*(dx/6378137)/cos_init_long;
    %lat(i) = initial_latitude + (180.0/pi)*(dy/6378137);    
end

% % Plot position
figure();
plot(lon, lat, 'b')
axis([min(lon) max(lon) min(lat) max(lat)])
title('Position (earth coordinates)')
xlabel('Longitude (degrees)')
ylabel('Latitude (degrees)')
legend('Trajectory', 'Location', 'NorthWest')

delay = 0.005; % Delay in seconds in every loop
n_loop = size(x, 1)
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(lon(1), lat(1), 'b*'); % Get the plot hanlder
axis([min(lon) max(lon) min(lat) max(lat)])
xlabel('Longitude (degrees)')
ylabel('Latitude (degrees)')
legend('Trajectory', 'Location', 'NorthWest')

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', my_position(i, 1), lon(i), lat(i)); % Update title
    p.XData(i) = lon(i);
    p.YData(i) = lat(i);
    %drawnow();
    pause(delay);
end

% Create a sub-set of data
old_indexes = [1:size(lat,1)];
old_n_data = size(lat,1);
new_n_data=200-1;
my_new_step=old_n_data/new_n_data;
new_indexes=[1:my_new_step:old_n_data];
new_lat=interp1(indexes, lat, new_indexes);
new_lon=interp1(indexes, lon, new_indexes);

% Create a txt file with the latitude and longitude data
header1 = 'Latitude';
header2 = 'Longitude';
fid=fopen('lat_lon.txt','w');
fprintf(fid, [ header1 '\t' header2 '\n']);
%fprintf(fid, '%f\t%f \n', [lat lon]');
fprintf(fid, '%f\t%f \n', [transpose(new_lat) transpose(new_lon)]');
fclose(fid);

%% FFT raw gyroscope
raw_gyro_no_time = raw_gyro(:,(2:4));
length_raw_gyro_no_time = length(raw_gyro_no_time);
raw_gyro_fft = fft(raw_gyro_no_time, length_raw_gyro_no_time);
raw_gyro_fft_half = raw_gyro_fft(1:(length_raw_gyro_no_time/2), :);

Fs = 15;
f = Fs*(0:length_raw_gyro_no_time/2-1)/length_raw_gyro_no_time;
figure
plot(f, abs(raw_gyro_fft_half(:, 1)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[X] Raw Gyro Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(raw_gyro_fft_half(:, 2)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[Y] Raw Gyro Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(raw_gyro_fft_half(:, 3)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[Z] Raw Gyro Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

%% Designing a filter for the Gyro data
cut_off_frequency = 0.5/Fs/2; % Normalised to Nyquist frequency which is half the sampling rate
order = 15; % The order of the filter
%order = 128; % The order of the filter
% Impose response of the low-pass filter
h = fir1(order, cut_off_frequency);
% Perform the convolution
filtered_gyro_x = conv(raw_gyro_no_time(:,1), h);
filtered_gyro_y = conv(raw_gyro_no_time(:,2), h);
filtered_gyro_z = conv(raw_gyro_no_time(:,3), h);

figure
plot(filtered_gyro_x, 'b')
title('[X] Filtered Gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro x', 'Location', 'NorthWest')

figure
plot(filtered_gyro_y, 'b')
title('[Y] Filtered Gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro y', 'Location', 'NorthWest')

figure
plot(filtered_gyro_z, 'b')
title('[Z] Filtered Gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro z', 'Location', 'NorthWest')

%% FFT raw acceleration
raw_accelerations_no_time = raw_accelerations(:,(2:4));
length_raw_accelerations_no_time = length(raw_accelerations_no_time);
raw_accelerations_fft = fft(raw_accelerations_no_time, length_raw_accelerations_no_time);
raw_accelerations_fft_half = raw_accelerations_fft(1:(length_raw_accelerations_no_time/2), :);

Fs = 15;
f = Fs*(0:length_raw_accelerations_no_time/2-1)/length_raw_accelerations_no_time;
figure
plot(f, abs(raw_accelerations_fft_half(:, 1)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 2)), 'b')
title('[X] Raw Acceleration Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(raw_accelerations_fft_half(:, 2)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 3)), 'b')
title('[Y] Raw Acceleration Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(raw_accelerations_fft_half(:, 3)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 4)), 'b')
title('[Z] Raw Acceleration Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

%% Designing a filter for the Accelerometer data
cut_off_frequency = 0.25/Fs/2; % Normalised to Nyquist frequency which is half the sampling rate
order = 15; % The order of the filter
%order = 128; % The order of the filter
% Impose response of the low-pass filter
h = fir1(order, cut_off_frequency);
% Perform the convolution
filtered_acc_x = conv(raw_accelerations_no_time(:,1), h);
filtered_acc_y = conv(raw_accelerations_no_time(:,2), h);
filtered_acc_z = conv(raw_accelerations_no_time(:,3), h);

figure
plot(filtered_acc_x, 'b')
title('[X] Filtered Accelerometer')
xlabel('Time (s)')
ylabel('x-acc')
legend('Filtered acc x', 'Location', 'NorthWest')

figure
plot(filtered_acc_y, 'b')
title('[Y] Filtered Accelerometer')
xlabel('Time (s)')
ylabel('y-acc')
legend('Filtered acc y', 'Location', 'NorthWest')

figure
plot(filtered_acc_z, 'b')
title('[Z] Filtered Accelerometer')
xlabel('Time (s)')
ylabel('z-acc')
legend('Filtered acc z', 'Location', 'NorthWest')
