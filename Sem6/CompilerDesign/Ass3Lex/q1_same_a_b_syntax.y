%{
    #include<iostream>
%}
%token A B
%%
S1 : S '\n'{return 0;}
S: A C| B D|A B|B A;
C: A C C| B S;
D: B D D| A S;
%%

main(int argc, char* argv[]) {
    if(argc!=2){
        printf("Enter one one input arg \n");
    } else {
        yyin = fopen(argv[1], "r");
        do {
            yyparse();
        } while (!feof(yyin));
    }
}
void yyerror(char *s) {
	std::cout << "EEK, parse error!  Message: " << s << std::endl;
	// might as well halt now:
	exit(-1);
}
