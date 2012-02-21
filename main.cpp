#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include"include/transform.h"

using namespace std;

void InitializeContract(ifstream &infile, OptionType &Type, double &Spot, vector<double> &Strikes);
void InitializeEngine(ifstream &infile, string &EngineType, vector<unsigned int> &size, vector<double> &alpha, vector<double> &eta);
void InitializeModel(ifstream &infile, string &ModelType, double &sigma, double &rate, double &div_rate, double &T);

void RunFFT(FFT &engine, 
	     pricemodel &model, 
	     double Spot,
	     double C,
	     vector<double> &Strikes,
	     vector<unsigned int> &size,
	     vector<double> &alpha,
	     vector<double> &eta, 
	     string file);
 
//begin main
int main(int argv, char* argc[]){
  
  //check arguments to main 
  if(argv < 2){ throw("Invalid Number of Arguments to Pricing Engine."); }
  string output = "results/";
  output.append(argc[1]);
  output.append(".out");

  //initialize variables
  double Spot, T, rate, div_rate, sigma; 
  vector<double> Strikes, alpha, eta, lambda; 
  vector<unsigned int> size;
  string ModelType, EngineType;
  OptionType ContractType;
  
  //initialize fstream to read .trial files
  ifstream infile;
  infile.open(argc[1]);
  string word;
  
  while(infile>>word){
    if(word=="<CONTRACT>"){ InitializeContract(infile, ContractType, Spot, Strikes); }
    if(word=="<ENGINE>"){ InitializeEngine(infile, EngineType, size, alpha, eta); }
    if(word=="<MODEL>"){ InitializeModel(infile, ModelType, sigma, rate, div_rate, T); } 
    cout<<word<<endl;
    }
  
  if(EngineType == "FFT"){
    FFT Engine;
    if(ModelType =="GBM"){
      GBM Model(sigma,rate,div_rate,T);
      RunFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,output);
      }
    }
  return 0;
  } //<-- End Main

void InitializeModel(ifstream &infile, string &ModelType, double &sigma, double &rate, double &div_rate, double &T){
  string word;
  double val;
  while(infile>>word){
    if(word=="name:"){infile >> ModelType; }
    else if(word=="sigma:"){ infile >> sigma; } 
    else if(word=="rate:"){ infile>>rate; }
    else if(word=="dividend:"){ infile >> div_rate; }
    else if(word=="T:"){ infile >> T; }
    else if(word=="</MODEL>"){ return; } else{cout<<"Error in Model Configuration"<<endl; throw("Invalid Input."); }
    }
  }

void InitializeEngine(ifstream &infile, string &EngineType, vector<unsigned int> &size, vector<double> &alpha, vector<double> &eta){
  string word;
  unsigned int ival;
  double dval; 
  while(infile>>word){
    if(word=="name:"){infile >> EngineType; }
    else if(word=="N:"){ infile>>ival; size.push_back(ival); }
    else if(word=="alpha:"){ infile>>dval; alpha.push_back(dval); }
    else if(word=="eta:"){ infile>>dval; eta.push_back(dval); }
    else if(word=="</ENGINE>"){ return; } else {cout<<"Error in engine configuration while processing: "<<word; throw("Invalid Input."); }
    }
  }

void InitializeContract(ifstream &infile, OptionType &Type, double &Spot, vector<double> &Strikes){
  string word;
  double val; 
  while(infile>>word){
    if(word=="Spot:"){ infile>>Spot; }	
    else if(word=="Type:"){
      infile>>word; 
      if(word=="call"){Type = call;} 
      else if(word =="put"){Type = put; } else {cout<<"Error in Contract Configuration"<<endl; throw("Invalid Option Type.");}
      }
    else if(word=="Strike:"){infile>>val; Strikes.push_back(val); } 
    else if(word=="</CONTRACT>"){ return; } 
    else {throw("Invalid Input.");}
    }
  }
  
void RunFFT(FFT &engine, 
	     pricemodel &model, 
	     double Spot,
	     double C,
	     vector<double> &Strikes, 
	     vector<unsigned int> &size, 
	     vector<double> &alpha, 
	     vector<double> &eta, 
	     string file){
  cout<<"Running FFT pricing engine. Results printing to file: "<<file<<endl;
  ofstream outfile(file.c_str());

  
  for(vector<double>::iterator strike_it = Strikes.begin(); strike_it!=Strikes.end();strike_it++){
    outfile<<"STRIKE: "<<*strike_it<<"\n Eta:\t";
    
    for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++){
      for(vector<double>::iterator eta_it = eta.begin(); eta_it!= eta.end(); eta_it++){
	  outfile<<*eta_it<<"\t";
	}
      }

    outfile<<"\n Alpha:\t";
    
    for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++){
      for(vector<double>::iterator eta_it = eta.begin(); eta_it!= eta.end(); eta_it++){
	  outfile<<*alpha_it<<"\t";
	}
      }
   
    outfile<<endl;
     
    for(vector<unsigned int>::iterator size_it = size.begin(); size_it != size.end(); size_it++){
      outfile<<*size_it<<":\t";
      for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++){
	for(vector<double>::iterator eta_it = eta.begin(); eta_it!= eta.end(); eta_it++){
	  engine.N(*size_it);
	  engine.Alpha(*alpha_it);
	  engine.Eta(*eta_it);
	  outfile<<engine.Price(Spot,*strike_it,C,model)<<"\t";
	}
      }
    outfile<<endl;
    }
    outfile<<endl<<endl;
  }
  
  outfile.close();
  outfile.clear();
}
