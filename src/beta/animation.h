#ifndef _ANIMATION_H
#define _ANIMATION_H

#pragma once
#include <iostream>

#define dleft 0
#define dright 1

enum State {MOBILE,STATIC,ATTACK,ULTIMATE,DEAD,NB_STATE};

#define TELEPORT 5
#define SHOCK 6
#define LIFE 7

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	Animation(std::string name, int h, int w);
	Animation(std::string name, int h, int w, int s_u);
	//~Animation();
	void update(State val); // update une animation qui depend de l'etat
	void update(float _x, float _y);
	void setPosition(float _x, float _y){_sprite->setPosition(_x,_y);}
	sf::Sprite& getSprite() const { return *_sprite;}
	sf::Texture& getTexture() const { return *_texture;}
	void reset_rectint() { _sprite->setTextureRect(sf::IntRect(0, 0, _w, _h));}
	void set_h(int h) {_h = h;}
	void set_w(int w) {_w = w;}
	bool get_last() const {return _last;}
	void set_last(bool b){_last = b;}
	void set_dir(int dir){_dir = dir;}

private:
	sf::Sprite* _sprite;
	sf::Texture* _texture;
	int _h;
	int _w;
	int _nb_sprite;
	bool _last;
	int _speed_tick;
	int _speed_update;
	int _dir;
	bool activate_col;
	bool activate_tp;
};

#endif