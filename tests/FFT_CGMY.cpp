#include"../include/transform.h"
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

int main(){
  double Spot, Strike, rate, q, T, C, G, M, Y ;
  Spot = 100;
  Strike = 90;
  C=1.2;
  G=6.5;
  M=8.5;
  Y=0.05;
  rate = .1;
  q = 0.0;
  T=1.0/12.0;

  CGMY model(C,G,M,Y,rate,q,T);
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
  
  n.push_back(256);
  n.push_back(1024);
  n.push_back(4096);

  for(vector<double>::iterator ait = alpha.begin(); ait!=alpha.end(); ait++){
    for(vector<double>::iterator eit = eta.begin(); eit!= eta.end(); eit++){
      for(vector<unsigned int>::iterator nit = n.begin(); nit!=n.end(); nit++){
	  Engine.N(*nit);
	  Engine.Alpha(*ait);
	  Engine.Eta(*eit);
	  cout<<Engine.Prices(Spot,Strike,exp(-rate*T),model)[*nit/2].premium<<"  ";
	}
      }
    cout<<endl;
    }
  return 0;
  }
