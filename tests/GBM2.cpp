#include"../include/pricemodel.h"
#include<cmath>
#include<iostream>

using namespace std;
void printComplex(double complex c){
  cout<<"("<<creal(c)<<","<<cimag(c)<<")"<<endl;  
  }

int main(){
  GBM model(.3,.05,0,1);
  double complex val;
  val = model.logCF(100,.15-2*I); //should give real val of ~.6065
  printComplex(val);
   
  return 0;
  }
