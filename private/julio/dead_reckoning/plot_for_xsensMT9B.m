%% Read data
% 76 secs. with 257 data per second
%MT9euler = importfileMT9euler('xsensMT9B/no_movement/MT9_euler_00007154_000.log', 1, 18273);
%MT9all = importfileMT9raw('xsensMT9B/no_movement/MT9_cal_00007154_000.log', 1, 18273);

% 76 secs. with 257 data per second (no movement)
% MT9euler = importfileMT9euler('xsensMT9B/01_no_movement/MT9_euler_00007154_000.log', 1, 18148);
% MT9all = importfileMT9raw('xsensMT9B/01_no_movement/MT9_cal_00007154_000.log', 1, 18148);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 19533);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 19533);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 19533);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 19533);
% rawmagnetometers = importfile_raw_magnetometers('RESLT/raw_magnetometers.dat', 1, 19533);

% 82 secs. with 257 data per second (characterise yaw drift)
% MT9euler = importfileMT9euler('xsensMT9B/03_characterise_yaw_drift/MT9_euler_00007154_000.log', 2188, 20993);
% MT9all = importfileMT9raw('xsensMT9B/03_characterise_yaw_drift/MT9_cal_00007154_000.log', 2188, 20993);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 21075);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 21075);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 21075);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 21075);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 21075);
% rawmagnetometers = importfile_raw_magnetometers('RESLT/raw_magnetometers.dat', 1, 21075);

% 17 mins. with 257 data per second (characterise yaw drift2)
% MT9euler = importfileMT9euler('xsensMT9B/04_characterise_yaw_drift2/MT9_euler_00007154_000.log', 1, 266959);
% MT9all = importfileMT9raw('xsensMT9B/04_characterise_yaw_drift2/MT9_cal_00007154_000.log', 1, 266959);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 273707);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 273707);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 273707);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 273707);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 273707);
% rawmagnetometers = importfile_raw_magnetometers('RESLT/raw_magnetometers.dat', 1, 273707);

% x secs. with 257 data per second (ellipse movement)
% MT9euler = importfileMT9euler('xsensMT9B/02_test_ellipse_movement/MT9_euler_00007154_000.log', 1, 20076);
% MT9all = importfileMT9raw('xsensMT9B/02_test_ellipse_movement/MT9_cal_00007154_000.log', 1, 20076);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 26472);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 26472);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 26472);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 26472);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 26472);

% half hour with 257 data per second
% MT9euler = importfileMT9euler('xsensMT9B/06_characterise_yaw_drift_0.5hrs/MT9_euler_00007154_001.log', 1, 524668);
% MT9all = importfileMT9raw('xsensMT9B/06_characterise_yaw_drift_0.5hrs/MT9_cal_00007154_001.log', 1, 524668);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 527622);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 527622);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 527622);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 527622);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 527622);

% 2 hours with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1808483);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1808483);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1816991);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 1816991);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 1816991);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 1816991);
my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 1816991);

%% Euler angles
% Original vs processed roll
figure
%plot(MT9euler(:, 1), MT9euler(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r')
plot(MT9euler(:, 1), MT9euler(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g')
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')

% Original vs processed pitch
figure
%plot(MT9euler(:, 1), MT9euler(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r')
plot(MT9euler(:, 1), MT9euler(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g')
title('Euler angle [pitch]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')

% Original vs processed rollacc_angles[2] = atan2(acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
figure
%plot(MT9euler(:, 1), MT9euler(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r')
plot(MT9euler(:, 1), MT9euler(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g')
title('Euler angle [yaw]')
xlabel('Time(s)')
ylabel('\psi (degrees)')
legend('Solution', 'Gyroscope and accelerometer fusion', 'Angle from accelerometer', 'Location', 'NorthWest')

%% ddrift yaw
figure
plot(my_roll_pitch_yaw(:,1), my_ddrift_yaw(:, 4)*180.0/pi, 'b')
title('Rate of change yaw')
xlabel('Time(s)')
ylabel('ddrift (degrees)')
legend('ddrift yaw', 'Location', 'NorthWest')

%% Interpolate the obtained Euler angles
my_roll_interpolated = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2), MT9euler(:,1));
my_pitch_interpolated = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3), MT9euler(:,1));
my_yaw_interpolated = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4), MT9euler(:,1));

my_diff_roll = abs(MT9euler(:,2) - my_roll_interpolated*180.0/pi);
my_diff_pitch = abs(MT9euler(:,3) - my_pitch_interpolated*180.0/pi);
my_diff_yaw = abs(MT9euler(:,4) - my_yaw_interpolated*180.0/pi);

figure
plot(MT9euler(:, 1), my_diff_roll, 'b')
title('Error \phi (roll)')
xlabel('Time(s)')
ylabel('\epsilon (degrees)')
legend('Error', 'Location', 'NorthWest')

figure
plot(MT9euler(:, 1), my_diff_pitch, 'b')
title('Error \theta (pitch)')
xlabel('Time(s)')
ylabel('\epsilon (degrees)')
legend('Error', 'Location', 'NorthWest')

figure
plot(MT9euler(:, 1), my_diff_yaw, 'b')
title('Error \psi (yaw)')
xlabel('Time(s)')
ylabel('\epsilon (degrees)')
legend('Error', 'Location', 'NorthWest')
hold

% Get the best fit
P = polyfit(MT9euler(:, 1), my_diff_yaw, 1)
%evaluate the polynomial to get some points
poly = polyval(P, MT9euler(:, 1));
plot(MT9euler(:, 1), poly, 'r')

%% Inertial acceleration
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

%% Magnetometers
figure
plot(rawmagnetometers(:, 1), rawmagnetometers(:, 2), 'b')
title('Raw magnetometer [x]')
xlabel('Time(s)')
ylabel('data')
legend('Data', 'Location', 'NorthWest')

figure
plot(rawmagnetometers(:, 1), rawmagnetometers(:, 3), 'b')
title('Raw magnetometer [y]')
xlabel('Time(s)')
ylabel('data')
legend('Data', 'Location', 'NorthWest')

figure
plot(rawmagnetometers(:, 1), rawmagnetometers(:, 4), 'b')
title('Raw magnetometer [z]')
xlabel('Time(s)')
ylabel('data')
legend('Data', 'Location', 'NorthWest')

%% Position
% % Plot position
% figure
% plot(my_position(:, 2), my_position(:, 3), 'b')
% title('Trajectory')
% xlabel('x')
% ylabel('y')
% legend('Trajectory', 'Location', 'NorthWest')
