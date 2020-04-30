/* ------------------------------------------------------------------------
-- module analyse_syntaxique
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "analyse_lexicale.h"
#include "table_symbole.h"


void pgm(Ast *A1);
void rec_seq_inst(Ast *A1, int a_executer);
void suite_seq_inst(Ast Ag, Ast *A1, int a_executer);
void rec_inst(Ast *A1, int a_executer);
int rec_condition(Ast *A1);
void seq_affectation(Ast *A1);
void rec_affectation(Ast *A1, int a_executer);
void rec_eag(Ast *A1);
void seq_terme(Ast *A2);
void suite_seq_terme(Ast A1, Ast *A2);
void terme(Ast *A1);
void seq_facteur(Ast *A2);
void suite_seq_facteur(Ast A1, Ast *A2);
void facteur(Ast *A1);
int op1(TypeOperateur *Op);
int op2(TypeOperateur *Op);
TypeOperateur Operateur(Nature_Lexeme nature);
//--------------Tp5------------

Couple TableSymbole[20] ;

void pgm(Ast *A1){
	rec_seq_inst(A1, 1);
}


void rec_seq_inst(Ast *A1, int a_executer){
	Ast Ag ;
	rec_inst(&Ag, a_executer);
	suite_seq_inst(Ag, A1, a_executer);
}


void suite_seq_inst(Ast Ag, Ast *A1, int a_executer){
	Ast Ad ;
	switch (lexeme_courant().nature) {
		case IDF :
		rec_seq_inst(&Ad, a_executer);
		*A1 = creer_sepinst(Ag, Ad);
		break;
		case IF_L:
		rec_seq_inst(&Ad, a_executer);
		*A1 = creer_sepinst(Ag, Ad);
		break;
		case POINTV:
		avancer();
		rec_seq_inst(&Ad, a_executer);
		*A1 = creer_sepinst(Ag, Ad);
		break;
		rec_seq_inst(&Ad, a_executer);
		*A1 = creer_sepinst(Ag, Ad);
		break;
		default:
		*A1 = Ag ;
		break;
	}
}

void rec_inst(Ast *A1, int a_executer){
	Ast Acond,Athen,Aelse;
	int res = -1;  // resultat de condition
	switch (lexeme_courant().nature) {
		case IDF:
		rec_affectation(A1, a_executer) ;
		break;
		case IF_L:
		avancer();
		res=rec_condition(&Acond);
		switch (lexeme_courant().nature) {
			case THEN_L:
			avancer();
			break;
			default:
			printf("ERREUR:INST_THEN\n");
			break;
		}
		rec_seq_inst(&Athen, a_executer && res);
		switch (lexeme_courant().nature) {
			case ELSE_L:
			avancer();
			break;
			default:
			printf("ERREUR:INST_ELSE\n" );
			break;
		}
		rec_seq_inst(&Aelse, a_executer && !res);
		switch (lexeme_courant().nature) {
			case FI_L:
			avancer();
			break;
			default:
			printf("ERREUR:INST_FI\n" );
			break;
		}
		break ;
		case FIN_SEQUENCE:
		break;
		default:
		printf("ERREUR:REC_INST\n%d\n",lexeme_courant().nature);
		break;
	}
	if(res){
		*A1=creer_if(Acond,Athen);
	}else{
		*A1=creer_if(Acond,Aelse);
	}
}
int rec_condition(Ast *A1){   // fonction ok
	Ast Ag, Ad;
	TypeOperateur op;
	rec_eag(&Ag);   // fils gauche de la condition
	int res=-1;
	int variable = -1;
	int entier = -1;
	switch (lexeme_courant().nature) {
		case OKEGALE:
		op = Operateur(OKEGALE) ;
		avancer() ; // pour lire le lexeme OPCOMP
		rec_eag(&Ad);  // fils droit de la condition
		*A1 = creer_operation (op, Ag, Ad);
		variable = Ag->valeur;  // a verifier
		entier = Ad->valeur;
		res = (variable == entier);
		break;
		case NONEGALE:
		op = Operateur(NONEGALE) ;
		avancer() ; // pour lire le lexeme OPCOMP
		rec_eag(&Ad);  // fils droit de la condition
		*A1 = creer_operation (op, Ag, Ad);
		variable = Ag->valeur;  // a verifier
		entier = Ad->valeur;
		res = (variable != entier);
		break;
		case INFERIEUR:
		op = Operateur(INFERIEUR) ;
		avancer() ; // pour lire le lexeme OPCOMP
		rec_eag(&Ad);  // fils droit de la condition
		*A1 = creer_operation (op, Ag, Ad);
		variable = Ag->valeur;  // a verifier
		entier = Ad->valeur;
		res = (variable < entier);
		break;
		case SUPERIEUR:
		op = Operateur(SUPERIEUR) ;
		avancer() ; // pour lire le lexeme OPCOMP
		rec_eag(&Ad);  // fils droit de la condition
		*A1 = creer_operation (op, Ag, Ad);
		variable = Ag->valeur;  // a verifier
		entier = Ad->valeur;
		res = (variable > entier);
		break;

		default:
		printf("ERREUR:CONDITION \n" );
		break;
	}
	return res;
}

void seq_affectation(Ast *A1){

	switch (lexeme_courant().nature) {
		case FIN_SEQUENCE:
		avancer();
		break;
		default:
		rec_affectation(A1, 1);
		seq_affectation(A1);
		break;
	}
}


void rec_affectation(Ast *A1, int a_executer){
	char id;int v;
	switch (lexeme_courant().nature) {
		case IDF:
		id=lexeme_courant().chaine[0];
		avancer();
		break;
		default:
		printf(" ERREUR : affectation_IDF \n "); exit(1) ;
		break;
	};
	switch (lexeme_courant().nature) {
		case AFFECTATION:
		avancer();
		break;
		default:
		printf(" ERREUR : affectation_AFF \n "); exit(1) ;
		break;
	};
	rec_eag(A1);
	v=evaluation(*A1);
	switch (lexeme_courant().nature) {
		case POINTV:
		if (a_executer)
		entrer_tab(TableSymbole,id,v);
		avancer();
		break;
		default:
		printf(" ERREUR : affectation_POINTV \n "); exit(1) ;
		break;
	}
}

//--------------FinTp5------------
void rec_eag(Ast *A1) {
	seq_terme(A1);
}

void seq_terme(Ast *A2){
	Ast A1;
	terme(&A1);
	suite_seq_terme(A1,A2);
}

void suite_seq_terme(Ast A1, Ast *A2){
	Ast A3,A4;
	TypeOperateur op;
	if(op1(&op))
	{
		terme(&A3);
		A4 = creer_operation(op,A1,A3);
		suite_seq_terme(A4,A2);
	}
	else
	{
		*A2=A1;
	}
}

void terme(Ast *A1){
	seq_facteur(A1);
}

void seq_facteur(Ast *A2){
	Ast A1;
	facteur(&A1);
	suite_seq_facteur(A1,A2);
}

void suite_seq_facteur(Ast A1, Ast *A2){
	Ast A3,A4;
	TypeOperateur op;
	int r = op2(&op);
	if(r==1)
	{
		facteur(&A3);
		A4 = creer_operation(op,A1,A3);
		suite_seq_facteur(A4,A2);
	}
	else if (r==2)
	{
		if(lexeme_courant().valeur==0)
		{
			printf(" ERREUR : division par 0 impossible \n ");
			exit(3);
		}
		facteur(&A3);
		A4 = creer_operation(op,A1,A3);
		suite_seq_facteur(A4,A2);
	}
	else
	{
		*A2=A1;
	}


}

void facteur(Ast *A1){
	char id;
	switch(lexeme_courant().nature) {
		case ENTIER:
		*A1 = creer_valeur(lexeme_courant().valeur);
		avancer();
		break;
		case PARO:
		avancer();
		rec_eag(A1);
		if(lexeme_courant().nature == PARF)
		{
			avancer();
		}
		else
		{
			printf("ERREUR PARENTHESES\n");
			exit(1);
		}
		break;
		//--------------Tp5------------
		case IDF:
		id=lexeme_courant().chaine[0];
		*A1=creer_valeur(cher_valeur(TableSymbole,id));
		avancer();
		break;
		//------------FinTp5---------
		default:
		printf("Erreur facteur ii\n");
		exit(0);
	}
}

int op1(TypeOperateur *Op){
	switch(lexeme_courant().nature) {
		case PLUS:
		case MOINS:
		*Op = Operateur(lexeme_courant().nature);
		avancer();
		return 1;
		default:
		return 0;
	}
}

int op2(TypeOperateur *Op){
	switch(lexeme_courant().nature) {
		case MUL:
		*Op = Operateur(lexeme_courant().nature);
		avancer();
		return 1;
		case DIV:
		*Op = Operateur(lexeme_courant().nature);
		avancer();
		return 2;
		default:
		return 0;
	}
}

TypeOperateur Operateur(Nature_Lexeme nature){
	switch(nature)
	{
		case PLUS: return N_PLUS;
		case MOINS: return N_MOINS;
		case MUL: return N_MUL;
		case DIV: return N_DIV;

		case OKEGALE:return N_EGAL;
		case NONEGALE:return N_DIFF;
		case INFERIEUR: return N_INF;
		case SUPERIEUR: return N_SUP;
		case INFERIEUREGALE: return N_INFE;
		case SUPERIEUREGALE: return N_SUPE;

		default: printf("Erreur operateur\n"); exit(1);
	}
}

/* ----------------------------------------------------------------------- */
void analyser(char* nomFichier)
{
	Ast A;
	demarrer(nomFichier);
	pgm(&A);
	if(lexeme_courant().nature == FIN_SEQUENCE){
		printf("SYNTAXE CORRECTE\n");
	}else
	{printf("SYNTAXE INCORRECTE\n"); exit(1);};

	aff_tab(TableSymbole);
}
