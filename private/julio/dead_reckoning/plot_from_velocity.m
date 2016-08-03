%% Read the data from file
data = importfile_data_original('data.dat', 2850, 78056);
longitudeEuler = importfile_longitude_from_velocity('RESLT/longitude_from_velocityEuler.dat', 367, 10001);
latitudeEuler = importfile_latitude_from_velocity('RESLT/latitude_from_velocityEuler.dat', 367, 10001);
longitudeRK4 = importfile_longitude_from_velocity('RESLT/longitude_from_velocityRK4.dat', 367, 10001);
latitudeRK4 = importfile_latitude_from_velocity('RESLT/latitude_from_velocityRK4.dat', 367, 10001);
%longitudeEuler = importfile_longitude_from_velocity('RESLT/longitude_from_velocityEuler.dat', 3653, 100001);
%latitudeEuler = importfile_latitude_from_velocity('RESLT/latitude_from_velocityEuler.dat', 3653, 100001);
%longitudeRK4 = importfile_longitude_from_velocity('RESLT/longitude_from_velocityRK4.dat', 3653, 100001);
%latitudeRK4 = importfile_latitude_from_velocity('RESLT/latitude_from_velocityRK4.dat', 3653, 100001);

%% Scale
% Get max, min and the range of the original latitude
latitude_max = max(data(:,2));
latitude_min = min(data(:,2));
range_latitude = latitude_max - latitude_min;

% Get max, min and the range of the original longitud
longitude_max = max(data(:,3));
longitude_min = min(data(:,3));
range_longitude = longitude_max - longitude_min;

% Get max, min and the range of the longitudEuler
longitudeEuler_max = max(longitudeEuler(:,2));
longitudeEuler_min = min(longitudeEuler(:,2));
range_longitudeEuler = longitudeEuler_max - longitudeEuler_min;

% Get max, min and the range of the target latitudeEuler
latitudeEuler_max = max(latitudeEuler(:,2));
latitudeEuler_min = min(latitudeEuler(:,2));
range_latitudeEuler = latitudeEuler_max - latitudeEuler_min;

% Scale longitud based on the target longitudeEuler
longitude_scaled(:,1) = data(:,1);
longitude_scaled(:,2) = longitudeEuler_min + ((data(:,3)-longitude_min)/range_longitude)*range_longitudeEuler;

% Scale latitud based on the target latitudeEuler
latitude_scaled(:,1) = data(:,1);
latitude_scaled(:,2) = latitudeEuler_min + ((data(:,2)-latitude_min)/range_latitude)*range_latitudeEuler;

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
%title('Trajectory [Euler]')
%xlabel('x-direction')
%ylabel('y-direction')
title('Trayectoria [Euler]')
xlabel('Dirección x (m)')
ylabel('Dirección y (m)')

figure
plot(longitude_scaled(:,2), latitude_scaled(:,2), 'b', longitudeRK4(:,2), latitudeRK4(:,2), ':g')
%title('Trajectory [Runge-Kutta 4]')
%xlabel('x-direction')
%ylabel('y-direction')
title('Trayectoria [Runge-Kutta 4]')
xlabel('Dirección x (m)')
ylabel('Dirección y (m)')

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
%title('Absolute error [Euler]')
%xlabel('Time (s)')
%ylabel('\epsilon')
%legend('Absolute error x-direction', 'Absolute error y-direction', 'Location', 'NorthWest')
title('Error absoluto [Euler]')
xlabel('Tiempo (s)')
ylabel('\epsilon (m)')
legend('Error absoluto dirección x', 'Error absoluto dirección y', 'Location', 'NorthWest')

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
%title('Absolute error [RK4]')
%xlabel('Time (s)')
%ylabel('\epsilon')
%legend('Absolute error x-direction', 'Absolute error y-direction', 'Location', 'NorthWest')
title('Error absoluto [RK4]')
xlabel('Tiempo (s)')
ylabel('\epsilon (m)')
legend('Error absoluto dirección x', 'Error absoluto dirección y', 'Location', 'NorthWest')

figure
plot(longitudeRK4(:,1), longitude_RK4_relative_error, 'b', latitudeRK4(:,1), latitude_RK4_relative_error, 'r')
title('Relative error [RK4]')
xlabel('Time (s)')
ylabel('\eta')
legend('Relative error x-direction', 'Relative error y-direction', 'Location', 'NorthWest')
