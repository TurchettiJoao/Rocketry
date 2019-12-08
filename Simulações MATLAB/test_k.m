tic;
for k=1:21
    Kp = (k-1)*0.05;
    for m=1:6
        Ki = (m-1)*0.05;
        for n=1:21
            Kd = (n-1)*0.05;
            control_function_k(Kp,Ki,Kd);
        end
    end
end
time = toc;
disp(time);

figure(1);
legend('show');
figure(2);
legend('show');
figure(3);
legend('show');