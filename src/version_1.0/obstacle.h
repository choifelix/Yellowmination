#ifndef OBSTACLE_HH_
#define OBSTACLE_HH_

#include "screen.h"

/****************************************************/
/* Classe des obstacles sur le terrain              */
/****************************************************/
class Obstacle //classe virtuelle
{
public:
    //Constructeurs
  	Obstacle(float x, float y): _x(x), _y(y){}
  	Obstacle() = default;
    //Destructeur
  	virtual ~Obstacle() {}; // Pas de new

  	void set_position(float x,float y){_x = x; _y = y;}
  	float get_x(){return _x;}
  	float get_y(){return _y;}
  	
protected:
  float _x, _y;
};

#endif
 
