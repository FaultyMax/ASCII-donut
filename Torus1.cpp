#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif
using namespace std;

int main(){

    system(CLEAR_SCREEN);

    float A = 0,B = 0;
    float phi,theta;
    int k;
    float z[1760];
    char b[1760];
    while(true){
        memset(b,32,1760);
        memset(z,0,7040);
        for(theta=0; theta < 6.28; theta += 0.07){ // 6.28 to Donut, 0.28 to jebany pierścień XDD
            for(phi=0; phi < 6.28; phi += 0.02){
                float c = sin(phi);
                float d = cos(theta);
                float e = sin(A);
                float f = sin(theta);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (sin(phi) * (cos(theta) + 2 ) * sin(A) + sin(theta) * cos(A) + 10);
                float l = cos(phi);
                float m = cos(B);
                float n = sin(B);
                float t = sin(phi) * (cos(theta) + 2) * cos(A) - sin(theta) * sin(A);

                int rozmiar = 2;

                int x = 40 + 30 * rozmiar * D * (cos(phi) * (cos(theta) + 2) * m-t * n);
                int y = 12 + 15 * rozmiar * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]){
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < 1761; k++){
            putchar(k%80 ? b[k] : 10);
            A += 0.00011; // speed?
            B += 0.000015; // speed.
        }
        

        usleep(8000);
    }
    
    
    

    // pooof magic happens 

    return 0;
}