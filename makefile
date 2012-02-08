OBJ= main.o pricemodels.o
CPL= g++ -c
LNK= g++ -o
INC=include/
SRC=src/

main : $(OBJ)
	$(LNK) main $(OBJ) -lfftw3 -lm
	
main.o : main.cpp
	$(CPL) main.cpp

pricemodels.o : $(SRC)pricemodels.cpp $(INC)pricemodels.h
	$(CPL) $(SRC)pricemodels.cpp

run :
	./main

.PHONY : clean
clean :
	-rm main $(OBJ)
