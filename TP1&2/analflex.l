%{
    /*Zone de Définition*/
typedef union {
    long typeEntier;
    float typeFlottant;
    char* typeChaineCara;
} YYSTYPE;

YYSTYPE yylval;
#include <stdlib.h> /* pour double atof(char *) */
#include <stdio.h> /* pour printf */
enum{KEY=300,C10,C8,C16,ID,FLOT,MATH,LOGIC,BLOC,STRING,AFFECT,FINSTRU,DEFINE,LIB};
%}

%%

    /*Zone des Règles*/

if|else|th(en|row)                                          {return KEY;}   //Lkey
[1-9][0-9]*                                                 {yylval.typeEntier=strtol(yytext, NULL, 10); return C10;}       //Lc10
0[0-7]*                                                     {yylval.typeEntier=strtol(yytext, NULL, 8); return C8;}   //Lc8
0x[0-9A-Fa-f]+                                              {yylval.typeEntier=strtol(yytext, NULL, 16); return C16;}       //Lc16
"<".*">"                                                    {return LIB;}   //Llib
[_A-Za-z][_0-9A-Za-z]*                                      {yylval.typeChaineCara=malloc(1+strlen(yytext));return ID;}   //Lid
(([0-9]+"."[0-9]*)|"."[0-9]+)([eEdD]"-"?[0-9]+)?            {return FLOT;}   //Lflot
[+-/*^%]|"**"|"++"|"--"|"+="|"-="|"*="|"/="                 {return MATH;}  //Lmath
==|<=?|>=?|=<|=>|&&|"||"                                    {return LOGIC;}    //Llogic
"("|")"|"["|"]"|"{"|"}"                                     {return BLOC;} //Lbloc
["][^"]*["]                                                 {return STRING;}    //Lstring
=                                                           {return AFFECT;}   //Laffect
;                                                           {return FINSTRU;}     //Lfin_instruction
"#"[^\n ]*                                                  {return DEFINE;}    //Ldefine
" "|"\t"|"\n"|("//".*"\n")|("/*"[^*/]*"*/")                 {}     //Lsep 
.|"\n"                                                      {return -1;}     //tout le reste

%%
    /*Zone des Fonctions C*/
    
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

        printf("Jeton = %i(%s) ; Lexeme = %s ; de valeur = %f\n",j,jstring,yytext,yylval);
    }
    return 0;
}