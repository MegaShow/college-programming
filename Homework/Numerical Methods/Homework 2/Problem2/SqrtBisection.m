function [sqrt, step, time, e, ok] = SqrtBisection(val, lower, upper, max)
step = zeros(max, 1);
time = zeros(max, 1);
e = zeros(max, 1);
count = 0;
tic;
while count < max && upper - lower > 10e-6
    count = count + 1;
    sqrt = lower + (upper - lower) / 2;
    if sqrt * sqrt == val
        return;
    elseif sqrt * sqrt < val
        lower = sqrt;
    else
        upper = sqrt;
    end
    step(count) = count;
    time(count) = toc;
    e(count) = upper - lower;
end
if count == max
    ok = 0;
else
    ok = 1;
end
end
