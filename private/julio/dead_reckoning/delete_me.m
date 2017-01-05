%% Position (Yo)
n_data = size(my_velocity,1);
n_seconds_of_test = n_data / 15.0;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = 1.0/14.0;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
for i=2:n_data
    x(i) = step_size * my_velocity(i, 2) * cos(my_roll_pitch_yaw(i,4)) + x(i-1);
    y(i) = step_size * my_velocity(i, 2) * sin(my_roll_pitch_yaw(i,4)) + y(i-1);
end

%% Latitude and longitude
initial_latitude=19.017476;
initial_longitude=98.191140;
lon = zeros(n_data, 1);
lat = zeros(n_data, 1);
cos_init_long = cos(initial_longitude*pi/180.0);
for i=2:n_data
    dx=x(i);
    dy=y(i);
    lon(i) = initial_longitude + (180.0/pi)*(dx/6378137)/cos_init_long;
    lat(i) = initial_latitude + (180.0/pi)*(dy/6378137);
end

%% Position (From velocity from GPS)
n_data = size(my_speed_in_m_per_sec ,1);
n_seconds_of_test = n_data;
n_minutes_of_test = n_seconds_of_test / 60.0;
step_size = n_seconds_of_test / n_data;
x = zeros(n_data, 1);
y = zeros(n_data, 1);
for i=2:n_data
    x(i) = step_size * my_speed_in_m_per_sec(i, 2) * cos(my_roll_pitch_yaw(i,4)) + x(i-1);
    y(i) = step_size * my_speed_in_m_per_sec(i, 2) * sin(my_roll_pitch_yaw(i,4)) + y(i-1);
end