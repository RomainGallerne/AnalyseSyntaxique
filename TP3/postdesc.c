/** @file analdesc.c        
 *@author Michel Meynard
 *@brief Analyse descendante récursive d'expression arithmétique
 *
 * Ce fichier contient un reconnaisseur d'expressions arithmétiques composée de 
 * littéraux entiers sur un car, des opérateurs +, * et du parenthésage ().
 * Remarque : soit rediriger en entrée un fichier, soit terminer par deux 
 * caractères EOF (Ctrl-D), un pour lancer la lecture, l'autre comme "vrai" EOF.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <string.h>
                             /* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d \n",numcar); exit(1);} 

char *E();char *R(char*);char *T();char *S(char*);char *F(); /* déclars */

char jeton;                       /* caractère courant du flot d'entrée */
int numcar=0;                    /* numero du caractère courant (jeton) */
char retour[1024];

char *E(){
  printf("E");
  char *tg = T();                          /* regle : E->TR */
  strcpy(retour,R(tg));
  return retour;
}

char *R(char *t1){
  printf("R");
  if (jeton=='+') {             /* regle : R->+TR */
    AVANCER
    char t3[1024]; strcpy(t3,t1);
    char *t2 = T();
    strcat(t3,R(t2));strcat(t3,"+");
    strcpy(retour,t3);
    return retour;
  }
  else return t1;                        /* regle : R->epsilon */
}

char *T(){
  printf("T");
  char *tg = F();
  strcpy(retour,S(tg));
  return retour;                          /* regle : T->FS */
}

char *S(char *t10){
  printf("S");
  if (jeton=='*') {             /* regle : S->*FS */
    AVANCER
    char t30[1024]; strcpy(t30,t10);
    char *t20 = F();
    strcat(t30,S(t20));strcat(t30,"*");
    strcpy(retour,t30);
    return retour;
  }
  else {return t10;}                        /* regle : S->epsilon */
}
char *F(){
  printf("F");
  if (jeton=='(') {             /* regle : F->(E) */
    AVANCER
    char *e = E();
    TEST_AVANCE(')')
    strcpy(retour,"(");
    strcat(e,")");strcat(retour,e);
    return retour;
  }
  else 
    if (isdigit(jeton)){         /* regle : F->0|1|...|9 */
      strcpy(retour,&jeton);
      AVANCER
      return retour;
    }
    else{
      ERREUR_SYNTAXE
    }
}

int main(void){                 /* Fonction principale */
  AVANCER			/* initialiser jeton sur le premier car */
  printf("Début\nOrdre d'appel : ");
  char *e = E();                          /* axiome */
  if (jeton==EOF)               /* expression reconnue et rien après */
    printf("\nCalcul en postfixe : %s\n",e); 
  else ERREUR_SYNTAXE           /* expression reconnue mais il reste des car */
  return 0;
}
