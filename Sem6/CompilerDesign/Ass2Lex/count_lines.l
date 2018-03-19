%{
    #include <stdio.h>
    int lines =0;
%}

%%
\n lines++;
%%


main(int argc, char* argv[]) {
    if(argc!=2){
        printf("Enter one one input arg \n");
    } else {
        yyin = fopen(argv[1], "r");
        yylex();
        printf("No of lines are %d", lines);
    }
}
