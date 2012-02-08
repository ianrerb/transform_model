#ifndef PRICEMODELS_H
#define PRICEMODELS_H
#define PI 3.14159265358979
#include<complex.h>
#include<fftw3.h>
#include<math.h>
#include<vector>

struct Option {double strike; double premium; }; //struct to hold strike, premium pairs

class fft_base {//abc
  public:
    //ctor and dtor
    fft_base(){ };
    virtual ~fft_base(){ };
    
    //defined functions
    double getLambda(const unsigned int &N, const double &eta){ return 2.0*PI/(static_cast<double>(N)*eta);};
    std::vector<Option> PutPrices(const double &Spot,
				  const double &Strike, 
				  const double &C, 
				  const unsigned int &N, 
				  const double &alpha, 
				  const double &eta);
    
    //pure virtual functions
    virtual double complex logCF(const double &S, const double complex &u) const=0;
  
  private:
    //helper function
    void ComputeX(double complex X[], 
		  const double &Spot,
		  const double &Strike, 
		  const double &C, 
		  const unsigned int &N, 
		  const double &alpha, 
		  const double &eta); 
  };

class GBM_model : public fft_base {
  public:
    GBM_model(const double sigma_, const double r_, const double q_, const double t_): sigma(sigma_), r(r_), q(q_), t(t_) { }; 
    ~GBM_model(){ }; 
    double complex logCF(const double &S, const double complex &u) const;
  private:
    double sigma, r, q, t;
  };


#endif
