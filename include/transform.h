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
    FFT(unsigned int size, double alpha_,double eta_) : N_(size), alpha(alpha_), eta(eta_){ }; 
    virtual ~FFT(){ }; 
    
    void N(const unsigned int &val){ N_ = val; };
    void Alpha(const double &val){ alpha = val; };
    void Eta(const double &val){eta = val; };
    
    unsigned int N() const { return N_; };
    double Alpha() const { return alpha; };
    double Eta() const { return eta; };
    virtual double Lambda() const {return 2.0*PI/(static_cast<double>(N_)*eta); };
    
    virtual std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const; //defined in FFTengine.cpp
    

  protected:
    double alpha, eta;
    unsigned int N_;
    
    void ComputeX(double complex X[], const double &Spot, const double &Strike, const double &C, const pricemodel &model) const;  //defined in FFTengine.cpp
  };

class FrFFT : public FFT {
  public:
  FrFFT(unsigned int n, double alpha_, double eta_, double lambda_, bool testing = false): FFT(n, alpha_, eta_), lambda(lambda_), testmode(testing){};
  ~FrFFT(){ };
  
  void Lambda(const double &l){ lambda = l; };
  double Lambda() const { return lambda; };
  
  double Gamma() const { return eta*lambda/(2.0*PI); };

  std::vector<Option> Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const; //defined in FrFFT.cpp
  
  private:
    double lambda;
    bool testmode;
         
    void ComputeY(double complex Y[],const double complex X[]) const; //defined in FrFFT.cpp

    void ComputeZ(double complex Z[]) const; //defined in FrFFT.cpp

    void ComputeXi(double complex Xi[], const double complex Y[], const double complex Z[]) const; //defined in FrFFT.cpp

  };

#endif
