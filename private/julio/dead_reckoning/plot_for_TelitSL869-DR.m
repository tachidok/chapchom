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

% putty_8_car_ride_square_wait_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 6651);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 6651);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 6651);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 6651);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 6651);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 6651);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 6651);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 6651);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 6651);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 6651);

% putty_9_car_ride_tona_acatepec_inaoe_wait_large.log
n_input_data = 7370;
%n_output_data = 7901;
n_output_data = 6839; % order 2
n_output_data = 5246; % order 4
n_output_data = 3122; % order 8
n_output_data = 1005; % order 12
n_output_data = 532; % order 14
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, n_input_data);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, n_input_data);
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, n_output_data);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, n_output_data);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, n_output_data);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, n_output_data);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, n_output_data);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, n_output_data);
my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, n_output_data);
my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, n_output_data);

% my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 75338);
% my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 75338);
% my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 75338);
% inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 75338);
% my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 75338);
% my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 75338);
% my_filtered_gyro = importfile_TelitSL869DR_3columns('RESLT/filtered_gyro.dat', 1, 75338);
% my_filtered_acc = importfile_TelitSL869DR_3columns('RESLT/filtered_acc.dat', 1, 75338);

%% Euler angles
% Processed roll
figure
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r')
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')

% Processed pitch
figure
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r')
title('Euler angle [pitch]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')

% Processed yaw
figure
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r')
title('Euler angle [yaw]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')

%% Raw gyro and euler angles rates
figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 2)*180.0/pi, 'b', my_euler_angles_rates(:,1), my_euler_angles_rates(:,2)*180.0/pi, '--r')
title('[X] Gyro & [Roll] Euler angle rate')
xlabel('Time (s)')
ylabel('dps')
legend('Raw gyro', '[Roll] Euler angle rate', 'Location', 'NorthWest')

figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 3)*180.0/pi, 'b', my_euler_angles_rates(:,1), my_euler_angles_rates(:,3)*180.0/pi, '--r')
title('[Y] Gyro & [Pitch] Euler angle rate')
xlabel('Time (s)')
ylabel('dps')
legend('Raw gyro', '[Pitch] Euler angle rate', 'Location', 'NorthWest')
 
figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 4)*180.0/pi, 'b', my_euler_angles_rates(:,1), my_euler_angles_rates(:,4)*180.0/pi, '--r')
title('[Z] Gyro & [Yaw] Euler angle rate')
xlabel('Time (s)')
ylabel('dps')
legend('Raw gyro', '[Yaw] Euler angle rate', 'Location', 'NorthWest')

%% Raw vs filtered gyro
figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 2)*180.0/pi, 'b')
title('[X] Raw gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Raw gyro', 'Location', 'NorthWest')

figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 3)*180.0/pi, 'b')
title('[Y] Raw gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Raw gyro', 'Location', 'NorthWest')
 
figure
plot(my_raw_gyro(:, 1), my_raw_gyro(:, 4)*180.0/pi, 'b')
title('[Z] Raw gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Raw gyro', 'Location', 'NorthWest')

figure
plot(my_filtered_gyro(:, 1), my_filtered_gyro(:, 2)*180.0/pi, 'r')
%plot(my_raw_gyro(:, 1), my_raw_gyro(:, 3)*180.0/pi, 'b', my_filtered_gyro(:, 1), my_filtered_gyro(:, 3)*180.0/pi, 'r')
title('[X] Filtered gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro', 'Location', 'NorthWest')

figure
plot(my_filtered_gyro(:, 1), my_filtered_gyro(:, 3)*180.0/pi, 'r')
%plot(my_raw_gyro(:, 1), my_raw_gyro(:, 3)*180.0/pi, 'b', my_filtered_gyro(:, 1), my_filtered_gyro(:, 3)*180.0/pi, 'r')
title('[Y] Filtered gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro', 'Location', 'NorthWest')
 
figure
plot(my_filtered_gyro(:, 1), my_filtered_gyro(:, 4)*180.0/pi, 'r')
%plot(my_raw_gyro(:, 1), my_raw_gyro(:, 4)*180.0/pi, 'b', my_filtered_gyro(:, 1), my_filtered_gyro(:, 4)*180.0/pi, 'r')
title('[Z]  Filtered gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro', 'Location', 'NorthWest')

%% Raw and inertial acceleration
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 2), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 2), 'r')
title('[X] Acceleration')
xlabel('Time (s)')
ylabel('x-acceleration')
legend('Raw acceleration', 'Inertial acceleration', 'Location', 'NorthWest')
 
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 3), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 3), 'r')
title('[Y] Acceleration')
xlabel('Time (s)')
ylabel('y-acceleration')
legend('Raw acceleration', 'Inertial acceleration', 'Location', 'NorthWest')
 
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 4), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 4), 'r')
title('[Z] Acceleration')
xlabel('Time (s)')
ylabel('z-acceleration')
legend('Raw acceleration', 'Inertial acceleration', 'Location', 'NorthWest')

%% Raw vs filtered acceleration
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 2), 'b')
title('[X] Acceleration')
xlabel('Time (s)')
ylabel('x-acceleration')
legend('Raw acceleration',  'Location', 'NorthWest')

figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 3), 'b')
title('[Y] Acceleration')
xlabel('Time (s)')
ylabel('y-acceleration')
legend('Raw acceleration', 'Location', 'NorthWest')
 
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 4), 'b')
title('[Z] Acceleration')
xlabel('Time (s)')
ylabel('z-acceleration')
legend('Raw acceleration',  'Location', 'NorthWest')

figure
plot(my_filtered_acc(:, 1), my_filtered_acc(:, 2), 'r')
%plot(my_filtered_acc(:, 1), my_filtered_acc(:, 3)*180.0/pi, 'b', my_filtered_acc(:, 1), my_filtered_acc(:, 3)*180.0/pi, 'r')
title('[X] Filtered acc')
xlabel('Time (s)')
ylabel('x-acceleration')
legend('Filtered acc', 'Location', 'NorthWest')

figure
plot(my_filtered_acc(:, 1), my_filtered_acc(:, 3), 'r')
%plot(my_filtered_acc(:, 1), my_filtered_acc(:, 3)*180.0/pi, 'b', my_filtered_acc(:, 1), my_filtered_acc(:, 3)*180.0/pi, 'r')
title('[Y] Filtered acc')
xlabel('Time (s)')
ylabel('y-acceleration')
legend('Filtered acc', 'Location', 'NorthWest')
 
figure
plot(my_filtered_acc(:, 1), my_filtered_acc(:, 4), 'r')
%plot(my_filtered_acc(:, 1), my_filtered_acc(:, 4)*180.0/pi, 'b', my_filtered_acc(:, 1), my_filtered_acc(:, 4)*180.0/pi, 'r')
title('[Z]  Filtered acc')
xlabel('Time (s)')
ylabel('z-acceleration')
legend('Filtered acc', 'Location', 'NorthWest')

%% Raw and inertial acceleration
%figure
%plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 2), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 2), 'r', body_frame_gravity(:, 1), body_frame_gravity(:,2), 'g', body_frame_gravity(:, 1), body_frame_gravity(:,5), 'y')
%title('[X] Acceleration')
% xlabel('Time (s)')
% ylabel('x-acceleration')
% legend('Raw acceleration', 'Inertial acceleration', 'Body frame gravity', 'Magnitude body frame gravity', 'Location', 'NorthWest')
%  
% figure
% plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 3), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 3), 'r', body_frame_gravity(:, 1), body_frame_gravity(:,3), 'g', body_frame_gravity(:, 1), body_frame_gravity(:,5), 'y')
% title('[Y] Acceleration')
% xlabel('Time (s)')
% ylabel('y-acceleration')
% legend('Raw acceleration', 'Inertial acceleration', 'Body frame gravity', 'Magnitude body frame gravity', 'Location', 'NorthWest')
%  
% figure
% plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 4), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 4), 'r', body_frame_gravity(:, 1), body_frame_gravity(:,4), 'g', body_frame_gravity(:, 1), body_frame_gravity(:,5), 'y')
% title('[Z] Acceleration')
% xlabel('Time (s)')
% ylabel('z-acceleration')
% legend('Raw acceleration', 'Inertial acceleration', 'Body frame gravity', 'Magnitude body frame gravity', 'Location', 'NorthWest')

%% Position
% % Plot position
figure
plot(my_position(:, 2), my_position(:, 3) * 1/1000, 'b')
title('Trajectory')
xlabel('x (km)')
ylabel('y (km)')
legend('Trajectory', 'Location', 'NorthWest')

%% Velocity
m_per_sec_to_km_per_h = 3600/1000;
% % Plot velocity
figure
plot(my_velocity(:, 1), my_velocity(:, 2)*m_per_sec_to_km_per_h, 'b', my_velocity(:, 1), my_velocity(:, 3)*m_per_sec_to_km_per_h, 'r', my_velocity(:, 1), my_velocity(:, 4)*m_per_sec_to_km_per_h, 'g',  my_velocity(:, 1), my_velocity(:, 5)*m_per_sec_to_km_per_h, 'y')
title('Velocity')
xlabel('time (s)')
ylabel('velocity km/h')
legend('x-velocity', 'y-velocity', 'z-velocity', 'xy-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b')
title('Velocity')
xlabel('time (s)')
ylabel('x-velocity')
legend('x-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1),[Z] Filtered Accelerometer')
xlabel('Time (s)') my_velocity(:, 3), 'b')
title('Velocity')
xlabel('time (s)')
ylabel('y-velocity')
legend('Y-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 4), 'b')
title('Velocity')
xlabel('time (s)')
ylabel('z-velocity')
legend('Z-velocity', 'Location', 'NorthWest')

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
order = 14; % The order of the filter
%order = 128; % The order of the filter
% Impose response of the low-pass filter
h = fir1(order, cut_off_frequency);
% Perform the convolution
filtered_acc_x = conv(my_raw_gyro_no_time(:,1), h);
filtered_acc_y = conv(my_raw_gyro_no_time(:,2), h);
filtered_acc_z = conv(my_raw_gyro_no_time(:,3), h);

figure
plot(filtered_acc_x, 'b')
title('[X] Filtered Gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro x', 'Location', 'NorthWest')

figure
plot(filtered_acc_y, 'b')
title('[Y] Filtered Gyro')
xlabel('Time (s)')
ylabel('dps')
legend('Filtered gyro y', 'Location', 'NorthWest')

figure
plot(filtered_acc_z, 'b')
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
order = 14; % The order of the filter
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
