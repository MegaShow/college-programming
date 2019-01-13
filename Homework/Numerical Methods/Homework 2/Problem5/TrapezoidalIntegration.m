function T = TrapezoidalIntegration(n)
h = 1 / n;
T = 1 + sin(1) / 1;
for k = 1 : n - 1
    T = T + 2 * sin(h * k) / (h * k);
end
T = T * h / 2;
end
