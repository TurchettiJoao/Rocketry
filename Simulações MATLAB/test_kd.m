Kp = 0.00;
Ki = 0.00;

for i=1:21
    Kd = (i-1)*0.05;
    control_function_kd(Kp,Kd,Ki);
end

figure(1);
legend('show');