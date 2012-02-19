#include "../include/transform.h"

void FFT::ComputeX(double complex X[], const double &Spot, const double &Strike, const double &C, const pricemodel &model) const {
  double lnK = log(Strike); //takes log of strike price
  double lambda = Lambda(); //computes lambda

  for(int j = 0; j!=N_; j++){
    double complex nu = static_cast<double>(j)*eta; //nu = (j-1)eta
    double complex val = alpha+I*nu; //denominator of C term
    double complex temp = eta*C/(val*(1.0+val))*cexp(-I*nu*(lnK-PI/eta))*model.logCF(Spot,nu-(alpha+1.0)*I); //x_j j!=0
    if(j==0){ temp*=.5; }//adjustment for j = 0
    X[j]=temp;
    }
  
  if(testmode==true){
    std::cout<<std::endl<<" <++ THIS IS RAW X ARRAY ++>"<<std::endl;
      for(int i = 0; i!= size; i++)
	std::cout<<"("<<creal(Y[i])<<" , "<<cimag(Y[i])<<")"<<std::endl;
    }
  }

std::vector<Option> FFT::Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const {
  double complex vals[N_];
  std::vector<Option> retvals;
  double lambda = Lambda();
  
  //FFT call
  fftw_plan p = fftw_plan_dft_1d(N_,vals,vals,FFTW_FORWARD, FFTW_ESTIMATE);
  ComputeX(vals,Spot,Strike,C, model);
  fftw_execute(p);
  
  //extract prices
 for(int i =0; i!= N_; i++){
    double lnK = log(Strike)-lambda*(static_cast<double>(N_)/2.0-static_cast<double>(i));
    Option temp;
    temp.strike = exp(lnK); 
    temp.premium = exp(-alpha*lnK)*creal(vals[i])/PI; 
    retvals.push_back(temp);
    }
    
  return retvals;
  
  }

