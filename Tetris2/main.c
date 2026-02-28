#include<time.h>
#include<MLV/MLV_all.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include "menu_principale.h"
#include "bouton.h"
#include "jeu.h"


int main(){

    MLV_Mouse_button mouse_button;
    MLV_Button_state state;
    MLV_Keyboard_button key_sym;
    MLV_Event event;


    unsigned int hauteur, largeur;
    int mouse_x,mouse_y, id_bouton;
    int compteur_gauche = 0, compteur_droit = 0;

    
    MLV_get_desktop_size(&largeur, &hauteur);

    Jeu jeu;

    initialiser_jeu(&jeu, hauteur/1.2, largeur/1.2);


    srand(time(NULL));

    MLV_create_window("Tetris","Tetris",largeur/1.2,hauteur/1.2);
    
    
    afficher_menu_principale(hauteur/1.2, largeur/1.2, &jeu.boutons);

    MLV_change_frame_rate(60);

    while(1) {

        MLV_actualise_window();


        event = MLV_get_event(&key_sym,NULL,NULL,NULL,NULL,&mouse_x,&mouse_y,&mouse_button,&state);

        switch (event)
        {
        case MLV_MOUSE_MOTION:

            est_sur_bouton(&mouse_x,&mouse_y,&jeu.boutons);
            break;

        case MLV_MOUSE_BUTTON:

            if (mouse_button == MLV_BUTTON_LEFT && state == MLV_RELEASED) {
                id_bouton = a_clique_sur_bouton(&mouse_x, &mouse_y, &jeu.boutons);
                if (id_bouton != -1) {
                    printf("%d\n",id_bouton);
                    if (id_bouton == 0) {

                        nouvelle_partie(&jeu);

                    } else if (id_bouton == 1) {

                        /*jeu.etat = DANS_JEU;
                        MLV_clear_window(MLV_COLOR_BLACK);


                        commencer_plateau(&jeu.tabl);


                        if (charger_sauvegarde(&jeu.tabl,&jeu.prochaine_piece,&jeu.p,jeu.score,jeu.temps) == 0){
                            
                        
                            creer_piece(&jeu.prochaine_piece);
                        
                            prochaine_piece_to_piece(&jeu.prochaine_piece,&jeu.p);

                            creer_piece(&jeu.prochaine_piece);
                        }

                        MLV_draw_filled_rectangle(15,15,100,80,MLV_COLOR_BLACK);
                        
                        MLV_draw_text(20,20,"Score : %d",MLV_COLOR_GREEN,jeu.score);
        
                        jeu.temps ++;
                        MLV_draw_text(20,50,"Tour : %d",MLV_COLOR_GREEN,jeu.temps);

                        
                        afficher_prochaine_piece(jeu.tabl,&jeu.prochaine_piece);

                        actualiser_plateau(&jeu.tabl);

                        
                        placer_piece(jeu.tabl,&jeu.p);*/
                    }
                }
                
            }
            
            break;

        case MLV_KEY:

            if (jeu.etat == DANS_JEU) {
                /*MLV_draw_filled_rectangle(0,hauteur/1.25,largeur,hauteur/1.2,MLV_COLOR_CYAN);
                MLV_draw_filled_rectangle(largeur/1.2,0,largeur,hauteur/1.2,MLV_COLOR_CYAN);
                */

                
                if (key_sym == MLV_KEYBOARD_LEFT){

                    jeu.va_a_droite = 0;
                    jeu.intervalle_descend = 45;

                    if (state == MLV_PRESSED) {

                        jeu.va_a_gauche = 1;

                        if (peut_aller_a_gauche(&jeu.tabl,&jeu.p) == 0){
                            actualiser_plateau(&jeu.tabl);
                            bouger_piece(&jeu.tabl, &jeu.p, 'g');
                        }

                    } else if (state == MLV_RELEASED) {

                        jeu.va_a_gauche = 0;

                    }

                } else if (key_sym == MLV_KEYBOARD_DOWN) {

                    jeu.va_a_droite = 0;
                    jeu.va_a_gauche = 0;

                    if (state == MLV_PRESSED) {

                        jeu.est_descendu = 1;

                        jeu.intervalle_descend = 3;
                        actualiser_plateau(&jeu.tabl);

                        bouger_piece(&jeu.tabl, &jeu.p, 'b');

                    } else if (MLV_RELEASED) {

                        jeu.intervalle_descend = 45;
                    }

                } else if (key_sym == MLV_KEYBOARD_RIGHT) {

                    jeu.va_a_gauche = 0;
                    jeu.intervalle_descend = 45;

                    if (state == MLV_PRESSED) {
                        
                        jeu.va_a_droite = 1;

                        if (peut_aller_a_droite(&jeu.tabl,&jeu.p) == 0){
                
                            actualiser_plateau(&jeu.tabl);
                            bouger_piece(&jeu.tabl, &jeu.p, 'd');
                        }

                    } else if (state == MLV_RELEASED) {

                        jeu.va_a_droite = 0;

                    }

                }else if (key_sym == MLV_KEYBOARD_l && state == MLV_PRESSED) {

                    if (peut_tourner(&jeu.tabl,&jeu.p, 'l') == 0){
                        actualiser_plateau(&jeu.tabl);
                        tourner(&jeu.tabl, &jeu.p, 'l');
                    }
                }else if (key_sym == MLV_KEYBOARD_m && state == MLV_PRESSED) {

                    if (peut_tourner(&jeu.tabl,&jeu.p, 'm') == 0){
                        actualiser_plateau(&jeu.tabl);
                        tourner(&jeu.tabl, &jeu.p, 'm');
                    }
                    
                }
                
            }

            break;
        case MLV_NONE:
            if (jeu.boutons.nb_boutons) {

                MLV_get_mouse_position(&mouse_x,&mouse_y);
                /*est_sur_bouton(&mouse_x,&mouse_y,&boutons);*/
            }
            break;

        default:
            break;
        }

        if (jeu.va_a_droite) {

            if (compteur_droit == 5){
            
                if (peut_aller_a_droite(&jeu.tabl,&jeu.p) == 0){
                
                    actualiser_plateau(&jeu.tabl);
                    bouger_piece(&jeu.tabl, &jeu.p, 'd');
                }
                compteur_droit = 0;

            } else {

                compteur_droit++;

            }

        } else if (jeu.va_a_gauche) {
            if (compteur_gauche == 5) {

                if (peut_aller_a_gauche(&jeu.tabl,&jeu.p) == 0){
                    actualiser_plateau(&jeu.tabl);
                    bouger_piece(&jeu.tabl, &jeu.p, 'g');
                }

                compteur_gauche = 0;

            } else {
                compteur_gauche++;
            }

        } else {
            compteur_droit = 0;
            compteur_gauche = 0;
        }

        piece_descend(&jeu);

        if(jeu.etat == DANS_JEU) {
            if (peut_est_place(jeu.tabl,&jeu.p) && jeu.compteur == jeu.intervalle_descend/2){
                poser_piece(&jeu.tabl,&jeu.p);
                if (ligne_complete(&jeu.tabl,jeu.lignes) == 1){
                    enlever_ligne(&jeu.tabl,jeu.lignes);
                    jeu.score += compter_score(&jeu.tabl,jeu.lignes);

                }
                prochaine_piece_to_piece(&jeu.prochaine_piece,&jeu.p);
                creer_piece(&jeu.prochaine_piece);
                    
                MLV_draw_filled_rectangle(15,15,100,80,MLV_COLOR_BLACK);
                        
                MLV_draw_text(20,20,"Score : %d",MLV_COLOR_GREEN,jeu.score);
                    
                jeu.temps ++;
                MLV_draw_text(20,50,"Tour : %d",MLV_COLOR_GREEN,jeu.temps);
                    
                afficher_prochaine_piece(jeu.tabl,&jeu.prochaine_piece);
                    
                actualiser_plateau(&jeu.tabl);
                    
                    
                placer_piece(jeu.tabl,&jeu.p);
                    /*sauvegarder(&tabl,&prochaine_piece,&p,score,temps);*/
            }
        }


            

        MLV_flush_event_queue();

        MLV_delay_according_to_frame_rate();

    }
    /*MLV_wait_mouse(&x,&y);*/

    
    exit(EXIT_SUCCESS);
}
