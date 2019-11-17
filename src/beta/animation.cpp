#include "animation.h"

Animation::Animation(std::string name, int h, int w, int s_u):_h(h),_w(w),_speed_update(s_u)
{

	_texture = new sf::Texture();
	_texture->loadFromFile("../../interface/image/" + name + ".png");
	_sprite = new sf::Sprite(*_texture, sf::IntRect(0, 0, h, w));
	_last = false;
	_speed_tick = 0;
	_dir = dright;
	
}

Animation::Animation(std::string name, int h, int w):_h(h),_w(w)
{

	_texture = new sf::Texture();
	_texture->loadFromFile("../../interface/image/" + name + ".png");
	_sprite = new sf::Sprite(*_texture, sf::IntRect(0, 0, h, w));
	_last = false;
	_speed_tick = 0;
	_speed_update = 0;
	_dir = dright;
	
}


void Animation::update(State val)
{

    if (_speed_tick < _speed_update)
    	_speed_tick++;
	else
	{
		// if(_last)
		// 	_last = false;
	    int pos_top = _sprite->getTextureRect().top;
	    int pos_left = _sprite->getTextureRect().left;
	    int lim_top = _texture->getSize().y - _h;
	    int lim_left = _texture->getSize().x - _w;

	    if ( (pos_left != lim_left) || (pos_top != lim_top) )
	    {
	    	std::cout << "not end " <<  _last << ' ' << pos_top << ' ' << pos_left << " if " << std::endl;
			if ( pos_left == lim_left )
				_sprite->setTextureRect(sf::IntRect(0, pos_top+_h, _w, _h));
			else
				_sprite->setTextureRect(sf::IntRect(pos_left + _w, pos_top, _w, _h));
		}
		else if (val == ULTIMATE)
		{
	    	std::cout << "end ult avant " << _last << ' ' << pos_top << ' ' << pos_left << "positions " << std::endl;
			_last = true;
			_sprite->setTextureRect(sf::IntRect(0, 0, _w, _h));
			std::cout << "end ult apres " << _last << ' ' << _sprite->getTextureRect().top << ' ' << _sprite->getTextureRect().left << "positions " << std::endl;
		}
		else if (val != DEAD)
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
	if (_speed_tick < 2)
    	_speed_tick++;
	else
	{
		int pos_top = _sprite->getTextureRect().top;
	    int pos_left = _sprite->getTextureRect().left;
	    int lim_top = _texture->getSize().y - _h;
	    int lim_left = _texture->getSize().x - _w;

	    if ( (pos_left != lim_left) || (pos_top != lim_top) )
	    {
			if ( pos_left == lim_left )
				_sprite->setTextureRect(sf::IntRect(0, pos_top+_h, _w, _h));
			else
				_sprite->setTextureRect(sf::IntRect(pos_left + _w, pos_top, _w, _h));
		}
		else
			_last = true;
		this->setPosition(_x,_y);
	}
}


// Animation::~Animation()
// {
// 	delete[] _sprite;
// 	delete[] _texture;
// }