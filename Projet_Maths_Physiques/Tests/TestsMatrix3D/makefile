SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC)) Matrix3D.o

CC=g++
CFLAGS=-Wall -std=c++2a -pedantic -g
CLIBS=-lm
BIN=TestsMatrix3D.exe

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(CLIBS)

Matrix3D.o: ../../src/Matrix3D.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ -I "../../includes" $(CLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ $(CLIBS)

clean:
	del *.o
	del *.exe
