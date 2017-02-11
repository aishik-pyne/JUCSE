#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define MAX_X 640
#define MAX_Y 480
#define SCALE 10
#define AXIS_COLOR GREEN
#define COLOR BLUE
const int TOP = 8;
const int BOTTOM = 4;
const int RIGHT = 2;
const int LEFT = 1;

void grid();

void initialiseGraph(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
}
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

// Pixel drawing
int getPixelColor(int x, int y){
    int X = x*SCALE + MAX_X/2;
    int Y = -y*SCALE + MAX_Y/2;
    return getpixel(X + SCALE/2, Y - SCALE/2);
}
void drawPixel(int x, int y){
    int color = COLOR;
    int x_range = MAX_X / SCALE;
    int y_range = MAX_Y / SCALE;
    int X = x*SCALE + MAX_X/2;
    int Y = -y*SCALE + MAX_Y/2;
    setcolor(color);
    rectangle(X+1,Y-1,X+SCALE-1,Y-SCALE+1);
    floodfill(X+2,Y-2, color);
    setcolor(BLACK);
}
void drawColorPixel(int x, int y, int color){
    int x_range = MAX_X / SCALE;
    int y_range = MAX_Y / SCALE;
    int X = x*SCALE + MAX_X/2;
    int Y = -y*SCALE + MAX_Y/2;
    setcolor(color);
    rectangle(X+1,Y-1,X+SCALE-1,Y-SCALE+1);
    floodfill(X+2,Y-2, color);
    setcolor(BLACK);
}

// Line Drawing
void dda(int x1, int y1, int x2, int y2){
    if(x1==x2 && y1==y2) {
        drawPixel(x1,y1);
    } else if(x1==x2) {
        int i;
        int ymin = y1<y2?y1:y2;
        int ymax = y1<y2?y2:y1;
        for(i=ymin;i<=ymax;i++) {
            drawPixel(x1, i);
        }
    } else if (y1==y2) {
        int i;
        int xmin = x1<x2?x1:x2;
        int xmax = x1<x2?x2:x1;
        for(i=xmin;i<=xmax;i++) {
            drawPixel(i, y1);
        }
    } else {
        printf("here\n");
        float dx, dy, len;
        if(abs(x1-x2)>abs(y1-y2)) {
            len = abs(x1-x2);
        } else {
            len = abs(y1-y2);
        }
        dx = (float)(x2-x1)/len;
        dy = (float)(y2-y1)/len;

        float x = x1;
        float y = y1;

        int i=0;
        while (i<=len) {
            printf("%f %f\n", x, y);
            drawPixel((int)x,(int)y);
            x += dx;
            y += dy;
            i++;
        }
    }
}
void bresenham(int x1, int y1, int x2, int y2){
    int x, y, dx, dy, s1, s2, interchange, e;
    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    // Initialze signs
    s1 = x1==x2?0:(x2>x1?1:-1);
    s2 = y1==y2?0:(y2>y1?1:-1);
    // Set interchange flag
    if(dy > dx ){
        interchange = 1;
        int temp = dx;
        dx = dy;
        dy = temp;
    }else{
        interchange=0;
    }
    e = 2 * dy - dx;

    int i;
    for(i=1;i<=dx;i++){
        drawPixel(x,y);
        while(e>0){
            if(interchange){
                x = x + s1;
            }else{
                y = y + s2;
            }
            e = e - 2*dx;
        }
        if(interchange){
            y = y + s2;
        }else{
            x = x + s1;
        }
        e = e + 2*dy;
    }
}
void bresenhamColor(int x1, int y1, int x2, int y2, int color){
    int x, y, dx, dy, s1, s2, interchange, e;
    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    // Initialze signs
    s1 = x1==x2?0:(x2>x1?1:-1);
    s2 = y1==y2?0:(y2>y1?1:-1);
    // Set interchange flag
    if(dy > dx ){
        interchange = 1;
        int temp = dx;
        dx = dy;
        dy = temp;
    }else{
        interchange=0;
    }
    e = 2 * dy - dx;

    int i;
    for(i=1;i<=dx;i++){
        drawColorPixel(x,y,color);
        while(e>0){
            if(interchange){
                x = x + s1;
            }else{
                y = y + s2;
            }
            e = e - 2*dx;
        }
        if(interchange){
            y = y + s2;
        }else{
            x = x + s1;
        }
        e = e + 2*dy;
    }
}

// Polygon Drawing
void drawPoly(int* points, int n){
    int i;
    for(i=0;i<n-1;i++){
        bresenham(points[2*i], points[2*i+1], points[2*i+2], points[2*i+3]);
    }
    bresenham(points[2*n-2], points[2*n-1], points[0], points[1]);
}
void drawColorPoly(int* points, int n, int color){
    int i;
    for(i=0;i<n-1;i++){
        bresenhamColor(points[2*i], points[2*i+1], points[2*i+2], points[2*i+3], color);
    }
    bresenhamColor(points[2*n-2], points[2*n-1], points[0], points[1], color);
}


// Line Clipping
int computeCode(int x, int y, int* clipWindow){
        int x_min = clipWindow[0];
        int x_max = clipWindow[1];
        int y_min = clipWindow[2];
        int y_max = clipWindow[3];

        int code = 0;
        if(x<x_min)
                code = code | LEFT;
        else if (x>x_max)
                code = code | RIGHT;
        if (y<y_min)
                code = code | TOP;
        else if (y>y_max)
                code = code | BOTTOM;

        return code;
}
void suderland_cohen(int x1, int y1, int x2, int y2, int* clipWindow){
        int code1 = computeCode(x1, y1, clipWindow);
        int code2 = computeCode(x2, y2, clipWindow);

        int x_min = clipWindow[0];
        int x_max = clipWindow[1];
        int y_min = clipWindow[2];
        int y_max = clipWindow[3];

        if(code1==0 & code2==0) {
                bresenham(x1, y1, x2, y2);
        } else if(code1 & code2) {
                bresenhamColor(x1, y1, x2, y2, YELLOW);
        } else {
                int code_out;
                double x, y;

                // At least one endpoint is outside the
                // rectangle, pick it.
                if (code1 != 0)
                        code_out = code1;
                else
                        code_out = code2;

                // Find intersection point;
                // using formulas y = y1 + slope * (x - x1),
                // x = x1 + (1 / slope) * (y - y1)
                if (code_out & TOP)
                {
                        // point is above the clip rectangle
                        x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                        y = y_max;
                }
                else if (code_out & BOTTOM)
                {
                        // point is below the rectangle
                        x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                        y = y_min;
                }
                else if (code_out & RIGHT)
                {
                        // point is to the right of rectangle
                        y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                        x = x_max;
                }
                else if (code_out & LEFT)
                {
                        // point is to the left of rectangle
                        y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                        x = x_min;
                }

                // Now intersection point x,y is found
                // We replace point outside rectangle
                // by intersection point
                if (code_out == code1)
                {
                        x1 = x;
                        y1 = y;
                        suderland_cohen(x1, y1, x2, y2, clipWindow);
                }
                else
                {
                        x2 = x;
                        y2 = y;
                        suderland_cohen(x1, y1, x2, y2, clipWindow);
                }
        }
}
void midpoint_clip(int x1, int y1, int x2, int y2, int* clipWindow){
        int code1 = computeCode(x1, y1, clipWindow);
        int code2 = computeCode(x2, y2, clipWindow);

        int x_min = clipWindow[0];
        int x_max = clipWindow[1];
        int y_min = clipWindow[2];
        int y_max = clipWindow[3];
        if(abs(x1-x2)<=1 && abs(y1-y2)<=1){
            return;
        }
        if(code1==0 & code2==0) {
                bresenham(x1, y1, x2, y2);
                // delay(4000);
        } else if(code1 & code2) {
                bresenhamColor(x1, y1, x2, y2, YELLOW);
                // delay(4000);
        } else {
                int m_x = (x2+x1)>>1;
                int m_y = (y2+y1)>>1;
                midpoint_clip(x1, y1, m_x, m_y, clipWindow);
                midpoint_clip(m_x, m_y, x2, y2, clipWindow);
        }
}
