SRC=$(wildcard *.cpp) ../../src/Vecteur3D.cpp
OBJ=$(patsubst %.cpp, %.o, $(SRC))

CC=g++
CFLAGS=-Wall -std=c++2a -pedantic -g -I"../../includes"
BIN=TestsVecteur3D.exe

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	del ..\..\src\Vecteur3D.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	del *.o
	del *.exe
