#include "graphics_utils.h"

void seedfill(int x, int y, int boundaryColor){

    if(boundaryColor != getPixelColor(x,y)){
        drawPixel(x,y);
        delay(100);
        seedfill(x+1,y, boundaryColor);
        seedfill(x,y+1, boundaryColor);
        seedfill(x-1,y, boundaryColor);
        seedfill(x,y-1, boundaryColor);

    }
}
int main(int argc, char const *argv[]) {
    initialiseGraph();
    grid();

    int points[10] = {0,10,7,4,4,-7,-4,-7,-7,4};
    int n = 5;
    drawPoly(points, n);
    // int points2[8] = {2,0,2,2,-2,2,-2,0};
    // drawPoly(points2, 4);
    delay(5000);
    seedfill(0, -6, BLUE);

    delay(400000);
    closegraph();
    return 0;
}
