OBJ= main.o
CPL= g++ -c
LNK= g++ -o

main : $(OBJ)
	$(LNK) main $(OBJ) -lfftw3 -lm
	
main.o : main.cpp
	$(CPL) main.cpp
run :
	./main

.PHONY : clean
clean :
	-rm main $(OBJ)
