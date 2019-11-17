#include "personnage.h"
#define screen_w 1280 
#define screen_h 720

Personnage::Personnage(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed )
:Obstacle(x,y),_audio(audio_file,new_team,100),_h(100),_w(100),_radius(50),_team(new_team){	
    // initialisation des caracteristiques
  	_etat   = STATIC;
  	_name   = new_name;
  	_hp_max = hp;
  	_hp     = _hp_max;
  	_atk    = atk;
  	_def    = def;
  	_speed  = speed;
    _radius = radius;
  	_range  = 15 + (2 * _radius); 

    //initialisation de variables utiles en back (variables systemes) 
  	_attack_frame = 0;
  	

    //initialisation de l'animation
    animations[STATIC] = Animation(new_name+std::to_string(STATIC), _h, _w);
    animations[STATIC].setPosition(_x,_y);
    animations[ULTIMATE] = Animation(new_name+std::to_string(ULTIMATE), 720, 1280);
    animations[ULTIMATE].setPosition(0,0);
    animations[LIFE] = Animation("life"+std::to_string(_team), 8, _w); // Texture vie 6 pixel hauteur
    //animations[LIFE].setPosition(_x,_y);

}

Personnage::Personnage(float x, float y, std::string new_name, int new_team, std::string audio_file,int hp, int atk, int def, float dodge, float radius, float speed , int ult_speed, float volume)
:Obstacle(x,y),_audio(audio_file,new_team, volume),_h(100),_w(100),_radius(50),_team(new_team){	
	// initialisation des caracteristiques
    _etat   = STATIC;
    _name   = new_name;
    _hp_max = hp;
    _hp     = _hp_max;
    _atk    = atk;
    _def    = def;
    _speed  = speed;
    _radius = radius;
    _range  = 15 + (2 * _radius); 

    //initialisation de variables utiles en back (variables systemes) 
    _attack_frame = 0;


	//initialisation de l'animation
  	animations[STATIC] = Animation(new_name+std::to_string(STATIC), _h, _w);
    animations[STATIC].setPosition(_x,_y);
  	animations[ULTIMATE] = Animation(new_name+std::to_string(ULTIMATE), 720, 1280, ult_speed);	
  	animations[ULTIMATE].setPosition(0,0);
    animations[LIFE] = Animation("life"+std::to_string(_team), 8, _w);
    //animations[LIFE].setPosition(_x,_y);
}

void Personnage::draw(Screen& s, sf::Music * m){

	if( ( _etat != ULTIMATE ) && (_etat != DEAD) ){
		s.display( animations[_etat].getSprite() ); // affichage de la frame de l'etat actuel
    s.display( animations[LIFE].getSprite() ); // affichage de la barre de vie 
	}
  else if (_etat == DEAD)
    s.display( animations[_etat].getSprite() ); //  affichage de l'etat DEAD(sans barre de vie)
	else if (_etat == ULTIMATE)
	{
		std::cout<< _etat << std::endl;
		m->pause();
		_audio.sound_ultimate();

		// Arrete le temps pour ne voir que l'ultimate -> while interne
		
		sf::Clock clock;
		int close = 0;

		while(!close)
		{	
			s.SetFramerateLimit(60);
     	s.render();
			s.display( animations[_etat].getSprite() );

      //mise à jour de l'image à afficher
			if(clock.getElapsedTime().asSeconds() > 0.1f)
			{
				this->animation_update();
        clock.restart();
			}

      //quand l'animation arrive à sa fin.
  		if (animations[ULTIMATE].get_last() == true){
  			close = 1;
  			animations[ULTIMATE].set_last(false);
  		}

  		//pouvoir fermer quand meme.
  		sf::Event event;
		 	while (s.pollEvent(event)){
	    	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
	    		close = 1;
		  		s.close();
		  	}
	    }
  	}
  	m->play();
  	this->set_etat(STATIC);
	}
}
	

void Personnage::sound(std::string sound_type){
	if(sound_type == "ultimate")
		_audio.sound_ultimate();
	else if(sound_type == "death")
		_audio.sound_death();
}

float Personnage::distance(Personnage* per){
  // std::cout << sqrt( pow(per->get_x() - _x,2) + pow( per->get_y() - _y,2) ) << std::endl;
  // std::cout << _x << " , " << _y << std::endl;
  // std::cout << per->get_x() << " , " << per->get_y() << std::endl;
  // std::cout << _name << " "<< per->get_name() << std::endl;
	return sqrt( pow(per->get_x() - _x,2) + pow( per->get_y() - _y,2) );
}

void Personnage::set_team(int team){
  _team = team;
  animations[LIFE].set_texture("../../interface/image/life"+std::to_string(_team) + ".png");
}































