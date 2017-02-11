#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define MAX_X 640
#define MAX_Y 480
#define SCALE 10
#define AXIS_COLOR GREEN


void grid(){
    int x,y;
    setbkcolor(WHITE);
    setcolor(BLACK);
    for(x=0; x<MAX_X; x+=SCALE) {
        if(x==MAX_X/2){
            setcolor(AXIS_COLOR);
            setlinestyle(0, 0, 2);
            line(x,0,x,MAX_Y);
            setcolor(BLACK);
            setlinestyle(0, 0, 1);
            continue;
        }
        line(x,0,x,MAX_Y);
    }
    for(y=0; y<MAX_Y; y+=SCALE) {
        if(y==MAX_Y/2){
            setcolor(AXIS_COLOR);
            setlinestyle(0, 0, 2);
            line(0,y,MAX_X,y);
            setcolor(BLACK);
            setlinestyle(0, 0, 1);
            continue;
        }
        line(0,y,MAX_X,y);
    }
}
void drawPixel(int x, int y, int color){
    int x_range = MAX_X / SCALE;
    int y_range = MAX_Y / SCALE;
    int X = x*SCALE + MAX_X/2;
    int Y = -y*SCALE + MAX_Y/2;
    setcolor(color);
    rectangle(X+1,Y-1,X+SCALE-1,Y-SCALE+1);
    floodfill(X+2,Y-2, color);
    setcolor(BLACK);
}

void naiveDrawLine(int x1, int y1, int x2, int y2){
   float m = (float)(y2 - y1)/(float)(x2 - x1);
   float c = (float)(x2*y1-x1*y2) / (float)(x2-x1);
   int x, y;
   for (x  = x1; x <= x2; x++)
   {
      y = (int)(m*x + c);
      drawPixel(x, y, RED);
   }
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    grid();
    // drawPixel(0, 0, RED);
    // naiveDrawLine(0,0,10,10);

    delay(4000000000);
    closegraph();
    return 0;
}
