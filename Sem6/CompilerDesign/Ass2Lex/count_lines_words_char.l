%{
    #include <stdio.h>
    int lines=0;
    int words=0;
    int chars=0;
%}

%%
[a-z] chars++;
\n { lines++; words++;}
[\t ' '] words++;
%%


int main(int argc, char* argv[]) {
    if(argc!=2){
        printf("Enter one one input arg \n");
    } else {
        yyin = fopen(argv[1], "r");
        yylex();
        printf("No of lines are %d \n", lines);
        printf("No of words are %d \n", words);
        printf("No of chars are %d \n", chars);
    }
    return 0;
}
