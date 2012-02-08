#ifndef PRICEMODELS_H
#define PRICEMODELS_H
#define PI 3.14159265358979
#include<complex.h>
#include<fftw3.h>
#include<math.h>
#include<vector>

class transform_model_base {//ABC
  public:
    transform_model_base(const unsigned int N_, 
			 const double alpha_, 
			 const double eta_): 
			 N(N_), alpha(alpha_), eta(eta_){ };
    virtual ~transform_model_base(){ };
    virtual double complex logCF(const double &S, const double complex &u) const=0; //pure virtual function
  protected:
    double alpha, eta;
    unsigned int N;
  };

class fft_base : public transform_model_base {//abc
  public:
    fft_base(const unsigned int N_, const double alpha_, const double eta_): transform_model_base(N_,alpha_,eta_){ };
    virtual ~fft_base(){ };
    double getLambda(){ return 2.0*PI/(static_cast<double>(N)*eta);};
    virtual double complex logCF(const double &S, const double complex &u) const=0; //pure virtual function
    std::vector<double> PutPrices(const double &S, const double &C, const double &offset=0);
  private:
    void ComputeX(double complex X[], const double &S, const double &C, const double &offset); 
  };

class GBM_model : public fft_base {
  public:
    GBM_model(const double sigma_, 
	     const double r_, 
	     const double q_, 
	     const double t_, 
	     const unsigned int N_, 
	     const double alpha_, 
	     const double eta_): 
	     fft_base(N_,alpha_,eta_),sigma(sigma_), r(r_), q(q_), t(t_) { }; 
    ~GBM_model(){ }; 
    double complex logCF(const double &S, const double complex &u) const;
  private:
    double sigma, r, q, t, alpha, eta;
    unsigned int N;
  };


#endif
