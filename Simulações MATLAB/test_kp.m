Kp = 0.45;
Ki = 0.05;
Kd = 0.3;

for i=1:11
    Kp = (i-1)*0.05;
    control_function_kp(Kp,Kd,Ki);
end

figure(1);
legend('show');