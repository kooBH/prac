https://kr.mathworks.com/help/stats/iwishrnd.html    
## iwishrnd  
Inverse Wishart random numbers  
## Syntax  
```matlab
W = iwishrnd(Tau,df)
W = iwishrnd(Tau,df,DI)
[W,DI] = iwishrnd(Tau,df)
```
Description  
W = iwishrnd(Tau,df) generates a random matrix W from the inverse Wishart distribution with parameters Tau and df. The inverse of W has the Wishart distribution with covariance matrix Sigma = inv(Tau) and with df degrees of freedom. Tau is a symmetric and positive definite matrix.
  
W = iwishrnd(Tau,df,DI) expects DI to be the transpose of the inverse of the Cholesky factor of Tau, so that DI'*DI = inv(Tau), where inv is the MATLAB® inverse function. DI is lower-triangular and the same size as Tau. If you call iwishrnd multiple times using the same value of Tau, it is more efficient to supply DI instead of computing it each time.
  
\[W,DI\] = iwishrnd(Tau,df) returns DI so you can use it as an input in future calls to iwishrnd.
  
Note that different sources use different parametrizations for the inverse Wishart distribution. This function defines the parameter tau so that the mean of the output matrix is Tau/(df-d-1) where d is the dimension of Tau.