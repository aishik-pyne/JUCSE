#include "graphics_utils.h"

void drawCircle(int xc, int yc, int x, int y)
{
        drawPixel(xc+x, yc+y);
        drawPixel(xc-x, yc+y);
        drawPixel(xc+x, yc-y);
        drawPixel(xc-x, yc-y);
        drawPixel(xc+y, yc+x);
        drawPixel(xc-y, yc+x);
        drawPixel(xc+y, yc-x);
        drawPixel(xc-y, yc-x);
}
// Function for circle-generation
// using Bresenham's algorithm
void circleBres(int xc, int yc, int r)
{
        int x = 0, y = r;
        int d = 3 - 2 * r;
        while (y >= x)
        {
                // for each pixel we will
                // draw all eight pixels
                drawCircle(xc, yc, x, y);
                x++;
                // check for decision parameter
                // and correspondingly
                // update d, x, y
                if (d > 0)
                {
                        y--;
                        d = d + 4 * (x - y) + 10;
                }
                else
                        d = d + 4 * x + 6;
                drawCircle(xc, yc, x, y);
                delay(200);
        }
}

// driver function
int main()
{
        int xc = 0, yc = 0, r2 = 15;
        initialiseGraph();
        grid();
        delay(5000);
        circleBres(xc, yc, r2);
        delay(1000000);
        closegraph();
        return 0;
}
