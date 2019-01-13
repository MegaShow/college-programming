function [sqrt, step, time, e, ok] = SqrtNewton(val, max)
prev = 0;
sqrt = val;
step = zeros(max, 1);
time = zeros(max, 1);
e = zeros(max, 1);
count = 0;
tic;
while count < max && abs(sqrt - prev) > 10e-6
    count = count + 1;
    prev = sqrt;
    sqrt = (sqrt + val / sqrt) / 2;
    step(count) = count;
    time(count) = toc;
    e(count) = abs(sqrt - prev);
end
if count == max
    ok = 0;
else
    ok = 1;
end
end
