%% Plot gyro data
figure
plot(caractgyro(:,1), caractgyro(:,4),'b')
figure
plot(caractgyro(:,1), caractgyro(:,6),'r')

n_steps = size(rawgyro,1);
n_data_per_second = 15;
n_seconds = n_steps / n_data_per_second;
step_size = n_seconds / n_steps;
time = 0:step_size:n_seconds-step_size;
figure
%plot(time, rawgyro(:,4), 'b')
plot((rawgyro(:,1) - rawgyro(1, 1)) *1.0e-3, rawgyro(:,4)*-1, 'c')
xlabel('Time (s)')
ylabel('Angular velocity (deg)')

rawgyro3 = [zeros(900,1); rawgyro2(:,1)];
rawgyro3(end-899:end) = [];

rawgyro2 = [(rawgyro(:,1) - rawgyro(1,1)) * 1.0e-3 rawgyro(:,2) rawgyro(:,3) rawgyro(:,4)]

sub = spline(caractgyro(:,1), caractgyro(:,4), rawgyro2(1:734,1));
figure
plot(rawgyro2(1:734,1), rawgyro2(1:734,4), 'b', rawgyro2(1:734,1), -sub, 'r')

n_steps = size(rawgyro,1);
n_data_per_second = 15;
n_seconds = n_steps / n_data_per_second;
step_size = n_seconds / n_steps;
time = 0:step_size:n_seconds-step_size;
figure
%plot(time, rawgyro(:,4), 'b')
plot((rawgyro(:,1) - rawgyro(1, 1)) *1.0e-3, rawgyro(:,4)*-1, 'c')
xlabel('Time (s)')
ylabel('Angular velocity (deg)')

%% Integrate gyro data
n_steps = size(rawgyro,1);
integral = zeros(1,n_steps);
integral(1) = 0.0;
step_size = n_seconds / n_steps;
time = 0:step_size:n_seconds-step_size;
for i = 2:size(rawgyro,1)
    integral(i) = integral(i-1) + rawgyro(:,i-1) * step_size;
end
figure
plot(time, integral, 'm')
