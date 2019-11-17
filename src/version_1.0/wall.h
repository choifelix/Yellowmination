#ifndef Wall_HH_
#define Wall_HH_

#include "obstacle.h"
#include "personnage_actif.h"

/****************************************************/
/* Classe des murs sur le terrain                   */
/****************************************************/
class Wall: public Obstacle{
 	public:
 		Wall(float x, float y,float h, float w, int id): Obstacle(x,y),_h(h),_w(w),_id(id){}
  		~Wall() {}
  		void draw(Screen& s);
 		void interract(Personnage_actif* per);
 	private:
  		float _h, _w;
  		int _id;
  		
};

#endif
