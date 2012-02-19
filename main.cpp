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
  
  GBM model(.3,.05,0,1);
  FrFFT PriceEngine(pow(2,6),1,.15,.5/pow(2,6));

  output = PriceEngine.Prices(100,100,exp(-.05),model);
  for(int i =0; i!=output.size();i++)
    cout<<output[i].strike<<" : "<<output[i].premium<<endl; 
  return 0;
  }

