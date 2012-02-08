/* Testing with Values in Computational Methods in Finance Chapter 2, page 42 (section2.1.5)  */ 

#include"../include/pricemodels.h"
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

int main(){
  double Spot = 100;
  double Strike = 90;
  GBM_model gbm(.3,.05,0,1);
  
  vector<double> alpha;
  alpha.push_back(0.01);  
  alpha.push_back(0.5);  
  alpha.push_back(1);  
  alpha.push_back(1.5);  
  alpha.push_back(2);  
  alpha.push_back(5);  
  alpha.push_back(10);  
 
  vector<double> eta;
  eta.push_back(0.15); 
  eta.push_back(0.1);
  eta.push_back(0.05); 

  vector<unsigned int> N;
  N.push_back(pow(2,6));
  N.push_back(pow(2,8));
  N.push_back(pow(2,10));
 
  for(vector<double>::iterator a_iter=alpha.begin(); a_iter!= alpha.end(); a_iter++){
    for(vector<double>::iterator e_iter=eta.begin(); e_iter!= eta.end(); e_iter++){
      for(vector<unsigned int>::iterator N_iter = N.begin(); N_iter!=N.end(); N_iter++){
	vector<Option> results =gbm.PutPrices(Spot,Strike,exp(-.05),*N_iter,*a_iter,*e_iter);
	cout<<results[*N_iter/2].premium<<" ";
	} 
      }
      cout<<endl;
    }
  
  return 0;
  }
