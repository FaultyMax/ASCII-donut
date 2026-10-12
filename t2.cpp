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
#include <random>
#include <ctime>

float random_float(float min, float max) {

	return ((float)rand() / RAND_MAX) * (max - min) + min;

}

using namespace std;

int main(){

    srand(time(0));

    float a_val=0;
    float b_val=0;

    char cont;

    do {

        cout << "Utworzyć donuta? ( y )" << endl;

        cin >> cont; if (cont != 'y'){break;}

        // potrzebne zmienne

        int inc = 0;
        int inc_goal = 1;

        int debug_info = 1;

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
            a_val = random_float(0.0000001,0.00000920);
            b_val = random_float(0.0000001,0.00000599);
            memset(b,32,1760);
            memset(z,0,7040);
            for(theta=0; theta < 6.28; theta += 0.09){ 
                for(phi=0; phi < 6.28; phi += 0.05){
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
                A += a_val; // obrót o oś x
                B += b_val; // obrót o oś z

                // zmienna float jest ograniczona więc co 2pi ją resetujemy

                if (A > 6.28){ A -= 6.28; }
                if (B > 6.28){ B -= 6.28; }

            }
            inc++;
            if(debug_info == 1){
                cout << "wartość A i B: " << A << " " << B << endl;
            }
            cout << "inc: " << inc << endl; // dlaczego donut sie przez to zapada? ( dobra ok terminal był za mały )
            usleep(7000);
        }

    } while (cont == 'y');

    return 0;
}
