.PHONY: all clean test 3D 2D images

RELEASE=yes

CC = g++
PC=povray
PY=python3

ifeq ($(RELEASE),yes)
CFLAGS = -std=c++11 -O3 -march=native -I headers/ -I tests/cxxtest
else
CFLAGS = -std=c++11 -Wall -g -I headers/ -I tests/cxxtest
endif

TARGET = main
OBJS = bin/main.o bin/basis.o bin/hermite.o bin/laguerre.o bin/poly.o bin/plot.o

#Test Variables 
TESTGEN = tests/cxxtest/bin/cxxtestgen
TESTFLAGS = --error-printer
TESTFILE = tests/my_tests.h
TESTOUTPUT = tests/my_tests.cpp
TESTEXE = tests/my_tests_runner
TEST_OBJS = bin/basis.o bin/hermite.o bin/laguerre.o bin/poly.o bin/plot.o 

#Libraries
LIBS = -larmadillo


PFLAGS=+A0.0001 +W960 +H720 +Q11 +P
IMG3D=visu3D.png
DENSITY3D=assets/density3D.df3

IMG2D=visu2D.png
DENSITY2D=assets/density2D.csv

all: $(TARGET)

3D: $(IMG3D)

2D: $(IMG2D)
	open $(IMG2D)

images: $(IMG3D) $(IMG2D)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

bin/main.o: src/main.cpp headers/plot.h headers/basis.h headers/poly.h headers/hermite.h headers/laguerre.h
	$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

bin/basis.o: src/basis.cpp headers/basis.h headers/poly.h headers/hermite.h headers/laguerre.h
	$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

bin/poly.o: src/poly.cpp headers/poly.h headers/hermite.h headers/laguerre.h
	$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

#Generic rule if a source file relies on exactly 1 header file
bin/%.o: src/%.cpp headers/%.h
	$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)


#Build & run tests 
test: $(TESTEXE)
	./$(TESTEXE)

$(TESTEXE): $(TESTOUTPUT) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TESTOUTPUT) $(TEST_OBJS) -o $(TESTEXE) $(LIBS)


$(TESTOUTPUT): $(TESTFILE)
	$(TESTGEN) $(TESTFLAGS) -o $(TESTOUTPUT) $(TESTFILE)


$(IMG3D): src/visu.pov $(DENSITY3D)
	$(PC) +O$@ $(PFLAGS) $<

$(DENSITY3D): $(TARGET)
	./$(TARGET)


$(IMG2D): src/plot.py $(DENSITY2D)
	$(PY) $^

$(DENSITY2D): $(TARGET)
	./$(TARGET)

clean:
	rm -vf $(OBJS) $(TARGET) $(TESTOUTPUT) $(TESTEXE) $(IMG3D) $(IMG2D) $(DENSITY3D) $(DENSITY2D) 
