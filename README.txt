# inf404_calculette

# Function:
Une calculatrice qui peut effectuer des calculs d'affectation, et il aussi peut effectuer "if- then-else"

# Mode d'emploi:
$ make
$./calculette entreeText.txt

# Description de la structure du répertoire
├── Readme.md                        // Aide
├── calculette                       // calculatrice
│   ├── calculette                   //main
│   |   ├── analyse_syntaxique       // analyse_les_syntaxique
|   |   |   ├──analyse_syntaxique.c
│   |   |   ├── ast_construction     // Creer_les_partielle_de_ast
|   |   |   |   ├──ast_construction.c 
|   |   |   |   ├──ast_construction.h
|   |   |   |   └──type_ast.h
│   |   |   ├── ast_parcours         // Calcul_le_ast
|   |   |   |   ├──ast_parcours.c 
|   |   |   |   ├──ast_parcours.h 
|   |   |   |   └──type_ast.h
│   └── └── analyse_lexicale         // analyse_les_lexicale
|           ├──analyse_lexicale.c
|           ├──analyse_lexicale.h 
│           └── lecture_caracteres   // Lire_les_caracters
|               ├── lecture_caracteres.h 
|               └── lecture_caracteres.c
├── test_lexeme                     //test_de_lire_fichers
|   ├──analyse_lexicale
|   ├──lecture_caracteres
|   └──test_lexeme.c
|
└── cor1.txt/coe2.txt              //ficher enteree

# Licences
MIT License
