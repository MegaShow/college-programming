function y = FastFourierTransform(x, n)
p = log2(n);
y = x';
m = (0 : n / 2 - 1);
w = exp(-1i * 2 * pi * m / n)';
for q = 1 : p
    yprev = y;
    for k = 0 : 2^(p-q) - 1
        for j = 0 : 2^(q-1) - 1
            y(k*2^q+j+1) = ...
                yprev(k*2^(q-1)+j+1) + yprev(k*2^(q-1)+j+2^(p-1)+1);
            y(k*2^q+j+2^(q-1)+1) = ...
                (yprev(k*2^(q-1)+j+1) - yprev(k*2^(q-1)+j+2^(p-1)+1)) * ...
                w(k*2^(q-1)+1);
        end
    end
end
end
