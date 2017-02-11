#include "graphics_utils.h"
#include <stdio.h>
void cyrus_beck(int x1, int y1, int x2, int y2, int* vertices, int n){
    float tl = 1;
    float tu = 0;
    int i;
    for(i=0;i<n;i++){
        // printf("edge %d\n",i );
        // printf("%d %d \n", vertices[((2*i)%n+2)], vertices[((2*i)%n)]);
        float dx = (float)(vertices[((2*i)%n+2)] - vertices[((2*i)%n)]);
        float dy = (float)(vertices[((2*i)%n+3)] - vertices[((2*i)%n+1)]);
        float n_i = -dy;
        float n_j = dx;
        float D_i = (float)(x2-x1);
        float D_j = (float)(y2-y1);
        float f_x = vertices[(2*i+2)%n];
        float f_y = vertices[(2*i+3)%n];
        float Wn = (x1-f_x)*n_i + (y1-f_y)*n_j;
        float Dn = D_i*n_i + D_j*n_j;
        // printf("D_i=%f D_j=%f n_i=%f n_j=%f\n", D_i, D_j, n_i, n_j);
        // D.n == 0 Reject
        if(Dn == 0){
            if(Wn<0) return;
        } else {
            float t = - Wn/Dn;
            if (Dn > 0){
                // printf("DN>0\n" );
                if(t>1) return;
                if(t>tl) tl = t;
            } else {
                // printf("DN<0\n" );
                if(t<0) return;
                if(t<tu) tu = t;
            }
        }
    }
    // printf("%f %f\n", tl, tu);
    int X1 = (int)((float)x1 + tl*(float)(x2-x1));
    int Y1 = (int)((float)y1 + tl*(float)(y2-y1));
    int X2 = (int)((float)x1 + tu*(float)(x2-x1));
    int Y2 = (int)((float)y1 + tu*(float)(y2-y1));
    bresenham(X1, Y1, X2, Y2);

}
int main(int argc, char const *argv[]) {
        printf("Enter no of vertices: " );
        int n;
        scanf("%d", &n);
        int box[2*n];
        int i;
        for(i=0;i<n;i++){
            printf("Enter vertex %d (x, y): ", i);
            scanf("%d %d", &box[2*i], &box[2*i+1]);
        }
        printf("Enter no of lines: " );
        int l;
        scanf("%d", &l);
        int lines[4*l];
        for(i=0;i<l;i++){
            printf("Enter vertex %d (x1, y1, x2, y1): ", i);
            scanf("%d %d %d %d", &lines[4*i], &lines[4*i+1], &lines[4*i+2], &lines[4*i+3]);
        }


        initialiseGraph();
        grid();

        drawColorPoly(box, n, GREEN);
        for(i=0;i<l;i++){
            cyrus_beck(lines[4*i],lines[4*i+1],lines[4*i+2],lines[4*i+3],box, n);
        }

        delay(100000);
        closegraph();
        return 0;
}
