#include <stdlib.h>
#include <stdio.h>

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr, Ast opde_gauche, Ast opde_droit)
{
        Ast expr;
        expr = (Ast) malloc (sizeof(NoeudAst));
        expr->nature = OPERATION;
        expr->operateur = opr;
        if (opde_gauche == NULL || opde_droit == NULL) {
                printf("ERREUR_EXPRESSION\n");
                exit(1);
        } else {
                expr->gauche = opde_gauche;
                expr->droite = opde_droit;
        };
        return expr;
}

Ast creer_if(Ast Acond,Ast Asuite){
        Ast nif;
        nif=(Ast) malloc(sizeof(NoeudAst));
        nif->gauche=Acond;
        nif->droite=Asuite;
        return nif;
}

Ast creer_valeur(int val) {
        Ast expr;
        expr = (Ast) malloc (sizeof(NoeudAst));
        expr->nature = VALEUR;
        expr->valeur = val;
        return expr;
}

Ast creer_sepinst(Ast Ag,Ast Ad){
       Ast sepins;
       sepins=(Ast)malloc(sizeof(NoeudAst));
       sepins->gauche=Ag;
       sepins->droite=Ad;
       return sepins;
}
