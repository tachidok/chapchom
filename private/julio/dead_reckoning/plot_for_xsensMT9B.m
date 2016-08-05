%% Read data
% 76 secs. with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/no_movement/MT9_euler_00007154_000.log', 1, 18273);
MT9all = importfileMT9raw('xsensMT9B/no_movement/MT9_cal_00007154_000.log', 1, 18273);

my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 19533);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 19533);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 19533);
my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 19533);

% x secs. with 257 data per second
%MT9euler = importfileMT9euler('xsensMT9B/test1/MT9_euler_00007154_000.log', 1, 20076);
%MT9all = importfileMT9raw('xsensMT9B/test1/MT9_cal_00007154_000.log', 1, 20076);

%my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 26472);
%my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 26472);
%inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 26472);
%my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 26472);

%% Euler angles
% Original vs processed roll
figure
%plot(MT9euler(:, 1), MT9euler(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r')
plot(MT9euler(:, 1), MT9euler(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g')
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
%legend('Original', 'Euler angle from gyroscope', 'Location', 'NorthWest')
%legend('Solution', 'Gyroscope and accelerometer fusion', , 'Location', 'NorthWest')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')
%title('Ángulo de Euler [roll]')
%xlabel('Tiempo (s)')
%ylabel('\phi (grados)')
%legend('Resultado esperado', 'Ángulo de Euler desde giróscopos', 'Location', 'NorthWest')
%legend('Original', 'Fusión giróscopos y acelerómetros', 'Location', 'NorthWest')

% Original vs processed pitch
figure
%plot(MT9euler(:, 1), MT9euler(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r')
plot(MT9euler(:, 1), MT9euler(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g')
title('Euler angle [pitch]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
%legend('Original', 'Euler angle from gyroscope', 'Location', 'NorthWest')
%legend('Solution', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')
%title('Ángulo de Euler [pitch]')
%xlabel('Tiempo(s)')
%ylabel('\theta (grados)')
%legend('Resultado esperado', 'Ángulo de Euler desde giróscopos', 'Location', 'NorthWest')
%legend('Original', 'Fusión giróscopos y acelerómetros', 'Location', 'NorthWest')

% Original vs processed rollacc_angles[2] = atan2(acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
figure
%plot(MT9euler(:, 1), MT9euler(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r')
plot(MT9euler(:, 1), MT9euler(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g')
title('Euler angle [yaw]')
xlabel('Time(s)')
ylabel('\psi (degrees)')
%legend('Original', 'Euler angle from gyroscope', 'Location', 'NorthWest')
%legend('Solution', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')
%title('Ángulo de Euler [yaw]')
%xlabel('Tiempo(s)')
%ylabel('\psi (grados)')
%legend('Resultado esperado', 'Ángulo de Euler desde giróscopos', 'Location', 'NorthWest')
%legend('Original', 'Fusión giróscopos y acelerómetros', 'Location', 'NorthWest')

% %% Inertial acceleration
% figure
% plot(inertial_acceleration(:, 1), inertial_acceleration(:, 2), 'b')
% title('Inertial acceleration')
% xlabel('Time (s)')
% ylabel('x-acceleration')
% legend('Acceleration', 'Location', 'NorthWest')
% 
% figure
% plot(inertial_acceleration(:, 1), inertial_acceleration(:, 3), 'b')
% title('Inertial acceleration')
% xlabel('Time (s)')
% ylabel('y-acceleration')
% legend('Acceleration', 'Location', 'NorthWest')
% 
% figure
% plot(inertial_acceleration(:, 1), inertial_acceleration(:, 4), 'b')
% title('Inertial acceleration')
% xlabel('Time (s)')
% ylabel('z-acceleration')
% legend('Acceleration', 'Location', 'NorthWest')
% 
% %% Position
% % Plot position
% figure
% plot(my_position(:, 2), my_position(:, 3), 'b')
% title('Trajectory')
% xlabel('x')
% ylabel('y')
% legend('Trajectory', 'Location', 'NorthWest')
