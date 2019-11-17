#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	Animation(std::string name, int h, int w);
	//~Animation();
	void update();
	void setPosition(float _x, float _y){_sprite->setPosition(_x,_y);}
	sf::Sprite& getSprite() const { return *_sprite;}
	void set_h(int h) {_h = h;}
	void set_w(int w) {_w = w;}
private:
	sf::Sprite* _sprite;
	sf::Texture* _texture;
	int _h;
	int _w;
	int _nb_sprite;
};