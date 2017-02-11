#include<graphics.h>
#include<stdio.h>

void wait_for_char()
{
  //Wait for a key press
  int in = 0;
  while (in == 0) {
     in = getchar();
  }
}


int main()
{
  // int gd=DETECT,gm;
  int gd = 100;
  int gm = 100;
  int i,x,y;
  initgraph(&gd,&gm,NULL);
  line(0,0,10,0);

  getch();
  wait_for_char();
  closegraph();
  return 0;
}
