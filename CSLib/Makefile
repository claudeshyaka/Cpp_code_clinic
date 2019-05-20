# makefile for CSLib
# reference: Bill Weinman <http://bw.org/>
# by Claude Shyaka

TARGET=CSLib.a
CC=c++
CPPFLAGS=-O3 -std=gnu++11
LDFLAGS=-L.

all: test.out

CSUnitTest.o: CSUnitTest.h CSUnitTest.cpp
	$(CC) $(CPPFLAGS) -c CSUnitTest.cpp

CSString.o: CSString.h CSString.cpp
	$(CC) $(CPPFLAGS) -c CSString.cpp

$(TARGET): CSUnitTest.o CSString.o
	ar rcs $(TARGET) CSUnitTest.o CSString.o

test.out: $(TARGET) main.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o test.out main.cpp $(TARGET)

clean:
	rm *.o test.out $(TARGET)