#include"../include/pricemodels.h"
#include<cmath>
#include<iostream>

using namespace std;
void printComplex(double complex c){
  cout<<"("<<creal(c)<<","<<cimag(c)<<")"<<endl;  
  }

int main(){
  GBM_model gbm(1,.5,0,1);
  double complex val;
  val = gbm.logCF(1,1); //should give real val of ~.6065
  printComplex(val);
   
  val = gbm.logCF(100,0); //should give real val of 1
  printComplex(val);
  
  val = gbm.logCF(exp(1),1); //should give ~.3277 + .5104i
  printComplex(val);
  return 0;
  }
