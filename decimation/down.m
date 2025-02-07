close all

[x,fs] = audioread("speech_1.wav");

figure()
specgram(x)
title("x");

y = conv(x,coef);

figure()
specgram(y)
title("y");

z = downsample(y,4);

figure()
specgram(z)
title("z");

audiowrite("4kHz.wav",z,4000);


k = downsample(x,4);

audiowrite("4kHz_no_filter.wav",k,4000);

m = decimate(x,4);
audiowrite("4kHz._m.wav",z,4000);

resample(x,4000,16000);
