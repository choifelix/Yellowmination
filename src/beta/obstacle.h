#ifndef OBSTACLE_HH_
#define OBSTACLE_HH_

#include "screen.h"



class Obstacle //class virtuelle
{
public:
  	Obstacle(float x, float y): _x(x), _y(y){}
  	Obstacle() = default;
  	virtual ~Obstacle() {}
  	//virtual void draw(Screen& s)  = 0;    //affichage du perso sur le screen
  	//virtual void interract(Obstacle& obs) = 0; //interaction entre les obstacles, ex: personnages-mur, ou perso-perso
  	void set_position(float x,float y){_x = x; _y = y;}
  	float get_x(){return _x;}
  	float get_y(){return _y;}
  	//virtual void computeSpeed(Ball& ball) const{};
protected:
  float _x, _y;
};

#endif
 
