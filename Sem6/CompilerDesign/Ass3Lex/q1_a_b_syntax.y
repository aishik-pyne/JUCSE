%{
    #include<stdio.h>
    #include<stdlib.h>
%}
%token A B
%%
S1 : S '\n' {return 0;}
S: C D;
C: A C|;
D: B D|;
%%

int main(void)
{
    printf ("Grammar to accept strings of the form A*B*\n");
    printf("Enter the string:");
    yyparse();
    printf("Valid String\n");
}
void yyerror(char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
