#include "european.h"
double EuropeanPut::PayOff(const double &Spot){
  return Spot > strike ? 0 : strike - Spot;
  }
