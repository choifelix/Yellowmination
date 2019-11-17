#include "personnage.h"
#define screen_w 1280 
#define screen_h 720

Personnage::Personnage(float x, float y, std::string new_name, int new_team, std::string audio_file)
:Obstacle(x,y),_audio(audio_file,new_team,100),_h(100),_w(100),_radius(50),_team(new_team){	
	_etat  = STATIC;
	_name  = new_name;
	_hp_max= 50;
	_hp    = _hp_max;
	_atk   = 1;
	_def   = 0;
	_speed = 1;
	_range = 5 + 100; // il faut addition 2*RADIUS d'ou "+100"
	_attack_frame = 0;
	//std::cout << "before animation" << std::endl;
  	//animations[MOBILE] = Animation(new_name+std::to_string(MOBILE), _h, _w);
  	animations[STATIC] = Animation(new_name+std::to_string(STATIC), _h, _w);
  	//animations[ATTACK] = Animation(new_name+std::to_string(ATTACK), _h, _w);
  	animations[ULTIMATE] = Animation(new_name+std::to_string(ULTIMATE), 720, 1280);
  	

  	//animations[DEAD] = Animation("death", 284, 1114);
  	//animations[TELEPORT] = Animation("teleport", _h, _w);
  	//animations[SHOCK] = Animation("shock", _h, _w);

  	//std::cout << "animation etape 1" << std::endl;
  	//animations[_etat].setPosition(_x,_y);
  	//animations[ULTIMATE] = Animation(new_name+std::to_string(3), _h, _w);
  	//std::cout << "animation etape 2" << std::endl;
  	// for(int i = 0; i < 4; i++)
  	// {
  	// 	animations[i] = Animation(new_name+std::to_string(i+1), h, w);
  	// 	animations[i].setPosition(_x,_y);
  	// }
  	animations[ULTIMATE].setPosition(0,0);
}

Personnage::Personnage(float x, float y, std::string new_name, int new_team, std::string audio_file, int ult_speed, float volume)
:Obstacle(x,y),_audio(audio_file,new_team, volume),_h(100),_w(100),_radius(50),_team(new_team){	
	_etat  = STATIC;
	_name  = new_name;
	_hp_max= 10;
	_hp    = _hp_max;
	_atk   = 1;
	_def   = 0;
	_speed = 1;
	_range = 5 + 100; // il faut addition 2*RADIUS d'ou "+100"
	_attack_frame = 0;
	//std::cout << "before animation" << std::endl;
  	//animations[MOBILE] = Animation(new_name+std::to_string(MOBILE), _h, _w, 6);
  	animations[STATIC] = Animation(new_name+std::to_string(STATIC), _h, _w);
  	//animations[ATTACK] = Animation(new_name+std::to_string(ATTACK), _h, _w);
  	animations[ULTIMATE] = Animation(new_name+std::to_string(ULTIMATE), 720, 1280, ult_speed);
  	//animations[DEAD] = Animation("dead1", 284, 1114);
  	//animations[TELEPORT] = Animation("teleport", _h, _w);
  	//animations[SHOCK] = Animation("shock", _h, _w);

  	//std::cout << "animation etape 1" << std::endl;
  	//animations[_etat].setPosition(_x,_y);
  	//animations[ULTIMATE] = Animation(new_name+std::to_string(3), _h, _w);
  	//std::cout << "animation etape 2" << std::endl;
  	// for(int i = 0; i < 4; i++)
  	// {
  	// 	animations[i] = Animation(new_name+std::to_string(i+1), h, w);
  	// 	animations[i].setPosition(_x,_y);
  	// }
  	animations[ULTIMATE].setPosition(0,0);
}

void Personnage::draw(Screen& s, sf::Music * m)  {
	if(/*_etat != DEAD and*/ _etat != ULTIMATE ){
		//std::cout<< _etat << std::endl;
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
	/*if(activate_tp){
  		s.display( animations[TELEPORT].getSprite() );
  		if(animations[TELEPORT].get_last() == true)
  			activate_tp = false;
  		if(tp_count > 3){
  			activate_tp = false;
  			tp_count = 0; 
  		}
  		else{
  			tp_count++;
  		}
  	}

  	if(activate_col){
  		std::cout << " DISPLAYIN SHOCK" << std::endl;
  		s.display( animations[SHOCK].getSprite() );
  		if(animations[SHOCK].get_last() == true)
  			activate_col = false;
  		if(shock_count > 7){
  			activate_col = false;
  			shock_count = 0;
  		}
  		else{
  			shock_count++;
  		}
  	}*/
	
	//s.disc(_x+ _radius,_y + _radius,_radius);
}


// void Personnage::animation_update(){
// 	if(this->isAlive()){
// 		if(animations[ATTACK].get_last() == true){
// 			this->set_etat(STATIC);
// 			//std::cout << _etat << " _etat = STATIC" << std::endl;
// 		}
// 		animations[_etat].update(_etat);
// 		//std::cout << _etat << " _etat " << std::endl;
		
// 	}
// }

void Personnage::sound(std::string sound_type){
	if(sound_type == "ultimate")
		_audio.sound_ultimate();
	else if(sound_type == "death"){
		_audio.sound_death();
	}
}

float Personnage::distance(Personnage* per){
	return sqrt( pow(per->get_x() - _x,2) + pow( per->get_y() - _y,2) );
}
































