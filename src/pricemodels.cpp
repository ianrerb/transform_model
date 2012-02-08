#include"../include/pricemodels.h"

void fft_base::ComputeX(double complex X[], 
			const double &Spot,
			const double &Strike, 
			const double &C, 
			const unsigned int &N, 
			const double &alpha, 
			const double &eta){
  double lnK = log(Strike); //takes log of strike price
  double lambda = getLambda(N,eta); //computes lambda

  for(int j = 0; j!=N; j++){
    double complex nu = j*static_cast<double complex>(N); //nu = (j-1)eta
    double complex val1 = alpha+I*nu; //denominator of C term
    double complex temp = eta*C/(val1*(1.0+val1))*cexp(-I*(lnK-PI/eta))*logCF(Spot,nu-(alpha+1)*I); //x_j j!=0
    if(j==0){ temp*=.5; }//adjustment for j = 0
    X[j]=temp;
    }
  }

std::vector<Option> fft_base::PutPrices(const double &Spot,
					const double &Strike, 
					const double &C, 
					const unsigned int &N, 
					const double &alpha, 
					const double &eta){
  double complex xvals[N];
  double complex yvals[N];
  std::vector<Option> retvals;
  
  double lambda = getLambda(N,eta);
  
  //FFT call
  fft_base::ComputeX(xvals,Spot,Strike,C,N,alpha,eta);
  fftw_plan p = fftw_plan_dft_1d(N,xvals,yvals,FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  
  //extract prices
 for(int i =0; i!= N; i++){
    double lnK = log(Strike)-lambda*(static_cast<double>(N)/2.0-static_cast<double>(i));
    Option temp;
    temp.strike = exp(lnK); 
    temp.premium = exp(-alpha*lnK)*creal(yvals[i])/PI; 
    retvals.push_back(temp);
    }
    
  return retvals;
  
  }

double complex GBM_model::logCF(const double &S, const double complex &u) const{
  double complex retval = I*(log(S) + (r - q - cpow(sigma,2.0)/2.0)*t)*u - cpow(sigma*u,2.0)*t/2.0;
  return cexp(retval);
  }
