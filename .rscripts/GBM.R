GBM_CF<-function(S,u,sigma,r,q,t){
  I = complex(real=0, imaginary=1);
  val = I*(log(S)+(r-q-sigma^2/2)*t)*u - .5*sigma^2*u^2*t;
  return(exp(val));
  }
