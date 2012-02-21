#include "../include/transform.h"

using namespace std;

int main(){
  GBM model(.25,.01,0,.1);
  COS Engine(16);
  cout<<Engine.LowerBound()<<" "<<Engine.UpperBound()<<endl;

  Engine.BestBounds(model);
  cout<<Engine.LowerBound()<<" "<<Engine.UpperBound()<<endl;
  cout<<Engine.isValid()<<endl;
 
  
  return 0;
  }
