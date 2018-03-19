%{
#include<stdio.h>
int linenum = 1, columncount = 1, TOKEN_ID = 0;
%}

IDENTIFIER _{0,1}[a-zA-z]+[a-zA-z0-9]*
NUMERICAL -?([0-9]+|[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)
PUNCTUATION [;,"{}()]
ASSIGN_OP [=]
ARITH_OP [+*/\-]=?
REL_OP [<>]=?
EQUAL_SIGN ={2}
KEYWORD "if"|"else"|"for"|"int"|"float"|"void"|"return"|"char"

%%
\n {++linenum; columncount = 1;}
[\t ' '] {++columncount;}
\/\/.* ;
\/\*(.*\n)*.*\*\/ ;
[0-9&%^@$]+[a-zA-Z][a-zA-Z0-9&%^#@$]+ { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tINVALID\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
{KEYWORD} {printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tKEYWORD\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng;}
{ARITH_OP} { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tARITH_OP\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
{REL_OP} { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tREL_OP\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng;}
{ASSIGN_OP} { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tASSIGN_OP\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
{EQUAL_SIGN} { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tEQUAL_SIGN\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
{PUNCTUATION} { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tPUNCTUATION\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
{IDENTIFIER} {printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tIDENTIFIER\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng;}
{NUMERICAL} {printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tNUMERICAL\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng;}
\'[a-zA-Z0-9]\' { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tCHARACTER\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
\"[a-zA-Z0-9]*\" { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tLITERAL\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
[#\.%&:] { printf("%d\t\t",++TOKEN_ID); ECHO; printf("\t\tSPECIAL\t\t"); printf("(%d,%d)\n",linenum,columncount); columncount += yyleng; }
%%

int yywrap(){
    return 1;
}

int main(void){
    printf("ID\t\tLEXEME\t\tTYPE\t\tPOSITION\n");
    printf("-----------------------------------------------------------------\n");
    yyin = fopen("../input.txt","r");
    yylex();
}
