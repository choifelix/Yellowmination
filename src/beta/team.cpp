#include "team.h"
#include <math.h>
#define COOLDOWN 60 * 10 //cooldown de 10 secondes pour une framerate de 60
#define INVOC_COST 2000



Team::Team(int team_nb){// , Personnage_actif ** actif_list, int nb_actif, Personnage_support ** support_list, int nb_support){

    /*definition de l'id'*/
    _id = team_nb;
    _support_point = 0;
    ///////////////////////

    //## les personnages de l'equipe ##
    /*_support_list = new Personnage_support *[nb_support];
    _support_list = support_list;
    _actif_list = new Personnage_actif *[nb_actif];
    _actif_list = _actif_list;

    _nb_actif = nb_actif;
    _nb_support = nb_support;*/

    /*definition de la position*/
    switch(_id){
    	case 1: _x = 0; _y = 0;
    		break;

    	case 2: _x = 0; _y = 250 - 30;
    		break;

    	case 3: _x = 0; _y = 500 - 60;
    		break;

    	case 4: _x = 500 - 60; _y = 0;
    		break;

    	case 5: _x = 500 - 60; _y = 250 - 30;
    		break;

    	case 6: _x = 500 - 60; _y = 500 - 60;
    		break;

    	default: std::cout<< "team attribution problem - team.cpp 37"<< std::endl;
    		break;

    }
    /////////////////////////////
}

Team::~Team(){
    delete _support_list;
    delete _actif_list;
}


void Team::activate_support(Personnage_actif ** actif_list, int nb_actif, Personnage_support ** support_list, int nb_support, Personnage_actif ** ennemy_team, int nb_ennemy){
    // compte support point
    for(int i = 0 ; i< nb_actif ; i++){
        if( actif_list[i]->isAlive() ){
            _support_point += actif_list[i]->get_mana();
        }
    }

    // si les points pour support invoque sont suffisant :
	if (_support_point > INVOC_COST and nb_support != 0){
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
            //std::cout << " choix support" << std::endl;
    		r = rand()%nb_available;               //on choisit au hasard le support
            indice = available_list[r];
    		support_list[ indice ]->set_activate(true);     //activation du suppor
            support_list[ indice ]->set_etat(ULTIMATE);

            //std::cout << " choix support : done " << std::endl;
                //active etat pour animation d'enttree
                

            //##### son equipe -> buff #####
            int nb_alive = 0;
            for(int i = 0 ; i< nb_actif ; i++){      // effet instantanné du support
                //std::cout << "iteration : " << i << " boucle d'effet" << std::endl;
                if ( actif_list[i]->isAlive()){
                    //std::cout << " alive " << std::endl;
                    support_list[indice]->effect(actif_list[i]);
                    //std::cout << "iteration : " << i << " effet done " << std::endl;
                    nb_alive++;
                }
                //actif_list[i]->set_mana(0); //gestion a faire -> fait juste en dessous
            }
           // std::cout << " effect actif done" << std::endl;

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
            
            /*else{ //un truc just in case
                for(int i=0 ; i<nb_support ; i++){
                    support_list[i]->set_etat(STATIC);
                    support_list[i]->set_activate(false);
                }
            }*/
        }
	}
}

