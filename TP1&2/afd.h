/**
 * @file afd.h     
 * @author Michel Meynard
 * @brief Définition d'un AFD
 */
#define EINIT 0
#define EI 1
#define EID 2
#define EIF 3
#define EINT 4
#define EFLOT 5
#define EEXPO 6
#define EEXPONB 7
#define ESLASH 8
#define ECOMMLIGNE 9
#define ECOMMZONE 10
#define EETOILE 11
#define NBETAT 12

int TRANS[NBETAT][256];		/* table de transition : état suivant */
int JETON[NBETAT];		/* jeton à retourner */

int classe(int EDEB,char A,char Z, int EFIN){
  for(int i=A; i<=Z; i++)TRANS[EDEB][i] = EFIN;
  return 0;
}

int creerAfd(){			/* Construction de l'AFD */
  int i;int j;			/* variables locales */
  for (i=0;i<NBETAT;i++){
    for(j=0;j<256;j++) TRANS[i][j]=-1; /* init vide */
    JETON[i]=0;			/* init tous états non finaux */
  }
  /* Transitions de l'AFD */

  /*if*/
  TRANS[EINIT][' ']=EINIT;
  TRANS[EINIT]['\n']=EINIT;
  TRANS[EINIT]['i']=EI;
  TRANS[EI]['f']=EIF;

  /*ID*/
  classe(EINIT,'A','Z',EID);
  classe(EINIT,'a','h',EID);
  classe(EINIT,'j','z',EID);
  classe(EI,'A','Z',EID);
  classe(EI,'a','e',EID);
  classe(EI,'g','z',EID);
  classe(EI,'0','9',EID);
  classe(EID,'A','Z',EID);
  classe(EID,'a','z',EID);
  classe(EID,'0','9',EID);
  classe(EIF,'A','Z',EID);
  classe(EIF,'a','z',EID);
  classe(EIF,'0','9',EID);

  /*INT*/
  classe(EINIT,'0','9',EINT);
  classe(EINT,'0','9',EINT);

  /*REEL*/
  TRANS[EINT]['.']=EFLOT;
  TRANS[EINIT]['.']=EFLOT;
  classe(EFLOT,'0','9',EFLOT);
  TRANS[EFLOT]['e']=EEXPO;
  TRANS[EFLOT]['E']=EEXPO;
  TRANS[EEXPO]['-']=EEXPONB;
  classe(EEXPO,'0','9',EEXPONB);
  classe(EEXPONB,'0','9',EEXPONB);

  /*COMMENTAIRE*/
  TRANS[EINIT]['/']=ESLASH;

  TRANS[ESLASH]['/']=ECOMMLIGNE;
  classe(ECOMMLIGNE,'A','Z',ECOMMLIGNE);
  classe(ECOMMLIGNE,'a','z',ECOMMLIGNE);
  classe(ECOMMLIGNE,'0','9',ECOMMLIGNE);
  TRANS[ECOMMLIGNE]['-']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE]['.']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE]['_']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE][')']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE]['(']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE][',']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE][' ']=ECOMMLIGNE;
  TRANS[ECOMMLIGNE]['\n']=EINIT;

  TRANS[ESLASH]['*']=ECOMMZONE;

  classe(ECOMMZONE,'A','Z',ECOMMZONE);
  classe(ECOMMZONE,'a','z',ECOMMZONE);
  classe(ECOMMZONE,'0','9',ECOMMZONE);
  TRANS[ECOMMZONE]['-']=ECOMMZONE;
  TRANS[ECOMMZONE]['.']=ECOMMZONE;
  TRANS[ECOMMZONE]['_']=ECOMMZONE;
  TRANS[ECOMMZONE][')']=ECOMMZONE;
  TRANS[ECOMMZONE]['(']=ECOMMZONE;
  TRANS[ECOMMZONE][',']=ECOMMZONE;
  TRANS[ECOMMZONE]['\n']=ECOMMZONE;
  TRANS[ECOMMZONE][' ']=ECOMMZONE;

  TRANS[ECOMMZONE]['*']=EETOILE;

  classe(EETOILE,'A','Z',ECOMMZONE);
  classe(EETOILE,'a','z',ECOMMZONE);
  classe(EETOILE,'0','9',ECOMMZONE);
  TRANS[EETOILE]['-']=ECOMMZONE;
  TRANS[EETOILE]['.']=ECOMMZONE;
  TRANS[EETOILE]['_']=ECOMMZONE;
  TRANS[EETOILE][')']=ECOMMZONE;
  TRANS[EETOILE]['(']=ECOMMZONE;
  TRANS[EETOILE][',']=ECOMMZONE;
  TRANS[EETOILE][' ']=ECOMMZONE;
  TRANS[EETOILE]['*']=ECOMMZONE;
  TRANS[EETOILE]['\n']=ECOMMZONE;

  TRANS[EETOILE]['/']=EINIT;

  /*JETON*/

  JETON[EI]=JETON[EID]=300+EID;
  JETON[EINT]=300+EINT;
  JETON[EEXPONB]=300+EEXPONB;
  JETON[EIF]=300+EIF;
  JETON[EFLOT]=JETON[EEXPONB]=300+EFLOT;
  /* états finaux */
  return 0;
}