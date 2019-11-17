#include "personnage_actif.h"
#define screen_w 1280 
#define screen_h 720
#define BORD 10
#define RELOAD_TIME 30
#define ULTIMATE_COST 4
#define ULT_COOLDOWN 60 * 20
#define ATTACK_FRAME 5

Personnage_actif::Personnage_actif(float x, float y, std::string new_name, int new_team, std::string audio_file)
:Personnage(x,y,new_name,new_team,audio_file){
	std::cout << "actif init" << std::endl;
	//_etat    = STATIC;
	_vx      = 0; //set up de test
	_vy      = 0;
	_mana    = 0;
	_reload  = 0;
	_dodge_rate = 0.2;
	_ult_cooldown = ULT_COOLDOWN;
	activate_col = false;
	activate_tp = false;
	_x_shock = -100;
	_y_shock = -100;
	shock_count = 0;
	tp_count = 0;
	_x_tp= -100;
	_y_tp= -100;
  	animations[MOBILE] = Animation(new_name+std::to_string(MOBILE), _h, _w);
  	animations[ATTACK] = Animation(new_name+std::to_string(ATTACK), _h, _w);
  	animations[DEAD] = Animation("dead1", 125, 550, 1);
  	animations[TELEPORT] = Animation("teleport", _h, _w, 1);
  	animations[SHOCK] = Animation("shock", _h, _w);
	std::cout << "actif init fin" << std::endl;

}

Personnage_actif::Personnage_actif(float x, float y, std::string new_name, int new_team, std::string audio_file, int ult_speed,float volume)
:Personnage(x,y,new_name,new_team,audio_file,ult_speed,volume){
	std::cout << "actif init" << std::endl;
	//_etat    = STATIC;
	_vx      = 0; //set up de test
	_vy      = 0;
	_mana    = 0;
	_reload  = 0;
	_dodge_rate = 0.2;
	_ult_cooldown = ULT_COOLDOWN;
	activate_col = false;
	activate_tp = false;
	_x_shock = -100;
	_y_shock = -100;
	shock_count = 0;
	tp_count = 0;
	_x_tp= -100;
	_y_tp= -100;
  	animations[MOBILE] = Animation(new_name+std::to_string(MOBILE), _h, _w, 5);
  	animations[ATTACK] = Animation(new_name+std::to_string(ATTACK), _h, _w);
  	animations[DEAD] = Animation("dead1", 125, 550, 1);
  	animations[TELEPORT] = Animation("teleport", _h, _w, 1);
  	animations[SHOCK] = Animation("shock", _h, _w);
	std::cout << "actif init fin" << std::endl;

}

void Personnage_actif::draw(Screen& s, sf::Music * m)  {
	if(/*_etat != DEAD and*/ _etat != ULTIMATE ){
		//std::cout<< _etat << std::endl;
		s.display( animations[LIFE].getSprite() )
		s.display( animations[_etat].getSprite() );
	}
	else if (_etat == ULTIMATE)
	{
		std::cout<< _etat << std::endl;
		m->pause();
		_audio.sound_ultimate();
		// Arrete le temps pour ne voir que l'ultimate -> while interne
		//std::cout << "ultimate animation" << std::endl;
		sf::Clock clock;
		int close = 0;

		while(!close)
		{	
			//std::cout << "displaying ultimate " << close << std::endl;
			s.SetFramerateLimit(60);
     		s.render();
			s.display( animations[_etat].getSprite() );
			if(clock.getElapsedTime().asSeconds() > 0.1f)
			{
				this->animation_update();
        		clock.restart();
			}

    		if (animations[ULTIMATE].get_last() == true){
    			close = 1;
    			animations[ULTIMATE].set_last(false);
    		}

    		//pouvoir fermer quand meme
    		sf::Event event;
		 	while (s.pollEvent(event)){
		    	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
		    		close = 1;
			  		s.close();
			  		//_play = false;
			  	}
		    }
      	}
      	m->play();
      	this->set_etat(STATIC);

	}

	if(activate_tp){
  		s.display( animations[TELEPORT].getSprite() );
  		if(animations[TELEPORT].get_last() == true)
  		{	
  			std::cout << "testtp" << std::endl;
  			activate_tp = false;
  			animations[TELEPORT].set_last(false);
  			animations[TELEPORT].reset_rectint();
  		}
  	}

  	if(activate_col){
  		//std::cout << " DISPLAYIN SHOCK" << std::endl;
  		s.display( animations[SHOCK].getSprite() );
  		if(animations[SHOCK].get_last() == true)
  		{	
  			std::cout << "testcol" << std::endl;
  			activate_col = false;
  			animations[SHOCK].set_last(false);
  			animations[SHOCK].reset_rectint();
  		}

  	}
	
	//s.disc(_x+ _radius,_y + _radius,_radius);
}

bool Personnage_actif::isAlive(){
	if(_etat != DEAD)
		return true;
	else
		return false;
}


void Personnage_actif::attack(Screen& s,Personnage_actif * per){
	if(_reload > RELOAD_TIME){
		_etat = ATTACK;
		float dodge = float(rand())/float(RAND_MAX);
		//std::cout << dodge << std::endl;
		if (dodge < per->get_dodge()){
			_audio.dodge_sound();
			// draw(s,5);
			// animations[TELEPORT].update(_x,_y);
			//if(tp_count == 0){
				activate_tp = true;
				_x_tp = _x;
				_y_tp = _y;
			//}


			int x = rand()%(screen_w - 20) + 10;
			int y = rand()%(screen_h - 20) + 10;
			per->set_position(x ,y );

			// draw(s,5);
			// animations[TELEPORT].update(_x,_y);
		}
		else{
			int damage = _atk - per->get_def();

			if(damage < 1)
				damage = 1;

			per->set_hp(per->get_hp() - damage);
			_mana++;
		}
		_reload = 0;
	}
}


void Personnage_actif::update_state(){
	/*a completer*/
	if(this->isAlive()){
		if(_hp <= 0){
			if(_etat != DEAD){
				_audio.sound_death();
			}
			_etat = DEAD;
		}
		else if (_etat == ULTIMATE){
			if(_vx + _vy == 0 and _etat != ATTACK){
				_etat = STATIC;
			}
			else if( _etat != ATTACK)
				_etat = MOBILE;
		}

		else if(_mana > ULTIMATE_COST and _ult_cooldown > ULT_COOLDOWN){
			if(_etat != ULTIMATE){
				std::cout << "ultimate" << std::endl;
				//_audio.sound_ultimate();
			}
			_etat = ULTIMATE;
			_mana -= ULTIMATE_COST;
			_ult_cooldown = 0;
		}
		else if ( _vx + _vy != 0 and _etat != ATTACK){
			_etat = MOBILE;
		}

		if(_vx + _vy == 0 and _etat != ATTACK){
			_etat = STATIC;
		}

		if(_etat == ATTACK and _attack_frame >= ATTACK_FRAME){
			_attack_frame = 0;
			if(_vx + _vy != 0)
				_etat = MOBILE;
			else
				_etat = STATIC;
		}
		else if (_etat == ATTACK)
			_attack_frame++;


		//modif position
		_x += _vx;
		_y += _vy;
	}
	//std::cout << " fin update state" << std::endl;
}


void Personnage_actif::interract(Screen& s,Personnage_actif * per){
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
		x  +=  n[0]*sqrt(delta/2);
		y  +=  n[1]*sqrt(delta/2);
		_x += -n[0]*sqrt(delta/2);
		_y += -n[1]*sqrt(delta/2);

		per->set_position(x - radius,y -radius);

		//dessiner le shock
		// int x_shock;
		// int y_shock;

		//if(shock_count == 0){
			_x_shock = _x + (x - _x)/2 ;
			_y_shock = _y + (y - _y)/2 ;

			activate_col = true;
		//}

		// draw(s,6);

		// animations[SHOCK].update(x_shock,y_shock);



		//decomposition des vitesses sur la nouvelle base orthonormee (n,g)

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



void Personnage_actif::behavior(Screen& s,Personnage_actif ** ennemy_team, int nb_ennemy){
	int alive = 0;
	for(int i = 0 ; i < nb_ennemy ; i++)       //pour ne pas avoir a faire ca,
		if( ennemy_team[i]->isAlive() )        // on aurait pu avoir un vecteur
			alive++ ;                          // des ennemis en vie

	if( alive != 0){

		int ennemy_memory = closest_ennemy(ennemy_team,nb_ennemy);
		
		//modif vitesse vers l'ennemi le plus proche
		float vx = ennemy_team[ennemy_memory]->get_vx();
		float vy = ennemy_team[ennemy_memory]->get_vy();
		float x  = ennemy_team[ennemy_memory]->get_x();
		float y  = ennemy_team[ennemy_memory]->get_y();

		float dy = y - _y;
		float dx = x - _x;
		float dt =0.05;
		float f =0.4;

		float frac = dx/dy;

		_vx += dx/fabs(dx) * _speed * dt;
		_vy += dy/fabs(dy) * _speed * dt;
		

		//###### attacking ######

		if(this->distance(ennemy_team[ennemy_memory]) <= _range){
			this->attack(s,ennemy_team[ennemy_memory]);
			std::cout << "attack" << std::endl;
		}
	}
	else{
		_vx = 0;
		_vy = 0;
	}
}


void Personnage_actif::update(Screen& s,Personnage_actif ** ennemy_team, int nb_ennemy){
	//std::cout << _name << _hp << std::endl;
	update_state();
	if(this->isAlive()){
		if (_ult_cooldown <= ULT_COOLDOWN){
			_ult_cooldown++;
		}

		int r  =rand()%nb_ennemy;
		if(_etat == ULTIMATE){
			for(int i = 0; i<nb_ennemy ; i++){
				if(ennemy_team[(i+r)%nb_ennemy]->isAlive()){
					ennemy_team[(i+r)%nb_ennemy]->set_hp(ennemy_team[(i+r)%nb_ennemy]->get_hp()/2);
				}
			}
		}

		if(_reload <= RELOAD_TIME)
			_reload++;

		behavior(s,ennemy_team, nb_ennemy);
		for(int i = 0 ; i < nb_ennemy ; i++){
			if(ennemy_team[i]->isAlive())
				 this->interract(s,ennemy_team[i]);			
		}
		float dt =0.01;
		this->speed_update();
		this->deplace();
		if(_etat != ULTIMATE){
			animations[_etat].setPosition(_x,_y);
		}

		animations[TELEPORT].setPosition(_x_tp,_y_tp);
		animations[SHOCK].setPosition(_x_shock,_y_shock);
	}
	else{
		animations[DEAD].setPosition(_x,_y);
	}
	//std::cout << "fin update perso actif" << std::endl;
}



void Personnage_actif::deplace(){
	float delta_t = 0.35;
	_x += delta_t * _vx; 
	_x += delta_t * _vy; 
}


void Personnage_actif::speed_update(){
	float norm = sqrt( pow(_vx,2) + pow(_vy,2) );
	float ACC = 1.5;
	float delta_t = 0.35;
	if( norm < 0.005 ){
		_vx = 0;
		_vy = 0;
	}
	/*else
		_vx -= (ACC* delta_t* (_vx/norm ) );
		_vy -= (ACC* delta_t* (_vy/norm ) );
*/
}

int Personnage_actif::closest_ennemy(Personnage_actif ** ennemy_team, int nb_ennemy){
	float distance = 100000;
	int ennemy_memory;
	for(int i = 0 ; i < nb_ennemy ; i++){
		if( ennemy_team[i]->isAlive() ){
			//=std::cout << this->distance(ennemy_team[i]) << std::endl;
			if (distance > this->distance(ennemy_team[i])){
				distance = this->distance(ennemy_team[i]);
				ennemy_memory = i;
			}	
		}
	}
	return ennemy_memory;
}

void Personnage_actif::animation_update(){
	if(this->isAlive()){
		if(animations[ATTACK].get_last() == true){
			this->set_etat(MOBILE);
			//std::cout << _etat << " _etat = STATIC" << std::endl;
		}
		if( _vx < 0)
			this->anim_dir(dleft);
		else
			this->anim_dir(dright);
		animations[_etat].update(_etat);
		//std::cout << _etat << " _etat " << std::endl;


		if(activate_tp){
      		animations[TELEPORT].update(_x_tp,_y_tp);
		}

      	if(activate_col){
      		std::cout << "UPDATING SHOCK" << std::endl;
      		animations[SHOCK].update(_x_shock,_y_shock);
      	}
	}
	else{
		animations[DEAD].update(DEAD);
	}
}


void Personnage_actif::anim_dir(int dir)
{
	animations[STATIC].set_dir(dir);
	animations[MOBILE].set_dir(dir);
	animations[ATTACK].set_dir(dir);
}







