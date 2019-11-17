#ifndef Personnage_support_HH_
#define Personnage_support_HH_

#pragma once
#include "personnage.h"
#include "personnage_actif.h"


/****************************************************/
/* Classe des personnages supports	                */
/****************************************************/
class Personnage_support : public Personnage{
	public:
		// Constructeurs
		Personnage_support(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed,int hp_buff_inst, int atk_buff, int def_buff, int dodge_buff, int hp_buff, int speed_buff );
		Personnage_support(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed,int hp_buff_inst, int atk_buff, int def_buff, int dodge_buff, int hp_buff, int speed_buff , int ult_speed,float volume);
		// Methodes
		void interract(Personnage_actif * per);
		void effect(Personnage_actif * pers);
		void effect_negate(Personnage_actif * pers);
		bool isAlive(){return _activate;}
		void update(Personnage_actif ** ennemy_team, int nb_ennemy,Personnage_actif ** actif_list, int nb_actif);
		void constant_effect();
		void deactivate(Personnage_actif ** actif_list, int nb_actif, Personnage_actif ** ennemy_team, int nb_ennemy);
		virtual void animation_update();


		//accesseurs
		void set_activate(bool set){ _activate = set;}
		int get_cooldown(){return _cooldown;}


	private:
		
		int _timer;
		int _cooldown;
		bool _activate;
		
		bool _Buff; //true buff, false debuff team adverse
		int _hpBuff;

  		int _instant_hpBuff;
    	int _instant_atkBuff;
  		int _instant_defBuff;
  		int _instant_dodgeBuff;
  		int _speed_boost;



	
};




#endif