clc; clear; close all;

fs = 16000;

t = linspace(0,1,256);

x1 = sin(2*pi*fs*t);
figure;plot(x1);title('x1');
figure;specgram(x1);title('x1');caxis([-80 20])

x2 = zeros(1,256);
x2(1:160) = x1(1:160);

figure;plot(x2);title('x2');
figure;specgram(x2);title('x2');caxis([-80 20])