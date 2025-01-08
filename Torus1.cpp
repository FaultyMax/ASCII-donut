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

// leciutka modyfikacja, dodano parametry dla pi, thety i phi

float theta_goal = 6.28, phi_goal = 6.28;

float theta_spacing = 0.07, phi_spacing = 0.02;

int main(){

    system(CLEAR_SCREEN);

    cout << "do jakiej wartości ma zmierzać theta? "; cin >> theta_goal;
    cout << "do jakiej wartości ma zmierzać phi? "; cin >> phi_goal;

    cout << "co ile zwiększać kąt theta? "; cin >> theta_spacing;
    cout << "co ile zwiększać kąt phi? "; cin >> phi_spacing;

    system(CLEAR_SCREEN);

    float A = 0,B = 0;
    float phi,theta;
    int k;
    float z[1760];
    char b[1760];
    while(true){
        memset(b,32,1760);
        memset(z,0,7040);
        for(theta=0; theta < theta_goal; theta += theta_spacing){ 
            for(phi=0; phi < phi_goal; phi += phi_spacing){
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
            A += 0.000011; 
            B += 0.0000049;

            // zmienna float jest ograniczona więc co 2pi ją resetujemy

            if (A > 6.28){ A -= 6.28; }
            if (B > 6.28){ B -= 6.28; }

        }
        

        usleep(30000);
    }

    return 0;
}