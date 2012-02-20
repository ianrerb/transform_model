#ifndef TRANSFORM_H
#define TRANSFORM_H
#define PI M_PI 
#include"pricemodel.h"
#include<complex.h>
#include<fftw3.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>

struct Option {double strike; double premium; }; //struct to hold strike, premium pairs

/********************************************
 * ABSTRACT BASE CLASS FOR TRANSFORM CLASSES 
 ********************************************/

class transform_base {//abc
  public:
    transform_base(unsigned int size, bool test = false):N_(size), testmode(test){ };
    virtual ~transform_base(){ };
    
    void N(const unsigned int &val){ N_ = val; };
    unsigned int N() const { return N_; };

    virtual std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const =0;

  protected:
    unsigned int N_;

    //the testmode variable and print routine are used for debugging 
    bool testmode;
    void printComplexArray(double complex array[], unsigned int length, std::string title) const {
      std::cout<<"Array: "<<title<<std::endl;
      for(unsigned int i=0; i!=length; i++){
	std::cout<<"("<<creal(array[i])<<","<<cimag(array[i])<<")"<<"  ";
	}
      std::cout<<std::endl;
      };
 };
 
/**********************************
 * BEGIN DEFINITION OF FFT CLASS 
 **********************************/

 class FFT : public transform_base {
  public:
    FFT(unsigned int size, double alpha_,double eta_, bool test = false) : transform_base(size,test), alpha(alpha_), eta(eta_){ }; 
    virtual ~FFT(){ }; 
    
    void Alpha(const double &val){ alpha = val; };
    void Eta(const double &val){eta = val; };
    
    double Alpha() const { return alpha; };
    double Eta() const { return eta; };
    virtual double Lambda() const {return 2.0*PI/(static_cast<double>(N_)*eta); };
    
    virtual std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const; //defined in FFTengine.cpp

  protected:
    double alpha, eta;

    void ComputeX(double complex X[], const double &Spot, const double &Strike, const double &C, const pricemodel &model) const;  //defined in FFTengine.cpp
  };

/**********************************
 * BEGIN DEFINITION OF FrFFT CLASS 
 **********************************/

class FrFFT : public FFT {
  public:
  FrFFT(unsigned int size, double alpha_, double eta_, double lambda_, bool test = false): FFT(size, alpha_, eta_,test), lambda(lambda_){
    RefreshGamma();
    };
  ~FrFFT(){ };
  
  void Lambda(const double &l){ lambda = l; RefreshGamma(); };
  double Lambda() const { return lambda; };
  double Gamma() const { return gamma; }

  std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const; //defined in FrFFT.cpp
  
  private:
    double lambda;
    double gamma;
    
    double RefreshGamma() { gamma = eta*lambda/(2.0*PI); };
    void ComputeY(double complex Y[],const double complex X[]) const; //defined in FrFFT.cpp

    void ComputeZ(double complex Z[]) const; //defined in FrFFT.cpp

    void ComputeXi(double complex Xi[], const double complex Y[], const double complex Z[]) const; //defined in FrFFT.cpp

  };
/**********************************
 * Payoff Function for COS METHOD
 **********************************/

class COS_Payoff {
  public:
    enum OptionType {call, put};
    COS_Payoff(OptionType type_ = call, double strike_=0.0): type(type_), strike(strike_) { };
    ~COS_Payoff(){ };

    double operator()(const unsigned int &k, const double &a, const double &b, const double &c, const double &d) const;
   
   OptionType ContractType() const {return type;};
   void ContractType(const OptionType &t){ type = t; }; 
  private:
    OptionType type;
    double strike;

    double phi_helper(const unsigned int &k, const double &a, const double &b, const double &c, const double &d) const;
    double chi_helper(const unsigned int &k, const double &a, const double &b, const double &c, const double &d) const; 
  };

/**********************************
 * BEGIN DEFINITION OF COS METHOD CLASS 
 **********************************/

class COS : public transform_base {
  public:
    COS(unsigned int size, double low_bound=0, double high_bound=0, bool test = false): transform_base(size,test), a(low_bound), b(high_bound) { VerifyBounds(); };
    ~COS(){};
    
    void Bounds(const double &low, const double &high);
    void LowerBound(const double &low);
    void UpperBound(const double &high);
    void ContractType(const COS_Payoff::OptionType &type){ V_func.ContractType(type); }; 
    
    double LowerBound() const {return a; };
    double UpperBound() const {return b; };
    bool isValid() const { return valid_flag; };
    COS_Payoff::OptionType ContractType() const {return V_func.ContractType(); };

    std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const;

  private:
    double a;
    double b; 
    COS_Payoff V_func;
    bool valid_flag;
    void VerifyBounds();
  };
#endif
