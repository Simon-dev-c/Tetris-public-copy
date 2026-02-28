#ifndef BOUTON
#define BOUTON
#include<MLV/MLV_all.h>

#define NB_MAX_BOUTON 50

struct un_bouton {
        int x; /* (x,y) Point nord ouest du bouton entier */
        int y; 
        int hauteur; /* hauteur total du bouton */
        int largeur; /* largeur total du bouton */
        int rayon; /* rayon des deux cercles constituant l'arondi du bouton */

        int x_rectangle_no; /* coin nord ouest de la partie rectangulaire du bouton */
        int y_rectangle_no;

        int x_rectangle_se; /* coin sud est de la partie rectangulaire du bouton */
        int y_rectangle_se;

        int x_cercle_gauche; /* centre du cercle */
        int y_cercle_gauche;

        int x_cercle_droit;
        int y_cercle_droit;

        short est_over;
        int animation;
        const char* nom;
        int taille_police;
        MLV_Font* police;
        MLV_Color couleur;

        short est_actif;

};

typedef struct {

    struct un_bouton liste_boutons[NB_MAX_BOUTON];

    int nb_boutons; /* nombre de boutons */

} Bouton;



void changer_couleur_bouton(Bouton* boutons, int id_bouton, MLV_Color couleur);
short a_clique_sur_bouton(int* mouse_x, int* mouse_y, Bouton* boutons);
void est_sur_bouton(int* mouse_x, int* mouse_y, Bouton* boutons);
void creer_bouton(Bouton* boutons, int x, int y, int hauteur, int largeur, const char* chaine, int taille_police,MLV_Color couleur);

#endif