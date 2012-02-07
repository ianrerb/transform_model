#ifndef EUROPEAN_H
#define EUROPEAN_H

class European_base {//abstract base class
  public:
    European_base(const double &strike_ = 0.0): strike(strike_) { };
    virtual ~European_base(){ };
    double Strike() const { return strike; };
    void setStrike(const double &strike_) { strike = strike_; };
    virtual double PayOff(const double &Spot)const=0; //pure virtual function
  
  protected:
    double strike;
  };

class EuropeanPut : public European_base {
  public:
    double PayOff(const double &Spot);
  };

#endif
