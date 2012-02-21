
I = complex(real=0,imaginary=1);
source("GBM.R")  


FrFFT<-function(N,alpha,eta,lambda,Spot,Strike,sigma,r,q,t){
  gamma = eta*lambda/(2*pi);
  X<-array(0,N);
  results = X;
  Y<-array(0,N*2);
  Z=Y; 

  for(i in 1:N){
    nu = eta*(i-1);
    val1= eta*exp(-r*t)
    val2 = (alpha+I*nu)*(alpha+1+I*nu)
    val3 = -I*(log(Strike)-lambda*N/2)*nu
    val4 = GBM_CF(Spot,nu-(alpha+1)*I,sigma,r,q,t)
    X[i]=val1/val2*exp(val3)*val4;
    }
    X[1]=X[1]/2
  
  for(i in 1:N){
    Y[i]=exp(-I*gamma*pi*(i-1)^2)*X[i]
    } 
   
  for(i in 1:N){
    Z[i] = exp(I*gamma*pi*(i-1)^2);
    Z[N*2-i+1] = Z[i];
    } 
  print('<== RAW X VECTOR ==>')
  print(X)
  print('<== RAW Y VECTOR ==>')
  print(Y)
  print('<== RAW Z VECTOR ==>')
  print(Z)
  
  Y = fft(Y);
  Z = fft(Z);
  print('<== TRANSFORMED Y VECTOR ==>')
  print(Y)
  print('<== TRANSFORMED Z VECTOR ==>')
  print(Z)

  Xi = Y*Z;  
  print('<== RAW Xi VECTOR ==>')
  print(Xi) 
  Xi = fft(Xi,inverse=T)/(2*N)
  print('<== TRANSFORMED Xi VECTOR ==>')
  print(Xi)

  for(i in 1:N){
    results[i]=exp(-alpha*(log(Strike)-(N/2 - i)*lambda))*Re(exp(-I*pi*gamma)*Xi[i])/pi
    }
  return(results)
  }
