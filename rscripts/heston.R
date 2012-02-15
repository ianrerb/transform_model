
HestonCF<-function(S,u,r,q,t,k,th,rho,sigma,v0){
  i = complex(real=0, imaginary=1);
  
  gamma = sqrt(sigma^2*(u^2+i*u)+(k-i*rho*sigma*u)^2);
  v1 = k-i*rho*sigma*u;
  v2 = u*u+i*u;
  v3 = k*th/sigma^2;

  result = exp(i*u*(log(S)+(r-q)*t)+v3*t*v1);
  
  temp = cosh(gamma*t/2)+v1/gamma*sinh(gamma*t/2);
  
  result = result/temp^(2*v3); 
  temp = v0*v2;
  temp2 = gamma/tanh(gamma*t/2)+v1;
  temp3 = exp(-temp/temp2);
  result = result*exp(-(u^2*v0+i*u*v0)/(gamma*cosh(gamma*t/2)/sinh(gamma*t/2)+k-i*rho*sigma*u));
  return(result);
}
