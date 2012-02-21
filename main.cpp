#include<iostream>
#include<complex.h>
#include<math.h>
#include<vector>
#include"include/transform.h"
#include<cstdio>
using namespace std;

int main(){
  
  GBM model(.3,.05,0,1);
  COS PriceEngine(16,-.25,.35);
  PriceEngine.ContractType(call);
  PriceEngine.BestBounds(model);
  cout<<PriceEngine.LowerBound()<<endl;
  
  cout<<PriceEngine.Price(100,90,exp(-.05),model)<<endl;

  return 0;
  }

