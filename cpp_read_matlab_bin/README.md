X.bin is 575x257x6 complex double of MATLAB    
```MATLAB
	fid = fopen('X.bin','w');
	fwrite(fid,X);
	fclose(fid);
```

-> Read as C++ double[6][512+2]  

