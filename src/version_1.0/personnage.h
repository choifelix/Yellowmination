#ifndef PERSONNAGE_HH_
#define PERSONNAGE_HH_

#pragma once
#include "obstacle.h"
#include "animation.h"
#include "screen.h"
#include <iostream>
#include <string>
#include "audio.h"
#include <cmath>
#include <array>
#include <SFML/Graphics.hpp>

/****************************************************/
/* Classe des personnages                           */
/****************************************************/
class Personnage: public Obstacle{ // Classe virtuelle
  public:
    // Constructeurs
    Personnage(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed );
    Personnage(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed , int ult_speed,float volume);
    // Destructeur
    virtual ~Personnage(){}; // Pas de new
    // Methodes
    void draw(Screen& s, sf::Music * m); // Affichage des personnages et besoin du son pour l'ultimate
    void sound(std::string sound_type); // Sons des personnages
    virtual void animation_update() = 0; //update de l'image (sprite)
    virtual bool isAlive()=0;


    float distance(Personnage* per);

    void set_hp(int hp){_hp = hp;}
    int get_hp(){return _hp;}
    void set_atk(int atk){_atk = atk;}
    int get_atk(){return _atk;}
    void set_def(int def){_def = def;}
    int get_def(){return _def;}
    void set_range(int r){_range = r;}
    float get_range(){return _range;}
    int get_team(){return _team;}

    float get_h(){return _h;}
    float get_w(){return _w;}
    float get_radius(){return _radius;}
    float get_dodge(){return _dodge_rate;}
    void  set_dodge(float dodge){_dodge_rate = dodge;}
    //State definit dans animation.h
    State get_etat(){return _etat;}
    void  set_etat(State etat){_etat = etat;}
    std::string get_name(){return _name;} 
    void set_team(int team);

  protected:
    std::string _name; // Le nom de l'image sera name+".png"
    Audio _audio;
    int _team; // Indexation de l'equipe
    std::array<Animation,int(State::NB_STATE+3)> animations;
    // 4 animations lies au personnage et 3 d'esquive, de choc et de vie
    float _speed;
    float _h, _w;
    int _hp_max;
    int _hp;
    int _atk;
    int _def;
    float _range;
    float _radius;
    float _dodge_rate;
    State _etat;
    int _attack_frame;


};

#endif
