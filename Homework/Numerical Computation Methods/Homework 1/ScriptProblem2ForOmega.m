addpath Functions;

n = [ 10 50 100 200 ];
table = zeros(11, 21);
for j = 1 : 4
    [A, b] = CreateMatrix(n(j));
    for i = 10 : 20
        table(i - 9, 1) = i / 10;
        [~, step, err, ok] = IterationSOR(A, b, n(j), 1000, i / 10);
        table(i - 9, j*5-3 : j*5+1) = err(1:5);
    end
end

f = figure;
t = uitable(f);
t.ColumnName = {'Omega', ...
    '1(n=10)','2(n=10)','3(n=10)','4(n=10)','5(n=10)', ...
    '1(n=50)','2(n=50)','3(n=50)','4(n=50)','5(n=50)', ...
    '1(n=100)','2(n=100)','3(n=100)','4(n=100)','5(n=100)', ...
    '1(n=200)','2(n=200)','3(n=200)','4(n=200)','5(n=200)' ...
};
t.ColumnEditable = true;
t.Data = table;
t.Position = [ 20 20 640 240 ];

function [A, b] = CreateMatrix(n)
X = diag(rand(n, 1));
U = orth(rand(n));
A = U' * X * U;
b = randn(n, 1);
end
