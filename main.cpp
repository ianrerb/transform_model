#include<iostream>
#include<fftw3.h>
#include<cmath>
#include<vector>

using namespace std;

void resetStrikes(vector<double> &);

int main(){

  // Constants
  const double Spot = 1300;
  const double T = 0.25;
  const double r = 0.0025;
  const double q = .0125;
  vector<double> K; 
  resetStrikes(K);
  
  for(int i = 0; i!=K.size(); i++)
    cout<<K[i]<<endl;
  return 0;
  }

void resetStrikes(vector<double> &K){
  K.empty();
  for(int val = 1000; val <= 1300; val+=50)
    K.push_back(static_cast<double>(val));
  };
