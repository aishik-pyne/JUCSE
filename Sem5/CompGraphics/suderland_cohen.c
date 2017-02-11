#include "graphics_utils.h"

int main(int argc, char const *argv[]) {
        initialiseGraph();
        grid();
        bresenhamColor(10,10,10,-10, RED);
        bresenhamColor(10,-10,-10,-10, RED);
        bresenhamColor(-10,-10,-10,10, RED);
        bresenhamColor(-10,10,10,10, RED);

        int clipWindow[4] = {-10, 10, -10, 10};
        suderland_cohen(20, 20, -20, -20, clipWindow);
        suderland_cohen(-5, 5, 5, -5, clipWindow);
        suderland_cohen(20, 20, 20, -20, clipWindow);
        delay(100000);
        closegraph();
        return 0;
}
