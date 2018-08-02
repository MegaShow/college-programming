addpath Problem4;

Fs = 100;            % Sampling frequency                    
T = 1 / Fs;          % Sampling period       
L = 1024;            % Length of signal
t = (0 : L-1) * T;   % Time vector

X = zeros(1, L);
for i = 1 : L / 2 - 1
    X = X + randi(100) * sin(2 * pi * i * t);
end

y0 = FastFourierTransform(X, L);
y1 = fft(X, L);

k = norm(y1) / norm(y0);
if abs(k - 1) < 10e-6
    disp(['e = ' num2str(abs(k - 1))]);
else
    disp('Fail FFT');
end

subplot(2, 2, 1);
plot(L * t(1:50), X(1:50));
title('Signal Corrupted');
xlabel('t (milliseconds)');
ylabel('X(t)');

subplot(2, 2, 3);
plot(L / 10 * t(1:L/2), y0(1:L/2));
title('Custom FFT');
xlabel('k');
ylabel('Y(t)');

subplot(2, 2, 4);
plot(L / 10 * t(1:L/2), y1(1:L/2));
title('Standard FFT');
xlabel('k');
ylabel('Y(t)');
