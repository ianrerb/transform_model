#include "../include/transform.h"

double COS_Payoff::operator()(const unsigned int &k, const double &a, const double &b, const double &c, const double &d) const{
  switch(type){
    case call :
      return 2.0/(b-a)*strike*(chi_helper(k,a,b,0,b)-phi_helper(k,a,b,0,b));
      break;
    case put :
      return 2.0/(b-a)*strike*(-chi_helper(k,a,b,a,0)+phi_helper(k,a,b,a,0));
      break;
    default :
      throw("Unknown option type.");
    }
  }

double COS_Payoff::phi_helper(const unsigned int &k, const double &a, const double &b, const double &c, const double &d) const {
  if(k==0){ return(d-c); }; //case where k = 0

  //case where k!= 0
  double v1,v2, retval;
  v1 = (d-a)/(b-a);
  v2 = (c-a)/(b-a);

  retval = sin(k*PI*v1)-sin(k*PI*v2);
  retval *= (b-a)/(k*PI);
  return retval;
  }

double COS_Payoff::chi_helper(const unsigned int &k, const double &a, const double &b, const double &c, const double &d) const {
  double v1, v2, retval;
  v1 = (d-a)/(b-a);
  v2 = (c-a)/(b-a);
  
  retval = cos(k*PI*v1)*exp(d) - cos(k*PI*v2)*exp(c);
  retval += k*PI/(b-a)*( sin(k*PI*v1)*exp(d) - sin(k*PI*v2)*exp(c) ); 
  retval /= 1.0+pow(k*PI/(b-a),2);
  return retval;
  } 


void COS::Bounds(const double &low, const double &high){
  LowerBound(low);
  UpperBound(high); 
  }

void COS::VerifyBounds(){valid_flag = (a < b ? true : false); }

void COS::LowerBound(const double &low){ a = low; VerifyBounds(); }

void COS::UpperBound(const double &high){ b = high; VerifyBounds(); }
    
std::vector<Option> COS::Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const{
  std::vector<Option> options;
  if(isValid() == false){ 
    std::cout<<"Invalid Bounds, returning empty vector."<<std::endl;
    return options;
    }

  double F[N_];
  
  if(testmode == true){
    Option temp;
    temp.premium = 1;
    temp.strike = 1;
    options.push_back(temp);
    }

  return options;
  }
