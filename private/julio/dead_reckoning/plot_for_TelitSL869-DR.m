%% Read data

% CadenasGNSS.txt
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 538);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 538);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 538);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 538);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 538);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 538);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 538);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 538);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 538);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 538);

% putty_1_espera.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 921);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 921);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 921);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 921);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 921);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 921);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 921);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 921);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 921);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 921);

% putty_2_sin_espera_basura.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 178);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 178);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 178);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 178);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 178);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 178);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 178);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 178);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 178);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 178);

% putty_3_sin_espera_sin_basura.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 836);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 836);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 836);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 836);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 836);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 836);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 836);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 836);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 836);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 836);

% putty_4_sin_espera_sin_basura_final.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 739);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 739);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 739);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 739);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 739);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 739);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 739);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 739);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 739);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 739);

% putty_5_espera_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 2920);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 2920);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 2920);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 2920);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 2920);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 2920);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 2920);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 2920);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 2920);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 2920);

% putty_6_espera_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 3762);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 3762);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 3762);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 3762);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 3762);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 3762);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 3762);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 3762);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 3762);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 3762);

% putty_7_espera_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 1844);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 1844);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 1844);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 1844);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 1844);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 1844);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 1844);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 1844);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 1844);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 1844);

body_frame_gravity = importfile_TelitSL869DR_4columns('RESLT/body_frame_gravity.dat', 1, 1844);

%% putty_8_car_ride_square_wait_large.log
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

%% putty_9_car_ride_tona_acatepec_inaoe_wait_large.log
initial_time = 0;
final_time = 550;
n_input_data = 7370;
%n_output_data = 7901;
n_output_data = 6839; % order 2
n_output_data = 5246; % order 4
n_output_data = 3122; % order 8
n_output_data = 1005; % order 12
n_output_data = 532; % order 14
n_output_data = 7356; % order 14
%n_output_data = 14804; % order 14
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, n_input_data);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, n_input_data);
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, n_output_data);
%my_true_course_in_degrees = importfile_TelitSL869DR_2columns('RESLT/true_course_in_degrees.dat', 1, 531);
my_true_course_in_degrees = importfile_TelitSL869DR_2columns('RESLT/true_course_in_degrees.dat', 1, n_output_data);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, n_output_data);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, n_output_data);
my_inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, n_output_data);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, n_output_data);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, n_output_data);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, n_output_data);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, n_output_data);

%% Euler angles
% Processed roll
figure
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r')
axis([initial_time final_time -180 180])
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')

% Processed pitch
figure
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r')
axis([initial_time final_time -180 180])
title('Euler angle [pitch]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')

% Processed yaw
figure
%plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r')
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r', my_true_course_in_degrees(:,1), my_true_course_in_degrees(:,2), 'b')
%axis([initial_time final_time -180 180])
title('Euler angle [yaw]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
%legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'TRUE COURSE (Heading)', 'Location', 'NorthWest')

%% True course in degrees
figure
plot(my_true_course_in_degrees(:,1), my_true_course_in_degrees(:,2), 'b')
axis([initial_time final_time -180 180])
title('True course in degrees [yaw]')
xlabel('Time(s)')
ylabel('\theta (degrees)')

%% Raw gyro and euler angles rates
% figure
% plot(my_raw_gyro(:, 1), my_raw_gyro(:, 2)*180.0/pi, 'b', my_euler_angles_rates(:,1), my_euler_angles_rates(:,2)*180.0/pi, '--r')
% title('[X] Gyro & [Roll] Euler angle rate')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Raw gyro', '[Roll] Euler angle rate', 'Location', 'NorthWest')
% 
% figure
% plot(my_raw_gyro(:, 1), my_raw_gyro(:, 3)*180.0/pi, 'b', my_euler_angles_rates(:,1), my_euler_angles_rates(:,3)*180.0/pi, '--r')
% title('[Y] Gyro & [Pitch] Euler angle rate')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Raw gyro', '[Pitch] Euler angle rate', 'Location', 'NorthWest')
%  
% figure
% plot(my_raw_gyro(:, 1), my_raw_gyro(:, 4)*180.0/pi, 'b', my_euler_angles_rates(:,1), my_euler_angles_rates(:,4)*180.0/pi, '--r')
% title('[Z] Gyro & [Yaw] Euler angle rate')
% xlabel('Time (s)')
% ylabel('d/s')
% legend('Raw gyro', '[Yaw] Euler angle rate', 'Location', 'NorthWest')

%% Raw vs filtered gyro
figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 2)*180.0/pi, 'b', my_filtered_gyro(:, 1), my_filtered_gyro(:, 2)*180.0/pi, 'r')
axis([initial_time final_time -40 40])
title('x-gyro (device system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw gyro', 'Filtered gyro', 'Location', 'NorthWest')

figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 3)*180.0/pi, 'b', my_filtered_gyro(:, 1), my_filtered_gyro(:, 3)*180.0/pi, 'r')
axis([initial_time final_time -40 40])
title('y-gyro (device system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw gyro', 'Filtered gyro', 'Location', 'NorthWest')

figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 4)*180.0/pi, 'b', my_filtered_gyro(:, 1), my_filtered_gyro(:, 4)*180.0/pi, 'r')
axis([initial_time final_time -40 40])
title('z-gyro (device system coordinate)')
xlabel('Time (s)')
ylabel('d/s')
legend('Raw gyro', 'Filtered gyro', 'Location', 'NorthWest')

%% Raw vs filtered acceleration
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 2), 'b', my_filtered_acc(:, 1), my_filtered_acc(:, 2), 'r')
axis([initial_time final_time -5 15])
title('x-acceleration (device system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw acceleration', 'Filtered acceleration', 'Location', 'NorthWest')

figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 3), 'b', my_filtered_acc(:, 1), my_filtered_acc(:, 3), 'r')
axis([initial_time final_time -5 15])
title('y-acceleration (device system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw acceleration', 'Filtered acceleration', 'Location', 'NorthWest')
 
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 4), 'b', my_filtered_acc(:, 1), my_filtered_acc(:, 4), 'r')
axis([initial_time final_time -5 15])
title('z-acceleration (device system coordinate)')
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Raw acceleration',  'Filtered acceleration', 'Location', 'NorthWest')

%% Filtered and inertial acceleration
figure
plot(my_filtered_acc(:, 1), my_filtered_acc(:, 2), 'b', my_inertial_acceleration(:, 1), my_inertial_acceleration(:, 2), 'r')
title('x-acceleration')
axis([initial_time final_time -5 15])
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Filtered acceleration (device system coordinate)', 'Inertial acceleration', 'Location', 'NorthWest')

% figure
% plot(my_inertial_acceleration(:, 1), my_inertial_acceleration(:, 2), 'r')
% title('x-acceleration')
% axis([initial_time final_time -5 15])
% xlabel('Time (s)')
% ylabel('Acceleration (m/s^2)')
% legend('Inertial acceleration', 'Location', 'NorthWest')

figure
plot(my_filtered_acc(:, 1), my_filtered_acc(:, 3), 'b', my_inertial_acceleration(:, 1), my_inertial_acceleration(:, 3), 'r')
title('y-acceleration')
axis([initial_time final_time -5 15])
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Filtered acceleration (device system coordinate)', 'Inertial acceleration', 'Location', 'NorthWest')
 
figure
plot(my_filtered_acc(:, 1), my_filtered_acc(:, 4), 'b', my_inertial_acceleration(:, 1), my_inertial_acceleration(:, 4), 'r')
title('z-acceleration')
axis([initial_time final_time -5 15])
xlabel('Time (s)')
ylabel('Acceleration (m/s^2)')
legend('Filtered acceleration (device system coordinate)', 'Inertial acceleration', 'Location', 'NorthWest')

%% Velocity
m_per_sec_to_km_per_h = 3.6;
% % Plot velocity
figure
%plot(my_velocity(:, 1), my_velocity(:, 2)*m_per_sec_to_km_per_h, 'b', my_velocity(:, 1), my_velocity(:, 3)*m_per_sec_to_km_per_h, 'r', my_velocity(:, 1), my_velocity(:, 4)*m_per_sec_to_km_per_h, 'g',  my_velocity(:, 1), my_velocity(:, 5)*m_per_sec_to_km_per_h, 'y')
plot(my_velocity(:, 1), my_velocity(:, 2)*m_per_sec_to_km_per_h, 'b', my_velocity(:, 1), my_velocity(:, 3)*m_per_sec_to_km_per_h, 'r', my_velocity(:, 1), my_velocity(:, 4)*m_per_sec_to_km_per_h, 'g')
title('Velocity')
xlabel('Time (s)')
ylabel('Velocity km/h')
%legend('x-velocity', 'y-velocity', 'z-velocity', 'xy-velocity', 'Location', 'NorthWest')
legend('x-velocity', 'y-velocity', 'z-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b')
title('Velocity')
xlabel('Time (s)')
ylabel('x-velocity')
legend('X-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b')
title('Velocity')
xlabel('Time (s)')
ylabel('y-velocity')
legend('Y-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 4), 'b')
title('Velocity')
xlabel('Time (s)')
ylabel('z-velocity')
legend('Z-velocity', 'Location', 'NorthWest')

%% Position (from double integration of acceleration)
delay = 0.05; % Delay in seconds in every loop
n_loop = size(my_position, 1)
meters_to_kilometers = 1.0/1000.0;
% % Plot position
figure();
hold('on'); % The painting is done over this plot
t = title('Trajectory, t=0'); % Initial title, we get a hanlder as well
p = plot(my_position(1, 2) * meters_to_kilometers, my_position(1, 3) * meters_to_kilometers, 'b*'); % Get the plot hanlder
%plot(my_position(i, 2) * meters_to_kilometers, my_position(i, 3) * meters_to_kilometers, 'b*') % Draw new point
%axis([-max(my_position(:, 2) * meters_to_kilometers) max(my_position(:, 2) * meters_to_kilometers) -max(my_position(:, 3) * meters_to_kilometers) max(my_position(:, 3) * meters_to_kilometers)])
xlabel('x (km)')
ylabel('y (km)')
legend('Trajectory', 'Location', 'NorthWest')

for i = 1:n_loop
    t.String = sprintf('Trajectory, t = %.2f (%.2f, %.2f)', my_position(i, 1), my_position(i, 2) * meters_to_kilometers, my_position(i, 3) * meters_to_kilometers); % Update title
    p.XData(i) = my_position(i, 2) * meters_to_kilometers;
    p.YData(i) = my_position(i, 3) * meters_to_kilometers;
    %drawnow();
    pause(delay);
end

% Position x vs y
figure
plot(my_position(:, 2) * meters_to_kilometers, my_position(:, 3) * meters_to_kilometers, 'b')
title('xy-displacement')
xlabel('x-displacement (km)')
ylabel('y-displacement (km)')
legend('xy-displacement', 'Location', 'NorthWest')

% x-position vs time and y-position vs time
figure
plot(my_position(:, 1), my_position(:, 2) * meters_to_kilometers, 'b*', my_position(:, 1), my_position(:, 3) * meters_to_kilometers, 'r*')
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
my_raw_gyro_no_time = my_raw_gyro(:,(2:4));
length_my_raw_gyro_no_time = length(my_raw_gyro_no_time);
my_raw_gyro_fft = fft(my_raw_gyro_no_time, length_my_raw_gyro_no_time);
my_raw_gyro_fft_half = my_raw_gyro_fft(1:(length_my_raw_gyro_no_time/2), :);

Fs = 15;
f = Fs*(0:length_my_raw_gyro_no_time/2-1)/length_my_raw_gyro_no_time;
figure
plot(f, abs(my_raw_gyro_fft_half(:, 1)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[X] Raw Gyro Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(my_raw_gyro_fft_half(:, 2)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[Y] Raw Gyro Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(my_raw_gyro_fft_half(:, 3)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[Z] Raw Gyro Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

%% Designing a filter for the Gyro data
cut_off_frequency = 0.5/Fs/2; % Normalised to Nyquist frequency which is half the sampling rate
order = 28; % The order of the filter
%order = 128; % The order of the filter
% Impose response of the low-pass filter
h = fir1(order, cut_off_frequency);
% Perform the convolution
filtered_gyro_x = conv(my_raw_gyro_no_time(:,1), h);
filtered_gyro_y = conv(my_raw_gyro_no_time(:,2), h);
filtered_gyro_z = conv(my_raw_gyro_no_time(:,3), h);

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
my_raw_accelerations_no_time = my_raw_accelerations(:,(2:4));
length_my_raw_accelerations_no_time = length(my_raw_accelerations_no_time);
my_raw_accelerations_fft = fft(my_raw_accelerations_no_time, length_my_raw_accelerations_no_time);
my_raw_accelerations_fft_half = my_raw_accelerations_fft(1:(length_my_raw_accelerations_no_time/2), :);

Fs = 15;
f = Fs*(0:length_my_raw_accelerations_no_time/2-1)/length_my_raw_accelerations_no_time;
figure
plot(f, abs(my_raw_accelerations_fft_half(:, 1)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 2)), 'b')
title('[X] Raw Acceleration Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(my_raw_accelerations_fft_half(:, 2)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 3)), 'b')
title('[Y] Raw Acceleration Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

figure
plot(f, abs(my_raw_accelerations_fft_half(:, 3)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 4)), 'b')
title('[Z] Raw Acceleration Frequency')
xlabel('Frequency (Hz)')
ylabel('Magnitude')
legend('Frequency', 'Location', 'NorthWest')

%% Designing a filter for the Accelerometer data
cut_off_frequency = 0.25/Fs/2; % Normalised to Nyquist frequency which is half the sampling rate
order = 28; % The order of the filter
%order = 128; % The order of the filter
% Impose response of the low-pass filter
h = fir1(order, cut_off_frequency);
% Perform the convolution
filtered_acc_x = conv(my_raw_accelerations_no_time(:,1), h);
filtered_acc_y = conv(my_raw_accelerations_no_time(:,2), h);
filtered_acc_z = conv(my_raw_accelerations_no_time(:,3), h);

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
