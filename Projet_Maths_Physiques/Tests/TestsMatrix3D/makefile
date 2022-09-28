SRC=$(wildcard *.cpp) ../../src/Matrix3D.cpp
OBJ=$(patsubst %.cpp, %.o, $(SRC))

CC=g++
CFLAGS=-Wall -std=c++2a -pedantic -g -I"../../includes"
BIN=TestsMatrix3D.exe

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	del ..\..\src\Matrix3D.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	del *.o
	del *.exe
