#include "graphics_utils.h"
#include <time.h>



int main(int argc, char const *argv[]) {
    initialiseGraph();
    grid();

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int i;
    // for(i=0;i<1000;i++)
    bresenham(1, 1, -9, -9);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);


    delay(40000000);
    closegraph();
    return 0;
}
