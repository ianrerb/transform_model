#include "../include/pricemodel.h"

double complex Heston::logCF(const double &S, const double complex &u) const {
  double complex temp1,temp2,temp3, v1, v2, gamma, result;
  
  v1 = kappa-I*rho*sigma*u;
  v2 = u*u+I*u;

  gamma = sigma*sigma*v2+v1*v1;
  gamma = cpow(gamma,.5);
  
  temp1 = I*u*log(S);
  temp1 += I*(r-q)*T*u;
  temp1 += (kappa*theta*T*v1)/(sigma*sigma);
  temp1 = cexp(temp1);
  
  temp2 = 2.0*kappa*theta/(sigma*sigma);
  temp3 = ccosh(gamma*T/2.0)+v1/gamma*csinh(gamma*T/2.0);
  result = temp1/cpow(temp3,temp2);

  temp1 = v0*v2; //v0 is class variable defined in .h file
  temp2 = gamma*ccosh(gamma*T/2.0)/csinh(gamma*T/2.0)+v1;
  temp3 = cexp(-temp1/temp2);

  result = result*temp3;

  return result;
  
  }


