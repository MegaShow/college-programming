addpath Problem1;

format long;

x0 = [ 0.32 0.34 0.36 0.38 ];
y0 = sin(x0);

x = 0.35;
y = LinearInterpolation(x, x0(2), y0(2), x0(3), y0(3));
display(y);

y = BilinearInterpolation(x, x0(1), y0(1), x0(2), y0(2), x0(3), y0(3));
display(y);
y = BilinearInterpolation(x, x0(2), y0(2), x0(3), y0(3), x0(4), y0(4));
display(y);

y = LagrangeInterpolation(x, x0, y0);
display(y);
