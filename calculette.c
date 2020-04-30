
#include <stdlib.h> 
#include <stdio.h> 

#include "analyse_syntaxique.h"

 
int main (int argc, char *argv[]) {	
   if (argc != 2)
   {
			printf("Il faut donner un nom de fichier en argument f!");
			exit(0);
   }	
   analyser(argv[1]);
   return 0 ;
}
		
	
		
		
		
		

