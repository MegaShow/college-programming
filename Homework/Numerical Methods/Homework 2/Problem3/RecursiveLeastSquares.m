function [x, step, e, ok] = RecursiveLeastSquares(A, b)
[m, n] = size(A);
count = 0;
e = zeros(m, 1);
step = zeros(m, 1);
x = ones(n, 1) * 0.000001;
p = ones(n) * 1000000000;
while count < m && (count == 0 || e(count) > 10e-6)
    varphi = A(count + 1, :)';
    xprev = x;
    k = p * varphi / (1 + varphi' * p * varphi);
    p = (eye(n) - k * varphi') * p;
    x = x + k * (b(count + 1) - varphi' * x);
    count = count + 1;
    step(count) = count;
    e(count) = max(max(abs(x - xprev)));
end
if count == m
    ok = 0;
else
    ok = 1;
end
end
