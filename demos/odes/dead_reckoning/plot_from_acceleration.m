%% Plot roll from gyro and accelerometers 
figure
plot(rollpitchyawfromgyro(:,1), rollpitchyawfromgyro(:,2), 'b', rollpitchyawfromacc(:,1), rollpitchyawfromacc(:,2), 'r', filteredrollpitchyaw(:,1), filteredrollpitchyaw(:,2), 'g')
title('Roll from gyro, acceleration and filtered')
xlabel('Time (s)')
ylabel('Angle (radians)')
legend('Roll from gyro', 'Roll from acceleration', 'Roll filtered', 'Location', 'NorthWest')

figure
plot(rollpitchyawfromgyro(:,1), rollpitchyawfromgyro(:,3), 'b', rollpitchyawfromacc(:,1), rollpitchyawfromacc(:,3), 'r', filteredrollpitchyaw(:,1), filteredrollpitchyaw(:,3), 'g')
title('Pitch from gyro, acceleration and filtered')
xlabel('Time (s)')
ylabel('Angle (radians)')
legend('Pitch from gyro', 'Pitch from acceleration', 'Pitch filtered', 'Location', 'NorthWest')

figure
plot(rollpitchyawfromgyro(:,1), rollpitchyawfromgyro(:,4), 'b', rollpitchyawfromacc(:,1), rollpitchyawfromacc(:,4), 'r', filteredrollpitchyaw(:,1), filteredrollpitchyaw(:,4), 'g')
title('Yaw from gyro, acceleration and filtered')
xlabel('Time (s)')
ylabel('Angle (radians)')
legend('Yaw from gyro', 'Yaw from acceleration', 'Yaw filtered', 'Location', 'NorthWest')

%% Plot raw and modified accelerations
figure
plot(rawaccelerations(:,1), rawaccelerations(:,2), 'b', modifiedaccelerations(:,1), modifiedaccelerations(:,2), 'r')
title('x-acceleration')
xlabel('Time (s)')
ylabel('\frac{m}{s^2}')
legend('Raw acceleration', 'Modified acceleration', 'Location', 'NorthWest')

figure
plot(rawaccelerations(:,1), rawaccelerations(:,3), 'b', modifiedaccelerations(:,1), modifiedaccelerations(:,3), 'r')
title('y-acceleration')
xlabel('Time (s)')
ylabel('\frac{m}{s^2}')
legend('Raw acceleration', 'Modified acceleration', 'Location', 'NorthWest')

figure
plot(rawaccelerations(:,1), rawaccelerations(:,4), 'b', modifiedaccelerations(:,1), modifiedaccelerations(:,4), 'r')
title('z-acceleration')
xlabel('Time (s)')
ylabel('\frac{m}{s^2}')
legend('Raw acceleration', 'Modified acceleration', 'Location', 'NorthWest')

%% Draw vectors


