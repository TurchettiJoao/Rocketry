clear
clc

%% Definição de variáveis

N = 800;
pitch_referencia = 10; % Objetivo em graus
pitch_referencia = pitch_referencia*pi/180; % De graus para radianos

% Variáveis físicas no SI
m = 5; % Massa do foguete em kg
L = 0.5; % Distância entre o Cg e a hélice em metros
F = 100; % Empuxo da hélice em Newtons
In = 0.2; % Momento de inércia do foguete

% Condições iniciais
TVA_pitch_inicial = 0; % Ângulo do TVA imposto pelo servo, pode variar de -pi/2 a pi/2
torque_inicial = -F*sin(TVA_pitch_inicial)*L; % Torque causado pela hélice, dado por -F.sen(TVA_pitch).L
pitch_inicial = 0; % Ângulo do foguete em relação à vertical, pode variar de -pi/2 a pi/2
wx_inicial = 0; % pitch ponto
ang_acc_x_inicial = torque_inicial/In; % pitch ponto ponto

% Definição dos vetores necessários
TVA_pitch = zeros(N,1);
TVA_pitch(1) = TVA_pitch_inicial;

torque = zeros(N,1);
torque(1) = torque_inicial;

pitch = zeros(N,1);
pitch(1) = pitch_inicial;

wx = zeros(N,1); % pitch ponto
wx(1) = wx_inicial;

ang_acc_x = zeros(N,1); % pitch ponto ponto
ang_acc_x(1) = ang_acc_x_inicial;

erro = zeros(N,1);

% Definições adicionais
f = 50; % Frequência da malha em hz
dt = 1/f; %  Período da malha em s
Kp = 0.45;
Ki = 0.05;
Kd = 0.3;
a = Kp + Ki*dt/2 + Kd/dt;
b = -Kp + Ki*dt/2 - 2*Kd/dt;
c = Kd/dt;

wx_servo = zeros(N,1); % graus/s

%% Simulação em malha fechada, controle proporcional

aux = [pitch(1), wx(1)];
fx = @(t, aux) [aux(2) + ang_acc_x(1) * t, ang_acc_x(1)];
k1 = fx( 0       ,   aux                );
k2 = fx( 0.5 * dt,   aux + 0.5 * dt * k1);
k3 = fx( 0.5 * dt,   aux + 0.5 * dt * k2);
k4 = fx( 0       ,   aux + 1.0 * dt * k3);
AUX = aux + (1/6)*(k1 + 2*k2 + 2*k3 + k4)*dt;
pitch(2) = AUX(1);
wx(2) = AUX(2);
ang_acc_x(2) = torque(2)/In;

for i=3:N
    
    aux = [pitch(i-1) wx(i-1)];
    fx = @(t, aux) [aux(2) + ang_acc_x(i-1) * t, ang_acc_x(i-1)];
    k1 = fx( 0       ,   aux                );
    k2 = fx( 0.5 * dt,   aux + 0.5 * dt * k1);
    k3 = fx( 0.5 * dt,   aux + 0.5 * dt * k2);
    k4 = fx( 0       ,   aux + 1.0 * dt * k3);
    AUX = aux + (1/6)*(k1 + 2*k2 + 2*k3 + k4)*dt;
    pitch(i) = AUX(1);
    wx(i) = AUX(2);
    
%   pitch(i) = pitch(i-1) + dt*wx(i-1);
%   wx(i) = wx(i-1) + dt*ang_acc_x(i-1);

    
    erro(i) = pitch_referencia - pitch(i);
    %erro(i) = pitch_referencia - pitch(i) + randn()/50; % COM RUIDO
    
    torque(i) = torque(i-1) + a*erro(i) + b*erro(i-1) + c*erro(i-2);
    TVA_pitch(i) = asin(-torque(i)/(F*L));
    wx_servo(i) = (TVA_pitch(i)-TVA_pitch(i-1))*180/(dt*pi);
    ang_acc_x(i) = torque(i)/In;
end

tempo = 0:dt:dt*(N-1);

figure(1);
plot(tempo,pitch*180/pi);
title('Ângulo entre o foguete e a vertical (pitch)');
xlabel('t [s]');
ylabel('pitch [graus]');


figure(2)
plot(tempo,TVA_pitch*180/pi);
title('Ângulo aplicado pelo servo (pitch)');
xlabel('t [s]');
ylabel('TVA_ pitch [graus]');

figure(3)
plot(tempo,wx_servo);
title('Velocidade angular do servo');
xlabel('t [s]');
ylabel('wx_ servo [graus/s]');


[max_wx_servo, max_wx_servo_instant] = max(abs(wx_servo)); % Obtém a máxima vel angular do servo
% e o instante em que isso ocorreu

fprintf('Máxima velocidade angular do servo: %.2f rad/s @ %.2f s\n',max_wx_servo,(max_wx_servo_instant-1)*dt)
fprintf('Overshoot: %.2f%% \n\n',(max(abs(pitch))*sign(pitch_referencia)-pitch_referencia)*100/pitch_referencia)
















