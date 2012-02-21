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
    pricemodel(double interest_rate=0.0, double div_rate=0.0, double time=0.0) : r(interest_rate), q(div_rate), T(time), L_(10) { };
    virtual ~pricemodel(){ };

    void TimeToExpiry(double &time) { T=time; };
    void RiskFreeRate(double &rate) { r=rate; };
    void DividendRate(double &div_rate) { q=div_rate; };

    double TimeToExpiry() const {return T; };
    double RiskFreeRate() const {return r; };
    double DividendRate() const {return q; };
    double L() const {return L_; };    
    //computes E[exp(iulogS)]
    virtual double complex logCF(const double &S, const double complex &u) const=0;
    virtual double Cumulant(unsigned int k) const = 0;
 
  protected:
    double r;
    double q;
    double T;
    double L_; //for COS method
  };

class GBM : public pricemodel {
  public:
    GBM(double volatility, double interest_rate=0.0, double div_rate=0.0, double time=0.0): pricemodel(interest_rate, div_rate, time), sigma(volatility) { };
    virtual ~GBM(){ };
    
    void setVolatility(double &vol) {sigma = vol; };
    double Volatility() const {return sigma; };

    double complex logCF(const double &S, const double complex &u) const; //defined in GBM.cpp    
    double Cumulant(unsigned int k) const;
  
  private:
    double sigma;
  };

class Heston : public pricemodel {
  public:
    Heston(double kappa_, double theta_, double sigma_, double init_vol, double rho_=0.0,  double interest_rate=0.0, double div_rate=0.0, double time=0.0): pricemodel(interest_rate, div_rate, time),kappa(kappa_), theta(theta_), sigma(sigma_), v0(init_vol), rho(rho_) {
      L_ = 12;//since c4 cumulant not used for COS BOUND
    }; 
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
    double Cumulant(unsigned int k) const;

  private:
    double kappa, theta, sigma, rho, v0;
  };

class VarianceGamma : public pricemodel {
  public:
    VarianceGamma(double sigma_, double theta_, double v_, double interest_rate=0.0, double div_rate=0.0, double time=0.0): pricemodel(interest_rate, div_rate, time), sigma(sigma_), theta(theta_), v(v_) {}; 
    ~VarianceGamma(){};

    void setV(double &v_) {v = v_; };
    void setTheta(double &theta_) {theta = theta_; };
    void setSigma(double &sigma_) {sigma = sigma_; };

    double V() const {return v; };
    double Theta() const {return theta; };
    double Sigma() const {return sigma; };

    double complex logCF(const double &S, const double complex &u) const; //defined in VarianceGamma.cpp    
    double Cumulant(unsigned int k) const;

  private:
    double v, theta, sigma;
  };

class CGMY : public pricemodel {
  public:
    CGMY(double C_, double G_, double M_, double Y_, double interest_rate=0.0, double div_rate=0.0, double time=0.0): pricemodel(interest_rate, div_rate, time), C_param(C_), G_param(G_), M_param(M_), Y_param(Y_) {}; 
    ~CGMY(){};

    void setC(double &C_) {C_param = C_; };
    void setG(double &G_) {G_param = G_; };
    void setM(double &M_) {M_param = M_; };
    void setY(double &Y_) {Y_param = Y_; };

    double C() const {return C_param; };
    double G() const {return G_param; };
    double M() const {return M_param; };
    double Y() const {return Y_param; };

    double complex logCF(const double &S, const double complex &u) const; //defined in CGMY.cpp    
    double Cumulant(unsigned int k) const;

  private:
    double complex Omega_helper(double complex val = 1.0) const; //helper function to calculate omega for logCF
    double C_param, G_param, M_param, Y_param;
  };
#endif
