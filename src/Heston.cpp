#include "../include/pricemodel.h"
#include<iostream>

double complex Heston::logCF(const double &S, const double complex &u) const {
  double complex temp1,temp2,temp3, v1, v2,v3, gamma, result;
 
  v1 = kappa-I*rho*sigma*u;
  v2 = u*u+I*u;
  v3 = kappa*theta/(sigma*sigma);
  gamma = sigma*sigma*v2+v1*v1;
  gamma = cpow(gamma,.5);
  
  temp1 = cexp(I*u*(log(S)+(r-q)*T)+v3*T*v1);
  temp2 = ccosh(gamma*T/2.0)+v1/gamma*csinh(gamma*T/2.0);
  
  result = temp1/cpow(temp2,2.0*v3);

  temp1 = v0*v2; //v0 is class variable defined in .h file
  temp2 = gamma/ctanh(gamma*T/2.0)+v1;
  temp3 = cexp(-temp1/temp2);

  result = result*temp3;

  return result;
  
  }

double Heston::Cumulant(unsigned int k) const {
  switch(k){
    case 1 :
      return ( r*T + (1.0 - exp(-kappa*T))*(theta-v0)/(2.0*kappa) - .5*theta*T );
    
    case 2 :
      return(1.0/(8.0*pow(kappa,3))*
	  (
	  sigma*T*kappa*exp(-kappa*T)*(v0-theta)*(8.0*kappa*rho-4.0*sigma)
	  +kappa*rho*sigma*(1.0-exp(-kappa*T))*(16.0*theta - 8*v0)
	  +2.0*theta*kappa*T*(-4.0*kappa*rho*sigma + pow(sigma,2) + 4.0*pow(kappa,2))
	  +sigma*sigma*((theta-2.0*v0)*exp(-2*kappa*T)+theta*(6.0*exp(-kappa*T)-7.0)+2*v0)
	  +8.0*kappa*kappa*(v0-theta)*(1.0-exp(-kappa*T))
	  )
      );
      
    case 4 :
      return 0;
    
    default :
      throw("Invalid Cumulant Option"); 
    }
  }
