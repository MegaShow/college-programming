function y = LagrangeInterpolation(x, x0, y0)
n = length(x0);
y = 0;
for k = 1 : n
    l = 1;
    for i = 1 : n
        if i ~= k
            l = l * (x - x0(i)) / (x0(k) - x0(i));
        end
    end
    y = y + y0(k) * l;
end
end
