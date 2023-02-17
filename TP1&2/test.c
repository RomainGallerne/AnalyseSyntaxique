/*
Un très joli programme
*/
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
  int j = 0x3A;			/* variable inutile */
  if(argc>1){
    char *argument="Vous avez saisi un argument, le voici :";
    printf("%s%s\n",argument,argv[1]);
    /*Un petit commentaire*/
  } 
  else {printf("Vous n'avez pas saisi d'argument :(\n");}
  //Un autre petit commentaire

  
  return 0;
}