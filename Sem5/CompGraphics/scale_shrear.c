#include "graphics_utils.h"
#include <math.h>

int main(int argc, char const *argv[]) {
    initialiseGraph();
    grid();

    int points[8] = {10,10,10,0,0,0,0,10};
    int n = 4;
    drawColorPoly(points, n, RED);
    shear(points, n, PI/7, 0);
    drawColorPoly(points, n, YELLOW);
    translate(points, n, -16, 0);
    drawColorPoly(points, n, CYAN);
    scale(points, n, 2, 2);
    drawColorPoly(points, n, GREEN);

    delay(400000);
    closegraph();
    return 0;
}
