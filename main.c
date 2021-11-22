#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prepa.h"
#include "plateau.c"
int main(char argc, char**argv){
  Joueur *joueur = CreeJoueur();
  while(1){
    system("clear");
    Afficher_map(Labyrinthe_grid, 27,29,joueur);
    Deplacement(joueur, Labyrinthe_grid);
    if(joueur->y == 2 && joueur->x == 21){
      printf("ARRIVER");
    }
  }



}
