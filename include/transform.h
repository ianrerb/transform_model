#ifndef TRANSFORM_H
#define TRANSFORM_H
#define PI 3.14159265358979
#include"pricemodel.h"
#include<complex.h>
#include<fftw3.h>
#include<math.h>
#include<vector>

struct Option {double strike; double premium; }; //struct to hold strike, premium pairs

class transform_base {//abc
  public:
    transform_base(){ };
    virtual ~transform_base(){ };
    
    virtual std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const =0;
 };
 
 class FFT : public transform_base {
  public:
    FFT(unsigned int N_, double alpha_,double eta_) : N(N_), alpha(alpha_), eta(eta_){ }; 
    ~FFT(){ }; 
    
    void setN(const unsigned int &val){ N = val; };
    void setAlpha(const double &val){ alpha = val; };
    void setEta(const double &val){eta = val; };
    
    unsigned int getN() const { return N; };
    double Alpha() const { return alpha; };
    double Eta() const { return eta; };
    double Lambda() const {return 2.0*PI/(static_cast<double>(N)*eta); };
     
    std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const; //defined in FFTengine.cpp
    

  private:
    double alpha, eta;
    unsigned int N;
    
    void ComputeX(double complex X[], const double &Spot, const double &Strike, const double &C, const pricemodel &model) const;  //defined in FFTengine.cpp
  };

#endif
