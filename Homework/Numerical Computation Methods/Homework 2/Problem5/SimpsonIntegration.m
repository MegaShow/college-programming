function T = SimpsonIntegration(n)
h = 1 / n;
T = 1 + sin(1) / 1;
for k = 0 : n - 1
    T = T + 4 * sin(h * (k+1/2)) / (h * (k+1/2));
    if k ~= 0
        T = T + 2 * sin(h * k) / (h * k);
    end
end    
T = T * h / 6;
end
