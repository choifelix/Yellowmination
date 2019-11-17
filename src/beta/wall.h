#ifndef Wall_HH_
#define Wall_HH_

#include "obstacle.h"
#include "personnage_actif.h"

class Wall: public Obstacle{
 	public:
 		Wall(float x, float y,float h, float w, int id): Obstacle(x,y),_h(h),_w(w),_id(id){}
  		~Wall() {}
  		void draw(Screen& s) ;
 		void interract(Personnage_actif* per);
 		void shock( Personnage_actif* per);
 		void computeSpeed(Personnage_actif* per);
 		float distance_left(Personnage_actif* per);
 		float distance_right(Personnage_actif* per);
 		float distance_top(Personnage_actif* per);
 		float distance_bottom(Personnage_actif* per);
 	private:
  		float _h, _w;
  		int _id;
  		
};

#endif
