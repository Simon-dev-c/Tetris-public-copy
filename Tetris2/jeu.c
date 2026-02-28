





/*
  void afficher_jeu(unsigned int hauteur, unsigned int largeur,Bouton* boutons) {

    boutons->nb_boutons = 0;

    int hauteur_bouton, largeur_bouton;

    hauteur_bouton = hauteur / 10;
    largeur_bouton = largeur / 6;

    creer_bouton(boutons,(largeur/2)-(largeur_bouton/2),(hauteur/2)-hauteur_bouton-50,hauteur_bouton,largeur_bouton,"Nouvelle\nPartie",largeur_bouton/9,MLV_COLOR_RED);

    creer_bouton(boutons,(largeur/2)-(largeur_bouton/2),(hauteur/2),hauteur_bouton,largeur_bouton,"Parametres",largeur_bouton/12,MLV_COLOR_ORANGE);
    
    creer_bouton(boutons,(largeur/2)-(largeur_bouton/2),(hauteur/2) + hauteur_bouton + 50,hauteur_bouton,largeur_bouton,"Leaderboard",largeur_bouton/12,MLV_COLOR_GREEN);
}

}*/






#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<MLV/MLV_all.h>

#include "jeu.h"

MLV_Color entier_to_couleur(int couleur){
    switch (couleur)
    {
    case 1:
        return MLV_COLOR_RED;
    case 2:
        return MLV_COLOR_BLUE;
    case 3:
        return MLV_COLOR_YELLOW;
    case 4:
        return MLV_COLOR_VIOLET;
    case 5:
        return MLV_COLOR_WHITE;
    case 6:
        return MLV_COLOR_CYAN;
    case 7:
        return MLV_COLOR_GREEN;
    case 0:
        return MLV_COLOR_BROWN;
    default:
        return MLV_COLOR_BLACK;
    }
}


void commencer_plateau(tableau *tabl){
    int i,j;
    for(i=0;i<HAUTEUR_JEU;i++){
        for(j=0;j<LARGEUR_JEU;j++){
            tabl->plateau[i][j] = 0;
            if (i == 20 || j == 0 || j == 11){
                tabl->plateau[i][j] = 1;
            }
        }
    }
}

void actualiser_plateau(tableau *tabl){
    int i,j,t_c,lg,ht;
    t_c = tabl->t_c;
    lg = tabl->lg;
    ht = tabl->ht;
    /*
    MLV_draw_filled_rectangle(lg/3.5+t_c-1,ht/10-1, 10*t_c+1 , 20*t_c+1  ,MLV_COLOR_WHITE);
    */
    for(i=0;i<HAUTEUR_JEU-1;i++){
        for(j=1;j<LARGEUR_JEU-1;j++){
            if (tabl->plateau[i][j] == 0){
                MLV_draw_filled_rectangle(j*t_c+lg/3.5,i*t_c+ht/10,t_c-2,t_c-2,MLV_COLOR_GRAY14);
            }else if (tabl->plateau[i][j] > 0){
                MLV_draw_filled_rectangle(j*t_c+lg/3.5,i*t_c+ht/10,t_c-2,t_c-2,entier_to_couleur(tabl->plateau[i][j]));
            }
        }
    }
}



void creer_piece(piece *p){
    int i,j;
    int num_piece;
    for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                p->figure[i][j] = 0;
            }
    }
    num_piece = rand()%7;
    p->couleur = num_piece+1;
    p->num_piece = num_piece;
    if (num_piece == 0){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (i == 1){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }else if (num_piece == 1){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (((i == 1) || (i == 2)) && ((j == 1) || (j == 2))){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }else if (num_piece == 2){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (((j != 0) && (i == 1)) || ((i == 2) && (j == 2))){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }else if (num_piece == 3){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (((j != 0) && (i == 1)) || ((i == 2) && (j == 1))){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }else if (num_piece == 4){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (((j != 0) && (i == 1)) || ((i == 2) && (j == 3))){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }else if (num_piece == 5){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if ((((i == j) || (j == i+1)) && (i != 0) && (i != 3))){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }else if (num_piece == 6){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (((j == 2) && ((i == 1) || (i == 2))) || ((i==2) && (j == 1)) || ((i==1) && (j == 3))){
                    p->figure[i][j] = num_piece+1;;
                }
            }
        }
    }
}

void afficher_prochaine_piece(tableau tabl,piece *p){
    int i,j,t_c,lg,ht;
    t_c = tabl.t_c;
    lg = tabl.lg;
    ht = tabl.ht;
    MLV_draw_filled_rectangle(lg/1.8,t_c+ht/10,t_c*4,t_c*4,MLV_COLOR_BLACK);
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0){
                MLV_draw_filled_rectangle(j*t_c+lg/1.8,i*t_c+ht/10,t_c-2,t_c-2,entier_to_couleur(p->couleur));
            }
        }
    }
}

void placer_piece(tableau tabl,piece *p){
    int i,j,t_c,lg,ht;
    t_c = tabl.t_c;
    lg = tabl.lg;
    ht = tabl.ht;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0){
                MLV_draw_filled_rectangle((j+p->pos_j)*t_c+lg/3.5,i*t_c+ht/10,t_c-2,t_c-2,entier_to_couleur(p->couleur));
            }
        }
    }        
}


void bouger_piece(tableau *tabl,piece *p, char pos){
    int i,j,t_c,lg,ht;
    t_c = tabl->t_c;
    lg = tabl->lg;
    ht = tabl->ht;

    switch (pos)
    {
    case 'd':
        p->pos_j++;
        break;
    case 'g':
        p->pos_j--;
        break;
    case 'b':
        p->pos_i++;
        break;
    default:
        break;
    }

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0){
                
                MLV_draw_filled_rectangle((j+p->pos_j)*t_c+lg/3.5,(i+p->pos_i)*t_c+ht/10,t_c-2,t_c-2,entier_to_couleur(p->couleur));

            }
        }
    }
    
}


int peut_est_place(tableau tabl,piece *p){
    int val = 0;
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if ((p->figure[i][j] > 0) && (tabl.plateau[i+p->pos_i+1][j+p->pos_j] > 0)){
                val = 1; 
            }
        }
    }
    return val;
}

void poser_piece(tableau *tabl,piece *p){
    int i,j;
     for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0){
                tabl->plateau[i+p->pos_i][j+p->pos_j] = p->figure[i][j];
                p->figure[i][j] = 0;
            }
        }
     }
}

void prochaine_piece_to_piece(piece *prochaine_piece, piece *piece){
    int i,j;
    piece->couleur = prochaine_piece->couleur;
    piece->pos_i = 0;
    piece->pos_j = 4;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            piece->figure[i][j] = prochaine_piece->figure[i][j];
        }
    }
}

int peut_aller_a_gauche(tableau *tabl, piece *p){
    int i,j;
    int verif;
    verif = 0;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0 && (tabl->plateau[i+p->pos_i][j+p->pos_j-1] > 0)){
                verif = 1;
            }
        }
    }
    return verif;
}

int peut_aller_a_droite(tableau *tabl, piece *p){
    int i,j;
    int verif;
    verif = 0;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0 && (tabl->plateau[i+p->pos_i][j+p->pos_j+1] > 0)){
                verif = 1;
            }
        }
    }
    return verif;
}

int peut_tourner(tableau *tabl, piece *p, char pos){
    int i,j;
    int verif;
    verif = 0;
    if (pos == 'l'){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (p->figure[i][j] > 0 && (tabl->plateau[j+p->pos_i][(3-i)+p->pos_j] > 0)){
                    verif = 1;
                }
            }
        }
    }
    if (pos == 'm'){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                if (p->figure[i][j] > 0 && (tabl->plateau[(3-j)+p->pos_i][(i)+p->pos_j] > 0)){
                    verif = 1;
                }
            }
        }
    }
    return verif;
}
void tourner(tableau *tab,piece *p, char pos){
    int i,j,t_c,lg,ht;
    int tabl[4][4];
    t_c = tab->t_c;
    lg = tab->lg;
    ht = tab->ht;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            tabl[i][j] = p->figure[i][j];
        }
    }
    if (pos == 'l'){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                p->figure[j][3-i] = tabl[i][j];
            }
        }
    }else if (pos == 'm'){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                p->figure[3-j][i] = tabl[i][j];
            }
        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (p->figure[i][j] > 0){
                MLV_draw_filled_rectangle((j+p->pos_j)*t_c+lg/3.5,(i+p->pos_i)*t_c+ht/10,t_c-2,t_c-2,entier_to_couleur(p->couleur));
            }
        }
    }
}

int ligne_complete(tableau *tabl, int ligne[HAUTEUR_JEU]){
    int i,j;
    int val_ligne;
    int val_ret = 0;
    for(i=0;i<(HAUTEUR_JEU-1);i++){
        val_ligne = 1;
        for(j=1;j<LARGEUR_JEU;j++){
            if (tabl->plateau[i][j] > 0 && tabl->plateau[i][j+1] > 0){
                val_ligne ++;
            }
        }
        if (val_ligne == LARGEUR_JEU){
            ligne[i] = 1;
            val_ret = 1;
        }else{
            ligne[i] = 0;
        }
    }
    return val_ret;
}

void enlever_ligne(tableau *tabl,int ligne[HAUTEUR_JEU]){
    int i,k,j;
    int decalage = 0;
    for(i=(HAUTEUR_JEU-1);i>0;i--){
        if (ligne[i] == 1){
            for(k=i+decalage;k>0;k--){
                for(j=1;j<LARGEUR_JEU-1;j++){
                    tabl->plateau[k][j] = tabl->plateau[k-1][j];
                    tabl->plateau[k-1][j] = 0;
                }
            }
            decalage ++;
        }
    }
}

int compter_score(tableau *tabl,int ligne[(HAUTEUR_JEU-1)]){
    int i,j, nb_ligne;
    int perfect = 1;
    nb_ligne = 0;
    for(i=0;i<(HAUTEUR_JEU-1);i++){
        if (ligne[i] == 1){
            nb_ligne += 1;
        }
    }
    for(i=0;i<(HAUTEUR_JEU-1);i++){
        for(j=1;j<LARGEUR_JEU-1;j++){
            if (tabl->plateau[i][j] > 0)
                perfect = 0;
        }
    }
    if (perfect == 0 || perfect > 0){
        switch (nb_ligne)
        {
        case 1:
            return 40;
        case 2:
            return 100;
        case 3:
            return 300;
        case 4:
            return 1200;
        default :
            return 0;
        }
    }else{
        switch (nb_ligne)
        {
        case 1:
            return 800;
        case 2:
            return 1200;
        case 3:
            return 1800;
        case 4:
            return 2000;
        default :
            return 0;
        }
    }
    return 0;
}


void initialiser_jeu(Jeu* jeu, int hauteur, int largeur) {

    jeu->tabl.lg = largeur;
    jeu->tabl.ht = hauteur;
    jeu->tabl.t_c = ((hauteur)/25);

    jeu->boutons.nb_boutons = 0;
    jeu->etat = DANS_MENU_PRINCIPAL;
    jeu->score = 0;
    jeu->temps = 0;
    jeu->intervalle_descend = 45;
    jeu->compteur = 0;
    jeu->est_descendu = 0;
    jeu->va_a_droite = 0;
    jeu->va_a_gauche = 0;

}

void nouvelle_partie(Jeu* jeu) {
    
    jeu->etat = DANS_JEU;
    MLV_clear_window(MLV_COLOR_BLACK);


    jeu->boutons.nb_boutons = 0;


    commencer_plateau(&jeu->tabl);

    creer_piece(&jeu->prochaine_piece);
                        
    prochaine_piece_to_piece(&jeu->prochaine_piece, &jeu->p);

    creer_piece(&jeu->prochaine_piece);

    MLV_draw_filled_rectangle(15,15,100,80,MLV_COLOR_BLACK);
                        
    MLV_draw_text(20,20,"Score : %d",MLV_COLOR_GREEN,jeu->score);
    
    
    jeu->temps ++;
    
    MLV_draw_text(20,50,"Tour : %d",MLV_COLOR_GREEN,jeu->temps);

                        
    afficher_prochaine_piece(jeu->tabl, &jeu->prochaine_piece);
    
    actualiser_plateau(&jeu->tabl);
    placer_piece(jeu->tabl,&jeu->p);
}


void piece_descend(Jeu* jeu) {
    
    if (jeu->etat == DANS_JEU)
    { 
        
        
        if (jeu->compteur == jeu->intervalle_descend)
        { 
            
            
            if (jeu->est_descendu)
            {
                
                jeu->est_descendu = 0;
                jeu->compteur = 0;

                    
            } else {
                
                actualiser_plateau(&jeu->tabl);
                bouger_piece(&jeu->tabl,&jeu->p,'b');

            }

            jeu->compteur = 0;

        } else
        {
            if (jeu->est_descendu)
            {
                jeu->est_descendu = 0;
                jeu->compteur = 0;

            } else
            {
                jeu->compteur++;
            }
        }
    }
}


























