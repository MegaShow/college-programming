addpath Problem2;

val = 115;
max = 150;

format long;

[sqrt, step1, time1, e1, ok] = SqrtBisection(val, 10, 11, max);
if ok ~= 1; disp("Fail Bisection"); else; disp(sqrt); end

[sqrt, step2, time2, e2, ok] = SqrtNewton(val, max);
if ok ~= 1; disp("Fail Newton"); else; disp(sqrt); end

[sqrt, step3, time3, e3, ok] = SqrtSimpleNewton(val, max);
if ok ~= 1; disp("Fail SimpleNewton"); else; disp(sqrt); end

[sqrt, step4, time4, e4, ok] = SqrtSecant(val, max);
if ok ~= 1; disp("Fail Secant"); else; disp(sqrt); end

subplot(2, 1, 1);
plot(time1, e1, 'b', time2, e2, 'm', time3, e3, 'r', time4, e4, 'k');
legend('Bisection', 'Newton', 'SimpleNewton', 'Secant');
title("Convergence Curves with Time");
xlabel('time');
ylabel('convergence');

subplot(2, 1, 2);
plot(step1, e1, 'b', step2, e2, 'm', step3, e3, 'r', step4, e4, 'k');
legend('Bisection', 'Newton', 'SimpleNewton', 'Secant');
title("Convergence Curves with Steps");
xlabel('step');
ylabel('convergence');
