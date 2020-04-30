#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyse_lexicale.h"
#include "table_symbole.h"

Couple TableSymbole[20]={{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',},{'@',}};

/** insérer/remplacer un couple (IDF, valeur)*/
void entrer_tab(Couple *TableSymbole,char id,int v){
	int longeur = 20;
	int flag=0;//NOT FOUND
	int flag2=0;
	for(int  i=0; i<longeur && flag==0;i++){
		if(TableSymbole[i].idf==id){
			TableSymbole[i].valeur = v;
			flag = 1;
		}
	}
	if(flag==0){
		for(int i=0;i<longeur && flag2==0;i++){
			if(TableSymbole[i].idf=='@'){
				TableSymbole[i].idf = id;
				TableSymbole[i].valeur = v;
				flag2=1;
			}
		}
	}
}

/** rechercher la valeur de IDF*/
int cher_valeur(Couple *TableSymbole,char id){
	int longeur = 20;
	int flag=0;
	for(int  i=0; i<longeur;i++){
		if(TableSymbole[i].idf==id){
			flag=1;
			return TableSymbole[i].valeur;
		}
	}
	if(flag==0){
		printf("ERREUR_CHER_VALEUR\n");
	}
	return 0;
}

/** afficher la table*/
void aff_tab(Couple *TableSymbole){
	int indice = 0;
	int longeur = 20;
	for(; indice < longeur && &TableSymbole[indice] != NULL; indice++) {
		printf("%c		%d\n", TableSymbole[indice].idf, TableSymbole[indice].valeur);
	}
}
