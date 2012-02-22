#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include"include/transform.h"

using namespace std;

struct bound{double a; double b;};

void InitializeContract(ifstream &infile, OptionType &ContractType, double &Spot, vector<double> &Strikes);
void InitializeEngine(ifstream &infile, string &EngineType, vector<unsigned int> &size, vector<double> &alpha, double &eta, double &lambda, vector<bound> &bounds);
void InitializeModel(ifstream &infile, string &ModelType, double &nu, double &sigma, double &kappa, double &theta, double &rho, double &init_vol, double &C, double &G, double &M, double &Y, double &rate, double &div_rate, double &T);

void RunFFT(FFT &engine, 
	     pricemodel &model, 
	     double Spot,
	     double C,
	     vector<double> &Strikes,
	     vector<unsigned int> &size,
	     vector<double> &alpha,
	     double eta, 
	     string file);
 
void RunFrFFT(FrFFT &engine, 
	     pricemodel &model, 
	     double Spot,
	     double C,
	     vector<double> &Strikes,
	     vector<unsigned int> &size,
	     vector<double> &alpha,
	     double eta, 
	     double lambda,
	     string file);
 
void RunCOS(COS &engine, 
	     pricemodel &model, 
	     double Spot,
	     OptionType ContractType,
	     double C,
	     vector<double> &Strikes,
	     vector<unsigned int> &size,
	     vector<bound> &bounds,
	     string file);
 
//begin main
int main(int argv, char* argc[]){
  
  //check arguments to main 
  if(argv < 2){ throw("Invalid Number of Arguments to Pricing Engine."); }
  string s = argc[1];
  string s1(s.begin()+7,s.end());
  string output = "results/";
  output.append(s1);
  output.append(".out");

  //initialize variables
  double Spot, C, G, M, Y, T, rate, div_rate, sigma, nu, kappa, theta, rho, init_vol, eta, lambda; 
  vector<double> Strikes, alpha;
  vector<bound> bounds; 
  vector<unsigned int> size;
  string ModelType, EngineType;
  OptionType ContractType;
  
  //initialize fstream to read .trial files
  ifstream infile;
  infile.open(argc[1]);
  string word;
  
  while(infile>>word){
    if(word=="<CONTRACT>"){ InitializeContract(infile, ContractType, Spot, Strikes); }
    else if(word=="<ENGINE>"){ InitializeEngine(infile, EngineType, size, alpha, eta, lambda, bounds); }
    else if(word=="<MODEL>"){ InitializeModel(infile, ModelType, sigma, nu, kappa, theta, rho, init_vol, C,G,M,Y, rate, div_rate, T); }
    else {cout<<"Invalid Configuration at: "<<word<<endl; throw("Invalid Configuration File.");}
    }
  
  if(EngineType == "FFT"){
    FFT Engine;
    if(ModelType =="GBM"){
      GBM Model(sigma,rate,div_rate,T);
      RunFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,output);
      }
    else if(ModelType == "Heston"){
      Heston Model(kappa,theta, sigma, init_vol,rho, rate,div_rate,T);
      RunFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,output);
      }
    else if(ModelType == "VarianceGamma"){
      VarianceGamma Model(sigma,theta,nu,rate,div_rate,T);
      RunFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,output);
      }
    else if(ModelType == "CGMY"){
      CGMY Model(C,G,M,Y,rate,div_rate,T);
      RunFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,output);
      }
    }
  
  if(EngineType == "FrFFT"){
    FrFFT Engine;
    if(ModelType =="GBM"){
      GBM Model(sigma,rate,div_rate,T);
      RunFrFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,lambda,output);
      }
    else if(ModelType == "Heston"){
      Heston Model(kappa,theta, sigma, init_vol,rho, rate,div_rate,T);
      RunFrFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,lambda,output);
      }
    else if(ModelType == "VarianceGamma"){
      VarianceGamma Model(sigma,theta,nu,rate,div_rate,T);
      RunFrFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,lambda,output);
      }
    else if(ModelType == "CGMY"){
      CGMY Model(C,G,M,Y,rate,div_rate,T);
      RunFrFFT(Engine,Model,Spot,exp(-rate*T),Strikes,size,alpha,eta,lambda,output);
      }
    }
  
   if(EngineType == "COS"){
    COS Engine;
    if(ModelType =="GBM"){
      GBM Model(sigma,rate,div_rate,T);
      RunCOS(Engine,Model,Spot,ContractType,exp(-rate*T),Strikes,size,bounds,output);
      }
    else if(ModelType == "Heston"){
      Heston Model(kappa,theta, sigma, init_vol,rho, rate,div_rate,T);
      RunCOS(Engine,Model,Spot,ContractType,exp(-rate*T),Strikes,size,bounds,output);
      }
    else if(ModelType == "VarianceGamma"){
      VarianceGamma Model(sigma,theta,nu,rate,div_rate,T);
      RunCOS(Engine,Model,Spot,ContractType,exp(-rate*T),Strikes,size,bounds,output);
      }
    else if(ModelType == "CGMY"){
      CGMY Model(C,G,M,Y,rate,div_rate,T);
      RunCOS(Engine,Model,Spot,ContractType,exp(-rate*T),Strikes,size,bounds,output);
      }
    }
  
  return 0;
  } //<-- End Main

void InitializeModel(ifstream &infile, string &ModelType, double &sigma, double &nu, double &kappa, double &theta, double &rho, double &init_vol, double &C, double &G, double &M, double &Y, double &rate, double &div_rate, double &T){
  string word;
  double val;
  while(infile>>word){
    if(word=="name:"){infile >> ModelType; }
    else if(word=="sigma:"){ infile >> sigma; } 
    else if(word=="rate:"){ infile>>rate; }
    else if(word=="dividend:"){ infile >> div_rate; }
    else if(word=="T:"){ infile >> T; }
    else if(word=="kappa:"){ infile >> kappa; }
    else if(word=="nu:"){ infile >> nu; }
    else if(word=="theta:"){ infile >> theta; }
    else if(word=="init_vol:"){ infile >> init_vol; }
    else if(word=="rho:"){ infile >> rho; }
    else if(word=="C:"){ infile >> C; }
    else if(word=="G:"){ infile >> G; }
    else if(word=="M:"){ infile >> M; }
    else if(word=="Y:"){ infile >> Y; }
    else if(word=="</MODEL>"){ return; } else{cout<<"Error in Model Configuration"<<endl; throw("Invalid Input."); }
    }
  }

void InitializeEngine(ifstream &infile, string &EngineType, vector<unsigned int> &size, vector<double> &alpha, double &eta, double &lambda, vector<bound> &bounds){
  string word;
  unsigned int ival;
  double dval; 
  while(infile>>word){
    if(word=="name:"){infile >> EngineType; }
    else if(word=="N:"){ infile>>ival; size.push_back(ival); }
    else if(word=="alpha:"){ infile>>dval; alpha.push_back(dval); }
    else if(word=="eta:"){ infile>>eta; }
    else if(word=="lambda:"){ infile>>lambda; }
    else if(word=="bound:"){ 
      bound temp;
      infile >> temp.a; infile >> temp.b; bounds.push_back(temp);
      }
    else if(word=="</ENGINE>"){ return; } else {cout<<"Error in engine configuration while processing: "<<word; throw("Invalid Input."); }
    }
  }

void InitializeContract(ifstream &infile, OptionType &ContractType, double &Spot, vector<double> &Strikes){
  string word;
  double val; 
  while(infile>>word){
    if(word=="Spot:"){ infile>>Spot; }	
    else if(word=="Type:"){
      infile>>word; 
      if(word=="call"){ContractType = call;} 
      else if(word =="put"){ContractType = put; } else {cout<<"Error in Contract Configuration"<<endl; throw("Invalid Option Type.");}
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
	     double eta, 
	     string file){
  cout<<"Running FFT pricing engine. Results printing to file: "<<file<<endl;
  ofstream outfile(file.c_str());
  engine.Eta(eta);
  
  for(vector<double>::iterator strike_it = Strikes.begin(); strike_it!=Strikes.end();strike_it++){
    outfile<<"STRIKE: "<<*strike_it<<"\n Eta: "<<eta;
  
    outfile<<"\n Alpha:\t";
    
    for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++)
      outfile<<*alpha_it<<"\t";
   
    outfile<<endl;
     
    for(vector<unsigned int>::iterator size_it = size.begin(); size_it != size.end(); size_it++){
      outfile<<*size_it<<":\t";
      for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++){
	engine.N(*size_it);
	engine.Alpha(*alpha_it);
	outfile<<engine.Price(Spot,*strike_it,C,model)<<"\t";
	}
      
      outfile<<endl;
      }
    outfile<<endl<<endl;
  }
  outfile.close();
  outfile.clear();
}

  
void RunFrFFT(FrFFT &engine, 
	     pricemodel &model, 
	     double Spot,
	     double C,
	     vector<double> &Strikes, 
	     vector<unsigned int> &size, 
	     vector<double> &alpha, 
	     double eta,
	     double lambda, 
	     string file){
  cout<<"Running FrFFT pricing engine. Results printing to file: "<<file<<endl;
  ofstream outfile(file.c_str());
  engine.Eta(eta);
  engine.Lambda(lambda);
  
  for(vector<double>::iterator strike_it = Strikes.begin(); strike_it!=Strikes.end();strike_it++){
    outfile<<"STRIKE: "<<*strike_it<<"\n Eta: "<<eta<<"\n Lambda: "<<lambda;
  
    outfile<<"\n Alpha:\t";
    
    for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++)
      outfile<<*alpha_it<<"\t";
   
    outfile<<endl;
     
    for(vector<unsigned int>::iterator size_it = size.begin(); size_it != size.end(); size_it++){
      outfile<<*size_it<<":\t";
      for(vector<double>::iterator alpha_it = alpha.begin(); alpha_it!= alpha.end(); alpha_it++){
	engine.N(*size_it);
	engine.Alpha(*alpha_it);
	outfile<<engine.Price(Spot,*strike_it,C,model)<<"\t";
	}
      
      outfile<<endl;
      }
    outfile<<endl<<endl;
  }
  outfile.close();
  outfile.clear();
}

void RunCOS(COS &engine, 
	     pricemodel &model, 
	     double Spot,
	     OptionType ContractType,
	     double C,
	     vector<double> &Strikes, 
	     vector<unsigned int> &size, 
	     vector<bound> &bounds,
	     string file){
  cout<<"Running COS pricing engine. Results printing to file: "<<file<<endl;
  ofstream outfile(file.c_str());

  //set contract type
  engine.ContractType(ContractType);
  
  //add best bounds to bound vector
  double v1,v2;
  v1 = model.Cumulant(1);
  v2 = model.Cumulant(2)+pow(model.Cumulant(4),.5);
  v2 = pow(v2,.5);

  bound temp;
  temp.a = v1-model.L()*v2;
  temp.b = v1 + model.L()*v2;
  bounds.push_back(temp);
   
  for(vector<double>::iterator strike_it = Strikes.begin(); strike_it!=Strikes.end();strike_it++){
    outfile<<"STRIKE: "<<*strike_it;
  
    outfile<<"\n bounds:\t";
    
    for(vector<bound>::iterator bound_it = bounds.begin(); bound_it!= bounds.end(); bound_it++)
      outfile<<"("<<bound_it->a<<bound_it->b<<")"<<"\t";
   
    outfile<<endl;
     
    for(vector<unsigned int>::iterator size_it = size.begin(); size_it != size.end(); size_it++){
      outfile<<*size_it<<":\t";
      for(vector<bound>::iterator bound_it = bounds.begin(); bound_it!= bounds.end(); bound_it++){
	engine.N(*size_it);
	engine.LowerBound(bound_it->a);
	engine.UpperBound(bound_it->b);
	outfile<<engine.Price(Spot,*strike_it,C,model)<<"\t";
	}
      
      outfile<<endl;
      }
    outfile<<endl<<endl;
  }
  outfile.close();
  outfile.clear();
}

