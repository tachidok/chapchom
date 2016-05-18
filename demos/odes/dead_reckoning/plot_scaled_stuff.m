%% Get rid of the first 150 seconds
size_data = size(latitude, 1);
new_latitude = latitude([2851:size_data],:);
new_longitude = longitude([2851:size_data],:);

size_data_Euler = size(latitudeEuler, 1);
new_latitudeEuler = latitudeEuler([3621:size_data_Euler],:);
new_longitudeEuler = longitudeEuler([3621:size_data_Euler],:);

size_data_RK4 = size(latitudeRK4, 1);
new_latitudeRK4 = latitudeRK4([364:size_data_RK4],:);
new_longitudeRK4 = longitudeRK4([364:size_data_RK4],:);

new_latitude(:,1) = new_latitude(:,1) - 150;
new_longitude(:,1) = new_longitude(:,1) - 150;
new_latitudeEuler(:,1) = new_latitudeEuler(:,1) - 150;
new_longitudeEuler(:,1) = new_longitudeEuler(:,1) - 150;
new_latitudeRK4(:,1) = new_latitudeRK4(:,1) - 150;
new_longitudeRK4(:,1) = new_longitudeRK4(:,1) - 150;

latitude = new_latitude;
longitude = new_longitude;
latitudeEuler = new_latitudeEuler;
longitudeEuler = new_longitudeEuler;
latitudeRK4 = new_latitudeRK4;
longitudeRK4 = new_longitudeRK4;

%% Scale longitude
% Get max, min and the range of the original longitud
longitude_max = max(longitude(:,2));
longitude_min = min(longitude(:,2));
range_longitude = longitude_max - longitude_min;

% Get max, min and the range of the target longitud
longitudeEuler_max = max(longitudeEuler(:,2));
longitudeEuler_min = min(longitudeEuler(:,2));
range_longitudeEuler = longitudeEuler_max - longitudeEuler_min;

% Scale based on the target longitude
longitude_scaled = longitude;
longitude_scaled(:,2) = longitudeEuler_min + ((longitude(:,2)-longitude_min)/range_longitude)*range_longitudeEuler;

%% Scale latitude
% Get max, min and the range of the original latitude
latitude_max = max(latitude(:,2));
latitude_min = min(latitude(:,2));
range_latitude = latitude_max - latitude_min;

% Get max, min and the range of the target latitude
latitudeEuler_max = max(latitudeEuler(:,2));
latitudeEuler_min = min(latitudeEuler(:,2));
range_latitudeEuler = latitudeEuler_max - latitudeEuler_min;

% Scale based on the target latitude
latitude_scaled = latitude;
latitude_scaled(:,2) = latitudeEuler_min + ((latitude(:,2)-latitude_min)/range_latitude)*range_latitudeEuler;

%% Plot scaled movement in each direction
figure
plot(longitude_scaled(:,1), longitude_scaled(:,2), 'b', longitudeEuler(:,1), longitudeEuler(:,2), '--r', longitudeRK4(:,1), longitudeRK4(:,2), ':g')
title('Displacement in "x-direction"')
xlabel('Time (s)')
ylabel('Displacement (m)')
legend('Original', 'Euler', 'Runge-Kutta 4', 'Location', 'NorthWest')

figure
plot(latitude_scaled(:,1), latitude_scaled(:,2), 'b', latitudeEuler(:,1), latitudeEuler(:,2), '--r', latitudeRK4(:,1), latitudeRK4(:,2), ':g')
title('Displacement in "y-direction"')
xlabel('Time (s)')
ylabel('Displacement (m)')
legend('Original', 'Euler', 'Runge-Kutta 4')

%% Plot trajectory
figure
plot(longitude_scaled(:,2), latitude_scaled(:,2), 'b', longitudeEuler(:,2), latitudeEuler(:,2), '--r')
title('Trajectory [Euler]')
xlabel('x-direction')
ylabel('y-direction')

figure
plot(longitude_scaled(:,2), latitude_scaled(:,2), 'b', longitudeRK4(:,2), latitudeRK4(:,2), ':g')
title('Trajectory [Runge-Kutta 4]')
xlabel('x-direction')
ylabel('y-direction')

%% Get errors [Based on Euler]
% Interpolate the results to get the same points as in the original
% measurements
longitude_scaled_on_Euler_interpolated = interp1(longitude_scaled(:,1), longitude_scaled(:,2), longitudeEuler(:,1));
latitude_scaled_on_Euler_interpolated = interp1(latitude_scaled(:,1), latitude_scaled(:,2), latitudeEuler(:,1));

% Get the errors

% Absolute error
longitude_Euler_absolute_error = abs(longitude_scaled_on_Euler_interpolated - longitudeEuler(:,2));
latitude_Euler_absolute_error = abs(latitude_scaled_on_Euler_interpolated - latitudeEuler(:,2));

% Relative error
longitude_Euler_relative_error = longitude_Euler_absolute_error ./ abs(longitude_scaled_on_Euler_interpolated);
latitude_Euler_relative_error = latitude_Euler_absolute_error ./ abs(latitude_scaled_on_Euler_interpolated);

figure
plot(longitudeEuler(:,1), longitude_Euler_absolute_error, 'b', latitudeEuler(:,1), latitude_Euler_absolute_error, 'r')
title('Absolute error [Euler]')
xlabel('Time (s)')
ylabel('\epsilon')
legend('Absolute error x-direction', 'Absolute error y-direction', 'Location', 'NorthWest')

figure
plot(longitudeEuler(:,1), longitude_Euler_relative_error, 'b', latitudeEuler(:,1), latitude_Euler_relative_error, 'r')
title('Relative error [Euler]')
xlabel('Time (s)')
ylabel('\eta')
legend('Relative error x-direction', 'Relative error y-direction', 'Location', 'NorthWest')

%% Get errors [Based on RK4]
% Interpolate the results to get the same points as in the original
% measurements
longitude_scaled_on_RK4_interpolated = interp1(longitude_scaled(:,1), longitude_scaled(:,2), longitudeRK4(:,1));
latitude_scaled_on_RK4_interpolated = interp1(latitude_scaled(:,1), latitude_scaled(:,2), latitudeRK4(:,1));

% Get the errors

% Absolute error
longitude_RK4_absolute_error = abs(longitude_scaled_on_RK4_interpolated - longitudeRK4(:,2));
latitude_RK4_absolute_error = abs(latitude_scaled_on_RK4_interpolated - latitudeRK4(:,2));

% Relative error
longitude_RK4_relative_error = longitude_RK4_absolute_error ./ abs(longitude_scaled_on_RK4_interpolated);
latitude_RK4_relative_error = latitude_RK4_absolute_error ./ abs(latitude_scaled_on_RK4_interpolated);

figure
plot(longitudeRK4(:,1), longitude_RK4_absolute_error, 'b', latitudeRK4(:,1), latitude_RK4_absolute_error, 'r')
title('Absolute error [RK4]')
xlabel('Time (s)')
ylabel('\epsilon')
legend('Absolute error x-direction', 'Absolute error y-direction', 'Location', 'NorthWest')

figure
plot(longitudeRK4(:,1), longitude_RK4_relative_error, 'b', latitudeRK4(:,1), latitude_RK4_relative_error, 'r')
title('Relative error [RK4]')
xlabel('Time (s)')
ylabel('\eta')
legend('Relative error x-direction', 'Relative error y-direction', 'Location', 'NorthWest')
