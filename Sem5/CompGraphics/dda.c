#include <stdio.h>
#include <stdlib.h>
#include "graphics_utils.h"

int main()
{
    int x1,x2,y1,y2;
    printf("Enter x1 y1 x2 y2 in order\n");
    scanf("%d", &x1);
    scanf("%d", &y1);
    scanf("%d", &x2);
    scanf("%d", &y2);
    printf("%d %d %d %d\n", x1, y1, x2, y2);
    initialiseGraph();
    grid();
    dda(x1, y1, x2, y2);
    delay(4000000000);
    closegraph();
    return 0;
}
