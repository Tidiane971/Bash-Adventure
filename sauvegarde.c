void save(Joueur *joueur, Caste *caste){

  //STOCKER JOUEUR
  FILE *of;
  of= fopen ("saved_data/joueur.txt", "w");
  if (of == NULL) {
     fprintf(stderr, "\nError to open the file\n");
     exit (1);
  }

  fwrite (joueur, sizeof(struct Joueur), 1, of);
  if(fwrite != 0)
     printf("Contents to file written successfully !\n");
  else
     printf("Error writing file !\n");
  fclose (of);

  //STOCKER CASTE Joueur

  FILE *od;
  od= fopen ("saved_data/caste.txt", "w");
  if (od == NULL) {
     fprintf(stderr, "\nError to open the file\n");
     exit (1);
  }

  fwrite (caste, sizeof(struct Caste), 1, od);
  if(fwrite != 0)
     printf("Contents to file written successfully !\n");
  else
     printf("Error writing file !\n");
  fclose (od);



}

Joueur *get_saved(){

  Joueur *joueurFINAL = malloc(sizeof(Joueur));
  //GET JOUEUR
  FILE *inf;
  Joueur inp;
  inf = fopen ("saved_data/joueur.txt", "r");
  if (inf == NULL) {
     fprintf(stderr, "\nError to open the file\n");
     exit(1);
  }
  while(fread(&inp, sizeof(struct Joueur), 1, inf))
  strcpy(joueurFINAL->nom, inp.nom);
  joueurFINAL->x = inp.x;
  joueurFINAL->y = inp.y;
  joueurFINAL->argent = inp.argent;
  joueurFINAL->niveau = inp.niveau;


  fclose(inf);

  FILE *ind;
  Caste inpcastes;
  ind = fopen ("saved_data/caste.txt", "r");
  if (ind == NULL) {
     fprintf(stderr, "\nError to open the file\n");
     exit(1);
  }

  while(fread(&inpcastes, sizeof(struct Caste), 1, ind))
  printf("SA CLASSE EST %s",inpcastes.nom_caste);
  Caste *pinp = &inpcastes;
  joueurFINAL->caste = pinp;
  fclose(ind);

  return joueurFINAL;







}
