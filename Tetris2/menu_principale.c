#include<stdio.h>
#include<stdlib.h>
#include<MLV/MLV_all.h>
#include "bouton.h"




void afficher_menu_principale(unsigned int hauteur, unsigned int largeur,Bouton* boutons) {

    boutons->nb_boutons = 0;

    int hauteur_bouton, largeur_bouton;

    hauteur_bouton = hauteur / 10;
    largeur_bouton = largeur / 6;

    creer_bouton(boutons,(largeur/2)-(largeur_bouton/2),(hauteur/2)-hauteur_bouton-50,hauteur_bouton,largeur_bouton,"Nouvelle\nPartie",largeur_bouton/9,MLV_COLOR_RED);

    creer_bouton(boutons,(largeur/2)-(largeur_bouton/2),(hauteur/2),hauteur_bouton,largeur_bouton,"Parametres",largeur_bouton/12,MLV_COLOR_ORANGE);

    creer_bouton(boutons,(largeur/2)-(largeur_bouton/2),(hauteur/2) + hauteur_bouton + 50,hauteur_bouton,largeur_bouton,"Leaderboard",largeur_bouton/12,MLV_COLOR_GREEN);

    

}