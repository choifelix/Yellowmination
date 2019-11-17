#include <iostream>
#include "game.h"
#include <ctime>
int main(int argc, char **argv)
{
  std::cerr << "to quit, type C-c in the terminal" << std::endl;
  
  Game g = Game();
  
  srand ( time(NULL) ); 
  g.play();
  return 0;
}
