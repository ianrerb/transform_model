#ifndef SP_GAMMA_H
#define SP_GAMMA_H

#include <cmath>
#include <cstddef>

double sp_gamma(double z)
{
  const int a = 12;
  static double c_space[12];
  static double *c = NULL;
  int k;
  double accm;
 
  if ( c == NULL ) {
    double k1_factrl = 1.0; /* (k - 1)!*(-1)^k with 0!==1*/
    c = c_space;
    c[0] = sqrt(2.0*M_PI);
    for(k=1; k < a; k++) {
      c[k] = exp(a-k) * pow(a-k, k-0.5) / k1_factrl;
	  k1_factrl *= -k;
    }
  }
  accm = c[0];
  for(k=1; k < a; k++) {
    accm += c[k] / ( z + k );
  }
  accm *= exp(-(z+a)) * pow(z+a, z+0.5); /* Gamma(z+1) */
  return accm/z;
}

#endif //SP_GAMMA_H
