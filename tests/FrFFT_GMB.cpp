#include"../include/transform.h"
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

int main(){
  double Spot, Strike, rate, q, T, vol;
  Spot = 100;
  rate = .01;
  q = 0.0;
  T = .1;
  vol = .25;

  GBM model(vol,rate,q,T);
  FrFFT Engine(0,1.5,.15,.01);

  vector<unsigned int> n; 
  vector<double> strikes; 
  
  strikes.push_back(80);
  strikes.push_back(100);
  strikes.push_back(120);

  n.push_back(16);
  n.push_back(64);
  n.push_back(256);

  for(vector<double>::iterator sit = strikes.begin(); sit!=strikes.end(); sit++){
    for(vector<unsigned int>::iterator nit = n.begin(); nit!=n.end(); nit++){
	  Engine.N(*nit);
	  cout<<Engine.Prices(Spot,*sit,exp(-rate*T),model)[*nit/2].premium<<"  ";
      }
    cout<<endl;
    }
  return 0;
  }
