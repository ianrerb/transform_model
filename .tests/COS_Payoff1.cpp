#include "../include/transform.h"
#include <iostream>

using namespace std;

int main(){
  COS_Payoff func(call,100);

  cout<<func(1,-5,5);
  
  return 0;
  }
