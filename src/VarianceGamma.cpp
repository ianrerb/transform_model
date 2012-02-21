#include"../include/pricemodel.h"
#include<iostream>

double complex VarianceGamma::logCF(const double &S, const double complex &u) const{
  double complex temp1, temp2;
  temp1 = I*u*(log(S)+(r-q+log(1.0-sigma*sigma*v/2.0-theta*v)/v)*T);
  temp1 = cexp(temp1);
  
  temp2 = 1.0-I*u*theta*v + cpow(sigma*u,2)*v/2.0;
  temp2 = 1.0/temp2;
  temp2 = cpow(temp2,T/v);
  return temp1*temp2; 
  }

double VarianceGamma::Cumulant(unsigned int k) const{
  switch(k){
    case 1 :
      return ((r+theta)*T);
    
    case 2 :
      return ((sigma*sigma + v*theta*theta)*T);

    case 4 :
      return (3.0*(pow(sigma,4)*v + 2.0*pow(theta*v,3)*theta+4.0*pow(sigma*theta*v,2))*T);

    default :
      throw("Invalid Cumulant Option"); 
    }
  }
