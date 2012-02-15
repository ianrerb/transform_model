#include "../include/pricemodel.h"

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


