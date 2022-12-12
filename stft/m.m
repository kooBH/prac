close all;
clear;

path = "../data/wav/999.wav";

[x,fs ] = audioread(path);

fftSize = 512;
nFreq = fftSize/2+1;
nOverlap = 3*fftSize/4;
nShift = fftSize-nOverlap;
win = hanning(fftSize,'periodic');
win = win./sqrt(sum(win.^2)/nShift);

nFrame = fix((length(x)+fftSize)/nShift) - 2;

X = zeros(nFrame, nFreq, 1);
X = stft(x, fftSize, win, nOverlap, fs); % [ frame freq mic ]

L1 = load("librosa_stft_1.mat").data;
L2 = load("librosa_stft_2.mat").data;
L3 = load("librosa_stft_3.mat").data;
L4 = load("librosa_stft_4.mat").data;