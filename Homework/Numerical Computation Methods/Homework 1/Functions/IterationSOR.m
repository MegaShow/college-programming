function [x, step, err, ok] = IterationSOR(A, b, n, k, omega)
D = zeros(n);
L = zeros(n);
U = zeros(n);
for i = 1 : n
    for j = 1 : n
        if i == j
            D(i, j) = A(i, j);
        elseif i > j
            L(i, j) = -A(i, j);
        else
            U(i, j) = -A(i, j);
        end
    end
end
Lomega = (D - omega * L) ^ -1 * ((1 - omega) * D + omega * U);
f = omega * (D - omega * L) ^ -1 * b;
x = zeros(n, 1);
prev = x;
count = 0;
step = zeros(1, k);
err = zeros(1, k);
while count == 0 || max(abs(x - prev)) >= 10e-5
    prev = x;
    x = Lomega * x + f;
    count = count + 1;
    step(count) = count;
    err(count) = norm(x - prev);
    if count == k
        ok = 0;
        return
    end
end
step = step(1:count);
err = err(1:count);
ok = 1;
end
