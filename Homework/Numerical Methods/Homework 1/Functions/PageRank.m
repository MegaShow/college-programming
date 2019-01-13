function B = PageRank(A, alpha)
[~, n] = size(A);
B = ones(n, 1) / n;
for i = 1 : n
    val = sum(A(:, i));
    if val
        A(:, i) = A(:, i) / val;
    end
end
disp('finish modify matrix A');
% M = alpha / n * speye(n) + (1 - alpha) * A;
M = (1 - alpha) * A;
prev = B;
count = 0;
while count == 0 || max(abs(B - prev)) > 10e-10
    count = count + 1;
    prev = B;
    % B = M * B;
    B = M * B + alpha / n;
    disp(['finish iteration ' num2str(count)]);
end
end
