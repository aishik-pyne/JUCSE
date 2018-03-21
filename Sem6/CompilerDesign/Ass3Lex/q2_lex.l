DIGIT [0-9]+\.?|[0-9]*\.[0-9]+

%option noyywrap

%%

[ ]
{DIGIT} {yylval = atof(yytext); return ID;} // atof works ???
\n|. {return yytext[0];}

%%
