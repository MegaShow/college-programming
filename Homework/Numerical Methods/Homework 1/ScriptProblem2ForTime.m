addpath Functions;

% random test
n = [ 10 50 100 200 ];
t1 = zeros(1, 4);
t2 = zeros(1, 4);
t3 = zeros(1, 4);
t4 = zeros(1, 4);
t5 = zeros(1, 4);
t6 = zeros(1, 4);
for i = 1 : 4
    [A, b] = CreateMatrix(n(i));
    tic;
    [~, ~, ~, ok] = IterationJacobi(A, b, n(i), 1000);
    if ok; t1(i) = toc; else; t1(i) = inf; end
    tic;
    [~, ~, ~, ok] = IterationGaussSeidel(A, b, n(i), 1000);
    if ok; t2(i) = toc; else; t2(i) = inf; end
    tic;
    [~, ~, ~, ok] = IterationSOR(A, b, n(i), 1000, 1.2);
    if ok; t3(i) = toc; else; t3(i) = inf; end
    tic;
    [~, ~, ~, ok] = IterationCG(A, b, n(i), 1000);
    if ok; t4(i) = toc; else; t4(i) = inf; end
    tic;
    EliminationGaussian(A, b, n(i));
    t5(i) = toc;
    tic;
    EliminationColumn(A, b, n(i));
    t6(i) = toc;
end
plot(n, t1, 'b', n, t2, 'm', n, t3, 'r', n, t4, 'k', n, t5, 'g', n, t6, 'c');
legend('Jacobi', 'GaussSeidel', 'SOR', 'CG', 'E-Gaussian', 'E-Column');
title('Iteration Time Plot');
xlabel('n');
ylabel('time/s');

function [A, b] = CreateMatrix(n)
X = diag(rand(n, 1));
U = orth(rand(n));
A = U' * X * U;
b = randn(n, 1);
end
