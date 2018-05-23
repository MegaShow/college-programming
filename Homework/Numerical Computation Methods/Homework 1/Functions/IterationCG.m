function [x, step, err, ok] = IterationCG(A, b, n, k)
x = zeros(n, 1);
r = b - A * x;
p = r;
prev = x;
count = 0;
step = zeros(1, k);
err = zeros(1, k);
while count == 0 || max(abs(x - prev)) >= 10e-5
    prev = x;
    alpha = dot(r, r) / dot(p, A * p);
    x = x + alpha * p;
    rn = r - alpha * A * p;
    beta  = dot(rn, rn) / dot(r, r);
    r = rn;
    p = r + beta * p;
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
