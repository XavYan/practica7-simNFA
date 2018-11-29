IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = main.o DFA.o state_t.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: DFA

$(ODIR)/main.o: $(ODIR)/main.cpp $(ODIR)/DFA.cpp $(ODIR)/state_t.cpp $(IDIR)/DFA.hpp $(IDIR)/state_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

DFA: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
