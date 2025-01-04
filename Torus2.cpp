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

    char cont;

    do {

        cout << "Utworzyć donuta? ( y )" << endl;

        cin >> cont; if (cont != 'y'){break;}

        // potrzebne zmienne

        //int k;

        int inc = 0;
        int inc_goal;

        int debug_info;

        // wprowadzenie danych użytkownika

        cout << "Ilość iteracji pętli?" << endl; cin >> inc_goal;

        cout << "Debug info? (1/0)" << endl; cin >> debug_info;

        // generowanie donuta

        system(CLEAR_SCREEN);

        float A = 0,B = 0;

        float phi,theta; // <-- dwie zmienne potrzebne do stworzenia torusu

        float z[1760];
        char b[1760];
        while(inc < inc_goal){
            memset(b,32,1760);
            memset(z,0,7040);
            for(theta=0; theta < 6.28; theta += 0.09){ 
                for(phi=0; phi < 6.28; phi += 0.03){
                    float c = sin(phi);
                    float d = cos(theta);
                    float e = sin(A);
                    float f = sin(theta);
                    float g = cos(A);
                    float h = d + 2;
                    float Depth = 1 / (sin(phi) * (cos(theta) + 2 ) * sin(A) + sin(theta) * cos(A) + 10);
                    float l = cos(phi);
                    float m = cos(B);
                    float n = sin(B);
                    float t = sin(phi) * (cos(theta) + 2) * cos(A) - sin(theta) * sin(A);

                    int rozmiar = 2.5;

                    int x = 40 + 30 * rozmiar * Depth * (cos(phi) * (cos(theta) + 2) * m-t * n);
                    int y = 12 + 15 * rozmiar * Depth * (l * h * n + t * m);
                    int o = x + 80 * y;
                    int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                    if(22 > y && y > 0 && x > 0 && 80 > x && Depth > z[o]){
                        z[o] = Depth;
                        b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                    }
                }
            }
            printf("\x1b[H");
            for (int k = 0; k < 1761; k++){
                putchar(k%80 ? b[k] : 10);
                A += 0.000002; // speed?
                B += 0.0000005; // speed.

                if (A > 6.28){ A -= 6.28; }
                if (B > 6.28){ B -= 6.28; }

            }
            inc++;
            if(debug_info == 1){
                cout << "wartość A i B: " << A << " " << B << endl;
            }
            cout << "inc: " << inc << endl;
            usleep(5000);
        }

    } while (cont == 'y');

    return 0;
}
