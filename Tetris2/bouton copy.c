#include<MLV/MLV_all.h>
#include<math.h>
#include "bouton.h"


void changer_couleur_bouton(Bouton* boutons, int id_bouton, MLV_Color couleur){

    MLV_draw_filled_circle(boutons->liste_boutons[id_bouton].x + boutons->liste_boutons[id_bouton].rayon, boutons->liste_boutons[id_bouton].y + boutons->liste_boutons[id_bouton].rayon, boutons->liste_boutons[id_bouton].rayon, couleur);

    MLV_draw_filled_circle(boutons->liste_boutons[id_bouton].x + boutons->liste_boutons[id_bouton].largeur - boutons->liste_boutons[id_bouton].rayon,boutons->liste_boutons[id_bouton].y + boutons->liste_boutons[id_bouton].rayon,boutons->liste_boutons[id_bouton].rayon, couleur);


    MLV_draw_text_box_with_font(boutons->liste_boutons[id_bouton].x + boutons->liste_boutons[id_bouton].rayon, boutons->liste_boutons[id_bouton].y, boutons->liste_boutons[id_bouton].largeur-(boutons->liste_boutons[id_bouton].rayon*2),boutons->liste_boutons[id_bouton].hauteur,boutons->liste_boutons[id_bouton].nom,boutons->liste_boutons[id_bouton].police,0,couleur,MLV_COLOR_WHITE, couleur,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);

}


void est_sur_bouton(int* mouse_x, int* mouse_y,Bouton* boutons) {
    int i;
    short est_dans_rectangle;
    short est_dans_cercle;
    double distance1, distance2;

    for (i=0;i<boutons->nb_boutons;i++) {
        distance1 = sqrt(((*mouse_x - boutons->liste_boutons[i].x_cercle_gauche) * (*mouse_x - boutons->liste_boutons[i].x_cercle_gauche)) + ((*mouse_y - boutons->liste_boutons[i].y_cercle_gauche) * (*mouse_y - boutons->liste_boutons[i].y_cercle_gauche)));
        distance2 = sqrt(((*mouse_x - boutons->liste_boutons[i].x_cercle_droit) * (*mouse_x - boutons->liste_boutons[i].x_cercle_droit)) + ((*mouse_y - boutons->liste_boutons[i].y_cercle_droit) * (*mouse_y - boutons->liste_boutons[i].y_cercle_droit)));

        est_dans_cercle = (distance1 <= boutons->liste_boutons[i].rayon || distance2 <= boutons->liste_boutons[i].rayon);
        est_dans_rectangle = ((boutons->liste_boutons[i].x_rectangle_no <= *mouse_x && *mouse_x <= boutons->liste_boutons[i].x_rectangle_se) && (boutons->liste_boutons[i].y_rectangle_no <= *mouse_y && *mouse_y <= boutons->liste_boutons[i].y_rectangle_se));

        if ((est_dans_rectangle || est_dans_cercle)) {

            if (!boutons->liste_boutons[i].est_over) {

                boutons->liste_boutons[i].est_over = 1;

                changer_couleur_bouton(boutons, i, MLV_COLOR_GREY);

            }
        } else {

            if (boutons->liste_boutons[i].est_over) {

                boutons->liste_boutons[i].est_over = 0;
                changer_couleur_bouton(boutons, i, boutons->liste_boutons[i].couleur);


            }

        }
    }
    
}





/* Renvoie l'id du bouton clique sinon -1 */
short a_clique_sur_bouton(int* mouse_x, int* mouse_y, Bouton* boutons) {

    int i;
    short est_dans_rectangle;
    short est_dans_cercle;
    double distance1, distance2;

    for (i=0;i<boutons->nb_boutons;i++) {
        distance1 = sqrt(((*mouse_x - boutons->liste_boutons[i].x_cercle_gauche) * (*mouse_x - boutons->liste_boutons[i].x_cercle_gauche)) + ((*mouse_y - boutons->liste_boutons[i].y_cercle_gauche) * (*mouse_y - boutons->liste_boutons[i].y_cercle_gauche)));
        distance2 = sqrt(((*mouse_x - boutons->liste_boutons[i].x_cercle_droit) * (*mouse_x - boutons->liste_boutons[i].x_cercle_droit)) + ((*mouse_y - boutons->liste_boutons[i].y_cercle_droit) * (*mouse_y - boutons->liste_boutons[i].y_cercle_droit)));

        est_dans_cercle = (distance1 <= boutons->liste_boutons[i].rayon || distance2 <= boutons->liste_boutons[i].rayon);
        est_dans_rectangle = ((boutons->liste_boutons[i].x_rectangle_no <= *mouse_x && *mouse_x <= boutons->liste_boutons[i].x_rectangle_se) && (boutons->liste_boutons[i].y_rectangle_no <= *mouse_y && *mouse_y <= boutons->liste_boutons[i].y_rectangle_se));

        if ((est_dans_rectangle || est_dans_cercle)) {

            return i;
            
        } 
    }


    return -1;

}


void creer_bouton(Bouton* boutons, int x, int y, int hauteur, int largeur, const char* chaine, int taille_police, MLV_Color couleur){
    
    int rayon;
    MLV_Font* police;

    police = MLV_load_font("./polices/SuperMario256.ttf",taille_police);

    boutons->liste_boutons[boutons->nb_boutons].x = x;
    boutons->liste_boutons[boutons->nb_boutons].y = y;
    boutons->liste_boutons[boutons->nb_boutons].hauteur = hauteur;
    boutons->liste_boutons[boutons->nb_boutons].largeur = largeur;
    boutons->liste_boutons[boutons->nb_boutons].est_over = 0;
    boutons->liste_boutons[boutons->nb_boutons].nom = chaine;
    boutons->liste_boutons[boutons->nb_boutons].taille_police = taille_police;
    boutons->liste_boutons[boutons->nb_boutons].couleur = couleur;
    boutons->liste_boutons[boutons->nb_boutons].animation = 0;






    boutons->liste_boutons[boutons->nb_boutons].police = police;

    rayon = hauteur / 2;
    boutons->liste_boutons[boutons->nb_boutons].rayon = rayon;
    /*MLV_draw_filled_rectangle(x-(largeur),y-150,largeur,hauteur,MLV_COLOR_RED);*/

    boutons->liste_boutons[boutons->nb_boutons].x_cercle_gauche = x+rayon;
    boutons->liste_boutons[boutons->nb_boutons].y_cercle_gauche = y+rayon;

    MLV_draw_filled_circle(x+rayon,y+rayon,rayon,couleur);

    boutons->liste_boutons[boutons->nb_boutons].x_cercle_droit = x+largeur-rayon;
    boutons->liste_boutons[boutons->nb_boutons].y_cercle_droit = y+rayon;

    MLV_draw_filled_circle(x+largeur-rayon,y+rayon,rayon,couleur);

    boutons->liste_boutons[boutons->nb_boutons].x_rectangle_no = x + rayon;
    boutons->liste_boutons[boutons->nb_boutons].y_rectangle_no = y;

    boutons->liste_boutons[boutons->nb_boutons].x_rectangle_se = x + (largeur-(rayon*2));
    boutons->liste_boutons[boutons->nb_boutons].y_rectangle_se = y + hauteur;


    MLV_draw_text_box_with_font(x+rayon,y,largeur-(rayon*2),hauteur,chaine,police,0,couleur,MLV_COLOR_WHITE,couleur,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);

    boutons->nb_boutons++;
}