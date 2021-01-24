a = rand(5,1)+1i*rand(5,1);
R = a*a';
b = 0.5*(R'+R);
W = iwishrnd(R,9);
W