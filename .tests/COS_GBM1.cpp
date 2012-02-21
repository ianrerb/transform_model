#include "../include/transform.h"

using namespace std;

int main(){
  GBM model(.25,.01,0,.1);
  COS Engine(16);
  Engine.ContractType(call);
  Engine.BestBounds(model);
  double Spot = 100;
  double C = exp(-.001);

  vector<unsigned int> n;
  n.push_back(16);
  n.push_back(64);
  n.push_back(256);

  vector<double> strikes;
  strikes.push_back(80);
  strikes.push_back(100);
  strikes.push_back(120);
  
  for(vector<double>::iterator it1 = strikes.begin(); it1!= strikes.end(); it1++){
    for(vector<unsigned int>::iterator it2 = n.begin(); it2!= n.end(); it2++){
      Engine.N(*it2);
      cout<<Engine.Price(Spot,*it1,C,model)<<endl;
      }
    cout<<endl;
  }
  
  return 0;
  }
