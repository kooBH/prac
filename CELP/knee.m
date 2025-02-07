


close all
clear


fs = 16000;
T = 3;
x = zeros(fs*T,1);
unit = 0.01*fs; 

for i = 1:fs*3
    %x(i) = 2*mod(10*i,fs)/fs-1;

    i2 = mod(i,unit);

    if i2 > unit/2
        x(i) = 1-2*(20*(i2-unit/2)/fs);
        x(i)=0;
    else
        x(i) = (20*i2/fs)-0.5;
    end
end
figure
plot(x)
sound(x,fs)