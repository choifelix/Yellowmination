#ifndef Personnage_actif_HH_
#define Personnage_actif_HH_

#pragma once
#include "personnage.h"



class Personnage_actif : public Personnage{
	public:
		Personnage_actif(float x, float y, std::string new_name, int new_team, std::string audio_file);
		Personnage_actif(float x, float y, std::string new_name, int new_team, std::string audio_file, int ult_speed,float volume);
		//Personnage_actif() = default;
		//~Personnage_actif(){}
		void draw(Screen& s, sf::Music *m);
		void update(Screen& s,Personnage_actif ** ennemy_team, int nb_ennemy);
		void update_state();
		void attack(Screen& s,Personnage_actif* per);
		bool isAlive();
		void interract(Screen& s,Personnage_actif* per);
		void behavior(Screen& s,Personnage_actif ** ennemy_team, int nb_ennemy);
		void deplace();
		void speed_update();
		int closest_ennemy(Personnage_actif ** ennemy_team, int nb_ennemy);
		virtual void animation_update();
   		void  anim_dir(int dir);



		//accesseurs
		float get_vx(){return _vx;}
	    void set_vx(float vx){_vx = vx;}
	    float get_vy(){return _vy;}
	    void set_vy(float vy){_vy = vy;}
	    int get_mana(){return _mana;}
	    void set_mana(int nb){_mana = nb;}

	private:
		int _mana;
		float _vx, _vy;
		int _reload;
		int _ult_cooldown;
	    bool activate_col;
	    bool activate_tp;
	    int _x_shock;
	    int _y_shock;
	    int _x_tp;
	    int _y_tp;
	    int shock_count;
	    int tp_count;

	
};




#endif