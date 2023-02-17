%{
    /*Zone de Définition*/
typedef union {
    long typeEntier;
    float typeFlottant;
    char* typeChaineCara;
} YYSTYPE;

#include <stdlib.h> /* pour double atof(char *) */
#include <stdio.h> /* pour printf */
enum{KEY=300,C10,C8,C16,ID,FLOT,MATH,LOGIC,BLOC,STRING,AFFECT,FINSTRU,DEFINE,LIB};

int compteIndent=0;
int indexProchaineIndent=0;
int nvIndent[100] = [-1]*100;
int nvCourant=0;
%}

%%

    /*Zone des Règles*/

\n\n("*"|-)                                               {nvIndent[0] = compteIndent; nvCourant=compteIndent; indexProchaineIndent+=1; compteIndent=0; return ;} //Liste de 1er niveau


(*|-)[^\n]*\n                                           {
                                                            if((k=findInTab(nvIndent,compteIndent))!=-1){
                                                                return nvCourant-nvIndent[k]; //On retourne l'écart de niveau d'indentation des listes
                                                            }else{
                                                                nvIndent[indexProchaineIndent] = compteIndent;
                                                                nvCourant = compteIndent; 
                                                                return k;//On retourne le nouveau niveau d'indentation
                                                            }
                                                            compteIndent = 0;
                                                        } //Eléments Listés


"  "|\t                                                 {indent+=1; return INDENT;}



\n("  "|\t)                                             {nbList += 1; return DLIST;} //Nouvelle Liste de niveaux inférieurs
\n("  "|\t)                                             {return ELEM;} //On reste dans la liste de même niveau
" "|"\t"|"\n"                                           {}     //Lsep 
                                                            

%%
    /*Zone des Fonctions C*/

int findInTab(T,k){
    for(int i=0;i++;i<sizeof(T)){
        if(T[i]==k){return i;}
    }
    return -1;
}
    
int main() {
    int j;
    //char *invite = "Saisissez une chaine de caractère matchant un programme C\n";
    while((j=yylex())!=0){		/* analyser tq pas jeton 0 */
        //printf("%s",invite);		/* prompt */

        /*Affichage clair*/
        char* jstring = "unknown";

        if(j == KEY){jstring = "key";}
        if(j == C10){jstring = "c10";}
        if(j == C8){jstring = "c8";}
        if(j == C16){jstring = "c16";}
        if(j == ID){jstring = "id";}
        if(j == FLOT){jstring = "flot";}
        if(j == MATH){jstring = "math";}
        if(j == LOGIC){jstring = "logic";}
        if(j == BLOC){jstring = "bloc";}
        if(j == STRING){jstring = "string";}
        if(j == AFFECT){jstring = "affect";}
        if(j == FINSTRU){jstring = "finstru";}
        if(j == DEFINE){jstring = "define";}
        if(j == LIB){jstring = "lib";}

        printf("Jeton = %i(%s) ; Lexeme = %s\n",j,jstring,yytext;
    }
    return 0;
}