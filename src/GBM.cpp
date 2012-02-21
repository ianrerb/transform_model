#include "../include/pricemodel.h"

double complex GBM::logCF(const double &S, const double complex &u) const{
  double complex retval = I*(log(S) + (r - q - cpow(sigma,2.0)/2.0)*T)*u - cpow(sigma*u,2.0)*T/2.0;
  return cexp(retval);
  }

double GBM::Cumulant(unsigned int k) const {
  switch(k){
    case 1 :
      return ((r-q)*T);
    
    case 2 :
      return (sigma*sigma*T);

    case 4 :
      return 0;
    
    default :
      throw("Invalid Cumulant Option"); 
    }
  } 
