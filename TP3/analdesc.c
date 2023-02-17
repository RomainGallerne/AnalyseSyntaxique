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
                             /* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d \n",numcar); exit(1);} 

int E();int R(int);int T();int S(int);int F(); /* déclars */

int jeton;                       /* caractère courant du flot d'entrée */
int numcar=0;                    /* numero du caractère courant (jeton) */

int E(){
  int tg = T();                          /* regle : E->TR */
  return R(tg);
}
int R(int t1){
  if (jeton=='+') {             /* regle : R->+TR */
    AVANCER
    int t2 = T();
    return t1+R(t2);
  }
  else return t1;                        /* regle : R->epsilon */
}
int T(){
  int tg = F();
  return S(tg);                          /* regle : T->FS */
}
int S(int t1){
  if (jeton=='*') {             /* regle : S->*FS */
    AVANCER
    int t2 = F();
    return t1*S(t2);
  }
  else return t1;                        /* regle : S->epsilon */
}
int F(){
  if (jeton=='(') {             /* regle : F->(E) */
    AVANCER
    int e = E();
    TEST_AVANCE(')')
    return e;
  }
  else 
    if (isdigit(jeton)){         /* regle : F->0|1|...|9 */
      int r = jeton-'0';
      AVANCER
      return r;
    }
    else{
      ERREUR_SYNTAXE
    }
}
int main(void){                 /* Fonction principale */
  AVANCER			/* initialiser jeton sur le premier car */
  int e = E();                          /* axiome */
  if (jeton==EOF)               /* expression reconnue et rien après */
    printf("\nMot reconnu\n"); 
  else ERREUR_SYNTAXE           /* expression reconnue mais il reste des car */
  printf("E = %i\n",e);
  return e;
}
