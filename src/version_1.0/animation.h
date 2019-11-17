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


/****************************************************/
/* Classe qui gere l'animation                      */
/****************************************************/
class Animation
{
public:
	Animation() = default;
	// Constructeurs
	Animation(std::string name, int h, int w);
	Animation(std::string name, int h, int w, int s_u);
	// Destructeurs
	//~Animation(); // Probleme non resolu du destructeur
	// Methodes
	void update(State val); // Update une animation qui depend de l'etat
	void update(float _x, float _y); // Update une animation externe cree par le perso
	void update(float _x, float _y, int relative_life); // Update une animation, fait pour des barres de progression (vie par exemple)
	// Les updates des etats se font en boucle donc le reset du intrect se fait dans la methode. Le reste ne se fait pas en boucle.
	void reset_rectint() { _sprite->setTextureRect(sf::IntRect(0, 0, _w, _h));}
	void setPosition(float _x, float _y){_sprite->setPosition(_x,_y);}
	sf::Sprite& getSprite() const { return *_sprite;}
	sf::Texture& getTexture() const { return *_texture;}
	int get_h() {return _h;}
	int get_w() {return _w;}
	void set_h(int h) {_h = h;}
	void set_w(int w) {_w = w;}
	bool get_last() const {return _last;}
	void set_last(bool b){_last = b;}
	void set_dir(int dir){_dir = dir;}
	void set_texture( std::string name);

private:
	sf::Sprite* _sprite;
	sf::Texture* _texture;
	int _h; // hauteur du sprite
	int _w; // largeur du sprite
	int _nb_sprite; // nombre de sprite
	bool _last; // savoir si le dernier sprite est atteint ou pas
	int _lim_top; // limite de deplacement du top de la texture
	int _lim_left; // limite de deplacement du left de la texture
	int _speed_tick; // tick pour gerer vitesse des frames
	int _speed_update; // int a atteindre pour speed_tick
	int _dir; // si l'animation doit etre tourne vers la gauche ou la droite
};

#endif