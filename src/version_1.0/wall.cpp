#include "wall.h"



void Wall::draw(Screen& s) { 
  s.rect(_x, _y, _w, _h,0xFADA5EFF);
}

void Wall::interract(Personnage_actif* per){
	static const float damping = 0.85;
    float radius = per->get_radius();
  	float vx = per->get_vx();
	float vy = per->get_vy();
	float x  = per->get_x();
	float center_x = x + radius;
	float y  = per->get_y();
	float center_y = y + radius;


	if( ( (center_x - radius < _x + _w) and (center_x - radius > _x)) or ( (center_x + radius > _x ) and (center_x + radius < _x + _w)) ){

		switch(_id){
			case 1:
				x = _x + _w;
				vx = -vx * damping;
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:	
				x = _x - 2 * radius;
				vx = -vx * damping;	
				break;
		}
	}

	if(( (center_y - radius < _y + _h) and (center_y - radius > _y)) or ( (center_y + radius > _y ) and (center_y + radius < _y + _h)) ){

		switch(_id){
			case 1:
				break;
			case 2:
				y = _y + _h;
				vy = -vy * damping;
				break;
			case 3:
				y = _y - 2 * radius;
				vy = -vy * damping;
				break;
			case 4:
				break;
		}
	}

	per->set_vx(vx);
	per->set_vy(vy);
	per->set_position(x,y);
}




  

