
#include "game.h"

#define nb_team1 2
#define nb_team2 2
#define support1 0
#define support2 1
#define screen_w 1280 
#define screen_h 720
#define NB_MUSIC 2
#define STANDART_FRAME 0.2


Game::Game():_screen(screen_h,screen_w){
    _alive_team1 = nb_team1;
    _alive_team2 = nb_team1;
    srand ( time(NULL) );

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
	
	_board = new Wall*[4];


  _board[0]  = new Wall(0 - 1000, 0 , screen_h + 100,  10 + 1000,1);
  _board[1]  = new Wall(0, 0 - 1000, 10 + 1000, screen_w,2);
  _board[2]  = new Wall(0 , screen_h, 10 + 1000, screen_w,3);
  _board[3]  = new Wall(screen_w - 10, 0, screen_h + 100,1000 + 10,4);


  _Walls.push_back(new Wall(0 - 1000, 0 , screen_h + 100,  10 + 1000,1));
  _Walls.push_back(new Wall(0, 0 - 1000, 10 + 1000, screen_w,2));
  _Walls.push_back(new Wall(0 , screen_h, 10 + 1000, screen_w,3));
  _Walls.push_back(new Wall(screen_w - 10, 0, screen_h + 100,1000 + 10,4));


 	_team1_list = new Personnage_actif*[nb_team1];
  _team2_list = new Personnage_actif*[nb_team2];

std::cout << " init perso" << std::endl;
  _team1_list[0] = new Personnage_actif(200, 200, "GFreezer",1,AUDIO_PATH_FREEZER);
  _team1_list[1] = new Personnage_actif(200, 400, "SSJ3Goku",1,AUDIO_PATH_GOKU );
 std::cout << " perso 1 done" << std::endl;
  _team2_list[0] = new Personnage_actif(20  , 20 , "Kizaru",2,AUDIO_PATH_KIZARU, 30,100);
  _team2_list[1] = new Personnage_actif(20  , 300, "Pikachu",2,AUDIO_PATH_PIKACHU, 0,100);
std::cout << " perso 2 done" << std::endl;


 	_support_team1 = new Personnage_support*[support1];
 	//_support_team1[0] = new Personnage_support(200, 200, "Sonic",1,AUDIO_PATH_ONE_PUNCH,STANDART_FRAME,1500);
 	

  _support_team2 = new Personnage_support*[support2];
  _support_team2[0] = new Personnage_support(200 , 200  , "Sonic",2,AUDIO_PATH_ONE_PUNCH);

  //##### creation de l'equipe #####
  //std::cout << "inti team " << std::endl;
  _team1 = new Team(1);
  _team2 = new Team(2);
  //std::cout << " fin inti team " << std::endl;

  //##### bande son de game #####
  _music->setVolume(10);
  _music->play();

  std::cout << " init done" << std::endl;
}



void Game::handleEvent (){
	//pour l'instant y a juste quitter
 	sf::Event event;
 	while (_screen.pollEvent(event)){
    	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
	  		_screen.close();
	  		_play = false;
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
  //::cout << _music->getPlayingOffset().asSeconds() << std::endl;
  //std::cout << _music->getDuration().asSeconds() << std::endl;
  


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

      //std::cout << "activate support" << std::endl;
      if(_play){
        _team1->activate_support(_team1_list,nb_team1,_support_team1,support1,_team2_list,nb_team2);
        _team2->activate_support(_team2_list,nb_team2,_support_team2,support2,_team1_list,nb_team1);
      }
      //std::cout << " fin activate support" << std::endl;

      // affichage ######################

      _screen.background();
  //std::cout << "before draw wall" << std::endl;

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
      //std::cout << "before draw" << std::endl;


      for(int i=0 ; i < nb_team1 ; i++){
        if( _team1_list[i]->isAlive() )
          _team1_list[i]->draw(_screen,_music);
      }

      for(int i=0 ; i < nb_team2 ; i++){
        if( _team2_list[i]->isAlive() )
          _team2_list[i]->draw(_screen,_music);
      }

      //std::cout << " activ draw finish " << std::endl;
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
      //std::cout << "draw finish" << std::endl;

      // son (phase de test) #################### 

      /*if(a==1){
        for(int i=0 ; i < nb_team1 ; i++){
          _team1_list[i]->sound("ultimate");
        }

        for(int i=0 ; i < nb_team2 ; i++){
          _team2_list[i]->sound("ultimate");
        }

      }
      a++;
      if(a == 5000){
        for(int i=0 ; i < nb_team1 ; i++){
          _team1_list[i]->sound("death");
        }

        for(int i=0 ; i < nb_team2 ; i++){
          _team2_list[i]->sound("death");
        }
        a= -5000;
      }
      */
      //#####################################

      // gestion sprite et update ############

      if(clock.getElapsedTime().asSeconds() > 0.02f) {
        
  
        for(int i=0 ; i < nb_team1 ; i++){
          _team1_list[i]->animation_update();
        }

        for(int i=0 ; i < nb_team2 ; i++){
          _team2_list[i]->animation_update();
        }

        for(int i=0 ; i < support1 ; i++){
        //if(_support_team1[i]->isAlive())
        _support_team1[i]->animation_update();
      }

      for(int i=0 ; i < support2 ; i++){
        //if(_support_team2[i]->isAlive())
        _support_team2[i]->animation_update();
      }

        clock.restart();
      }
      //std::cout<<"before wall"<<std::endl;

      //std::cout << "update begin" << std::endl;
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
        //if(_support_team1[i]->isAlive())
        _support_team1[i]->update(this->_team2_list,nb_team2,this->_team1_list,nb_team1);
      }

      for(int i=0 ; i < support2 ; i++){
        //if(_support_team2[i]->isAlive())
        _support_team2[i]->update(this->_team1_list,nb_team1,this->_team2_list,nb_team2);
      }
      //----------
      //std::cout << "update end" << std::endl;

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


      //std::cout<<"after wall"<<std::endl;
     	handleEvent ();
      _play =  (_alive_team1 >= 1 and _alive_team2 >= 1)? _play: false; 
    }
  	return 0;
}
