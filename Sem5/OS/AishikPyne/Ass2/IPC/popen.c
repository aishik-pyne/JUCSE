#include <stdio.h>
#include <unistd.h>
int main ()
{
    FILE* stream = popen ("./pipe", "r");
    char buffer[1024];
    while (!feof (stream)
            && !ferror (stream)
            && fgets (buffer, sizeof (buffer), stream) != NULL){
        fputs (buffer, stdout);
        fflush(stream);
    }

    return pclose (stream);
}
