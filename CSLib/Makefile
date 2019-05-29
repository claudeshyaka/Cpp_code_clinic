# makefile for CSLib
# reference: Bill Weinman <http://bw.org/>
# by Claude Shyaka

TARGET=CSLib.a
CC=c++
CPPFLAGS=-O3 -std=gnu++11
LDFLAGS=-L. -lsqlite3

all: test.out

CSUnitTest.o: CSUnitTest.h CSUnitTest.cpp
	$(CC) $(CPPFLAGS) -c CSUnitTest.cpp

CSString.o: CSString.h CSString.cpp
	$(CC) $(CPPFLAGS) -c CSString.cpp

CSNumber.o: CSNumber.h CSNumber.cpp
	$(CC) $(CPPFLAGS) -c CSNumber.cpp

CSDB.o: CSDB.h CSDB.cpp
	$(CC) $(CPPFLAGS) -c CSDB.cpp

CSKV.o: CSKV.h CSKV.cpp
	$(CC) $(CPPFLAGS) -c CSKV.cpp

$(TARGET): CSUnitTest.o CSString.o CSNumber.o CSDB.o CSKV.o
	ar rcs $(TARGET) CSUnitTest.o CSString.o CSNumber.o CSDB.o CSKV.o

test.out: $(TARGET) main.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o test.out main.cpp $(TARGET)

clean:
	rm *.o test.out $(TARGET)