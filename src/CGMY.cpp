#include"../include/pricemodel.h"
#include"../include/sp_gamma.h"
double complex CGMY::Omega_helper(double complex val) const {
  double complex A, B, C, D;
  A = cpow(M_param - val,Y_param);
  B = cpow(M_param,Y_param);
  C = cpow(G_param - val,Y_param);
  D = cpow(G_param, Y_param);
  return -C_param*sp_gamma(-Y_param)*(A-B+C-D);
  
  //return -C_param*sp_gamma(-Y_param)*(cpow(M_param-val,Y_param)-cpow(M_param,Y_param)+cpow(G_param+val,Y_param)-cpow(G,Y_param));
  }

double complex CGMY::logCF(const double &S, const double complex &u) const {
  double complex temp1, temp2;
  
  temp1 = cexp(I*u*(log(S)+(r-q+Omega_helper())*T));
  temp2 = cexp(-Omega_helper(I*u)*T);
  return temp1*temp2;
  
  }

double CGMY::Cumulant(unsigned int k) const {
  double omega = creal(Omega_helper());
  double chi = 8.0*C_param/(pow(G_param+M_param,2)-pow(G_param-M_param,2));

  switch(k){
    case 1 :
      return ((r+omega)*T + T*C_param*sp_gamma(1.0-Y_param)*(-pow(M_param,Y_param-1)+pow(G_param,Y_param-1)));
    
    case 2 :
      return (chi + T*C_param*sp_gamma(2.0-Y_param)*(pow(M_param,Y_param-2)+pow(G_param,Y_param-2)));

    case 4 :
      return (C_param*T*sp_gamma(4.0-Y_param)*(pow(M_param,Y_param-4)+pow(G_param,Y_param-4)));
    
    default :
      throw("Invalid Cumulant Option"); 
 
    }
  }
