%{
#include<stdio.h>
int integer=0, fraction=0, numbers=0;
%}


%%
[0-9]+ {integer++;numbers++;}
[0-9]+(\.[0-9]+) {fraction++;numbers++;}

%%





int main(int argc, char* argv[])
{
    if(argc!=2){
        printf("Enter one one input arg \n");
    } else {
        yyin = fopen(argv[1], "r");
        yylex();
        printf("\n%d integers", integer);
        printf("\n%d fractions",fraction);
        printf("\n%d total numbers",numbers);        
    }
}

int yywrap()
{
    return(1);
}
