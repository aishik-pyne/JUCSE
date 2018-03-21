%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    
    #define YYSTYPE double // remember this
%}

%token ID
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S : S E '\n'{printf("Answer: %g \nEnter the expression:\n", $2); }
| S '\n';
|;
| error '\n' { yyerror("Error: Enter the expression\n" );yyerrok; }
;
E : E '+' E { $$ = $1 + $3; };
| E '-' E { $$ = $1 - $3; };
| E '*' E { $$ = $1 * $3; };
| E '/' E { $$ = $1 / $3; };
| '('E')' { $$ = $2; };
| '-'E %prec UMINUS { $$= -$2; };
| ID
;
%%

#include "lex.yy.c"

int main()
{
    printf("Enter the expression: ");
    yyparse();
}

int yyerror (char *s)
{
    printf("%s\n", s);
    exit(1);
}
