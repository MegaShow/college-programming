function y = BilinearInterpolation(x, x1, y1, x2, y2, x3, y3)
l1 = ((x - x2) * (x - x3)) / ((x1 - x2) * (x1 - x3));
l2 = ((x - x1) * (x - x3)) / ((x2 - x1) * (x2 - x3));
l3 = ((x - x1) * (x - x2)) / ((x3 - x1) * (x3 - x2));
y = y1 * l1 + y2 * l2 + y3 * l3;
end
