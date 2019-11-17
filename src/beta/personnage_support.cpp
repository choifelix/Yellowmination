#include "personnage_support.h"
#define TIME_LIMIT 60 * 4 //4 secondes si la framerate est de 60
#define COOLDOWN 60 * 10


Personnage_support::Personnage_support(float x, float y, std::string new_name, int new_team, std::string audio_file)
:Personnage(x,y,new_name,new_team,audio_file){
	//_etat              = STATIC;
	_activate          = false;
	_timer             = 0;
	_cooldown          = COOLDOWN; //les supports sont op des le debut
	_hpBuff            = 0;
	_instant_hpBuff    = 0;
    _instant_atkBuff   = 0;
  	_instant_defBuff   = 0;
  	_instant_rangeBuff = 0;
  	_instant_dodgeBuff = 0;
  	_speed_boost       = 0;
  	_Buff              = true;
}

Personnage_support::Personnage_support(float x, float y, std::string new_name, int new_team, std::string audio_file, int ult_speed,float volume)
:Personnage(x,y,new_name,new_team,audio_file,ult_speed,volume){
	//_etat              = STATIC;
	_activate          = false;
	_timer             = 0;
	_cooldown          = COOLDOWN; //les supports sont op des le debut
	_hpBuff            = 0;
	_instant_hpBuff    = 0;
    _instant_atkBuff   = 0;
  	_instant_defBuff   = 0;
  	_instant_rangeBuff = 0;
  	_instant_dodgeBuff = 0;
  	_speed_boost       = 0;
  	_Buff              = true;
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
		//_x += -n[0]*sqrt(delta/2);
		//_y += -n[1]*sqrt(delta/2);

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
	//std::cout << "entre dans effect.  team :  " << pers->get_team() << " et " << this->_team << std::endl;
	if( (pers->get_team() == this->_team) and _Buff ){
		//std::cout << "if meme team" << std::endl;
		pers->set_hp(pers->get_hp()  + _instant_hpBuff);
		pers->set_def(pers->get_def()+ _instant_defBuff);
		pers->set_atk(pers->get_atk()+ _instant_atkBuff);
		pers->set_range(pers->get_range() + _instant_rangeBuff);
		pers->set_dodge(pers->get_dodge() + _instant_dodgeBuff);
		
	}
	else if ( (pers->get_team() != this->_team) and !_Buff)  {
		//std::cout << "else if not meme team " << std::endl;

		pers->set_def(pers->get_def() - _instant_defBuff);

		if(pers->get_atk() - _instant_atkBuff < 1)
			pers->set_atk(1);
		else
			pers->set_atk(pers->get_atk() - _instant_atkBuff);
		
		if ( pers->get_hp() - _instant_hpBuff <= 0 )
			pers->set_hp(1);
		else
			pers->set_hp(pers->get_hp()   - _instant_hpBuff);

		if(pers->get_range() - _instant_rangeBuff <= 1 + 100)
			pers->set_range(1+ 100);
		else
			pers->set_range(pers->get_range() - _instant_rangeBuff);

		if(pers->get_dodge() - _instant_dodgeBuff < 0)
			pers->set_dodge(0);
		else
			pers->set_dodge(pers->get_dodge() - _instant_dodgeBuff);

		//pers.set_range(pers.get_range() - _range);
	}

}

void Personnage_support::effect_negate(Personnage_actif * pers){
	if( (pers->get_team() != this->_team) and !_Buff){
		pers->set_hp(pers->get_hp()  + _instant_hpBuff);
		pers->set_def(pers->get_def()+ _instant_defBuff);
		pers->set_atk(pers->get_atk()+ _instant_atkBuff);
		pers->set_range(pers->get_range() + _instant_rangeBuff);
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

		if(pers->get_range() - _instant_rangeBuff <= 1 + 100)
			pers->set_range(1+ 100);
		else
			pers->set_range(pers->get_range() - _instant_rangeBuff);

		if(pers->get_dodge() - _instant_dodgeBuff < 0)
			pers->set_dodge(0);
		else
			pers->set_dodge(pers->get_dodge() - _instant_dodgeBuff);

		//pers.set_range(pers.get_range() - _range);
	}

}

void Personnage_support::update(Personnage_actif ** ennemy_team, int nb_ennemy,Personnage_actif ** actif_list, int nb_actif){
	//std::cout << _name << " " << _cooldown << std::endl;
	
	if(this->isAlive()){
		
		for(int i = 0 ; i < nb_ennemy ; i++)
			if(ennemy_team[i]->isAlive())
				 this->interract(ennemy_team[i]);


		if(_timer > TIME_LIMIT or _hp <= 0){
			this->deactivate(actif_list,nb_actif, ennemy_team, nb_ennemy);
			_timer = 0;
			_hp = _hp_max;
		}
		_timer ++;
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
	if(this->isAlive()){
		animations[_etat].update(_etat);
		//std::cout << _etat << " _etat " << std::endl;
	}
}











