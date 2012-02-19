#include"../include/transform.h"

void FrFFT::ComputeY(double complex Y[], const double complex X[]) const {
  unsigned int size = 2*N_;
  for(int i=0; i!=N_; i++){
    Y[i] = X[i]*cexp(-I*PI*Gamma()*i*i);
    Y[i+N_] = 0;
    }
  
  if(testmode==true){printComplexArray(Y,size,"Raw Y Vector");}
  }

void FrFFT::ComputeZ(double complex Z[]) const {
  unsigned int size = 2*N_;
  for(int i=0; i!=N_; i++){
    Z[i] = cexp(I*Gamma()*PI*static_cast<double>(i*i));
    Z[size-i-1] = Z[i];
    }
  
  if(testmode==true){printComplexArray(Z,size,"Raw Z Vector");}
  }

void FrFFT::ComputeXi(double complex Xi[], const double complex Y[], const double complex Z[]) const {
  unsigned int size = 2*N_;
  for(int i=0; i!=size; i++)
    Xi[i]=Y[i]*Z[i];
  
  if(testmode==true){printComplexArray(Xi,size,"Raw Xi Vector");}
  }


std::vector<Option> FrFFT::Prices(const double &Spot, const double &Strike, const double &C, const pricemodel &model) const {
  std::vector<Option> retvals;
  const unsigned int size = 2*N_;
  double complex X[N_], Y[size], Z[size], Xi[size];
  
  ComputeX(X,Spot,Strike,C,model);  
  ComputeY(Y,X);
  ComputeZ(Z);
  
  //compute Xi array
  fftw_plan Yplan = fftw_plan_dft_1d(size,Y,Y,FFTW_FORWARD,FFTW_ESTIMATE);
  fftw_plan Zplan = fftw_plan_dft_1d(size,Z,Z,FFTW_FORWARD,FFTW_ESTIMATE);
  fftw_plan Xiplan = fftw_plan_dft_1d(size,Xi,Xi,FFTW_BACKWARD,FFTW_ESTIMATE);

  fftw_execute(Yplan);
  fftw_execute(Zplan);
  if(testmode==true){printComplexArray(Y,size,"Transformed Y Vector"); printComplexArray(Z,size,"Transformed Z Vector");}

  ComputeXi(Xi,Y,Z);
  fftw_execute(Xiplan);
  
  //need to scale down Xi by 2N
  for(int i=0; i!= size; i++)
    Xi[i]=Xi[i]/static_cast<double>(size);

  if(testmode==true){printComplexArray(Xi,size,"Transformed Xi Vector");}
  
    //extract prices
 for(int i =0; i!= N_; i++){
    double lnK = log(Strike)-lambda*(static_cast<double>(N_)/2.0-static_cast<double>(i));
    Option temp;
    temp.strike = exp(lnK); 
    temp.premium = exp(-alpha*lnK)*creal(cexp(-I*PI*Gamma()*i*i)*Xi[i])/PI; 
    retvals.push_back(temp);
    }
    
  return retvals;
 

  } 
