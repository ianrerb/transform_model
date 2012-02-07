#include<iostream>
#include<complex.h>
#include<math.h>
#include<vector>
#include"pricemodels.h"

using namespace std;

void resetStrikes(vector<double> &);

int main(){
  // Constants
  unsigned int N = pow(2,6);
  double alpha = 1.5;
  double eta = .1;
  const double Spot = 1300;
  const double T = 0.25;
  const double r = 0.0025;
  const double q = .0125;
  vector<double> K; 
  resetStrikes(K);
 
  GBM_model gbm(.35,r,q,T,N,alpha,eta);
  double complex val = gbm.logCF(100,1);
  
  cout<<creal(val)<<"\t"<<cimag(val)<<endl;
  return 0;
  }

void resetStrikes(vector<double> &K){
  K.empty();
  for(int val = 1000; val <= 1300; val+=50)
    K.push_back(static_cast<double>(val));
  };
