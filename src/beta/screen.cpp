#include "screen.h"
  

Screen::Screen(uint16_t h,uint16_t w):_w(w),_h(h){
  _win = new sf::RenderWindow(sf::VideoMode(_w , _h), "Un bordel jaune");
  _tx_bg = new sf::Texture();
  _tx_bg->loadFromFile("../../interface/image/background.png");
  _sp_bg = new sf::Sprite(*_tx_bg, sf::IntRect(0, 0, _w, _h));
}


void Screen::render(){
  _win->display();
  _win->clear();
}


void Screen::rect( float x, float y, float w, float h, uint32_t color)
{
  sf::RectangleShape rectangle(sf::Vector2f(w, h));
  rectangle.setFillColor(sf::Color(color));
  rectangle.setPosition(x, y);
  _win->draw(rectangle);
}

void Screen::disc(float x_center, float y_center, float radius, uint32_t color)
{
  sf::CircleShape shape(radius);
  shape.setFillColor(sf::Color(color));
  shape.setPosition(x_center-radius, y_center-radius);
  _win->draw(shape);
}

void Screen::background()
{
  _win->draw(*_sp_bg);
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
