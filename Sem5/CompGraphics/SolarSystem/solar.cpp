#include "graphics_utils.h"
#include <string>
#define ORIGIN_X 320
#define ORIGIN_Y 240
#define MAX_PLANETS 8
const double pi = 4*atan(1);
using namespace std;


const string planet_names[8] = {"MERCURY", "VENUS", "EARTH", "MARS", "JUPITER", "SATURN", "URANUS", "NEPTUNE"};
// const double planet_a[MAX_PLANETS] = {57.9, 108.2, 149.6, 227.9, 778.6, 1433.5, 2872.5, 4495.1};
// const double planet_b[MAX_PLANETS] = {50, 100, 130, 200, 700, 1300, 2550, 4000};
const double planet_a[MAX_PLANETS] = {40, 75, 100, 140, 200, 240, 280, 310};
const double planet_b[MAX_PLANETS] = {25, 55, 70, 100, 155, 190, 230, 210};
const double planet_speed[MAX_PLANETS] = {4.78, -3.50, 2.97, 2.40, 1.30, 0.96, -0.68,0.54};
const double planet_theta[MAX_PLANETS] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
const double planet_radius[MAX_PLANETS] = {4.8, 12.1, 12.7, 6.7, 142.9, 120.5, 52.118, 49.5};
const int planet_color[MAX_PLANETS] = {LIGHTGRAY, YELLOW, BLUE, RED, LIGHTRED, CYAN, LIGHTCYAN, LIGHTBLUE};


int shiftx(int x){
    return x+ORIGIN_X;
}
int shifty(int y){
    return -y+ORIGIN_Y;
}
class Planet {
    public:
    // Data Members
    string name;
    double a, b, speed, theta;
    double px, py;
    int radius, color;

    // Member Functions
    Planet(string name, double a, double b, double speed, double theta =0,int radius=100, int color=WHITE){
        this->name = name;
        this->a = a;
        this->b = b;
        this->speed = speed*pi/180.0;
        this->radius = radius;
        this->color = color;
        this->theta = theta;
        this->px = cos(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
        this->py = sin(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));

    }

    void drawPath(){
        setcolor(this->color);
        ellipse(shiftx(0), shifty(0), 0, 360, this->a, this->b);
    }
    void drawPlanet(){
        setcolor(this->color);
        fillellipse(shiftx(this->px), shifty(this->py), this->radius, this->radius);
    }
    void step(){
        this->theta = (this->theta+this->speed);
        if(this->theta>2*pi){
            this->theta -= 2*pi;
        }
        this->px = cos(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
        this->py = sin(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
    }

};
class SolarSystem{
    public:
    Planet* planets[MAX_PLANETS];

    SolarSystem(){
        for(int i=0;i<MAX_PLANETS;i++){
            this->planets[i] = new Planet(planet_names[i], planet_a[i], planet_b[i], planet_speed[i], planet_theta[i], planet_radius[i]/8, planet_color[i]);
        }
    }
    void simulate(int iterations){
        while(iterations--){
            setcolor(YELLOW);
            fillellipse(shiftx(-10), shifty(0), 15, 15);
            for(int i=0;i<MAX_PLANETS;i++){
                this->planets[i]->drawPath();
                this->planets[i]->drawPlanet();
                this->planets[i]->step();
            }
            delay(50);
            cleardevice();
        }
    }
};


int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    SolarSystem ss;
    ss.simulate(500);


    delay(400000);
    closegraph();
    return 0;
}
