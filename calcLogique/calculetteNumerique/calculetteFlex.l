%{
    /* calc.l */
#define YYSTYPE double /* ATTENTION AUX 2 MACROS dans lex et yacc */
#include "y.tab.h" /* JETONS crees par yacc et definition de yylval */
#include <stdlib.h> /* pour double atof(char *) */
#include <stdio.h> /* pour printf */
%}

chiffre ([0-9])
entier  ({chiffre}+)
%option noyywrap

%%

[ \t]+  {/* filtrer les blancs */ }
{entier}|{entier}\.{chiffre}*|{chiffre}*\.{entier} {yylval=atof(yytext);return (LITFLOT);}
sin                     { return(SIN); }
cos                     { return(COS); }
exp                     { return(EXP); }
ln                      { return(LN); }
pi                      { return(PI); }
exit|quit               { return (QUIT); }
aide|help|\?            { return (HELP); }
.|\n                    { return yytext[0]; /* indispensable !*/ }

%%