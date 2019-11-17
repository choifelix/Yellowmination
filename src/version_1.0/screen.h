#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <math.h> 
#include <SFML/Graphics.hpp>

 /**
     Constructor of Screen  open a SFML window
     @param w width of the window (e.g. 500)
     @param h height of the window (e.g. 500)
 **/

// Cette classe et la plupart des methodes ont ete faits par Mme Braunstein

class Screen{
  public:
  Screen(uint16_t h, uint16_t w);
  ~Screen(){delete _win;};
  bool isOpen(){return _win->isOpen();}
  void close(){_win->close();}
  bool pollEvent(sf::Event& event){return _win->pollEvent(event);}
  void render();
  void SetFramerateLimit(int nb_frame){_win->setFramerateLimit(nb_frame);} // Fait par les auteurs du projet

   /** draw a filled rectangle
      @param x x-coordinate of the center (in pixels)
      @param y y-coordinate of the center (in pixels)
      @param w width of the rectangle (in pixels)
      @param h height of the rectangle (in pixels)
      @param color 0xRRGGBBAA (default: blue)
  */
  void disc(float x, float y, float radius, uint32_t color = 0xFF0000FF); 
  void rect(float x, float y, float w, float h, uint32_t color = 0xFF0000FF);
  void text(float x ,float y,std::string text,uint32_t color = 0x35EEEEFF,std::string font_file = "font/ComicNeue-Regular.ttf");
  void background(); // Fait par les auteurs du projet
  void display(sf::Sprite& sp){_win->draw(sp);} // Fait par les auteurs du projet

  
  protected:


  private:
  sf::RenderWindow *  _win;
  uint16_t _w, _h;
  sf::Texture *_tx_bg; // Fait par les auteurs du projet
  sf::Sprite *_sp_bg; // Fait par les auteurs du projet

  
  
};
