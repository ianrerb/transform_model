#include"../include/pricemodels.h"

void fft_base::ComputeX(double complex X[], const double &S, const double &C, const double &offset){
  double s = log(S);
  double lambda = getLambda();

  for(int j = 0; j!=N; j++){
    double complex nu = j*static_cast<double complex>(N); //nu = (j-1)eta
    double complex val1 = alpha+I*nu; //denominator of C term
    double complex temp = eta*C/(val1*(1.0+val1))*cexp(-I*(s-PI/eta))*logCF(S,nu-(alpha+1)*I); //x_j j!=0
    if(j==0){ temp*=.5; }//adjustment for j = 0
    X[j]=temp;
    }
  }

std::vector<double> fft_base::PutPrices(const double &S, const double &C, const double &offset){
  double complex xvals[N];
  printf("Computing X...\n"); 
  fft_base::ComputeX(xvals,S,C,offset);
  double complex yvals[N];
  fftw_plan p = fftw_plan_dft_1d(N,xvals,yvals,FFTW_FORWARD, FFTW_ESTIMATE);
  std::vector<double> retvals;
  printf("Computing FFT...\n"); 
  fftw_execute(p);
//  fftw_destroy_plan(p);
  for(int i =0; i!= N; i++)
    retvals.push_back(exp(-alpha*(log(S)-static_cast<double>(N)*getLambda()/2.0))*creal(yvals[i])/PI);
  return retvals;
  
  }

double complex GBM_model::logCF(const double &S, const double complex &u) const{
  double complex retval = I*(clog(S) + (r - q - cpow(sigma,2.0)/2.0)*t)*u - cpow(sigma*u,2.0)*t/2.0;
  return cexp(retval);
  }
