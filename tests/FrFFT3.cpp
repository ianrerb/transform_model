/* This test checks that the accessability of the parameters for the FrFFT class */ 

#include"../include/transform.h"
#include<iostream>
#include<cmath>

using namespace std;

int main(){
  FrFFT test(64,1,.15,.01,true);
  GBM model(.25,.05,0,1);

  test.Prices(100,100,exp(-.05),model);
  return 0;
  }
