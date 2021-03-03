PRG	= test
SRC	= $(PRG).cpp
OBJ	= $(PRG).o

LIBDIR  = ../..
LIBS  = $(LIBDIR)/gu3000.a
LFLAGS	= -lwiringPi
CFLAGS	= -Wall -I$(LIBDIR)

CC	= g++ $(CFLAGS)

all: $(PRG)

$(PRG): $(OBJ) $(LIBS)
	$(CC) -o $@ $^ $(LFLAGS)

.cpp.o:
	$(CC) -c $< -o $@ 

clean:
	rm -rf $(PRG) $(OBJ)

cleanall:
	rm -rf $(PRG) $(OBJ) *~

$(PRG).o: $(SRC) $(LIBS)
