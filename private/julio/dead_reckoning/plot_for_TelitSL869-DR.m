%% Read data

% CadenasGNSS.txt
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 538);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 538);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 538);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 538);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 538);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 538);

% putty_1_espera.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 921);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 921);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 921);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 921);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 921);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 921);

% putty_2_sin_espera_basura.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 178);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 178);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 178);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 178);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 178);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 178);

% putty_3_sin_espera_sin_basura.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 836);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 836);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 836);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 836);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 836);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 836);

% putty_4_sin_espera_sin_basura_final.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 739);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 739);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 739);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 739);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 739);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 739);

% putty_5_espera_large.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 2920);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 2920);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 2920);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 2920);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 2920);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 2920);

% putty_6_espera_large.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 3762);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 3762);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 3762);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 3762);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 3762);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 3762);

% putty_7_espera_large.log
my_roll_pitch_yaw = import_results_TelitSL869DR('RESLT/roll_pitch_yaw.dat', 1, 1844);
my_raw_accelerations = import_results_TelitSL869DR('RESLT/raw_accelerations.dat', 1, 1844);
my_roll_pitch_yaw_from_acc = import_results_TelitSL869DR('RESLT/roll_pitch_yaw_from_acc.dat', 1, 1844);
inertial_acceleration = import_results_TelitSL869DR('RESLT/inertial_accelerations.dat', 1, 1844);
my_position = import_results_TelitSL869DR('RESLT/position.dat', 1, 1844);
my_velocity = import_results_TelitSL869DR('RESLT/velocity.dat', 1, 1844);

body_frame_gravity = importfile_TelitSL869DR_body_frame_gravity('RESLT/body_frame_gravity.dat', 1, 1844);

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
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 2), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 2), 'r', body_frame_gravity(:, 1), body_frame_gravity(:,2), 'g', body_frame_gravity(:, 1), body_frame_gravity(:,5), 'y')
title('[X] Acceleration')
xlabel('Time (s)')
ylabel('x-acceleration')
legend('Raw acceleration', 'Inertial acceleration', 'Body frame gravity', 'Magnitude body frame gravity', 'Location', 'NorthWest')
 
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 3), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 3), 'r', body_frame_gravity(:, 1), body_frame_gravity(:,3), 'g', body_frame_gravity(:, 1), body_frame_gravity(:,5), 'y')
title('[Y] Acceleration')
xlabel('Time (s)')
ylabel('y-acceleration')
legend('Raw acceleration', 'Inertial acceleration', 'Body frame gravity', 'Magnitude body frame gravity', 'Location', 'NorthWest')
 
figure
plot(my_raw_accelerations(:, 1), my_raw_accelerations(:, 4), 'b', inertial_acceleration(:, 1), inertial_acceleration(:, 4), 'r', body_frame_gravity(:, 1), body_frame_gravity(:,4), 'g', body_frame_gravity(:, 1), body_frame_gravity(:,5), 'y')
title('[Z] Acceleration')
xlabel('Time (s)')
ylabel('z-acceleration')
legend('Raw acceleration', 'Inertial acceleration', 'Body frame gravity', 'Magnitude body frame gravity', 'Location', 'NorthWest')

%% Position
% % Plot position
figure
plot(my_position(:, 2), my_position(:, 3), 'b')
title('Trajectory')
xlabel('x')
ylabel('y')
legend('Trajectory', 'Location', 'NorthWest')

%% Velocity
% % Plot velocity
figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b', my_velocity(:, 1), my_velocity(:, 3), 'r', my_velocity(:, 1), my_velocity(:, 4), 'g')
title('Velocity')
xlabel('time')
ylabel('velocity')
legend('x-velocity', 'y-velocity', 'z-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 2), 'b')
title('Velocity')
xlabel('time')
ylabel('x-velocity')
legend('x-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 3), 'b')
title('Velocity')
xlabel('time')
ylabel('y-velocity')
legend('Y-velocity', 'Location', 'NorthWest')

figure
plot(my_velocity(:, 1), my_velocity(:, 4), 'b')
title('Velocity')
xlabel('time')
ylabel('z-velocity')
legend('Z-velocity', 'Location', 'NorthWest')
