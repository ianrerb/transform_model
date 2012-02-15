#include"../include/transform.h"
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

int main(){
  double Spot, Strike, rate, q, T, sigma, v0, kappa, theta, rho ;
  Spot = 100;
  Strike = 90;
  kappa = 2;
  theta = .04;
  sigma = .5;
  v0=.04;
  rho=-0.7;
  rate = .03;
  q = 0.0;
  T=.5;

  Heston model(kappa, theta, sigma, v0, rho, rate,q,T);
  FFT Engine(0,0,0);

  vector<double> alpha, eta;
  vector<unsigned int> n; 
  
  alpha.push_back(.01);
  alpha.push_back(.5);
  alpha.push_back(1);
  alpha.push_back(1.5);
  alpha.push_back(2);
  alpha.push_back(5);
  alpha.push_back(10);

  eta.push_back(.15);
  eta.push_back(.1);
  eta.push_back(.05);
  
  n.push_back(64);
  n.push_back(256);
  n.push_back(1024);

  for(vector<double>::iterator ait = alpha.begin(); ait!=alpha.end(); ait++){
    for(vector<double>::iterator eit = eta.begin(); eit!= eta.end(); eit++){
      for(vector<unsigned int>::iterator nit = n.begin(); nit!=n.end(); nit++){
	  Engine.setN(*nit);
	  Engine.setAlpha(*ait);
	  Engine.setEta(*eit);
	  cout<<Engine.Prices(Spot,Strike,exp(-rate*T),model)[*nit/2].premium<<"  ";
	}
      }
    cout<<endl;
    }
  return 0;
  }
