%{
#include <stdlib.h>

#include "cce/parser.h"
#include "parser.h"
%}

%option noinput
%option nounput

%%
entero   { return entero;   }
mientras { return mientras; }
retorno  { return retorno;  }
sin_tipo { return sin_tipo; }
si       { return si;       }
sino     { return sino;     }


">"  { return relop_ge; }
"<"  { return relop_le; }
">=" { return relop_gq; }
"<=" { return relop_lq; }
"==" { return relop_eq; }
"!=" { return relop_ne; }

[=;,()\[\]{}+-/*] { return yytext[0]; }

[ \n\r\t]+ {}

[a-zA-Z_]+ { yylval.strval = strdup(yytext); return ID;   }
-?[0-9]+   { yylval.intval = atoi(yytext); return NUM; }

"/*".*"*/" {}
%%

void __parse_file_init(FILE* infile)
{
	yyin = infile;
}

void __parse_file_free(void)
{
	yyin = stdin;
}
