CC=g++
CFLAGS= -Wc++11-extensions -Wall 
LDFLAGS= -lsfml-system -lsfml-graphics -lsfml-audio -lsfml-window
EXEC= main
SRC=  screen.cpp wall.cpp personnage.cpp personnage_actif.cpp personnage_support.cpp audio.cpp team.cpp  animation.cpp game.cpp  main.cpp 
OBJ= $(SRC:.cc=.o)

all: $(EXEC)

main: $(OBJ)
	@$(CC)  -o $@ $^ $(LDFLAGS)

main.o: screen.h wall.h personnage.h obstacle.h path.h personnage_actif.h personnage_support.h audio.h team.h animation.h game.h

%.o: %.cc
	@$(CC)  -std=c++11 -o  $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

re: mrproper all
	./main