%% Read data
MT9euler = importfileMT9euler('xsensMT9B/MT9_euler_00007154_000.log', 1, 18273);
MT9all = importfileMT9raw('xsensMT9B/MT9_cal_00007154_000.log', 1, 18273);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 19533);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 19533);

%% Euler angles
% Original vs processed roll
figure
plot(MT9euler(:, 1), MT9euler(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g')
title('Original vs processed roll')
xlabel('Time (s)')
ylabel('\phi (degrees)')
legend('Original', 'Processed', 'Location', 'NorthWest')

% Original vs processed pitch
figure
plot(MT9euler(:, 1), MT9euler(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g')
title('Original vs processed pitch')
xlabel('Time (s)')
ylabel('\theta (degrees)')
legend('Original', 'Processed', 'Location', 'NorthWest')

% Original vs processed rollacc_angles[2] = atan2(acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
figure
plot(MT9euler(:, 1), MT9euler(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r', my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g')
title('Original vs processed yaw')
xlabel('Time (s)')
ylabel('\psi (degrees)')
legend('Original', 'Processed', 'Location', 'NorthWest')
