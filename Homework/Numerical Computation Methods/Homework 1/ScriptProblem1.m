addpath Functions;

% standard test
n = 3;
b = [ 6; 5; 1 ];
A = [ 1 1 1; 0 4 -1; 2 -2 1 ];
x = EliminationGaussian(A, b, n);
display(x);
x = EliminationColumn(A, b, n);
display(x);

% random test
n = [ 10 50 100 200 ];
t1 = zeros(1, 4);
t2 = zeros(1, 4);
for i = 1 : 4
    [A, b] = CreateMatrix(n(i));
    tic;
    EliminationGaussian(A, b, n(i));
    t1(i) = toc;
    tic;
    EliminationColumn(A, b, n(i));
    t2(i) = toc;
end
plot(n, t1, 'b', n, t2, 'm');
legend('Gaussian', 'Column')
title('Elimination Gaussian/Column Time Plot');
xlabel('n');
ylabel('time/s');

function [A, b] = CreateMatrix(n)
A = randn(n);
while ~all(all(A))
    A = randn(n);
end
b = randn(n, 1);
end
