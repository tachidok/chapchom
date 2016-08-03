%% Plot roll, pitch and yaw from gyro and accelerometers 
figure
plot(rollpitchyawfromgyro(:,1), rollpitchyawfromgyro(:,2), 'b', rollpitchyawfromacc(:,1), rollpitchyawfromacc(:,2), 'r', rollpitchyawfromacc2(:,1), rollpitchyawfromacc2(:,2), 'm', filteredrollpitchyaw(:,1), filteredrollpitchyaw(:,2), 'g', filteredrollpitchyaw2(:,1), filteredrollpitchyaw2(:,2), 'k')
title('Roll from gyro, acceleration and filtered')
xlabel('Time (s)')
ylabel('Angle (radians)')
legend('Roll from gyro', 'Roll from acceleration', 'Roll from acceleration2', 'Roll filtered', 'Roll filtered2', 'Location', 'NorthWest')

figure
plot(rollpitchyawfromgyro(:,1), rollpitchyawfromgyro(:,3), 'b', rollpitchyawfromacc(:,1), rollpitchyawfromacc(:,3), 'r', rollpitchyawfromacc2(:,1), rollpitchyawfromacc2(:,3), 'm', filteredrollpitchyaw(:,1), filteredrollpitchyaw(:,3), 'g', filteredrollpitchyaw2(:,1), filteredrollpitchyaw2(:,3), 'k')
title('Pitch from gyro, acceleration and filtered')
xlabel('Time (s)')
ylabel('Angle (radians)')
legend('Pitch from gyro', 'Pitch from acceleration', 'Pitch from acceleration2', 'Pitch filtered', 'Pitch filtered2', 'Location', 'NorthWest')

figure
plot(rollpitchyawfromgyro(:,1), rollpitchyawfromgyro(:,4), 'b', rollpitchyawfromacc(:,1), rollpitchyawfromacc(:,4), 'r', rollpitchyawfromacc2(:,1), rollpitchyawfromacc2(:,4), 'm', filteredrollpitchyaw(:,1), filteredrollpitchyaw(:,4), 'g', filteredrollpitchyaw2(:,1), filteredrollpitchyaw2(:,4), 'k')
title('Yaw from gyro, acceleration and filtered')
xlabel('Time (s)')
ylabel('Angle (radians)')
legend('Yaw from gyro', 'Yaw from acceleration', 'Yaw from acceleration2', 'Yaw filtered', 'Yaw filtered2', 'Location', 'NorthWest')

%% Plot roll, pitch and yaw from gyro and accelerometers 
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
plot(rawaccelerations(:,1), rawaccelerations(:,2), 'b', modifiedaccelerations(:,1), modifiedaccelerations(:,2), 'r', modifiedaccelerations2(:,1), modifiedaccelerations2(:,2), 'g')
title('x-acceleration')
xlabel('Time (s)')
ylabel('\frac{m}{s^2}')
legend('Raw acceleration', 'Modified acceleration', 'Modified acceleration2', 'Location', 'NorthWest')

figure
plot(rawaccelerations(:,1), rawaccelerations(:,3), 'b', modifiedaccelerations(:,1), modifiedaccelerations(:,3), 'r', modifiedaccelerations2(:,1), modifiedaccelerations2(:,3), 'g')
title('y-acceleration')
xlabel('Time (s)')
ylabel('\frac{m}{s^2}')
legend('Raw acceleration', 'Modified acceleration', 'Modified acceleration2', 'Location', 'NorthWest')

figure
plot(rawaccelerations(:,1), rawaccelerations(:,4), 'b', modifiedaccelerations(:,1), modifiedaccelerations(:,4), 'r', modifiedaccelerations2(:,1), modifiedaccelerations2(:,4), 'g')
title('z-acceleration')
xlabel('Time (s)')
ylabel('\frac{m}{s^2}')
legend('Raw acceleration', 'Modified acceleration', 'Modified acceleration2', 'Location', 'NorthWest')

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


