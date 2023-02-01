# MATLAB data to cpp  

+ NOTE : MATLAB matrix has column-first memory structure.    

ex) 
```MATLAB
x = rand(3,4);
```
=>  
```
    0.0975    0.9575    0.9706    0.8003
    0.2785    0.9649    0.9572    0.1419
    0.5469    0.1576    0.4854    0.4218
```
order in memory is 

``` 
0.0975 0.2785 0.5469 0.9575 0.9649 0.1576 0.9706 0.9572 0.4854 0.8003 0.1419 0.4218
```
