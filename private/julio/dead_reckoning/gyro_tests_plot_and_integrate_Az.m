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

close all,
figure
%plot(time, rawgyro(:,4), 'b')
plot((rawgyro(:,1) - rawgyro(1, 1)) *1.0e-3, rawgyro(:,4)*-1, 'c')
xlabel('Time (s)')
ylabel('Angular velocity (deg)')

rawgyro3 = [zeros(900,1); rawgyro2(:,1)];
rawgyro3(end-899:end) = [];
rawgyro2 = [(rawgyro(:,1) - rawgyro(1,1)) * 1.0e-3 rawgyro(:,2) rawgyro(:,3) rawgyro(:,4)]

Ts = rawgyro2(734,1)/733; %sum(diff(rawgyro2(1:end,1)))/length(rawgyro2(1:end,1));
Tc = (0:(Ts):(caractgyro(end,1)+Ts))';
sub = spline(caractgyro(:,1), caractgyro(:,4), .977*Tc );
sub3 = spline(rawgyro2(1:734,1), -rawgyro2(1:734,4), Tc);
Td = 11;
sub2 = [zeros(Td,1); sub(:,1)];
sub2(end-Td+1:end) = [];
figure,%1.02235*
velerr = sub2-sub3;
plot(Tc, sub3, 'b:', Tc, sub2, Tc, velerr)
legend('vel gyro','vel enc','vel err')

posgyro = .001*Ts*cumsum(sub3);
posenc = .001*Ts*cumsum(sub2)
poserr = posenc-posgyro;

figure, plot(Tc,posgyro,'b:',Tc,posenc, Tc, poserr)
grid on, legend('pos raw gyro','pos enc','pos err')

figure, plot(caractgyro(:,1), caractgyro(:,5))
grid on, legend('pos drive')

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
