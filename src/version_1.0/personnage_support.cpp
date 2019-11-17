#include "personnage_support.h"
#define TIME_LIMIT 60 * 4 //4 secondes si la framerate est de 60
#define COOLDOWN 60 * 20


Personnage_support::Personnage_support(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed,int hp_buff_inst, int atk_buff, int def_buff, int dodge_buff, int hp_buff, int speed_buff )
:Personnage(x,y,new_name,new_team,audio_file,hp,atk,def,dodge,radius,speed){
	
	// variables sytemes
	_activate          = false;
	_timer             = 0;
	_cooldown          = COOLDOWN; //les supports sont op des le debut
	_Buff              = true;


	//variables d'effet
	_hpBuff            = hp_buff;
	_instant_hpBuff    = hp_buff_inst;
    _instant_atkBuff   = atk_buff;
  	_instant_defBuff   = def_buff;
  	_instant_dodgeBuff = dodge_buff;
  	_speed_boost       = speed_buff;
  	
}

Personnage_support::Personnage_support(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed,int hp_buff_inst, int atk_buff, int def_buff, int dodge_buff, int hp_buff, int speed_buff , int ult_speed,float volume)
:Personnage(x,y,new_name,new_team,audio_file,hp,atk,def,dodge,radius,speed,ult_speed,volume){
	
	// variables sytemes
	_activate          = false;
	_timer             = 0;
	_cooldown          = COOLDOWN; //les supports sont op des le debut
	_Buff              = true;


	//variables d'effet
	_hpBuff            = hp_buff;
	_instant_hpBuff    = hp_buff_inst;
    _instant_atkBuff   = atk_buff;
  	_instant_defBuff   = def_buff;
  	_instant_dodgeBuff = dodge_buff;
  	_speed_boost       = speed_buff;
}



void Personnage_support::interract(Personnage_actif * per){
	static const float damping = 0.95;

	float radius = per->get_radius();
	float x = per->get_x();
	x += radius;
	float y = per->get_y();
	y+= radius;
	float vx = per->get_vx();
	float vy = per->get_vx();

	if(this->distance(per) < 2*_radius){
		std::cout << std::endl << "collision" << std::endl << std::endl;
		_audio.shock_sound();

		//vecteur n normal au plan de collision
		float n[2] ;
		n[0] = x - _x;
		n[1] = y - _y;

		//normalisation de n
		float norm = sqrt( pow(x - _x,2) + pow(y - _y,2) ) ;
		n[0] = n[0]/ norm ;
		n[1] = n[1]/ norm ;

		//rotation pi/2 sens direct du vecteur n par exemple pour le vecteur tangentiel normalisé g
		float g[2];
		g[0] = n[1];
		g[1] = -n[0];

		//si les boules se superposent, on les replace en position de contact strict (ici, le vecteur g est inutile)
		float delta = 2*_radius - this->distance(per);
		x  +=  n[0]*sqrt(delta);
		y  +=  n[1]*sqrt(delta);
		

		per->set_position(x - radius,y -radius);

		//decomposition des vitesses sur la nouvelle base orthonormee (n,g)
		float _vx = 0;
		float _vy = 0;

		float self_vn_B2 = _vx * n[0] + _vy * n[1];
		float self_vg_B2 = _vx * g[0] + _vy * g[1];
		float per_vn_B2  =  vx * n[0] +  vy * n[1];
		float per_vg_B2  =  vx * g[0] +  vy * g[1];

		//echange des composantes normales ; les composantes tangentielles sont conservees

		float save = per_vn_B2;
		per_vn_B2 = self_vn_B2;
		self_vn_B2 = save;

		//modification des vitesses en bases(x,y)
		 vx = n[0] * per_vn_B2  + g[0] * per_vg_B2;
		 vy = n[1] * per_vn_B2  + g[1] * per_vg_B2;
		_vx = n[0] * self_vn_B2 + g[0] *self_vg_B2;
		_vy = n[1] * self_vn_B2 + g[1] *self_vg_B2;

		per->set_vx(vx * damping);
		per->set_vy(vy * damping);
	}
}

void Personnage_support::effect(Personnage_actif * pers){

	if( (pers->get_team() == this->_team) and _Buff ){

		pers->set_hp(pers->get_hp()  + _instant_hpBuff);
		pers->set_def(pers->get_def()+ _instant_defBuff);
		pers->set_atk(pers->get_atk()+ _instant_atkBuff);
		pers->set_dodge(pers->get_dodge() + _instant_dodgeBuff);
	}
	else if ( (pers->get_team() != this->_team) and !_Buff)  {

		pers->set_def(pers->get_def() - _instant_defBuff);

		if(pers->get_atk() - _instant_atkBuff < 1)
			pers->set_atk(1);
		else
			pers->set_atk(pers->get_atk() - _instant_atkBuff);
		
		if ( pers->get_hp() - _instant_hpBuff <= 0 )
			pers->set_hp(1);
		else
			pers->set_hp(pers->get_hp()   - _instant_hpBuff);

		if(pers->get_dodge() - _instant_dodgeBuff < 0)
			pers->set_dodge(0);
		else
			pers->set_dodge(pers->get_dodge() - _instant_dodgeBuff);
	}
}

void Personnage_support::effect_negate(Personnage_actif * pers){
	if( (pers->get_team() != this->_team) and !_Buff){
		pers->set_hp(pers->get_hp()  + _instant_hpBuff);
		pers->set_def(pers->get_def()+ _instant_defBuff);
		pers->set_atk(pers->get_atk()+ _instant_atkBuff);
		pers->set_dodge(pers->get_dodge() + _instant_dodgeBuff);
		
	}
	else if ( (pers->get_team() == this->_team) and _Buff )  {

		pers->set_def(pers->get_def() - _instant_defBuff);

		if(pers->get_atk() - _instant_atkBuff < 1)
			pers->set_atk(1);
		else
			pers->set_atk(pers->get_atk() - _instant_atkBuff);
		
		if ( pers->get_hp() - _instant_hpBuff <= 0 )
			pers->set_hp(1);
		else
			pers->set_hp(pers->get_hp()   - _instant_hpBuff);

		if(pers->get_dodge() - _instant_dodgeBuff < 0)
			pers->set_dodge(0);
		else
			pers->set_dodge(pers->get_dodge() - _instant_dodgeBuff);
	}
}

void Personnage_support::update(Personnage_actif ** ennemy_team, int nb_ennemy,Personnage_actif ** actif_list, int nb_actif){
	if(this->isAlive()){
		
		for(int i = 0 ; i < nb_ennemy ; i++){
			if(ennemy_team[i]->isAlive())
				 this->interract(ennemy_team[i]);
		}

		if(_timer > TIME_LIMIT or _hp <= 0){
			this->deactivate(actif_list,nb_actif, ennemy_team, nb_ennemy);
			_timer = 0;
			_hp = _hp_max;
		}
		_timer ++;
		animations[STATIC].setPosition(_x,_y);
	}
	else
		_cooldown++;
					
		
}

void Personnage_support::constant_effect(){
	//vitesse ou guerison a faire
}


void Personnage_support::deactivate(Personnage_actif ** actif_list, int nb_actif, Personnage_actif ** ennemy_team, int nb_ennemy){
	set_activate(false);
	//son equipe -> debuff
    for(int i = 0 ; i< nb_actif ; i++){      // effet instantanné du support
        if ( actif_list[i]->isAlive())
            this->effect_negate(actif_list[i]);
        actif_list[i]->set_mana(0);
    }

    //equipe adverse -> buff
    for( int i=0 ; i < nb_ennemy ; i++){
        if ( ennemy_team[i]->isAlive())
            this->effect_negate(ennemy_team[i]);
    }
    _cooldown = 0; //reitnitialise le cooldown

}


void Personnage_support::animation_update(){
	if(this->isAlive())
	{
		animations[_etat].update(_etat);
		animations[LIFE].update(_x-animations[LIFE].get_h(), _y, int(_hp_max/_hp));
	}
	
}











