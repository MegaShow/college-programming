function [x, y] = ForwardEuler(x0, y0, h)
x = [ x0; zeros(1 / h, 1) ];
y = [ y0; zeros(1 / h, 1) ];
count = 1;
while count <= 1 / h + 1
    x(count+1) = count * h;
    y(count+1) = y(count) + h * (y(count) - 2*(count-1)*h / y(count));
    count = count + 1;
end
end
