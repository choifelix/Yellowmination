#ifndef TEAM_HH_
#define TEAM_HH_

#pragma once
#include <SFML/Audio.hpp>
#include "personnage_support.h"

class Team{
 	public:
 		Team(int team_nb);//, Personnage_actif ** actif_list, int nb_actif, Personnage_support ** support_list, int nb_support);
  		~Team();
 		float get_x(){return _x;}
 		float get_y(){return _y;}
 		void activate_support(Personnage_actif ** actif_list, int nb_actif, Personnage_support ** support_list, int nb_support, Personnage_actif ** ennemy_team, int nb_ennemy);

 	private:
  		float _x, _y;
  		int _id;
  		int _support_point;
  		int _nb_actif;
  		int _nb_support;
  		Personnage_support ** _support_list;
  		Personnage_actif ** _actif_list;
  		//ajouter un attribut couleur en hexa
};

#endif
