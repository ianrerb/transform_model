#include<iostream>
#include<complex.h>
#include<math.h>
#include<vector>
#include"include/pricemodels.h"
#include<cstdio>
using namespace std;

int main(){
  // Constants
  unsigned int N = pow(2,6);
  double alpha = 1.5;
  double eta = .1;
  const double Spot = 1300;
  const double T = 0.25;
  const double r = 0.0025;
  const double q = .0125;
  vector<double> output;

  GBM_model gbm(.35,r,q,T,N,alpha,eta);
  output = gbm.PutPrices(Spot,exp(-r*T));
  for(int i =0; i!=output.size();i++)
    cout<<output[i]<<endl; 
  return 0;
  }

