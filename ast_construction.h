
#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) ;
// renvoie un arbre abstrait de nature OPERATEUR,  d'operateur opr
// et ayant opde_gauche et opde_droit pour fils gauche et droit

Ast creer_valeur(int val) ;
// renvoie un arbre abstrait "feuille", de nature OPERATION
// et de valeur val

//Ast creer_if(Ast Acond,Ast Athen,Ast Aelse);
Ast creer_if(Ast Acond,Ast Asuite);
Ast creer_sepinst(Ast Ag,Ast Ad);
