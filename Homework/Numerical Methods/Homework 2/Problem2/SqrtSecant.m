function [sqrt, step, time, e, ok] = SqrtSecant(val, max)
prev = 0;
sqrt = val;
step = zeros(max, 1);
time = zeros(max, 1);
e = zeros(max, 1);
count = 0;
tic;
while count < max && abs(sqrt - prev) > 10e-6
    count = count + 1;
    tmp = sqrt;
    sqrt = sqrt - (sqrt * sqrt - val) / (sqrt + prev);
    prev = tmp;
    step(count) = count;
    time(count) = toc;
    e(count) = abs(sqrt - prev);
end
if count == max
    ok = 0;
else
    ok = 1;
end
e = abs(e);
end
