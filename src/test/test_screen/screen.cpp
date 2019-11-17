#include "screen.h"

Screen::Screen(uint16_t h,uint16_t w):_w(w),_h(h){
   _win = new sf::RenderWindow(sf::VideoMode(_w , _h), "NEW GAME");
}


void Screen::render()
{
  _win->display();
  _win->clear();
}

void Screen::text(float x ,float y,std::string str_txt,uint32_t color, std::string font_file)
{
  sf::Font font;
  if (!font.loadFromFile(font_file))
    {
      std::cerr << "no font found" << std::endl;
    }
  sf::Text text;

  text.setFont(font);

  text.setString(str_txt);
  text.setColor(sf::Color(color));
  text.setPosition(x,y);
  _win->draw(text);

}
