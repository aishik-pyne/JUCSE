#include "graphics_utils.h"
#include <math.h>

int main(int argc, char const *argv[]) {
    initialiseGraph();
    grid();

    int points[6] = {10,10,10,5,5,5};
    int n = 3;
    drawColorPoly(points, n, RED);
    rotate(points, n, PI/2);
    drawColorPoly(points, n, YELLOW);
    translate(points, n, -7, +3);
    drawColorPoly(points, n, GREEN);

    delay(400000);
    closegraph();
    return 0;
}
