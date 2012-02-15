#include"../include/pricemodel.h"
#include<cmath>
#include<iostream>

using namespace std;
void printComplex(double complex c){
  cout<<"("<<creal(c)<<","<<cimag(c)<<")"<<endl;  
  }

int main(){
  VarianceGamma model(.12,-.14,.2,.1,0,1.0/12.0);
  double complex val;
  val = model.logCF(1,1); 
  printComplex(val);
   
  val = model.logCF(100,0);
  printComplex(val);
  
  val = model.logCF(exp(1),1);
  printComplex(val);
  return 0;
  }
