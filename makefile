OBJ= main.o GBM.o Heston.o FFT.o
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

FFT.o : $(SRC)FFT.cpp $(INC)transform.h
	$(CPL) $(SRC)FFT.cpp

run :
	./main

.PHONY : clean
clean :
	-rm main $(OBJ)
