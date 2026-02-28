


#include "bouton.h"

/* Represente l'etat de jeu
typedef struct{

    short est_dans_menu_principale;
    short est_dans_partie;


} etatJeu;


void afficher_jeu(unsigned int hauteur, unsigned int largeur,Bouton* boutons);*/



#define HAUTEUR_JEU 21
#define LARGEUR_JEU 12


typedef struct {
    short plateau[HAUTEUR_JEU][LARGEUR_JEU];
    unsigned int lg;
    unsigned int ht;
    unsigned int t_c;   /* taille carre */
}tableau;

typedef struct {
    int figure[4][4];
    int pos_i;
    int pos_j;
    int num_piece;
    int couleur;
}piece;

enum etatJeu {
    DANS_JEU,
    DANS_MENU_PRINCIPAL,
};

typedef struct {
    tableau tabl;
    piece p, prochaine_piece;
    Bouton boutons;
    int lignes[HAUTEUR_JEU];
    enum etatJeu etat;
    int score;
    int temps;
    int compteur;
    int intervalle_descend;
    int est_descendu;
    int va_a_droite;
    int va_a_gauche;
} Jeu;


void commencer_plateau(tableau *tabl); /* Initialise le plateau de Jeu 1 pour les bordures et 0 pour le reste*/
void actualiser_plateau(tableau *tabl); /* Actualise le plateau */
void creer_piece(piece *p); /* Cree une piece dans p */
void afficher_prochaine_piece(tableau tabl,piece *p); /* Affiche la prochaine piece à cote du plateau */
void placer_piece(tableau tabl,piece *p); /* Place "piece" dans le plateau */
int peut_est_place(tableau tabl,piece *p);
void poser_piece(tableau *tabl,piece *p);
void prochaine_piece_to_piece(piece *prochaine_piece, piece *piece); /* Mets "prochaine_piece" dans "piece" */
int peut_aller_a_gauche(tableau *tabl, piece *p);
int peut_aller_a_droite(tableau *tabl, piece *p);
int peut_tourner(tableau *tabl, piece *p, char pos);
void tourner(tableau *tab,piece *p, char pos);
int ligne_complete(tableau *tabl,int ligne[HAUTEUR_JEU]);
void enlever_ligne(tableau *tabl,int ligne[HAUTEUR_JEU]);

void bouger_piece(tableau *tabl,piece *p, char pos);

int compter_score(tableau *tabl,int ligne[(HAUTEUR_JEU-1)]);

int sauvegarder(tableau *tabl,piece *prochaine_piece,piece *p,int score,int temps);
int charger_sauvegarde(tableau *tabl,piece *prochaine_piece,piece *p,int score,int temps);

void initialiser_jeu(Jeu* jeu, int hauteur, int largeur);

void nouvelle_partie(Jeu* jeu);
void piece_descend(Jeu* jeu);
