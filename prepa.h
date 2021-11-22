#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*--------------STRUCTURE DE DONNEES----------------*/
typedef struct Caste Caste;
struct Caste{
  char nom_caste[20];
  float attack_power;
  float defense;
  float magic_power;
  float vie;
  float agilite;

};


typedef struct Joueur Joueur;
struct Joueur{
  char nom[20];
  char sexe[10];
  int x;
  int y;
  Caste caste;
  int argent;
  int niveau;
};



typedef struct Objet Objet;
struct Objet{
  char nom[20];
  char type[20];
};

typedef struct Ennemi Ennemi;
struct Ennemi{
  char nom[20];
  float attack_power;
  float defense;
  float magic_power;
  float vie;
  float agilite;
  Objet *liste_objet;
  int argent;
  int niveau;
};




/*--------------FONCTIONS----------------*/


void *malloc_p(size_t s){
  void *p;
  if(!(p=malloc(s))){exit(EXIT_FAILURE);}
  return p;
}




Caste AssignerCaste(int n){
  Caste caste_choisis;
  if(n==1){
    strcpy(caste_choisis.nom_caste ,"Guerrier");
    caste_choisis.attack_power = 5;
    caste_choisis.defense = 5;
    caste_choisis.magic_power = 1;
    caste_choisis.vie = 5;
    caste_choisis.agilite = 3;
  }
  if(n==2){
    strcpy(caste_choisis.nom_caste , "Magicien");
    caste_choisis.attack_power = 1;
    caste_choisis.defense = 2;
    caste_choisis.magic_power = 9;
    caste_choisis.vie = 5;
    caste_choisis.agilite = 4;
  }
  if(n==3){
    strcpy(caste_choisis.nom_caste , "Assassin");
    caste_choisis.attack_power = 4;
    caste_choisis.defense = 2;
    caste_choisis.magic_power = 2;
    caste_choisis.vie = 2;
    caste_choisis.agilite = 9;
  }
  return caste_choisis;

}



Joueur *CreeJoueur(){
  Joueur *joueur = malloc(sizeof(*joueur));

  printf("Quel est votre nom ?\n");
  fgets(joueur->nom,20,stdin);

  printf("Quel est votre sexe ? (H/F)\n");
  fgets(joueur->sexe,10,stdin);

  joueur->x = 23;
  joueur->y = 26;

  printf("Choissisez une caste pour votre personnage :\n");
  printf("1 Guerrier | 2. Magicien | 3. Assassin\n");
  int choix;
  scanf("%d", &choix);
  while((getchar()) != '\n');
  joueur->caste = AssignerCaste(choix);

  joueur->argent = 0;
  joueur->niveau = 0;


  return joueur;

}



void Afficher_map(char grid[27][29], int longueur, int largeur, Joueur *joueur){

  grid[joueur->y][joueur->x] = 'T';

  for(int i =0; i<27;i++){
    for(int j =0; j<29;j++){
      if(i == joueur->y && j== joueur->x){
        printf("\033[0;33m");
        printf("%c", grid[i][j]);
        printf("\033[0m");
        printf("|");
      }else if(grid[i][j]=='X'){
        printf("\033[0;31m");
        printf("%c", grid[i][j]);
        printf("\033[0m");
        printf("|");
      }
      else{
        printf("%c|", grid[i][j]);
      }


    }
    printf("\n");
    for(int k = 0;k<29;k++){
      printf("--");
    }

    printf("\n");
  }


}

void Deplacement(Joueur *joueur, char grid[27][29]){

  int x_provisoire = joueur->x;
  int y_provisoire = joueur->y;

  char dir[5];
  fgets(dir, 5 ,stdin);
  dir[strcspn(dir, "\n")] =  0;
  if(strcmp(dir, "b")==0){
    y_provisoire ++;
  }
  if(strcmp(dir, "h")==0){
    y_provisoire --;
  }
  if(strcmp(dir, "d")==0){
    x_provisoire ++;
  }
  if(strcmp(dir, "g")==0){
    x_provisoire --;
  }

  if(grid[y_provisoire][x_provisoire] == ' '){
    grid[joueur->y][joueur->x] = ' ';
    joueur->x = x_provisoire;
    joueur->y = y_provisoire;
  }



}
