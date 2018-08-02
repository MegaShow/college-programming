addpath Problem5;

n = [ 5 9 17 33 ];

for i = 1 : 4
    T = TrapezoidalIntegration(n(i));
    disp(['TI: n=>' num2str(n(i)) ' result=>' num2str(T, '%.15f')]);
end
disp(' ');
for i = 1 : 4
    T = SimpsonIntegration(n(i));
    disp(['SI: n=>' num2str(n(i)) ' result=>' num2str(T, '%.15f')]);
end
