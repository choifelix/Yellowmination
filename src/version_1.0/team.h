#ifndef TEAM_HH_
#define TEAM_HH_

#pragma once
#include <SFML/Audio.hpp>
#include "personnage_support.h"

/****************************************************/
/* Classe des equipes				                */
/****************************************************/
class Team{
 	public:
 		Team(int team_nb):_id(team_nb){}
  		~Team();

 		void activate_support(Personnage_actif ** actif_list, int nb_actif, Personnage_support ** support_list, int nb_support, Personnage_actif ** ennemy_team, int nb_ennemy);

 	private:
  		int _id;
  		int _nb_actif;
  		int _nb_support;
  		Personnage_support ** _support_list;
  		Personnage_actif ** _actif_list;
  		//ajouter un attribut couleur en hexa
};

#endif
