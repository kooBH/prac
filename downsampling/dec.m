close all

f = fir1(512,0.5);

[x,fs] = audioread("speech_1.wav");

figure()
title("x");
specgram(x);
caxis([-100 20])

y = conv(x,f);
figure()
title("y")
specgram(y);
caxis([-100 20])

fileID = fopen('fir_lowpass_filter_n_512_r_0p5.bin','w');
fwrite(fileID,f,'float64');
fclose(fileID);


