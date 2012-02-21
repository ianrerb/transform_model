#include"../include/transform.h"
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

int main(){
  double Spot, Strike, rate, q, T, vol, lambda;
  Spot = 100;
  Strike = 90;
  rate = .05;
  q = 0.0;
  T = 1;
  vol = .3;
  lambda = 2.0*M_PI/(64.0*.15);

  GBM model(vol,rate,q,T);
  FrFFT Engine(64,0,.15,lambda);

  vector<double> alpha; 
  alpha.push_back(.01); 
  alpha.push_back(.5); 
  alpha.push_back(1); 
  alpha.push_back(1.5); 
  alpha.push_back(2); 
  alpha.push_back(5); 
  alpha.push_back(10); 

  for(vector<double>::iterator it = alpha.begin(); it!=alpha.end(); it++){
	  Engine.Alpha(*it);
	  cout<<Engine.Prices(Spot,Strike,exp(-rate*T),model)[32].premium<<endl;
    }
  return 0;
  }
