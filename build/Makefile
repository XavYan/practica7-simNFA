IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = main.o NFA.o state_t.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: NFA

$(ODIR)/main.o: $(ODIR)/main.cpp $(ODIR)/NFA.cpp $(ODIR)/state_t.cpp $(IDIR)/NFA.hpp $(IDIR)/state_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

NFA: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
