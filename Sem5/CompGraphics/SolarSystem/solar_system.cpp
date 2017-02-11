#include <iostream>
#include <bitset>
#include <algorithm>
#include <list>
#include <climits>
#include <graphics.h>
#include <assert.h>
#include <cmath>

#define ORIGIN_X 320
#define ORIGIN_Y 240
#define NUM_PLANETS 8
#define MAX_ASTEROIDS 100
const double pi = 4*atan(1);
using namespace std;


const string planet_names[8] = {"MERCURY", "VENUS", "EARTH", "MARS", "JUPITER", "SATURN", "URANUS", "NEPTUNE"};
const double planet_a[NUM_PLANETS] = {40, 75, 100, 140, 200, 240, 280, 310};
const double planet_b[NUM_PLANETS] = {25, 55, 70, 100, 155, 190, 230, 238};
const double planet_speed[NUM_PLANETS] = {4.78, -3.50, 2.97, 2.40, 1.30, 0.96, -0.68,0.54}; // assuming this to be the highest speed
const double planet_theta[NUM_PLANETS] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
const double planet_radius[NUM_PLANETS] = {26.8, 32.1, 42.7, 35.7, 142.9, 120.5, 52.118, 49.5};
const int planet_color[NUM_PLANETS] = {LIGHTGRAY, YELLOW, BLUE, RED, LIGHTRED, CYAN, LIGHTCYAN, LIGHTBLUE};

int shift_x(int x) {
	return x+ORIGIN_X;
}
int shift_y(int y) {
	return -y+ORIGIN_Y;
}
class HeavenlyBody{
	public:
		double a, b, speed, theta;
		double px, py;
		int radius, color;

		HeavenlyBody(){

		};
		HeavenlyBody(double a, double b, double speed, double theta, int radius, int color){
			this->a = a;
			this->b = b;
			this->speed = speed*pi/180.0;
			this->radius = radius;
			this->color = color;
			this->theta = theta;
			this->px = cos(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
			this->py = sin(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
		}

		void drawBody() {
			setcolor(this->color);
			//setfillstyle(SOLID_FILL,this->color);
			fillellipse(shift_x(this->px), shift_y(this->py), this->radius, this->radius);
		}
		double getSpeed() {
			double temp = this->speed;
			temp *= sqrt(pow(this->a,2)+pow(this->b,2));
			temp /= sqrt(pow(this->px,2)+pow(this->py,2));
			return temp;
		}
		void step() {
			this->theta = (this->theta + this->getSpeed());
			if(this->theta>2*pi) {
				this->theta -= 2*pi;
			}
			this->px = cos(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
			this->py = sin(this->theta)*(this->a*this->b)/sqrt(pow(this->b*cos(this->theta), 2)+pow(this->a*sin(this->theta), 2));
		}
};
class Planet : public HeavenlyBody{
	public:
		// Data Members
		string name;

		// Member Functions
		Planet(int num) :HeavenlyBody(planet_a[num], planet_b[num], planet_speed[num], planet_theta[num], planet_radius[num]/8, planet_color[num]) {
			;
			this->name = planet_names[num];
			/*
			this->a = planet_a[num];
			this->b = planet_b[num];
			this->speed = planet_speed[num]*pi/180.0;
			this->radius = planet_radius[num]/8;
			this->color = planet_color[num];
			this->theta = planet_theta[num];
			*/
		}
		void drawOrbit() {
			setcolor(this->color);
			ellipse(shift_x(0), shift_y(0), 0, 360, this->a, this->b);
		}
};
class Asteroid {
	public:
		int count;
		HeavenlyBody* list[MAX_ASTEROIDS];

		Asteroid(int num) {
			count = num;
		}
		double getRand(){
			double temp = rand()/100.0;
			temp = temp - floor(temp);
			return temp;
		}
		void initialise(){
			double temp,a,b,speed,theta;
			int radius;
			cout<<"initialising"<<endl;
			for(int i = 0; i<count; i++){
				a = planet_a[3] + 10 + (getRand()*(planet_a[4]-planet_a[3] - 30));
				b = planet_b[3] + 10 + (getRand()*(planet_b[4]-planet_b[3] - 30));
				speed = getRand();
				theta = getRand() * 2 * pi; // anyplace the asteroid can be at beginning
				radius = (((int)(getRand()*10))%2)+1;
				list[i] = new HeavenlyBody(a, b, speed, theta, radius, BROWN);
			}
		}
		void drawAsteroids(){
			for (int i = 0; i<count; i++){
				//cout<<"drawed asteroid "<<i<<endl;
				list[i]->drawBody();
				list[i]->step();
			}
		}
};
class SolarSystem {
	public:
		Planet* planets[NUM_PLANETS];
		Asteroid* asteroids;
		SolarSystem(int num) {
			for(int i=0; i<NUM_PLANETS; i++) {
				this->planets[i] = new Planet(i);
			}
			asteroids=new Asteroid(num);
		}
		void simulate(int iterations) {
			asteroids->initialise();
			while(iterations--) {
				setcolor(YELLOW);
				//setfillstyle(SOLID_FILL,YELLOW);
				fillellipse(shift_x(0), shift_y(0), 15, 15);
				for(int i=0; i<NUM_PLANETS; i++) {
					this->planets[i]->drawOrbit();
					this->planets[i]->drawBody();
					this->planets[i]->step();
				}
				asteroids->drawAsteroids();
				//getch();
				delay(50);
				if(iterations) cleardevice();
			}
		}
};


int main() {
	int gd = DETECT, gm;
	cout<<"start"<<endl;
	initgraph(&gd, &gm, NULL);
	SolarSystem ss(50);
	ss.simulate(500);
	getch();
	closegraph();
	return 0;
}
