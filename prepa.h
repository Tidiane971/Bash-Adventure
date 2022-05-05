#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include "getkey.c"
#include <math.h>
/*--------------STRUCTURE DE DONNEES----------------*/

typedef struct Caste Caste;
typedef struct Objet Objet;
typedef struct Ennemi Ennemi;
typedef struct Joueur Joueur;
typedef struct Attaque Attaque;
typedef struct Inventaire Inventaire;
typedef struct Pnj Pnj;
typedef struct Liste_PNJ Liste_PNJ;
typedef struct Equipement Equipement;

typedef int (*Effet)(Joueur *joueur, Ennemi *ennemi, int cout_magie, int cout_vie);




struct Objet{
  char nom[20];
  char description[50];
  char type[20];
  int prix;
  int poid;
  int stat_vie;
  int stat_force;
  int stat_agilite;
  int stat_mana;
  int stat_defense;
};




typedef struct Slot Slot;
struct Slot{
  struct Objet objet;
  Slot *suivant;

};



struct Inventaire{
  struct Slot *head;

};



struct Attaque{
  int cout_mana;
  int cout_vie;
  char nom[20];
  Effet effet;

};


struct Ennemi{
  char nom[20];
  int attack_power;
  int defense;
  int magic_power;
  int vie;
  int agilite;
  struct Objet drop;
  int argent;
  int niveau;
  char etat[20];
  float exp;
  struct Attaque attaque_basique;
  int mana;

};




struct Caste{
  char nom_caste[20];
  int attack_power;
  int defense;
  int magic_power;
  int agilite;
  int mana;
  int max_mana;
  struct Attaque attaque_special;
  struct Attaque attaque_basique;

};
struct Joueur{
  char nom[20];
  char sexe[10];
  int x;
  int y;
  Caste *caste;
  int argent;
  int niveau;
  int vie;
  int max_vie;
  float xp;
  Inventaire *inventaire;
  int pointlibre;
  int poid;
  int poid_max;
  Equipement *stuff;
};

struct Pnj{
  char nom[20];
  int argent;
  Inventaire *inventaire;
  char dialogue[100];
  int id;
  int x;
  int y;
  Pnj *suivant;

};

struct Liste_PNJ{
  struct Pnj *head;

};



const Objet gelee_slime = {"Une Gelée de Slime", "UN met ", "ressources", 5,3,0,0,0,0,0};
const Objet baton = {"Baton", "Un baton plutôt dur ", "armes", 3, 5,0,2,0,0,0};
const Objet casque_base = {"Casque Basique", "Un casque en fer très rudimentaire ", "casque", 10, 8,0,0,0,0,4};
const Objet armure_base = {"Armure Basique", "Un armure en fer très rudimentaire ", "armure", 15, 20,0,0,0,0,10};
const Objet botte_base = {"Botte Basique", "Des bottes en fer très rudimentaires ", "bottes", 12, 13,0,0,0,0,5};
const Objet bouclier_base = {"Bouclier Basique", "Un bouclier en fer très rudimentaire ", "bouclier", 8, 17,0,0,0,0,8};


Objet liste_objet[2] = {baton, gelee_slime};
Objet liste_objet_bob[6] = {baton, gelee_slime,casque_base, armure_base, botte_base,bouclier_base};
Objet liste_objet_joueur[6] = {baton, gelee_slime,casque_base, armure_base, botte_base,bouclier_base};

Objet liste_objet_total[6] = {baton, gelee_slime,casque_base, armure_base, botte_base,bouclier_base};



void *malloc_p(size_t s){
  void *p;
  if(!(p=malloc(s))){exit(EXIT_FAILURE);}
  return p;
}





void ajoutObjet(Inventaire *inventaire, Objet drop){
  Slot *slot = malloc_p(sizeof(*slot));
  slot->objet = drop;

  Slot *actual_slot = inventaire->head;
  while(actual_slot->suivant != NULL){actual_slot = actual_slot->suivant;}
  actual_slot->suivant = slot;
  slot->suivant=NULL;


  actual_slot = inventaire->head;

}


void suppObjet(Inventaire *inventaire, char nomASupp[20]){
  int found = 0;
  int i;



  Slot *actual_slot = inventaire->head;

  if(strcmp(inventaire->head->objet.nom,nomASupp)==0){
    found = 1;
    Slot *aSupp = inventaire->head;
    inventaire->head = inventaire->head->suivant;
    free(aSupp);
  }



  while(actual_slot->suivant!=NULL && found==0){
    if(strcmp(actual_slot->suivant->objet.nom,nomASupp)==0){
      found = 1;
      Slot *aSupp = actual_slot->suivant;
      actual_slot->suivant = actual_slot->suivant->suivant;
      free(aSupp);
    }
  }
  if(!found){printf("Cet objet n'existe pas ! \n");}


}


void afficheInventaire(Inventaire *inventaire, Joueur *joueur){
  Slot *actual_slot = inventaire->head;
  int i=1;

  for(int k=0;k<30;k++){printf("X");}
  printf("\n");

  for(int k = 0; k<16;k++){
    if(k==0){printf("INVENTAIRE :\n");}
    if(k==2){
      printf("Or %s : %d\n",joueur->nom, joueur->argent);
      printf("Poids : %d/%d\n",joueur->poid, joueur->poid_max);
    }
    if(k==5){
      if(actual_slot->objet.nom==NULL){printf("VIDE\n");}
      else{
        while(actual_slot!=NULL){
            printf("%d - %s : %s : %d OR POIDS : %d\n",i,actual_slot->objet.nom, actual_slot->objet.description, actual_slot->objet.prix, actual_slot->objet.poid);
            actual_slot = actual_slot->suivant;
            i++;
            }

          }
        }
        printf(" \n");
      }








  }



void afficheCaracteristique( Joueur *joueur){
    //
    // int force_additionnel = joueur->stuff->armes.stat_force + joueur->stuff->armure.stat_force + joueur->stuff->casque.stat_force + joueur->stuff->bottes.stat_force + joueur->stuff->bouclier.stat_force;
    // int vie_additionnel = joueur->stuff->armes.stat_vie + joueur->stuff->armure.stat_vie + joueur->stuff->casque.stat_vie + joueur->stuff->bottes.stat_vie + joueur->stuff->bouclier.stat_vie;
    // int agilite_additionnel = joueur->stuff->armes.stat_agilite + joueur->stuff->armure.stat_agilite + joueur->stuff->casque.stat_agilite + joueur->stuff->bottes.stat_agilite + joueur->stuff->bouclier.stat_agilite;
    // int mana_additionnel = joueur->stuff->armes.stat_mana + joueur->stuff->armure.stat_mana + joueur->stuff->casque.stat_mana + joueur->stuff->bottes.stat_mana + joueur->stuff->bouclier.stat_mana;
    // int defense_additionnel = joueur->stuff->armes.stat_defense + joueur->stuff->armure.stat_defense + joueur->stuff->casque.stat_defense + joueur->stuff->bottes.stat_defense + joueur->stuff->bouclier.stat_defense;
    int ouvert = 1;
    char c;
    while(ouvert==1){
      system("clear");

      for(int k=0;k<30;k++){printf("X");}
      printf("\n");

      for(int k = 0; k<16;k++){
        if(k==1){
          printf("%s %s\n",joueur->nom, joueur->sexe);
          printf("%s LVL %d\n",joueur->caste->nom_caste, joueur->niveau);
          printf("XP : %.1f/%.1f | PROCHAIN NIVEAU DANS : %.1fXP\n",joueur->xp,pow( ((joueur->niveau+1)/0.07),2 ),pow( ((joueur->niveau+1)/0.07),2 ) - joueur->xp );
          printf("\n");
          printf("\n");
        }


        if(k==3){
              printf("VIE : %d/%d \n",joueur->vie, joueur->max_vie);
              printf("FORCE : %d\n",joueur->caste->attack_power);
              printf("AGILITE : %d \n",joueur->caste->agilite);
              printf("MANA : %d/%d \n",joueur->caste->mana, joueur->caste->max_mana);
              printf("DEFENSE : %d \n",joueur->caste->defense);
              printf("\n");
              printf("\n");
              printf("Points de caractéristique non Attribué : %d\n",joueur->pointlibre);
              printf("\n");
              printf("\n");
              if(joueur->pointlibre > 0){
                printf("Voulez vous attribuez vos points ? (y): \n");
                c = getKey();
                if(c=='y'){
                  printf("\n");
                  printf("Ou voulez-vous attribuer des points ? \n");
                  printf("1 : VIE | 2 : FORCE | 3 : AGILITE | 4 : MANA\n");
                  char carac;
                  carac = getKey();
                  printf("\n");
                  int nb_pts;
                  if(carac=='1'){
                    printf("Combien de points voulez vous attribuer en VIE ? : ");
                    scanf("%d",&nb_pts);
                    while((getchar()) != '\n');
                    if(nb_pts<=joueur->pointlibre){
                      joueur->max_vie += nb_pts;
                      joueur->vie += nb_pts;
                      joueur->pointlibre -= nb_pts;
                    }else{
                      printf("Vous n'avez pas assez de points pour cette action !");
                      fflush(stdout);
                      sleep(1);
                    }
                  }
                  else if(carac =='2'){
                    printf("Combien de points voulez vous attribuer en FORCE ? : ");
                    scanf("%d",&nb_pts);
                    while((getchar()) != '\n');
                    if(nb_pts<=joueur->pointlibre){
                      joueur->caste->attack_power += nb_pts;
                      joueur->pointlibre -= nb_pts;
                      joueur->poid_max += nb_pts*2;
                    }else{
                      printf("Vous n'avez pas assez de points pour cette action !");
                      fflush(stdout);
                      sleep(1);
                    }
                  }
                  else if(carac=='3'){
                    printf("Combien de points voulez vous attribuer en AGILITE ? : ");
                    scanf("%d",&nb_pts);
                    while((getchar()) != '\n');
                    if(nb_pts<=joueur->pointlibre){
                      joueur->caste->agilite += nb_pts;
                      joueur->pointlibre -= nb_pts;
                    }else{
                      printf("Vous n'avez pas assez de points pour cette action !");
                      fflush(stdout);
                      sleep(1);
                    }
                  }
                  else if(carac=='4'){
                    printf("Combien de points voulez vous attribuer en MANA ? : ");
                    scanf("%d",&nb_pts);
                    while((getchar()) != '\n');
                    if(nb_pts<=joueur->pointlibre){
                      joueur->caste->max_mana += nb_pts;
                      joueur->caste->mana += nb_pts;
                      joueur->pointlibre -= nb_pts;
                    }else{
                      printf("Vous n'avez pas assez de points pour cette action !");
                      fflush(stdout);
                      sleep(1);
                    }

                  }


                }
                else{


                }


              }else{
                  c = getKey();
              }






            printf(" \n");
          }
        }


      for(int k=0;k<30;k++){printf("X");}
      printf("\n");
      if(c=='c'){ouvert = 0;}

    }



}











int BouleDeFeu(Joueur *joueur, Ennemi *ennemi, int cout_magie, int cout_vie){
  if(joueur->caste->mana > cout_magie){
    int degat = (joueur->caste->magic_power * 1.2)/ ennemi->defense;
    ennemi->vie -= degat;
    joueur->caste->mana -= cout_magie;
    return degat;
  }
  return 0;
}

int Fracas(Joueur *joueur, Ennemi *ennemi, int cout_magie, int cout_vie){
  if(joueur->caste->mana > cout_magie){
    int degat = (joueur->caste->attack_power * 0.8)/ ennemi->defense;
    strcpy(ennemi->etat , "sonne");
    ennemi->vie -= degat;

    joueur->caste->mana -= cout_magie;

    return degat;
  }
  return 0;
}

int Sournoiserie(Joueur *joueur, Ennemi *ennemi, int cout_magie, int cout_vie){
  if(joueur->caste->mana > cout_magie){
    int degat = (joueur->caste->attack_power * 0.5 + joueur->caste->agilite)/ ennemi->defense;
    strcpy(ennemi->etat , "poison");
    ennemi->vie -= degat;
    joueur->caste->mana -= cout_magie;
    return degat;
  }
  return 0;
}

int Basique(Joueur *joueur, Ennemi *ennemi, int cout_magie, int cout_vie){
  int degat = (joueur->caste->attack_power * 0.3 )/ ennemi->defense;
  ennemi->vie -= degat;
  return degat;
}

int BasiqueEnnemi(Joueur *joueur, Ennemi *ennemi, int cout_magie, int cout_vie){
  int degat = (ennemi->attack_power * 0.3 )/ joueur->caste->defense;
  joueur->vie -= degat;
  return degat;
}





/*--------------FONCTIONS----------------*/






Caste *AssignerCaste(int n){
  Caste *caste_choisis = malloc(sizeof(Caste));
  if(n==1){
    strcpy(caste_choisis->nom_caste ,"Guerrier");
    caste_choisis->attack_power = 5;
    caste_choisis->defense = 5;
    caste_choisis->agilite = 3;
    caste_choisis->mana = 5;
    caste_choisis->max_mana = 5;
    caste_choisis->magic_power = caste_choisis->mana/4;
    strcpy(caste_choisis->attaque_special.nom , "Fracas");
    caste_choisis->attaque_special.effet = Fracas;
    caste_choisis->attaque_special.cout_mana = 2;
    caste_choisis->attaque_special.cout_vie = 0;

    strcpy(caste_choisis->attaque_basique.nom , "Attaque Basique");
    caste_choisis->attaque_basique.effet = Basique;
    caste_choisis->attaque_basique.cout_mana = 0;
    caste_choisis->attaque_basique.cout_vie = 0;


  }
  if(n==2){
    strcpy(caste_choisis->nom_caste , "Magicien");
    caste_choisis->attack_power = 1;
    caste_choisis->defense = 2;
    caste_choisis->agilite = 4;
    caste_choisis->mana =20;
    caste_choisis->max_mana = 20;
    caste_choisis->magic_power = caste_choisis->mana/4;
    strcpy(caste_choisis->attaque_special.nom , "Boule de feu");
    caste_choisis->attaque_special.effet = BouleDeFeu;
    caste_choisis->attaque_special.cout_mana = 5;
    caste_choisis->attaque_special.cout_vie = 0;

    strcpy(caste_choisis->attaque_basique.nom , "Attaque Basique");
    caste_choisis->attaque_basique.effet = Basique;
    caste_choisis->attaque_basique.cout_mana = 0;
    caste_choisis->attaque_basique.cout_vie = 0;

  }
  if(n==3){
    strcpy(caste_choisis->nom_caste , "Assassin");
    caste_choisis->attack_power = 4;
    caste_choisis->defense = 2;
    caste_choisis->agilite = 9;
    caste_choisis->mana = 5;
    caste_choisis->max_mana = 5;
    caste_choisis->magic_power = caste_choisis->mana/4;
    strcpy(caste_choisis->attaque_special.nom , "Sournoiserie");
    caste_choisis->attaque_special.effet = Sournoiserie;
    caste_choisis->attaque_special.cout_mana = 1;
    caste_choisis->attaque_special.cout_vie = 0;

    strcpy(caste_choisis->attaque_basique.nom , "Attaque Basique");
    caste_choisis->attaque_basique.effet = Basique;
    caste_choisis->attaque_basique.cout_mana = 0;
    caste_choisis->attaque_basique.cout_vie = 0;

  }
  return caste_choisis;

}



Joueur *CreeJoueur(){
  Joueur *joueur = malloc(sizeof(*joueur));

  printf("Quel est votre nom ?\n");
  fgets(joueur->nom,20,stdin);
  joueur->nom[strcspn(joueur->nom,"\n")]=0;

  printf("Quel est votre sexe ? (H/F)\n");
  fgets(joueur->sexe,10,stdin);

  joueur->x = 14;
  joueur->y = 17;

  printf("Choissisez une caste pour votre personnage :\n");
  printf("1 Guerrier | 2. Magicien | 3. Assassin\n");
  int choix;
  scanf("%d", &choix);
  while((getchar()) != '\n');
  joueur->caste = AssignerCaste(choix);

  joueur->argent = 100;
  joueur->vie = 5;
  joueur->max_vie = 5;
  joueur->xp = 0;
  joueur->niveau = sqrt(joueur->xp*0.0049);
  joueur->pointlibre = 10;
  joueur->poid = 63;
  joueur->poid_max= 100;
  joueur->stuff = malloc(sizeof(joueur->stuff));

  joueur->inventaire = malloc_p(sizeof(joueur->inventaire));
  Slot *slot = malloc_p(sizeof(*slot));

  slot->objet = liste_objet[0];
  slot->suivant = NULL;
  joueur->inventaire->head = slot;
  for(int k=2; k<6;k++){
    ajoutObjet(joueur->inventaire, liste_objet_joueur[k]);
  }
  free(slot);






  return joueur;

}




Ennemi *CreeEnnemi(char nom[20],float attack_power,float defense, float magic_power, int vie , float agilite, Objet drop, int argent, int niveau , char etat[20], int exp, int mana){
  Ennemi *ennemi = malloc(sizeof(*ennemi));


  strcpy(ennemi->nom,nom);

  ennemi->attack_power = attack_power;
  ennemi->defense = defense;
  ennemi->magic_power = magic_power;
  ennemi->vie = vie;
  ennemi->agilite = agilite;
  ennemi->drop = drop;
  ennemi->argent = argent;
  ennemi->niveau = niveau;
  strcpy(ennemi->etat, etat);
  ennemi->exp = exp;
  ennemi-> mana;


  strcpy(ennemi->attaque_basique.nom , "Attaque Basique"); // METTRE FONCTION EN PARAMMETRE
  ennemi->attaque_basique.effet = BasiqueEnnemi;
  ennemi->attaque_basique.cout_mana = 0;
  ennemi->attaque_basique.cout_vie = 0;

  return ennemi;

}

Liste_PNJ *initListPNJ(){
  Liste_PNJ *liste = malloc_p(sizeof(*liste));
  Pnj *pnj = malloc_p(sizeof(*pnj));

  pnj->suivant = NULL;
  liste->head =pnj;
  liste->head->id = 0;


  return liste;
}

void *AjoutPnj(Liste_PNJ *liste, char nom[20], int argent, Objet liste_objet[5], char dialogue[100], void *map, int SIZE, int x, int y, int id){
  Pnj *pnj = malloc(sizeof(*pnj));


  strcpy(pnj->nom,nom);

  pnj->argent = argent;

  strcpy(pnj->dialogue, dialogue);

  pnj->inventaire = malloc_p(sizeof(*pnj->inventaire));
  Slot *slot = malloc_p(sizeof(*slot));

  slot->objet = liste_objet[0];
  slot->suivant = NULL;
  pnj->inventaire->head = slot;

  for(int k=1;k<5;k++){
    ajoutObjet(pnj->inventaire,liste_objet[k]);
  }

  pnj->id = id;
  pnj->x = x;
  pnj->y = y;

  int (*array)[SIZE] = map;
  array[pnj->y][pnj->x] = 3;

  if(liste->head->id == 0){
    liste->head = pnj;
    liste->head->suivant = NULL;
  }
  else{
    Pnj *actual_pnj = liste->head;
    while(actual_pnj->suivant != NULL){actual_pnj = actual_pnj->suivant;}
    actual_pnj->suivant = pnj;
    pnj->suivant=NULL;
    actual_pnj = liste->head;
  }




}







void Afficher_map(void *map, int SIZE, Joueur *joueur){
  int (*array)[SIZE] = map;
  array[joueur->y][joueur->x]= 2;

  for(int i =0; i<SIZE;i++){
    for(int j =0; j<SIZE;j++){

      if(i == joueur->y && j== joueur->x){

        printf("\033[1;90m");
        printf("\033[42m");
        printf(" J ");
        printf("\033[0m");

      }else if(array[i][j]==1){

        printf("\033[41m");
        printf("   ");
        printf("\033[0m");

      }
      else if(array[i][j]==0){
        printf("   ");

      }
      else if(array[i][j]==2){
        printf("\033[1;90m");
        printf("\033[41m");
        printf(" V ");
        printf("\033[0m");

      }
      else if(array[i][j] == 3){
        printf("\033[1;90m");
        printf("\033[42m");
        printf("PNJ");
        printf("\033[0m");

      }
      else if(array[i][j]/100000==5){
        printf("\033[1;90m");
        printf("\033[47m");
        printf(" O ");
        printf("\033[0m");

      }



    }



    printf("\n");
  }


}

void interraction(int x , int y, Liste_PNJ *liste_pnj, Joueur *joueur,void *map, int *SIZE){
  Pnj *actual_pnj = liste_pnj->head;

  int cont = 8;
  while(actual_pnj->x != x || actual_pnj->y != y){
    actual_pnj = actual_pnj->suivant;
  }


  while(cont !=0){

    if(cont==8){
      system("clear");
      Afficher_map(map, *SIZE, joueur);
      for(int k=0;k<60;k++){printf("X");}
      printf("\n");
      for(int k = 0; k<8;k++){
        if(k==3){
          printf("X%19cX", ' ');
          printf("%9c1%9cX",' ',' ');
          printf("%9c2%8cX", ' ',' ');
          printf("\n");
        }
        if(k==4){
          printf("X%8c%s%8cX", ' ',actual_pnj->nom,' ');
          printf("%6cDISCUTER%5cX",' ',' ');
          printf("%5cCOMMERCER%4cX", ' ',' ');
          printf("\n");
        }
        else{
          printf("X%19cX%19cX%18cX\n",' ',' ',' ');
        }

      }
      for(int k=0;k<60;k++){printf("X");}
      printf("\n");
      cont = scangets();
      if(cont == 'r'){cont=0;}
    }

    else if(cont == 1){
      system("clear");
      Afficher_map(map, *SIZE, joueur);

      for(int k=0;k<30;k++){printf("X");}
      printf("\n");

      for(int k = 0; k<16;k++){
        if(k==5){

          printf("%s", actual_pnj->dialogue);
        }
        printf(" \n");
      }
      for(int k=0;k<30;k++){printf("X");}
      fflush(stdout);
      sleep(3);
      cont = 8;
    }


    else if(cont == 2){
      int choix = 0;
      system("clear");
      Afficher_map(map, *SIZE, joueur);
      for(int k=0;k<30;k++){printf("X");}
      printf("\n");

      for(int k = 0; k<16;k++){
        if(k==5){

          printf(" -1 - Acheter" );
          printf(" -2 - Vendre" );

        }
        printf(" \n");
      }
      for(int k=0;k<30;k++){printf("X");}
      printf(" \n");

      choix = scangets();




      if(choix == 1){
        system("clear");
        Afficher_map(map, *SIZE, joueur);
        afficheInventaire(actual_pnj->inventaire, joueur);

        int article;
        Slot *actual_slot = actual_pnj->inventaire->head;
        article = scangets();
        if(article == 'r'){cont=2;}
        else{

          for(int k =0; k < article-1 ; k++){
            actual_slot = actual_slot->suivant;
          }
          system("clear");
          Afficher_map(map, *SIZE, joueur);
          printf("Etes-vous sur de vouloir acheter : %s pour le prix de %d Or ?", actual_slot->objet.nom, actual_slot->objet.prix);

          int confirmation =0;
          confirmation = scangets();

          if(confirmation == 'y'){
            if(joueur->poid+actual_slot->objet.poid <= joueur->poid_max){
              joueur->argent -= actual_slot->objet.prix;
              ajoutObjet(joueur->inventaire, actual_slot->objet);
              joueur->poid += actual_slot->objet.poid;
              actual_pnj->argent += actual_slot->objet.prix;
              suppObjet(actual_pnj->inventaire, actual_slot->objet.nom);
              cont = 8;
            }
            else{
              printf("Vous n'avez pas assez de place pour effectuer cette transaction !");
            }
          }
          else{cont=2;}
        }
        }


      else if(choix == 2){
        system("clear");
        Afficher_map(map, *SIZE, joueur);
        afficheInventaire(joueur->inventaire, joueur);

        int article;
        Slot *actual_slot = joueur->inventaire->head;

        article = scangets();
        if(article=='r'){cont=2;}
        else{
          for(int k =0; k < article-1 ; k++){
            actual_slot = actual_slot->suivant;
          }
          system("clear");
          Afficher_map(map, *SIZE, joueur);
          printf("Etes-vous sur de vouloir vendre : %s pour le prix de %d Or ?(y/n)", actual_slot->objet.nom, actual_slot->objet.prix);

          int confirmation =0;
          confirmation = scangets();

          if(confirmation == 'y'){
            joueur->argent += actual_slot->objet.prix;
            ajoutObjet(actual_pnj->inventaire, actual_slot->objet);
            joueur->poid -= actual_slot->objet.poid;

            actual_pnj->argent -= actual_slot->objet.prix;
            suppObjet(joueur->inventaire, actual_slot->objet.nom);
            cont = 8;
          }
          else{cont=2;}
        }
      }

      else if(choix=='r'){cont=8;}


    }

  }
}

int Deplacement(void *map, int *SIZE,Joueur *joueur, int *map_id,  Liste_PNJ *liste_pnj){

  int (*array)[*SIZE] = map;
  int x_provisoire = joueur->x;
  int y_provisoire = joueur->y;

  int c = getKey();
  if(c=='s'){
    y_provisoire ++;
  }
  if(c=='z'){
    y_provisoire --;
  }
  if(c=='d'){
    x_provisoire ++;
  }
  if(c=='q'){
    x_provisoire --;
  }
  if(c=='e'){
    system("clear");
    int ferme_inventaire = 0;
    char inv[5];
    while(ferme_inventaire == 0){
      afficheInventaire(joueur->inventaire, joueur);
      int c = getKey();
      if(c=='e'){ferme_inventaire=1;}

    }
  }
  if(c=='c'){
    afficheCaracteristique(joueur);
  }

  int prochaine_case = array[y_provisoire][x_provisoire];

  if(prochaine_case == 0){
    array[joueur->y][joueur->x] = 0;
    joueur->x = x_provisoire;
    joueur->y = y_provisoire;
    if(*map_id!=0){
      int r = rand() %8;
      if(r==1){return 1;}
    }

  }
  else if(prochaine_case== 3){
    interraction(x_provisoire, y_provisoire, liste_pnj,joueur, map , SIZE);
  }
  else if(prochaine_case/100000 == 5){
    array[joueur->y][joueur->x] = 0;
    char info[7];
    sprintf(info,"%d",prochaine_case);
    *map_id = info[1] - '0';
    if(info[2]=='0'){
      joueur->x =( info[2] - '0' )+ (info[3]  - '0');
    }
    else{
      joueur->x =(( info[2] - '0' )*10)+ (info[3]  - '0');
    }

    if(info[4]=='0'){
      joueur->y =( info[4] - '0' )+ (info[5]  - '0');
    }
    else{
      joueur->y =(( info[4] - '0' )*10)+ (info[5]  - '0');
    }
  }
  return 0;

}


void Combat(void (*afficher)(void *, int , Joueur * ) , void *map, int SIZE,Joueur *joueur, int *map_id, Objet drop){
  int (*array)[SIZE] = map;


  Ennemi *ennemi = CreeEnnemi("Slime", 1, 1, 0, 10, 1, drop, 15, 1, "normal", 500,0);
  //Ennemi *ennemi = CreeEnnemi("Goblin", 10, 2, 1, 3, 5, drop, 30, 3, "normal", 1500,4);
  // Ennemi *liste_ennemi = NULL;
  // r = rand()%3+1;
  // for(int i = 0; i<r; i++){
  //   i =
  // }
  array[3][6] = 2;

  int cont = 8;
  int initialX = joueur->x;
  int initialY = joueur->y;
  joueur->y = 15;
  joueur->x = 10;
  int r = 0;

  while(cont){
    system("clear");
    afficher(map, SIZE, joueur);

/*--------------------------------------*/

    if(cont ==8){


      for(int k=0;k<60;k++){printf("X");}
      printf("\n");
      for(int k = 0; k<8;k++){
        if(k==3){
          printf("%17c%s %s : %dPV | %dMANA\n",' ',joueur->caste->nom_caste, joueur->nom,joueur->vie,joueur->caste->mana);
        }
        else if(k==6){
          printf("%17c%s : %dPV\n",' ', ennemi->nom,ennemi->vie);
        }
        else{
          printf("\n");
        }

      }



      for(int k=0;k<60;k++){printf("X");}
      printf("\n");
      for(int k = 0; k<8;k++){
        if(k==3){
          printf("X%9c1%9cX", ' ',' ');
          printf("%9c2%9cX",' ',' ');
          printf("%9c3%8cX", ' ',' ');
          printf("\n");
        }
        if(k==4){
          printf("X%6cATTAQUE%6cX", ' ',' ');
          printf("%7cOBJETS%6cX",' ',' ');
          printf("%7cFUITE%6cX", ' ',' ');
          printf("\n");
        }
        else{
          printf("X%19cX%19cX%18cX\n",' ',' ',' ');
        }

      }
      for(int k=0;k<60;k++){printf("X");}
      scanf("%d",&cont);
      while((getchar()) != '\n');

    }

/*--------------------------------------*/

    else if(cont==1){
      int choix_attaque;
      for(int k=0;k<30;k++){printf("X");}
      printf("\n");
      for(int k = 0; k<16;k++){
        if(k==5){
          printf("1- %s\n", joueur->caste->attaque_basique.nom);
        }
        else if(k==10){
          printf("2- %s\n", joueur->caste->attaque_special.nom);
        }
        printf(" \n");
      }
      for(int k=0;k<30;k++){printf("X");}

      scanf("%d",&choix_attaque);
      while((getchar()) != '\n');


      if(choix_attaque==1){
        int attaque = joueur->caste->attaque_basique.effet(joueur, ennemi, joueur->caste->attaque_basique.cout_mana, joueur->caste->attaque_basique.cout_vie);
        system("clear");

        afficher(map, SIZE, joueur);

        for(int k=0;k<30;k++){printf("X");}
        printf("\n");

        for(int k = 0; k<16;k++){
          if(k==5){
            printf("%s Utilise %s sur %s\n", joueur->nom,joueur->caste->attaque_basique.nom, ennemi->nom);
            printf("Cela fait %d dégat !",attaque);
          }
          printf(" \n");
        }
        for(int k=0;k<30;k++){printf("X");}
        fflush(stdout);
        sleep(3);
        cont = 8;

      }
      else if(choix_attaque==2){
        int attaque = joueur->caste->attaque_special.effet(joueur, ennemi, joueur->caste->attaque_special.cout_mana, joueur->caste->attaque_special.cout_vie);
        if(attaque==0){
          system("clear");
          afficher(map, SIZE, joueur);

          for(int k=0;k<30;k++){printf("X");}
          printf("\n");

          for(int k = 0; k<16;k++){
            if(k==5){

              printf("Vous n'avez pas assez de Mana pour faire cette attaque");
            }
            printf(" \n");
          }
          for(int k=0;k<30;k++){printf("X");}
          fflush(stdout);
          sleep(3);
          cont = 8;
        }else{


        system("clear");
        afficher(map, SIZE, joueur);

        for(int k=0;k<30;k++){printf("X");}
        printf("\n");

        for(int k = 0; k<16;k++){
          if(k==5){
            printf("%s Utilise %s sur %s\n", joueur->nom,joueur->caste->attaque_special.nom, ennemi->nom);
            printf("Cela fait %d dégat !",attaque);
          }
          printf(" \n");
        }
        for(int k=0;k<30;k++){printf("X");}
        fflush(stdout);
        sleep(3);
        cont = 8;
      }

      }
      if(ennemi->vie >0 && joueur->vie >0){
        int ordi_attaque = ennemi->attaque_basique.effet(joueur, ennemi, ennemi->attaque_basique.cout_mana, ennemi->attaque_basique.cout_vie);
        system("clear");
        afficher(map, SIZE, joueur);

        for(int k=0;k<30;k++){printf("X");}
        printf("\n");

        for(int k = 0; k<16;k++){
          if(k==5){
            printf("%s Utilise %s sur %s\n", ennemi->nom,ennemi->attaque_basique.nom, joueur->nom);
            printf("Cela fait %d dégat !",ordi_attaque);
          }
          printf(" \n");
        }
        for(int k=0;k<30;k++){printf("X");}
        fflush(stdout);
        sleep(3);
        cont = 8;
      }

    }
    else if(cont==2){
      int ferme_inventaire = 0;
      char inv[5];
      while(ferme_inventaire == 0){
        afficheInventaire(joueur->inventaire, joueur);
        int c = getKey();
        if(c=='e'){ferme_inventaire=1;}

      }
      cont = 8;
    }
    else if(cont == 3){
      if(joueur->niveau < ennemi->niveau){ r = rand() % (ennemi->niveau-joueur->niveau) ;}
      else if(joueur->niveau == ennemi->niveau){ r = rand() % 2 ;}
      else if(joueur->niveau > ennemi->niveau){printf("yo"); r = 1 ;}
      if(r == 1){
        system("clear");
        afficher(map, SIZE, joueur);

        for(int k=0;k<30;k++){printf("X");}
        printf("\n");

        for(int k = 0; k<16;k++){
          if(k==5){
            printf("%s a fui le combat...\n", joueur->nom);
          }
          printf(" \n");
        }
        for(int k=0;k<30;k++){printf("X");}
        fflush(stdout);
        sleep(3);
        cont = 0;
      }
      else{
        system("clear");
        afficher(map, SIZE, joueur);

        for(int k=0;k<30;k++){printf("X");}
        printf("\n");

        for(int k = 0; k<16;k++){
          if(k==5){
            printf("Vous n'avez pas réussi à fuir...\n");
          }
          printf(" \n");
        }
        for(int k=0;k<30;k++){printf("X");}
        fflush(stdout);
        sleep(3);
        cont = 8;
      }
      }


    if(ennemi->vie <=0){
      int ancien_niveau = joueur->niveau;
      joueur->argent += ennemi->argent;
      joueur->xp += ennemi->exp;
      joueur->niveau =sqrt(joueur->xp*0.0049);

      system("clear");
      afficher(map, SIZE, joueur);

      for(int k=0;k<30;k++){printf("X");}
      printf("\n");

      for(int k = 0; k<16;k++){
        if(k==5){
          printf("%s a été vaincu !\n", ennemi->nom);
          if(joueur->poid + ennemi->drop.poid <= joueur->poid_max){
            ajoutObjet(joueur->inventaire, ennemi->drop);
            joueur->poid += ennemi->drop.poid;
            printf("Vous avez trouvé %s !\n",ennemi->drop.nom);
          }
          else{
            printf("Un %s a été trouvé mais vous n'avez pas la place de le récupérer !\n",ennemi->drop.nom);
          }
          printf("Vous avez gagné %.1f points d'exp et %d or !\n",ennemi->exp, ennemi->argent);
        }
        printf(" \n");
      }
      for(int k=0;k<30;k++){printf("X");}
      fflush(stdout);
      sleep(3);
      cont = 0;

      if(ancien_niveau<joueur->niveau){
        int niveau_gagne = joueur->niveau - ancien_niveau;
        system("clear");
        afficher(map, SIZE, joueur);

        for(int k=0;k<30;k++){printf("X");}
        printf("\n");

        for(int k = 0; k<16;k++){
          if(k==5){
            printf("Vous avez gagné %d niveau(x) !\n",niveau_gagne);
            printf("Vous avez gagné %d points de Vie !\n", 5*niveau_gagne);
            joueur->max_vie += 5*niveau_gagne;
            joueur->vie = joueur->max_vie;

            if(strcmp(joueur->caste->nom_caste , "Guerrier")==0){
              printf("Vous avez gagné %d points de Force !\n",5*niveau_gagne);
              joueur->caste->attack_power += 5*niveau_gagne;
              joueur->poid_max+= 5*niveau_gagne*2;
              printf("Vous avez gagné %d points d'Agilité !\n",2*niveau_gagne);
              joueur->caste->agilite += 2*niveau_gagne;
              printf("Vous avez gagné %d points de Mana !\n",1*niveau_gagne);
              joueur->caste->max_mana += 1*niveau_gagne;
              joueur->caste->mana = joueur->caste->max_mana;
              joueur->caste->magic_power = joueur->caste->mana/4;


            }
            if(strcmp(joueur->caste->nom_caste , "Magicien")==0){
              printf("Vous avez gagné %d points de Force !\n",niveau_gagne);
              joueur->caste->attack_power += niveau_gagne;
              joueur->poid_max+=niveau_gagne*2;
              printf("Vous avez gagné %d points d'Agilité !\n",2*niveau_gagne);
              joueur->caste->agilite += 2*niveau_gagne;
              printf("Vous avez gagné %d points de Mana !\n",5*niveau_gagne);
              joueur->caste->max_mana += 5*niveau_gagne;
              joueur->caste->mana = joueur->caste->max_mana;
              joueur->caste->magic_power = joueur->caste->mana/4;

            }
            if(strcmp(joueur->caste->nom_caste , "Assassin")==0){
              printf("Vous avez gagné %d points de Force !\n",2*niveau_gagne);
              joueur->caste->attack_power += 2*niveau_gagne;
              joueur->poid_max += 2*niveau_gagne*2;
              printf("Vous avez gagné %d points d'Agilité !\n",5*niveau_gagne);
              joueur->caste->agilite += 5*niveau_gagne;
              printf("Vous avez gagné %d points de Mana !\n",2*niveau_gagne);
              joueur->caste->max_mana += 2*niveau_gagne;
              joueur->caste->mana = joueur->caste->max_mana;
              joueur->caste->magic_power = joueur->caste->mana/4;

            }
            printf("Vous avez obtenu %d points de caractéristique non Attribué !\n",5*niveau_gagne);
            joueur->pointlibre += 5*niveau_gagne;


          }
          printf(" \n");
        }
        for(int k=0;k<30;k++){printf("X");}
        fflush(stdout);
        sleep(6);
      }

    }


    else if(joueur->vie <=0){
      joueur->argent = joueur->argent/2;
      system("clear");
      afficher(map, SIZE, joueur);

      for(int k=0;k<30;k++){printf("X");}
      printf("\n");

      for(int k = 0; k<16;k++){
        if(k==5){
          printf("Vous avez été vaincu par %s...\n", ennemi->nom);
          printf("Vous avez perdu %d or !",joueur->argent);
        }
        printf(" \n");
      }
      for(int k=0;k<30;k++){printf("X");}
      fflush(stdout);
      sleep(3);
      cont = 0;
      initialX = 23;
      initialY = 28;

    }
  }




  joueur->y = initialY;
  joueur->x = initialX;

  free(ennemi);

}
