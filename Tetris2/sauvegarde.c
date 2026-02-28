#include<stdlib.h>
#include<stdio.h>

#include "jeu.h"


int sauvegarder(tableau *tabl,piece *prochaine_piece,piece *p,int score,int temps){
    int i,j;
    FILE *f = NULL;
    f = fopen("sauvegarde.txt","w");
    if (f==NULL){
        return 0;
    }else{
        for(i=0;i<21;i++){
            for(j=0;j<12;j++){
                fprintf(f, "%d ", tabl->plateau[i][j]);
            }
            fprintf(f,"\n");
        }
        fprintf(f,"\n");
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                fprintf(f, "%d ", prochaine_piece->figure[i][j]);
            }
            fprintf(f,"\n");
        }
        fprintf(f,"\n");
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                fprintf(f, "%d ", p->figure[i][j]);
            }
            fprintf(f,"\n");
        }
        fprintf(f,"\n");

        fprintf(f, "%d  %d \n\n", p->pos_i,p->pos_j);
        fprintf(f, "%d\n\n", p->num_piece);
        fprintf(f, "%d\n\n", p->couleur);
        fprintf(f, "%d\n\n", prochaine_piece->num_piece);
        fprintf(f, "%d\n\n", prochaine_piece->couleur);
        fprintf(f, "%d\n", score);
        fprintf(f, "%d\n", temps);
    }
    fclose(f);
    
    return 1;
}

int charger_sauvegarde(tableau *tabl,piece *prochaine_piece,piece *p,int score,int temps){
    int i,j;
    FILE *f = NULL;
    f = fopen("sauvegarde.txt","r");
    if (f==NULL){
        return 0;
    }
    for(i=0;i<21;i++){
        for(j=0;j<12;j++){
            if (fscanf(f, "%hi", &tabl->plateau[i][j]) != 1) {
                printf("Erreur");
                fclose(f);
                return 0;  
            }
        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (fscanf(f, "%d", &prochaine_piece->figure[i][j]) != 1) {
                printf("Erreur");
                fclose(f);
                return 0;  
            }
        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if (fscanf(f, "%d", &p->figure[i][j]) != 1) {
                printf("Erreur");
                fclose(f);
                return 0; 
            }
        }
    }
    
    if (fscanf(f, "%d %d", &p->pos_i, &p->pos_j) != 2) {
        printf("Erreur");
        fclose(f);
        return 0; 
    }
    if (fscanf(f, "%d", &p->num_piece) != 1) {
        printf("Erreur");
        fclose(f);
        return 0;  
    }
    if (fscanf(f, "%d", &p->couleur) != 1) {
        printf("Erreur");
        fclose(f);
        return 0;  
    }
    if (fscanf(f, "%d", &prochaine_piece->num_piece) != 1) {
        printf("Erreur");
        fclose(f);
        return 0;  
    }
    if (fscanf(f, "%d", &prochaine_piece->couleur) != 1) {
        printf("Erreur");
        fclose(f);
        return 0;  
    }

    if (fscanf(f, "%d", &score) != 1) {
        printf("Erreur");
        fclose(f);
        return 0;  
    }
    
    if (fscanf(f, "%d", &temps) != 1) {
        printf("Erreur");
        fclose(f);
        return 0; 
    }
    fclose(f);
    
    return 1;
}