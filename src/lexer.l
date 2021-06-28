%{
#include <stdlib.h>
#include "parser.h"
%}

%option noinput
%option nounput

%%
entero      {  return entero;     }
main        {  return main;       }
mientras    {  return mientras;   }
retorno     {  return retorno;    }
sin_tipo    {  return sin_tipo;   }
si          {  return si;         }
sino        {  return sino;       }

[a-z][a-z]*        { yylval.strval = strdup(yytext); return ID;   }
-?[0-9]+               { yylval.intval = atoi(yytext); return NUM; }


%%
