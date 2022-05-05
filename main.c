#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prepa.h"
#include "plateau.c"
#include<time.h>
#include "sauvegarde.c"


int main(char argc, char**argv){

  Joueur *joueur = CreeJoueur();

  int actualmap_id = 0;
  int *p_actualmap_id = &actualmap_id;

  int actualmap_size = 29;
  int *p_actualmap_size = &actualmap_size;
  int (*actual_map)[*p_actualmap_size] = Labyrinthe_grid;
  srand(time(NULL));

  Liste_PNJ *liste_pnj = initListPNJ();
  Pnj *Marchand = AjoutPnj(liste_pnj,"Bob", 500, liste_objet_bob, "Je suis BOB", actual_map, *p_actualmap_size, 03,10,1);
  










  while(1){

    if(*p_actualmap_id == 0){
      *p_actualmap_size = 29;
      actual_map = Labyrinthe_grid;
    }
    else if(*p_actualmap_id == 1){
      *p_actualmap_size = 29;
      actual_map = Grotte_grid;

    }
    else if(*p_actualmap_id == 2){
      *p_actualmap_size = 20;
      actual_map = Combat_grid;

    }
    else if(*p_actualmap_id == 3){
      *p_actualmap_size = 43;
      actual_map = foret_grid;

    }

    system("clear");
    Afficher_map(actual_map, *p_actualmap_size,joueur);
    printf("%s %s : OR %d LVL %d ", joueur->nom, joueur->caste->nom_caste, joueur->argent,joueur->niveau);
    if(Deplacement(actual_map, p_actualmap_size, joueur, p_actualmap_id, liste_pnj) ==1){
      Combat(Afficher_map,Combat_grid, 20,joueur,p_actualmap_id, liste_objet[1]);
    }





  }



}
