addpath Functions;

% Directed graph (each unordered pair of nodes is saved once): soc-Epinions1.txt 
% Directed Epinions social network
% Nodes: 75879 Edges: 508837
% FromNodeId	ToNodeId

file = fopen('soc-Epinions1.txt', 'r', 'n','UTF-8');
cell = textscan(file, '%d%d');
fclose(file);

m = cell2mat(cell)' + 1;
n = double(max(m(1, length(m(1, :))), m(2, length(m(2, :)))));
A = sparse(double(m(1,:)), double(m(2,:)), 1 / n, n, n);
tic;
B = PageRank(A, 0.15);
t = toc;
csvwrite('out.txt', B);
display(t);
