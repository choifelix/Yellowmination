CC=g++
CFLAGS= -Wall 
LDFLAGS= -lsfml-system -lsfml-audio
EXEC= test
SRC=   test.cpp 
OBJ= $(SRC:.cc=.o)

all: $(EXEC)

test: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

test.o: 

%.o: %.cc
	@$(CC)  -std=c++11 -o  $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
