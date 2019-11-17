#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <math.h>   
#include <stdint.h>

#include <SFML/Graphics.hpp>

 /**
     Constructor of Screen  open a SFML window
     @param w width of the window (e.g. 500)
     @param h height of the window (e.g. 500)
 **/

class Screen{
 public:
  Screen(uint16_t h, uint16_t w);
  ~Screen(){delete _win;};
  bool isOpen(){return _win->isOpen();}
  void close(){_win->close();}
  bool pollEvent(sf::Event& event){return _win->pollEvent(event);}
  void render();
  void text(float x ,float y,std::string text,uint32_t color = 0x35EEEEFF,std::string font_file = "font/ComicNeue-Regular.ttf");
  void display(sf::Sprite& bg){return _win->draw(bg);}

 protected:


 private:
  sf::RenderWindow *  _win;
  uint16_t _w, _h;

  
  
};
