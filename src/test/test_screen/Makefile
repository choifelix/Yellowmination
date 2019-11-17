CC=g++
CFLAGS= -Wall 
LDFLAGS= -lsfml-system -lsfml-graphics -lsfml-window
EXEC= main
SRC=   main.cpp screen.cpp animation.cpp personnage.cpp 
OBJ= $(SRC:.cc=.o)

all: $(EXEC)

main: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: screen.h animation.h personnage.h

%.o: %.cc
	@$(CC)  -std=c++11 -v  $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

re: clean all
	./main