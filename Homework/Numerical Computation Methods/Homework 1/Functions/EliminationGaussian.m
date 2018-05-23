function x = EliminationGaussian(A, b, n)
for k = 1 : n - 1
    for i = k + 1 : n
        m = A(i, k) / A(k, k);
        for j = k : n
            A(i, j) = A(i, j) - m * A(k, j);
        end
        b(i) = b(i) - m * b(k);
    end
end
x = zeros(n, 1);
for k = n : -1 : 1
    x(k) = b(k) / A(k, k);
    for i = 1 : k - 1
        b(i) = b(i) - x(k) * A(i, k);
    end
end
end
