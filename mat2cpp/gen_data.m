

x = rand(3,4);

fileID = fopen('3_by_4_double.bin','w');
fwrite(fileID,x,'double');
fclose(fileID);

disp(x);