addpath Functions;

% standard test
n = 2;
A = [ 3 1; 1 2 ];
b = [ 5; 5 ];
[x, ~, ~, ok] = IterationJacobi(A, b, n, 20);
if ok; display(x); else; fprintf("Jacobi fail\n"); end
[x, ~, ~, ok] = IterationGaussSeidel(A, b, n, 20);
if ok; display(x); else; fprintf("GaussSeidel fail\n"); end
[x, ~, ~, ok] = IterationSOR(A, b, n, 20, 1.2);
if ok; display(x); else; fprintf("SOR fail\n"); end
[x, ~, ~, ok] = IterationCG(A, b, n, 20);
if ok; display(x); else; fprintf("CG fail\n"); end

n = 3;
A = [ 8 -3 2; 4 11 -1; 6 3 12 ];
b = [ 20; 33; 36 ];
[x, ~, ~, ok] = IterationJacobi(A, b, n, 20);
if ok; display(x); else; fprintf("Jacobi fail\n"); end
[x, ~, ~, ok] = IterationGaussSeidel(A, b, n, 20);
if ok; display(x); else; fprintf("GaussSeidel fail\n"); end
[x, ~, ~, ok] = IterationSOR(A, b, n, 20, 1.2);
if ok; display(x); else; fprintf("SOR fail\n"); end
[x, ~, ~, ok] = IterationCG(A, b, n, 20);
if ok; display(x); else; fprintf("CG fail\n"); end

% random test
n = [ 10 50 100 200 ];
t1 = zeros(1, 4);
t2 = zeros(1, 4);
t3 = zeros(1, 4);
t4 = zeros(1, 4);
for i = 1 : 4
    [A, b] = CreateMatrix(n(i));
    [~, step1, err1, ~] = IterationJacobi(A, b, n(i), 1000);
    [~, step2, err2, ~] = IterationGaussSeidel(A, b, n(i), 1000);
    [~, step3, err3, ~] = IterationSOR(A, b, n(i), 1000, 1.2);
    [~, step4, err4, ~] = IterationCG(A, b, n(i), 1000);
    subplot(2, 2, i);
    plot(step1, err1, 'b', step2, err2, 'm', step3, err3, 'r', step4, err4, 'k');
    legend('Jacobi', 'GaussSeidel', 'SOR', 'CG');
    title(['Error Plot(n=' num2str(n(i)) ')']);
    xlabel('step');
    ylabel('error');
end


function [A, b] = CreateMatrix(n)
X = diag(rand(n, 1));
U = orth(rand(n));
A = U' * X * U;
b = randn(n, 1);
end
