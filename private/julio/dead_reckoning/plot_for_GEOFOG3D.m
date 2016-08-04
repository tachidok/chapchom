%% Read data
%GEOFOG3DEulerAngles = importfileGEOFOG3Deulerangles('GEOFOG3D.dat', 2, 78056);
%my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 41081);
%my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 41081);

% Only read the first 10 sec. with 20 data per second
%GEOFOG3DEulerAngles = importfileGEOFOG3Deulerangles('GEOFOG3D.dat', 2, 192);
%my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 201);
%my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 201);

% Only read the first 20 sec. with 20 data per second
GEOFOG3DEulerAngles = importfileGEOFOG3Deulerangles('GEOFOG3D.dat', 2, 382);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 401);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 401);

% Only read the first 20 sec. with 1 data per second
%GEOFOG3DEulerAngles = importfileGEOFOG3Deulerangles('GEOFOG3D.dat', 2, 382);
%my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 21);
%my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 21);

% Only read the first 50 sec. with 20 data per second
%GEOFOG3DEulerAngles = importfileGEOFOG3Deulerangles('GEOFOG3D.dat', 2, 952);
%my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 1001);
%my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 1001);

%% Euler angles
% Original vs processed roll
figure
%plot(GEOFOG3DEulerAngles(:, 1), GEOFOG3DEulerAngles(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r')
plot(GEOFOG3DEulerAngles(:, 1), GEOFOG3DEulerAngles(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g')
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
%legend('Original', 'Euler angle from gyroscope', 'Location', 'NorthWest')
%legend('Solution', 'Gyroscope and accelerometer fusion', 'Location', 'NorthWest')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')
%title('Ángulo de Euler [roll]')
%xlabel('Tiempo (s)')
%ylabel('\phi (grados)')
%legend('Resultado esperado', 'Ángulo de Euler desde giróscopos', 'Location', 'NorthWest')
%legend('Original', 'Fusión giróscopos y acelerómetros', 'Location', 'NorthWest')

% Original vs processed pitch
figure
%plot(GEOFOG3DEulerAngles(:, 1), GEOFOG3DEulerAngles(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r')
plot(GEOFOG3DEulerAngles(:, 1), GEOFOG3DEulerAngles(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g')
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
%plot(GEOFOG3DEulerAngles(:, 1), GEOFOG3DEulerAngles(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r')
plot(GEOFOG3DEulerAngles(:, 1), GEOFOG3DEulerAngles(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g')
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
