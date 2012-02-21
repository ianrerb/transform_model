VarianceGammaCF<-function(S,u,sigma,theta,v,r,q,t){
  i=complex(real=0,imaginary=1);
  temp1 = exp(i*u*(log(S)+(r-q+1/v*log(1-sigma^2*v/2-theta*v))*t));
  print(temp1)
  temp2 = (1/(1-i*u*theta*v + sigma^2*u^2*v/2))^(t/v);
  print(temp2)
  result = temp1*temp2;
  return(result);
  }
