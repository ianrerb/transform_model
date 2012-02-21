/* This test checks that the accessability of the parameters for the FrFFT class */ 

#include"../include/transform.h"
#include<iostream>

using namespace std;

void printParams(FrFFT &model){
  cout<<model.N()<<"\t"<<model.Alpha()<<"\t"<<model.Eta()<<"\t"<<model.Lambda()<<"\t"<<model.Gamma()<<endl;
  };

int main(){
  FrFFT test(0,0,0,0);
  printParams(test);
  test.Alpha(1);
  test.N(64);
  test.Eta(.15);
  test.Lambda(.01);
  printParams(test);
  return 0;
  }
