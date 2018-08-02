function [x, y] = ImprovedEuler(x0, y0, h)
x = [ x0; zeros(1 / h, 1) ];
y = [ y0; zeros(1 / h, 1) ];
count = 1;
while count <= 1 / h + 1
    x(count+1) = count * h;
    fn = y(count) - 2*(count-1)*h / y(count);
    ynext = y(count) + h * fn;
    y(count+1) = y(count) + h / 2 * (fn + (ynext - 2 * count * h / ynext));
    y(count+1) = (ynext + y(count+1)) / 2;
    count = count + 1;
end
end
