%{
    /* calc.y */
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define YYSTYPE int
int yylex(void); void yyerror(char *s);
int varTab[26];
%}

/* définition des jetons */
%token VAR BOOLEAN V T F QUIT HELP

/* traitement des priorités */
%left '|' EQUIV '+'
%right IMPLIQUE
%left '&'
%right '!'

%%

liste   :                   {/* chaine vide sur fin de fichier Ctrl-D */ }
        |   liste ligne     {}
        ;
ligne   :   '\n'            {/* ligne vide : expression vide */}
        |   error '\n'      {yyerrok; /* après la fin de ligne */ }
        |   affect '\n'     {printf("Résultat : %c affecté à %i\n",(char)($1+97),varTab[$1]);}
        |   expr '\n'       {printf("Résultat : %i\n",$1);}
        |   QUIT '\n'       {return 0; /* fin de yyparse */ }
        |   HELP '\n'       {   printf("Aide de la calculette Logique\n");
                                printf("=====================\n");
                                printf("Taper une expression booléenne\n");
                                printf("puis taper <Entrée> \n");
                                printf("Ou taper une commande suivie de <Entrée>\n\n");
                                printf("Syntaxe des booléens : 1 pour vrai, 0 pour faux \n");
                                printf("Opérations binaires : | -> == + (ou exclusif) & \n");
                                printf("Opérations unaires : ! \n");
                                printf("Constantes prédéfinies : V F ou T F\n");
                                printf("Commandes : exit ou quit pour quitter la calculette\n");
                                printf("aide ou help ou \? pour afficher cette aide\n");
                            }
        ;
affect  :   VAR '=' expr    {varTab[$1] = $3; $$ = $1;};
expr    :   '(' expr ')'    {$$ = $2;}
        |   expr '|' expr   {$$ = $1 || $3;}
        |   expr IMPLIQUE expr   {$$ = !($1) || $3;}
        |   expr EQUIV expr   {$$ = $1 == $3;}
        |   expr '+' expr   {$$ = ($1 || $3) && !($1 && $3);}
        |   expr '&' expr   {$$ = $1 && $3;}
        |   '!' expr        {$$ = !$2;}
        |   VAR            {$$ = varTab[$1];}
        |   BOOLEAN         {$$ = $1;}

%%
void yyerror(char *s) {fprintf(stderr,"%s\n",s);}
int main(void){return yyparse();}