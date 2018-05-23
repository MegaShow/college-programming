function x = EliminationColumn(A, b, n)
for k = 1 : n - 1
    max = k;
    for i = k + 1 : n
        if A(i, k) > A(max, k)
            max = i;
        end
    end
    A([k max], :) = A([max k], :);
    b([k max]) = b([max k]);
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
