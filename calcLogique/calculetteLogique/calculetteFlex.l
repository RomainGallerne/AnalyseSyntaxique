%{
    /* calc.l */
#include "y.tab.h" /* JETONS crees par yacc et definition de yylval */
#include <stdlib.h> /* pour double atof(char *) */
#include <stdio.h> /* pour printf */
#include <stdbool.h>
#define YYSTYPE int /* ATTENTION AUX 2 MACROS dans lex et yacc */
%}

bool ([0-1])
var ([a-z])
%option noyywrap

%%

[ \t]+  {/* filtrer les blancs */ }
{bool}                   {yylval=atoi(yytext);return (BOOLEAN);}
{var}                   {yylval=(int)yytext[0]-97;return (VAR);}
V|T|vrai|true           {yylval=1;return (BOOLEAN);}
F|faux|false            {yylval=0;return (BOOLEAN);}
==                     { return(EQUIV); }
->                     { return(IMPLIQUE); }
exit|quit               { return (QUIT); }
aide|help|\?            { return (HELP); }
.|\n                    { return yytext[0]; /* indispensable !*/ }

%%