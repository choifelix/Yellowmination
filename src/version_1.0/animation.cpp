
#include "animation.h"

Animation::Animation(std::string name, int h, int w, int s_u):_h(h),_w(w),_speed_update(s_u)
{

	_texture = new sf::Texture(); // Besoin de delete les news mais probleme non resolu
	_texture->loadFromFile("../../interface/image/" + name + ".png");
	_lim_top = _texture->getSize().y - _h;
	_lim_left = _texture->getSize().x - _w;
	_sprite = new sf::Sprite(*_texture, sf::IntRect(0, 0, h, w)); // Rectangle initialise en 0,0 sur la texture
	_last = false;
	_speed_tick = 0; // Compteur pour gerer la vitesse des frames
	_dir = dright; // Direction des frames
	
}

Animation::Animation(std::string name, int h, int w):_h(h),_w(w)
{

	_texture = new sf::Texture();
	_texture->loadFromFile("../../interface/image/" + name + ".png");
	_lim_top = _texture->getSize().y - _h;
	_lim_left = _texture->getSize().x - _w;
	_sprite = new sf::Sprite(*_texture, sf::IntRect(0, 0, h, w));
	_last = false;
	_speed_tick = 0;
	_speed_update = 0; // Ici, vitesse des frames aussi rapide que les 20ms du game.cpp
	_dir = dright;
	
}


void Animation::update(State val)
{

    if (_speed_tick < _speed_update)
    	_speed_tick++; // Au bout de _speed_update tick, l'animation se met a jour
	else
	{
	    int pos_top = _sprite->getTextureRect().top; // pos.top actuel
	    int pos_left = _sprite->getTextureRect().left; // pos.left actuel

	    if ( (pos_left != _lim_left) || (pos_top != _lim_top) )
	    { // Si on est pas a la fin de la texture
	    	
			if ( pos_left == _lim_left ) // Si on doit avancer de colonne en colonne
				_sprite->setTextureRect(sf::IntRect(0, pos_top+_h, _w, _h));
			else // Sinon on descend d'une ligne en revenant tout a gauche
				_sprite->setTextureRect(sf::IntRect(pos_left + _w, pos_top, _w, _h));
		}
		else if (val == ULTIMATE)
		{ // Gere l'animation de l'etat ultimate (cas special)
			_last = true;
			_sprite->setTextureRect(sf::IntRect(0, 0, _w, _h));
		}
		else if (val != DEAD)
			// A l'etat DEAD le sprite ne se repete pas
			_sprite->setTextureRect(sf::IntRect(0, 0, _w, _h));
		_speed_tick = 0;
		if (_dir == dleft)
		{
			_sprite->setOrigin(_sprite->getLocalBounds().width, 0);
			_sprite->setScale(-1,1);
		}
		else if (_dir == dright)
		{
			_sprite->setOrigin(0, 0);
			_sprite->setScale(1,1);
		}	
	}
}

void Animation::update(float _x, float _y)
{
	if (_speed_tick < 2) // 2 est la vitesse de frame choc et esquive
    	_speed_tick++;
	else
	{
		int pos_top = _sprite->getTextureRect().top;
	    int pos_left = _sprite->getTextureRect().left;

	    if ( (pos_left != _lim_left) || (pos_top != _lim_top) )
	    {
			if ( pos_left == _lim_left )
				_sprite->setTextureRect(sf::IntRect(0, pos_top+_h, _w, _h));
			else
				_sprite->setTextureRect(sf::IntRect(pos_left + _w, pos_top, _w, _h));
		}
		else
			_last = true;
		this->setPosition(_x,_y);
	}
}

void Animation::update(float _x, float _y, int relative_life)
{
	_sprite->setTextureRect(sf::IntRect(0, _h*relative_life, _w, _h));
	this->setPosition(_x,_y);
}


// Animation::~Animation()
// {
// 	delete[] _sprite;
// 	delete[] _texture;
// }

void Animation::set_texture(std::string name){
	_texture->loadFromFile(name);
	_lim_top = _texture->getSize().y - _h;
	_lim_left = _texture->getSize().x - _w;
}