

typedef struct{
  char idf;
  int valeur;
} Couple;


// void entrer_tab(Couple[] TableSymbole,char* id,int v);// enregistrer la couple dans table de symbole
void entrer_tab(Couple *TableSymbole,char id,int v);// enregistrer la couple dans table de symbole
// int cher_valeur(Couple[] TableSymbole,char* id);// Chercher la valeur de IDF
int cher_valeur(Couple *TableSymbole,char id);// Chercher la valeur de IDF
// void aff_tab(Couple[] TableSymbole);//afficher la table
void aff_tab(Couple *TableSymbole);//afficher la table
