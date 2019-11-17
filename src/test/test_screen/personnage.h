#ifndef Personnage_HH_
#define Personnage_HH_

#pragma once
#include "obstacle.h"
#include "animation.h"
//#include "team.h"
//#include <SFML/Audio.hpp>
#include "screen.h"
#include <iostream>
#include <string>

enum State {MOBILE,STATIC,ATTACK,ULTIMATE,DEAD,NB_STATE};


class Personnage: public Obstacle{
  public:
    Personnage(float x, float y,float h, float w, std::string new_name/*,Team& new_team, std::string audio_file*/);
    //~Personnage();
    void draw(Screen& s) const;
    /*void interract(Obstacle& obs);
    void sound();
    void special_sound();*/
    void update(); //tout les update liee au personnage -> ulti, mort, etc
    void setState(State tmp){_etat = tmp;}

  private:
    std::string _name; //image sera name.gif
    /*sf::SoundBuffer _buffer;
    sf::Sound _sound;
    Team& _team;*/

    Animation animations[int(State::NB_STATE)];
    float _h, _w;
    float _vx, _vy;
    State _etat;

};

#endif
