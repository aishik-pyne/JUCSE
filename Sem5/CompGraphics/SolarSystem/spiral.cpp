#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define MAX_X 640
#define MAX_Y 480
#define ORIGIN_X 320
#define ORIGIN_Y 240
double const EXPANSION =0.6;

double const PI = 4*atan(1);
double const VEL = PI/32;

int shiftx(int x){
    return x+ORIGIN_X;
}
int shifty(int y){
    return -y+ORIGIN_Y;
}
double next_r(double r){
    return EXPANSION + r;
}
double next_theta(double theta){
    theta = (theta+VEL);
    if(theta>2*PI)
        theta-=2*PI;
    if(theta<-2*PI)
        theta+=2*PI;
        return theta;
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    int x=0, y=0;
    double r=1;
    double theta=0.0;
    do {
        r = next_r(r);
        theta = next_theta(theta);
        int next_x = r*cos(theta);
        int next_y = r*sin(theta);
        line(shiftx(x),shifty(y),shiftx(next_x), shifty(next_y));
        x=next_x;
        y=next_y;
    } while(x>-MAX_X/2 && x<MAX_X/2 && y>-MAX_Y/2 && y<MAX_Y/2);


    delay(400000);
    closegraph();
    return 0;
}
