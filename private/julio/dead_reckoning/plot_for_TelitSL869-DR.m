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

% putty_1_espera.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 921);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 921);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 921);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 921);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 921);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 921);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 921);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 921);

% putty_2_sin_espera_basura.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 178);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 178);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 178);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 178);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 178);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 178);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 178);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 178);

% putty_3_sin_espera_sin_basura.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 836);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 836);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 836);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 836);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 836);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 836);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 836);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 836);

% putty_4_sin_espera_sin_basura_final.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 739);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 739);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 739);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 739);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 739);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 739);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 739);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 739);

% putty_5_espera_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 2920);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 2920);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 2920);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 2920);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 2920);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 2920);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 2920);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 2920);

% putty_6_espera_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 3762);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 3762);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 3762);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 3762);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 3762);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 3762);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 3762);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 3762);

% putty_7_espera_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 1844);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 1844);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 1844);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 1844);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 1844);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 1844);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 1844);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 1844);

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

% putty_9_car_ride_tona_acatepec_inaoe_wait_large.log
my_roll_pitch_yaw = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw.dat', 1, 7370);
my_raw_gyro = importfile_TelitSL869DR_3columns('RESLT/raw_gyro.dat', 1, 7370);
my_euler_angles_rates = importfile_TelitSL869DR_3columns('RESLT/euler_angles_rates.dat', 1, 7370);
my_raw_accelerations = importfile_TelitSL869DR_3columns('RESLT/raw_accelerations.dat', 1, 7370);
my_roll_pitch_yaw_from_acc = importfile_TelitSL869DR_3columns('RESLT/roll_pitch_yaw_from_acc.dat', 1, 7370);
inertial_acceleration = importfile_TelitSL869DR_3columns('RESLT/inertial_accelerations.dat', 1, 7370);
my_position = importfile_TelitSL869DR_3columns('RESLT/position.dat', 1, 7370);
my_velocity = importfile_TelitSL869DR_4columns('RESLT/velocity.dat', 1, 7370);

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
ylabel('\psi (degrees)')
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
plot(my_position(:, 2), my_position(:, 3), 'b')
title('Trajectory')
xlabel('x (m)')
ylabel('y (m)')
legend('Trajectory', 'Location', 'NorthWest')

%% Velocity
m_per_sec_to_km_per_h = 3600/1000;
% % Plot velocity
figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b', my_velocity(:, 1), my_velocity(:, 3), 'r', my_velocity(:, 1), my_velocity(:, 4), 'g',  my_velocity(:, 1), my_velocity(:, 5)*m_per_sec_to_km_per_h, 'y')
title('Velocity')
xlabel('time (s)')
ylabel('velocity m/s')
legend('x-velocity', 'y-velocity', 'z-velocity', 'xy-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b')
title('Velocity')
xlabel('time (s)')
ylabel('x-velocity')
legend('x-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 3), 'b')
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

%% FFT
my_raw_gyro_fft = fft(my_raw_gyro(:,(2:4)));
my_raw_accelerations_fft = fft(my_raw_accelerations(:,(2:4)));

Fs = 15;
L = size(my_raw_gyro_fft,1);
f = Fs*(0:(L/2))/L;
P2 = abs(my_raw_gyro_fft/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

plot(f,P1)
title('Single-Sided Amplitude Spectrum of S(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')

%% FFT raw gyroscope
figure
plot(abs(my_raw_gyro_fft(:, 2)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[X] Raw Gyro FFT')
xlabel('Time (s)')
ylabel('x-frequence')
legend('Frequence', 'Location', 'NorthWest')

figure
plot(abs(my_raw_gyro_fft(:, 3)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[Y] Raw Gyro FFT')
xlabel('Time (s)')
ylabel('y-frequence')
legend('Frequence', 'Location', 'NorthWest')

figure
plot(abs(my_raw_gyro_fft(:, 4)), 'b')
%plot(my_raw_gyro(:, 1), abs(my_raw_gyro_fft(:, 2)), 'b')
title('[Z] Raw Gyro FFT')
xlabel('Time (s)')
ylabel('z-frequence')
legend('Frequence', 'Location', 'NorthWest')

%% FFT raw acceleration
figure
plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 2)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 2)), 'b')
title('[X] Raw Acceleration FFT')
xlabel('Time (s)')
ylabel('x-frequence')
legend('Frequence', 'Location', 'NorthWest')

figure
plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 3)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 3)), 'b')
title('[Y] Raw Acceleration FFT')
xlabel('Time (s)')
ylabel('y-frequence')
legend('Frequence', 'Location', 'NorthWest')

figure
plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 4)), 'b')
%plot(my_raw_accelerations(:, 1), abs(my_raw_accelerations_fft(:, 4)), 'b')
title('[Z] Raw Acceleration FFT')
xlabel('Time (s)')
ylabel('z-frequence')
legend('Frequence', 'Location', 'NorthWest')
