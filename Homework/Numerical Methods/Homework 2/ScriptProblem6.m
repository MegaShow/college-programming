addpath Problem6;

x0 = 0;
y0 = 1;
h = 0.1;

[x1, y1] = ForwardEuler(x0, y0, h);
[x2, y2] = BackwardEuler(x0, y0, h);
[x3, y3] = Trapezoidal(x0, y0, h);
[x4, y4] = ImprovedEuler(x0, y0, h);
for k = 0 : 3
    for i = 1 : 11
        if k == 0; disp(['ForwardEuler: (' num2str(x1(i)) ', ' num2str(y1(i)) ')']); end
        if k == 1; disp(['BackwardEuler: (' num2str(x2(i)) ', ' num2str(y2(i)) ')']); end
        if k == 2; disp(['Trapezoidal: (' num2str(x3(i)) ', ' num2str(y3(i)) ')']); end
        if k == 3; disp(['ImprovedEuler: (' num2str(x4(i)) ', ' num2str(y4(i)) ')']); end
    end
    disp(' ');
end


plot(x1, y1, 'b', x2, y2, 'm', x3, y3, 'r', x4, y4, 'k');
legend('ForwardEuler', 'BackwardEuler', 'Trapezoidal', 'ImprovedEuler');
title("Initial Value Problem");
xlabel('x');
ylabel('y');
