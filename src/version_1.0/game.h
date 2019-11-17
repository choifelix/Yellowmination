#ifndef _GAME_H
#define _GAME_H

#pragma once
#include "screen.h"
#include "obstacle.h"
#include "team.h"
#include "wall.h"
#include "personnage_actif.h"
#include "personnage_support.h"
#include <vector>
#include <ctime>
#include <thread>        
#include <chrono>
#include "path.h"
#include <SFML/Graphics.hpp>

/****************************************************/
/* Classe qui joue le jeu                           */
/****************************************************/
class Game{
 public :
 Game();
  ~Game();
  bool play();        //joue l'animation
 private:
  sf::Music * _music;
  std::string _music_name;
  Screen _screen;     //ecran d'affichage
  bool _play;         //attribut permettant de savoir si le jeu continu ou s'arrete
  std::vector<Wall *> _Walls; //voila, on a mis in container !!
  Personnage_actif ** _team1_list;
  Personnage_actif ** _team2_list;
  Personnage_support ** _support_team1;
  Personnage_support ** _support_team2;
  Team * _team1;
  Team * _team2;
  int _alive_team1;         //nombre de personnages en vie
  int _alive_team2;
  //std::vector<Team&> team_list;
private:
  void initGame();               //initialise le jeu 
  void handleEvent (); //permet d'interagir avec le clavier ->juste quitter avec q
  void update_music();
  
  
};
#endif
