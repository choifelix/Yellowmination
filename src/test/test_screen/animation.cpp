#include "animation.h"

Animation::Animation(std::string name, int h, int w):_h(h),_w(w)
{

	_texture = new sf::Texture();
	_texture->loadFromFile(name + ".png");
	_sprite = new sf::Sprite(*_texture, sf::IntRect(0, 0, w, h));
}

void Animation::update()
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
		_sprite->setTextureRect(sf::IntRect(pos_left - _w, pos_top, _w, _h));

	_sprite->setOrigin(_sprite->getLocalBounds().width, 0);
	_sprite->setScale(-1,1);
}


// Animation::~Animation()
// {
// 	delete[] _sprite;
// 	delete[] _texture;
// }