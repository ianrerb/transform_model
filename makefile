OBJ= main.o GBM.o Heston.o VarianceGamma.o CGMY.o FFT.o FrFFT.o
CPL= g++ -c
LNK= g++ -o
INC=include/
SRC=src/

main : $(OBJ)
	$(LNK) main $(OBJ) -lfftw3 -lm
	
main.o : main.cpp
	$(CPL) main.cpp

GBM.o : $(SRC)GBM.cpp $(INC)pricemodel.h
	$(CPL) $(SRC)GBM.cpp

Heston.o : $(SRC)Heston.cpp $(INC)pricemodel.h
	$(CPL) $(SRC)Heston.cpp

VarianceGamma.o : $(SRC)VarianceGamma.cpp $(INC)pricemodel.h
	$(CPL) $(SRC)VarianceGamma.cpp

CGMY.o : $(SRC)CGMY.cpp $(INC)pricemodel.h $(INC)sp_gamma.h
	$(CPL) $(SRC)CGMY.cpp

FFT.o : $(SRC)FFT.cpp $(INC)transform.h
	$(CPL) $(SRC)FFT.cpp

FrFFT.o : $(SRC)FrFFT.cpp $(INC)transform.h
	$(CPL) $(SRC)FrFFT.cpp


run :
	./main

.PHONY : clean
clean :
	-rm main $(OBJ)
