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
