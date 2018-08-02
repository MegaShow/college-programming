addpath Problem3;

format long;

n = 10;
m = 10000;
[A, b] = CreateMatrix(m, n);
[x, step, e, ok] = RecursiveLeastSquares(A, b);
if ok ~= 1; disp("Fail RLS"); else; disp(x); end

plot(step, e, 'b');
legend('RLS');
title("RLS step-error plot");
xlabel('step');
ylabel('error');

function [A, b] = CreateMatrix(m, n)
A = randn(m, n);
b = randn(1, m);
end
