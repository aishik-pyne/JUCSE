#include "graphics_utils.h"
int main(int argc, char const *argv[]) {
        initialiseGraph();
        grid();
        bresenhamColor(10,10,10,-10, RED);
        bresenhamColor(10,-10,-10,-10, RED);
        bresenhamColor(-10,-10,-10,10, RED);
        bresenhamColor(-10,10,10,10, RED);

        int clipWindow[4] = {-10, 10, -10, 10};
        // midpoint_clip(20, 20, -10, -20, clipWindow);
        // midpoint_clip(-5, 5, 5, -5, clipWindow);
        // midpoint_clip(20, 20, 20, -20, clipWindow);
        midpoint_clip(20, 20, -20, -20, clipWindow);
        midpoint_clip(-5, 5, 5, -5, clipWindow);
        midpoint_clip(23, 13, 17, -10, clipWindow);
        delay(100000);
        closegraph();
        return 0;
}
