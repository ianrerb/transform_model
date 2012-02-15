#ifndef PRICEMODEL_H
#define PRICEMODEL_H
#include<complex.h>
#include<math.h>
#include<vector>

/* pricemodel is an abstract base class (ABC).  
 * User cannot declare variables of type pricemodel
 * pricemodel provides interface for derived classes GBM, [...]
 */

class pricemodel {
  public:
    pricemodel(double interest_rate=0.0, double div_rate=0.0, double time=0.0) : r(interest_rate), q(div_rate), T(time){ };
    virtual ~pricemodel(){ };

    void setTimeToExpiry(double &time) { T=time; };
    void setRiskFreeRate(double &rate) { r=rate; };
    void setDividendRate(double &div_rate) { q=div_rate; };

    double TimeToExpiry() const {return T; };
    double RiskFreeRate() const {return r; };
    double DividendRate() const {return q; };
    
    //computes E[exp(iulogS)]
    virtual double complex logCF(const double &S, const double complex &u) const=0;
  
  protected:
    double r;
    double q;
    double T;
  };

class GBM : public pricemodel {
  public:
    GBM(double volatility, double interest_rate=0.0, double div_rate=0.0, double time=0.0): pricemodel(interest_rate, div_rate, time), sigma(volatility){ };
    virtual ~GBM(){ };
    
    void setVolatility(double &vol) {sigma = vol; };
    double Volatility() const {return sigma; };

    double complex logCF(const double &S, const double complex &u) const; //defined in GBM.cpp    
  private:
    double sigma;
  };

class Heston : public pricemodel {
  public:
    Heston(double kappa_, double theta_, double sigma_, double init_vol, double rho_=0.0,  double interest_rate=0.0, double div_rate=0.0, double time=0.0): pricemodel(interest_rate, div_rate, time),kappa(kappa_), theta(theta_), sigma(sigma_), v0(init_vol), rho(rho_) {}; 
    ~Heston(){};

    void setKappa(double &kappa_) {kappa = kappa_; };
    void setTheta(double &theta_) {theta = theta_; };
    void setSigma(double &sigma_) {sigma = sigma_; };
    void setRho(double &rho_) {rho = rho_; };
    void setInitialVolatility(double &vol) {v0=vol;};

    double Kappa() const {return kappa; };
    double Theta() const {return theta; };
    double Sigma() const {return sigma; };
    double Rho() const {return rho; };
    double InitialVolatility() const {return v0; };

    double complex logCF(const double &S, const double complex &u) const; //defined in Heston.cpp    

  private:
    double kappa, theta, sigma, rho, v0;
  };
#endif
