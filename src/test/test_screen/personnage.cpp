#include "personnage.h"

Personnage::Personnage(float x, float y, float h, float w, std::string new_name):Obstacle(x,y),_h(h),_w(w){
	_vx    = 0 ;
	_vy    = 0 ;
	_name  = new_name;
	_etat = MOBILE;
  	for(int i = 0; i < 4; i++)
  	{
  		animations[i] = Animation(new_name+std::to_string(i+1), h, w);
  		animations[i].setPosition(_x,_y);
  	}
  	animations[3].set_h(720);
  	animations[3].set_w(1280);


}


void Personnage::draw(Screen& s) const {
	switch(_etat)
	{
		case MOBILE:
			s.display( animations[0].getSprite() );
			break;
		case ULTIMATE:
			s.display( animations[1].getSprite() );
			break;
		case ATTACK:
			s.display( animations[2].getSprite() );
			break;
		case DEAD:
			s.display( animations[3].getSprite() );
			break;
	}
}


void Personnage::update() {
	switch(_etat)
	{
		case MOBILE:
			animations[0].update();
			break;
		case ULTIMATE:
			animations[1].update();
			break;
		case ATTACK:
			animations[2].update();
			break;
		case DEAD:
			animations[3].setPosition(0,0);
			animations[3].update();
			break;
	}

}



