function y = LinearInterpolation(x, x1, y1, x2, y2)
l1 = (x - x2) / (x1 - x2);
l2 = (x - x1) / (x2 - x1);
y = y1 * l1 + y2 * l2;
end
