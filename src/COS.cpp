#include "../include/transform.h"

double COS_Payoff::operator()(const unsigned int &k, const double &a, const double &b) const{
  double retval;
  switch(type){
    
    case call :
      retval = 2.0/(b-a)*strike*(chi_helper(k,a,b,0,b)-phi_helper(k,a,b,0,b));
     // std::cout<<"V("<<k<<") = "<<retval<<"\n\n";
      break;
    
    case put :
      retval= 2.0/(b-a)*strike*(-chi_helper(k,a,b,a,0)+phi_helper(k,a,b,a,0));
      break;
    
    default :
      std::cout<<"ERROR IN OPTION TYPE.";
      throw("Unknown option type.");
    }
    return retval;
  }

double COS_Payoff::phi_helper(const double &k, const double &a, const double &b, const double &c, const double &d) const {
  if(k==0){ return(d-c); }; //case where k = 0
  //case where k!= 0
  double v1,v2, retval;
  v1 = (d-a)/(b-a);
  v2 = (c-a)/(b-a);

  retval = sin(k*PI*v1)-sin(k*PI*v2);
  retval *= (b-a)/(k*PI);
  //std::cout<<"phi("<<k<<") = "<<retval<<std::endl;
  return retval;
  }

double COS_Payoff::chi_helper(const double &k, const double &a, const double &b, const double &c, const double &d) const {
  double v1, v2, retval;
  v1 = (d-a)/(b-a);
  v2 = (c-a)/(b-a);
  
  retval = cos(k*PI*v1)*exp(d) - cos(k*PI*v2)*exp(c);
  retval += k*PI/(b-a)*( sin(k*PI*v1)*exp(d) - sin(k*PI*v2)*exp(c) ); 
  retval /= 1.0+pow(k*PI/(b-a),2);
  //std::cout<<"chi("<<k<<") = "<<retval<<std::endl;
  return retval;
  } 

//START COS DEFINITIONS

void COS::Bounds(const double &low, const double &high){
  LowerBound(low);
  UpperBound(high); 
  }

void COS::BestBounds(pricemodel &model){
  double v1, v2;
  v1 = model.Cumulant(1);
  v2 = pow(model.Cumulant(2)+pow(model.Cumulant(4),.5),.5);
  LowerBound(v1 - model.L()*v2);
  UpperBound(v1 + model.L()*v2);
  }


void COS::VerifyBounds(){valid_flag = (a < b ? true : false); }
void COS::LowerBound(const double &low){ a = low; VerifyBounds(); }
void COS::UpperBound(const double &high){ b = high; VerifyBounds(); }
    
double COS::Price(const double &Spot, const double &Strike, const double &C, const pricemodel &model){
  V_func.Strike(Strike); 
  double retval=0;
  if(isValid() == false){ throw("Invalid Bounds for COS Method Pricing."); }
  
  for(unsigned int i = 0; i!= N_; i++){
    double k = static_cast<double>(i);
    double temp = creal(model.logCF(Spot,k*PI/(b-a))*cexp(-I*k*PI*a/(b-a)));
    //std::cout<<"Re(...,"<<i<<")"<<temp<<std::endl;
    retval += temp*CalcV(i)*(i==0 ? .5 : 1.0);
    }
  return C*retval;
  }
