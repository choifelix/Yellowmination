#include <iostream>
#include "screen.h"
#include "personnage.h"
#include <ctime>

int main(int argc, char **argv)
{
  sf::Event event;

  Screen _screen(720, 1280);

  Personnage sonic(200, 200, 100, 100, "Sonic");

  sf::Clock clock;
  
  srand ( time(NULL) );

  int index = 0;
  while(_screen.isOpen())
  {
    while(_screen.pollEvent(event))
    {
      if(event.type == sf::Event::EventType::Closed)
        _screen.close();
    }

    _screen.render();

    sonic.draw(_screen);


    if(clock.getElapsedTime().asSeconds() > 0.08f) {
      sonic.update();
      clock.restart();
    }

    if(index == 4000)
    {
      sonic.setState(DEAD);

    }
    index++;


  }
  return 0;
}
