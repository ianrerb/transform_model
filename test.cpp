#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

  ouble Spot;
  vector<double> Strikes;

  while(infile>>word){
    if(word=="<CONTRACT>"){ InitializeContract(infile, Spot, Strikes); };
    if(word=="<MODEL>"){ InitializeModel()}
    cout<<word<<endl;
    }

  cout<<Spot<<endl;
  for(int i =0; i!=Strikes.size(); i++)
    cout<<Strikes[i]<<endl;
  return 0;
  }
