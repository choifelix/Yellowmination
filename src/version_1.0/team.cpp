#include "team.h"
#include <math.h>
#define COOLDOWN 60 * 20 //cooldown de 20 secondes pour une framerate de 60
#define INVOC_COST 80
#define screen_w 1280 
#define screen_h 720


Team::~Team(){
    delete _support_list;
    delete _actif_list;
}


void Team::activate_support(Personnage_actif ** actif_list, int nb_actif, Personnage_support ** support_list, int nb_support, Personnage_actif ** ennemy_team, int nb_ennemy){
    // compte support point
    int support_point = 0;
    for(int i = 0 ; i< nb_actif ; i++){
        if( actif_list[i]->isAlive() ){
            support_point += actif_list[i]->get_mana();
        }
    }

    // si les points pour support invoque sont suffisant :
	if (support_point > INVOC_COST and nb_support != 0){

        //#### verifie la disponibilité des supports et enregistre dans une liste (tableau) #####
        int nb_available = 0;
        int available_list[nb_support];

        //creation du tablea disponible
        for(int i=0 ; i<nb_support ; i++){
            available_list[i] = 0;
            if(!support_list[i]->isAlive() and (support_list[i]->get_cooldown() > COOLDOWN)){
                available_list[nb_available] = i;
                nb_available++;
            }
        }

        //selection du support parmis les diponibles
        
        int r = -1;
        int indice= -1;
        if(nb_available != 0){

    		r = rand()%nb_available;               //on choisit au hasard le support
            indice = available_list[r];
    		support_list[ indice ]->set_activate(true);     //activation du suppor
            support_list[ indice ]->set_etat(ULTIMATE);
            support_list[ indice ]->set_position(rand()%(screen_w - 20) + 10, rand()%(screen_h - 20) + 10);



            //active etat pour animation d'enttree
                

            //##### son equipe -> buff #####
            int nb_alive = 0;
            for(int i = 0 ; i< nb_actif ; i++){      // effet instantanné du support
                if ( actif_list[i]->isAlive()){
                    support_list[indice]->effect(actif_list[i]);
                    nb_alive++;
                }
            }

            //##### le cout pour chaque perso est recalcule par iteration pour avoir la valeur adequate pour chaque perdsonnage. mana < 0 pas acceptable #####
            int total_cost = INVOC_COST;
            int cost = ceil(float(total_cost)/float(nb_alive));
            int id_available =0; // le n-ieme actif non-mort
            
            for(int i = 0 ; i< nb_actif ; i++){     
                if ( actif_list[i]->isAlive()){
                    int mana = actif_list[i]->get_mana();
                    if( (mana -  cost) < 0   ){
                        actif_list[i]->set_mana(0);
                        total_cost = total_cost - cost - (cost - mana);
                        cost  = ceil(float(total_cost)/float(nb_alive - id_available));
                    }
                    else{
                        actif_list[i]->set_mana(mana - cost ); 
                        total_cost -= cost;
                         cost  = ceil(float(total_cost)/float(nb_alive - id_available));
                    }

                    id_available++;
                }
            }

            //##### equipe adverse -> debuff #####
            for( int i=0 ; i < nb_ennemy ; i++){
                if ( ennemy_team[i]->isAlive())
                    support_list[indice]->effect(ennemy_team[i]);
            }
        }
	}
}

