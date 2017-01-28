
clear all, clc,
close all,

load azgad2,
load escalon2,

% Periodos de muestreo del Motor y de la Gyro
hM = 1.000000*mean(diff(TIME))*1e-03; 
hG = 1.000000*mean(diff(rawgyro(:,1)))*1e-06;

% Variable tiempo 1)Motor, 2)Gyro, 3)Gyro sobremuestreada
t1 = 1e-03*(TIME - TIME(1));
t2 = 1e-06*(rawgyro(:,1)-rawgyro(1,1)); 
t3 = (0:hM:t2(end))';

% Velocidades angulares del Motor y Gyro
u = -VLFB; 
wx = rawgyro(:,2);
wy = rawgyro(:,3);
wz = -rawgyro(:,4);% -comp1*wx -comp2*wy; 

% Calculo de desalineacion respecto a frame 'Virtual' horizontal
Gamma = atan(wy./wz);
Beta = -atan(wx.*sin(Gamma)./wy);
% Gamma = atan2(wy,wz); 
% Beta = -atan2(wx.*sin(Gamma),wy); 
Alpha = -0*ones(length(t2),1);

% Parametros de la matriz de rotacion de la Gyro al frame Virtual
b = cos(Beta);
c = cos(Gamma);
e = sin(Beta);
f = sin(Gamma);
 
%S = 160;
% Alpha = atan2(b.*wx + e.*f.*wy + c.*e.*wz, c.*wy-f.*wz); 
% Alpha = atan2(f.*wz - c.*wy, b.*wx + e.*f.*wy + c.*e.*wz); 
% Alpha(S) = -74.9*pi/180;%0.0750138*pi/180% Alpha(200) = 5.075013807*pi/180 % [0.0886]

a = cos(Alpha);
d = sin(Alpha);
% % % a = 5*pi/180
% % % cos(a)-1,     //body_accelerations[0]=aligned_acc_signal_x[i]-0.4942;
     //body_accelerations[1]=aligned_acc_signal_y[i]-0.4942;
     //body_accelerations[2]=aligned_acc_signal_z[i]-0.4942;
% % % -a^2/2

% wz en el marco de referencia virtual (calculo inverso)
wz_virtual = -(wx+wy+wz)./(b.*(c+f)-e);

% wz = 1.32*(-wz + wy); % Ajuste de escala simple
% figure, plot(t2,wz,t2,1.32*(-wz + wy),':')
% z1 = interp1(t2,1.3*wz, t3); %spline interp1

% Interpolacion lineal de wz-Virtual para comparacion con wz-Encoder
z1 = interp1(t2,wz, t3); %spline interp1

% Graficacion de velocidades 
N3 = abs(length(t1)-length(t3));

% % figure,
% % plot(t1,u,'c', t2,wz,'--', t3,z1,':'),
% % legend('u', 'wz (h-gruesa)','wz (interp1 h-fina)')

if(t1(end)>t3(end))
    t = t1;
    z1 = [z1; zeros(N3,1)];
%     figure,
%     plot(t,u,'-', t,z1,':'),
%     legend('u (h-fina)','wz (h-fina)')
else
    t = t3;
    u = [u; zeros(N3,1)];
%     figure,
%     plot(t,u,'-', t,z1,':'),
%     legend('u (h-fina)', 'wz (h-fina)')
end
% u-z
% 
% Desfase de mediciones para comparacion 
N = length(t);
Nd = 192;
u = [zeros(Nd,1);  u];
u(N+1:N+Nd) = [];

figure,
plot(t,u,'k--', t,-z1,'b:', t2,wx,'r', t2,-wy,'g'),
ylabel('Angular Velocities[deg/s]'), xlabel('t[s]')
legend('wz-Encoder (dephased)', 'wz-Gyro(interpolated)', 'wx-Gyro', 'wy-Gyro')

figure, 
plot(t,hM*cumsum(u),'k-', t,hM*cumsum(-z1),'b:'),
ylabel('Angular position[deg]'), xlabel('t[s]')
legend('Pos Encoder [deg]','Pos Gyro (interpolated) [deg]')

% figure, plot(t2,Beta,t2, Gamma,':'),
% legend('beta','gamma')

% Comprobacion de calculo directo de wz-Virtual mediante matriz de rotacion
for(k=1:length(t2))
    
    ak = a(k);
    bk = b(k);
    ck = c(k);    
    dk = d(k);
    ek = e(k);
    fk = f(k); 

    wxk = wx(k); 
    wyk = wy(k);     
    wzk = wz(k); 
    
    uz(:,k) = [ak*bk, ak*ek*fk-ck*dk, dk*fk+ak*ck*ek;
        bk*dk, ak*ck+dk*ek*fk, ck*dk*ek-ak*fk;
        -ek, bk*fk, bk*ck]'*[wxk wyk rawgyro(k,4)]';
end

% Velocidad angular 
figure, plot(t2,uz,t2,wx,':',t2,wy,':',t2,-wz,'.', t2,-wy+rawgyro(:,4),'k:', t2,Beta,':',t2,Gamma,':'),
legend('ux(generated)', 'uy (generated)', 'uz (generated)','wx (original)','wy (original)','wz (original)', 'wz (K_{Azgad})', 'Beta','Gamma'),
ylabel('Angular velocities [deg/s]'), xlabel('t[s]')

% Posicion angular
figure, plot(t2,zeros(length(t2),1),'k', t2,hG*cumsum(rawgyro(:,4)), t2,...
    hG*1.1285*( cumsum(wz)' -cumsum(uz(2,:))'-cumsum(uz(1,:))' ), t2,1.3*hG*cumsum(-wy+rawgyro(:,4)), t,hM*cumsum(u) )
legend('pos zero','pos wz-Gyro','pos uz-Virtual (generated)','pos wz-K_{Azgad}', 'pos wz-Motor'),
ylabel('Yaw position [deg]'), xlabel('t[s]')

% Comparacion wz-Gyro y wz-Virtual
%([uz(3,:) ; -wz']),
figure, plot(t2,-wz,t2,uz(3,:),t2,[uz(3,:) + wz'])
legend('wz-Gyro','wz-Virtual-Frame','wz-Difference between frames')
ylabel('wz [deg/s]'), xlabel('t[s]')


figure, plot(t2,cumsum( uz(2,:)) + cumsum( uz(1,:)) ),
ylabel('drift position [deg]'), xlabel('t[s]')
legend('Virtual Frame Total Drift')

% wz calculado mediante matriz de rotacion y mediante relacion geometrica
uz(3,:)' - wz_virtual % (wx+wy+wz)./(b.*(c+f)-e)


% uz(:,S)