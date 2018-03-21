%{
    #include "y.tab.c"
%}
%%
A   {return A;}
B   {return B;}
.   {return yytext[0];}
\n  {return yytext[0];}
%%
