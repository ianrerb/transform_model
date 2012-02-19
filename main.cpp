#include<iostream>
#include<complex.h>
#include<math.h>
#include<vector>
#include"include/transform.h"
#include<cstdio>
using namespace std;

int main(){
  // Constants
  vector<Option> output;
  unsigned int N = 2048;
  
  GBM model(.3,.05,0,1);
  FrFFT PriceEngine(N,1,.15,.5/static_cast<double>(N));

  output = PriceEngine.Prices(100,90,exp(-.05),model);
  for(int i =1000; i!=output.size();i++)
    cout<<output[i].strike<<" : "<<output[i].premium<<endl; 
  return 0;
  }

