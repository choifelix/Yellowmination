
#include "game.h"
 
#define nb_team1 4
#define nb_team2 4
#define nb_pers nb_team1 + nb_team2
#define support1 1
#define support2 1
#define screen_w 1280 
#define screen_h 720
#define NB_MUSIC 2
#define STANDART_FRAME 0.2


Game::Game():_screen(screen_h,screen_w){
    _alive_team1 = nb_team1;
    _alive_team2 = nb_team1;
    srand ( time(NULL) );
    _play = false;

    int r = rand()%NB_MUSIC;
    std::cout << r << std::endl;
    _music = new sf::Music;

    switch(r){
      case 0 : _music_name = MUSIC_PATH_SASAGEYO;
        break;

      case 1 :  _music_name = MUSIC_PATH_ULTIME_BATTLE;
        break;
    }
    if(!_music->openFromFile(_music_name))
      std::cout << " music failed " << std::endl;
    std::cout << "constructor done " << std::endl;

}

Game::~Game(){ 
  //#### wall #####
	for ( auto& iter : _Walls){
    delete iter;
  }


  //#### team actif #####
  for(int i=0 ; i < nb_team1 ; i++){
    delete _team1_list[i];
  }
  delete _team1_list;

  for(int i=0 ; i < nb_team2 ; i++){
    delete _team2_list[i];
  }
  delete _team2_list;


  //##### team support #####
  for(int i=0 ; i < support1 ; i++){
    delete _support_team1[i];
  }
  delete _support_team1;

  for(int i=0 ; i < support2 ; i++){
    delete _support_team2[i];
  }
  delete _support_team2;

  //###3 delete team #####
  //delete _team1;
  //delete _team2;

  //## delete game_music
  delete _music;	
}



// Init Level 1

void Game::initGame(){
  
  //initialiser les personnages et murs -> allouer memoire
	
  _Walls.push_back(new Wall(0 - 1000, 0 , screen_h + 100,  10 + 1000,1));
  _Walls.push_back(new Wall(0, 0 - 1000, 10 + 1000, screen_w,2));
  _Walls.push_back(new Wall(0 , screen_h, 10 + 1000, screen_w,3));
  _Walls.push_back(new Wall(screen_w - 10, 0, screen_h + 100,1000 + 10,4));



//initialiser les personnages
  //actif
                                                                                // hp, atk, def, dodge, radius, speed, ult_timer, ult_damage
  Personnage_actif ** persos = new Personnage_actif*[nb_pers];
  persos[0] = new Personnage_actif(1000, 50, "GFreezer" ,1, AUDIO_PATH_FREEZER,   500, 10 , 12 , 0.15 , 40    , 2    ,   11     ,  70      ,0 , 100);
  persos[1] = new Personnage_actif(1000, 250, "SSJ3Goku" ,1, AUDIO_PATH_GOKU,     420, 14 , 7  , 0.3  , 40    , 1    ,   20     ,  200     ,0 , 100);
  persos[2] = new Personnage_actif(1000, 450, "Bumblebee",1, AUDIO_PATH_DEJA_VU,  380, 15 , 8  , 0    , 40    , 6    ,    7     ,  50      ,0 , 100);
  persos[3] = new Personnage_actif(1000, 650, "Kizaru"  ,1, AUDIO_PATH_KIZARU,    225, 10 , 6  , 0.9  , 45    , 1    ,   13     ,   80     ,30, 100);
  persos[4] = new Personnage_actif(20  , 50, "Pikachu" ,2, AUDIO_PATH_PIKACHU,    300, 20 , 5  , 0.4  , 40    , 3    ,    12    ,   40     ,0 , 100 );
  persos[5] = new Personnage_actif(20  , 250, "Pacman"  ,2, AUDIO_PATH_PACMAN,    300, 17 , 3  , 0.1  , 50    , 2    ,   11     ,   90     ,0 , 100 );
  persos[6] = new Personnage_actif(20  , 450, "Naruto"  ,2, AUDIO_PATH_NARUTO  ,    450, 15 , 9  , 0.5  , 40    , 4    ,   14     ,   140    ,0 , 100 );
  persos[7] = new Personnage_actif(20  , 650, "Sailormoon",2, AUDIO_PATH_SAILORMOON  ,  350, 17 , 4  , 0.1  , 45    , 2    ,   13     ,   85     ,0 , 100 );


  



 	_team1_list = new Personnage_actif*[nb_team1];
  _team2_list = new Personnage_actif*[nb_team2];
  int team1 =0;
  int team2 =0;
  for(int i=0 ; i < nb_pers ; i++){

    float r = float(rand())/float(RAND_MAX);
    //std::cout << r << std::endl;
    if( r > 0.5 ){
      if( team1 < nb_team1){
        _team1_list[team1] = persos[i];
        _team1_list[team1]->set_position(1000,50 + 200*team1);
        _team1_list[team1]->set_team(1);
        team1++;
      }
      else{
        _team2_list[team2] = persos[i];
        _team2_list[team2]->set_position(20,50 + 200*team2);
        _team2_list[team2]->set_team(2);
        team2++;
      }
      
    }
    else{
      if(team2 < nb_team2){
        _team2_list[team2] = persos[i];
        _team2_list[team2]->set_position(20,50 + 200*team2);
        _team2_list[team2]->set_team(2);
        team2++;
      }
      else{
        _team1_list[team1] = persos[i];
        _team1_list[team1]->set_position(1000,50 + 200*team1);
        _team1_list[team1]->set_team(1);
        team1++;
      }
    }
  }



 	_support_team1 = new Personnage_support*[support1];
 	_support_team1[0] = new Personnage_support(rand()%(screen_w - 20) + 10, rand()%(screen_h - 20) + 10, "Sonic"  ,1,AUDIO_PATH_SONIC, 100,  0 , 10, 0, 40, 0, 50, 10, 5, 0.1, 0, 10);
 	

  _support_team2 = new Personnage_support*[support2];
  _support_team2[0] = new Personnage_support(rand()%(screen_w - 20) + 10, rand()%(screen_h - 20) + 10,"Saitama",2,AUDIO_PATH_ONE_PUNCH,1000, 0, 50, 0, 40, 0, 20, 20, 10, 0, 0, 0);

  //##### creation de l'equipe #####
  _team1 = new Team(1);
  _team2 = new Team(2);

  //##### bande son de game #####
  _music->setVolume(20);
  _music->play();

  std::cout << " init done" << std::endl;
}



void Game::handleEvent (){

 	sf::Event event;
 	while (_screen.pollEvent(event)){
    	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
	  		_screen.close();
	  		_play = false;
	  	}

      if (!_play and (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)  )){
        _play = true;
        _music->play();
      }
        
    }
    /*compte le nombre de survivant*/
    int alive =0 ;
    for( int i =0 ; i< nb_team1 ; i++)
      if(_team1_list[i]->isAlive())
        alive++;
    
    _alive_team1 = alive;
    alive =0 ;
    for( int i =0 ; i< nb_team2 ; i++)
      if(_team2_list[i]->isAlive())
        alive++;
    
    _alive_team2 = alive;
}

void Game::update_music(){

  


  if(_music->getPlayingOffset().asSeconds() + 0.1>= _music->getDuration().asSeconds()  ){
    if(_music_name == MUSIC_PATH_ULTIME_BATTLE)
       _music_name = MUSIC_PATH_SASAGEYO;  


    else if(_music_name == MUSIC_PATH_SASAGEYO)
      _music_name = MUSIC_PATH_ULTIME_BATTLE;


    if(!_music->openFromFile(_music_name))
      std::cout << " music failed " << std::endl;

    
    _music->play();
  }
}


bool Game::play(){
  	initGame();
    
    sf::Clock clock;
    int a = 1;
  	while( _screen.isOpen() ){
      _screen.SetFramerateLimit(60);
      _screen.render();
      update_music();
      handleEvent ();
      int close = 0;

      if(!_play){
        _music->pause();
        if(_alive_team1 >= 1 and _alive_team2 >= 1){
          _screen.text(400, 350, "Press Space to start THE epic battle",0xFADA5EFF,"../../interface/font/ComicNeue-Angular-Bold.ttf");
        }
        else{
          close++;
          std::cout << close << std::endl;
          if(close > 60 * 5){
            _screen.close();
          }
          if(_alive_team1 = 0){
            _screen.text(400, 350, "Victoire de team 2!  Press Q to quit",0xFADA5EFF,"../../interface/font/ComicNeue-Angular-Bold.ttf");

          }

          else
            _screen.text(400, 350, "Victoire de team 1!  Press Q to quit",0xFADA5EFF,"../../interface/font/ComicNeue-Angular-Bold.ttf");
        }
      }
      else{


          _team1->activate_support(_team1_list,nb_team1,_support_team1,support1,_team2_list,nb_team2);
          _team2->activate_support(_team2_list,nb_team2,_support_team2,support2,_team1_list,nb_team1);
        


        // affichage ######################

        _screen.background();


        for ( auto& iter : _Walls){
          iter->draw(_screen);
        }

        //#### dead :
        for(int i=0 ; i < nb_team1 ; i++){
          if( !_team1_list[i]->isAlive() )
            _team1_list[i]->draw(_screen,_music);
        }

        for(int i=0 ; i < nb_team2 ; i++){
          if( !_team2_list[i]->isAlive() )
            _team2_list[i]->draw(_screen,_music);
        }

        //##### alive :
        for(int i=0 ; i < nb_team1 ; i++){
          if( _team1_list[i]->isAlive() )
            _team1_list[i]->draw(_screen,_music);
        }

        for(int i=0 ; i < nb_team2 ; i++){
          if( _team2_list[i]->isAlive() )
            _team2_list[i]->draw(_screen,_music);
        }


        //##### support 
        for(int i=0 ; i < support1 ; i++){
          if( _support_team1[i]->isAlive() )
            _support_team1[i]->draw(_screen,_music);
        }

        for(int i=0 ; i < support2 ; i++){
          if( _support_team2[i]->isAlive() )
            _support_team2[i]->draw(_screen,_music);
        }
        //####################################
       

        // // gestion sprite et update ############

        if(clock.getElapsedTime().asSeconds() > 0.02f) {
          
    
          for(int i=0 ; i < nb_team1 ; i++){
            _team1_list[i]->animation_update();
          }

          for(int i=0 ; i < nb_team2 ; i++){
            _team2_list[i]->animation_update();
          }

          for(int i=0 ; i < support1 ; i++){
            _support_team1[i]->animation_update();
          }

          for(int i=0 ; i < support2 ; i++){
            _support_team2[i]->animation_update();
          } 

          clock.restart();
        }

        //##### update actif
        for(int i=0 ; i < nb_team1 ; i++){
          _team1_list[i]->update(_screen,this->_team2_list,nb_team2) ;
        }

        for(int i=0 ; i < nb_team2 ; i++){
          _team2_list[i]->update(_screen,this->_team1_list,nb_team1);
        }
        //------------

        //##### update support
        for(int i=0 ; i < support1 ; i++){
          _support_team1[i]->update(this->_team2_list,nb_team2,this->_team1_list,nb_team1);
        }

        for(int i=0 ; i < support2 ; i++){
          _support_team2[i]->update(this->_team1_list,nb_team1,this->_team2_list,nb_team2);
        }
        //----------


        // gestion des murs ##################
        for(int i = 0 ; i < nb_team1; i++){
          if(_team1_list[i]->isAlive()){
            for ( auto& iter : _Walls){
              iter->interract(_team1_list[i]);
            }
          }
        }
        for(int i = 0 ; i < nb_team2; i++){
          if(_team2_list[i]->isAlive()){
            for ( auto& iter : _Walls){
              iter->interract(_team2_list[i]);
            }
          }
        }
        //####################################
       	
        _play =  (_alive_team1 >= 1 and _alive_team2 >= 1)? _play: false; 
      }
    }
  	return 0;
}


