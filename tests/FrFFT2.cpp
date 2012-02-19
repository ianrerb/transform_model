/* This test checks that the accessability of the parameters for the FrFFT class */ 

#include"../include/transform.h"
#include<iostream>
#include<cmath>

using namespace std;

int main(){
  FrFFT test(8,1,.15,.01,true);
  GBM model(.3,.05,0,1);
  
  cout<<test.Prices(100,90,exp(-.05),model)[3].premium;
  return 0;
  }
