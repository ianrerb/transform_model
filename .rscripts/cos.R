source("GBM.R")
I = complex(real = 0, imaginary = 1);

phi<- function(k,a,b,c,d){
  if(k==0){return(d-c)}
  v1 = k*pi/(b-a);
  return(sin(v1*(d-a))-sin(v1*(c-a))/v1)
  }

chi<-function(k,a,b,c,d){
  v1 = k*pi/(b-a);
  temp = cos(v1*(d-a))*exp(d)-cos(v1*(c-a))*exp(c)+v1*(sin(v1*(d-a))*exp(d)-sin(v1*(c-a))*exp(c));
  return(temp/(1+v1^2))
  }

V<-function(k,strike,a,b){
  temp = 2/(b-a)*strike*(chi(k,a,b,0,b)-phi(k,a,b,0,b))
  print(chi(k,a,b,0,b))
  print(phi(k,a,b,0,b))
  
  return(temp)
  }

Price<-function(N,a,b,Spot,Strike,vol,r,q,t){
  value = array(0,N);

  for(i in 1:N){
    k = i-1;
    temp = exp(-r*t)*Re(GBM_CF(Spot/Strike,k*pi/(b-a),vol,r,q,t)*exp(-I*k*pi*a/(b-a)))*V(k,Strike,a,b)
    if(i==1){value[i]= temp/2}else{value[i]=temp+value[i-1]}
    }
  return(value)
}
