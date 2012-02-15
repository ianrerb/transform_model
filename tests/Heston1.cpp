#include"../include/pricemodel.h"
#include<cmath>
#include<iostream>

using namespace std;
void printComplex(double complex c){
  cout<<"("<<creal(c)<<","<<cimag(c)<<")"<<endl;  
  }

int main(){
  Heston model(2.0,.04,.5,.04,-0.7,.03,0.0,.5);
  double complex val;
  val = model.logCF(1,1); 
  printComplex(val);
   
  val = model.logCF(100,0);
  printComplex(val);
  
  val = model.logCF(exp(1),1); 
  printComplex(val);
  return 0;
  }
