#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(){

    char cont;

    do {

        cout << "Utworzyć donuta? ( y )" << endl;

        cin >> cont; if (cont != 'y'){break;}

        // potrzebne zmienne

        const float pi = 3.1415;

        int inc = 0;
        int inc_goal;

        float A_val = 0;
        float B_val = 0;

        float theta_spacing = 0;
        float phi_spacing = 0;

        int skala = 1;

        int debug_info;

        // wprowadzenie danych użytkownika

        cout << "Ilość iteracji pętli?" << endl; cin >> inc_goal;

        cout << "wartości zwiększenia A i B?" << endl; cin >> A_val; cin >> B_val;

        cout << "wartości zwiększenia thety i phi? ( zalecane 0.09 i 0.03 )" << endl; cin >> theta_spacing; cin >> phi_spacing;

        cout << "skala? ( liczba całkowita )" << endl; cin >> skala;

        cout << "Debug info? (1/0)" << endl; cin >> debug_info;

        // generowanie donuta

        printf("\x1b[2J");

        float A = 0,B = 0;

        float phi,theta; // <-- dwie zmienne potrzebne do stworzenia torusu

        float z[1760]; // 22 * 80 rozmiar terminala
        char b[1760];
        while(inc < inc_goal){
            memset(b,32,1760);
            memset(z,0,7040); // to jest 1760 * 4 bo float ma 4 bity
            for(theta=0 ; theta < 2 * pi ; theta += theta_spacing){ 

                float cos-theta = cos(theta);

                for(phi=0 ; phi < 2 * pi ; phi += phi_spacing){
                    float c = sin(phi);
                    float e = sin(A);
                    float f = sin(theta);
                    float g = cos(A);
                    float h = cos-theta + 2;

                    float Depth = 1 / (c * h * e + f * g + 5.5);

                    float l = cos(phi);

                    float m = cos(B);
                    float n = sin(B);

                    float t = c * h * g - f * e;

                    int x = 40 + 30 * skala * Depth * (l * h * m - t * n);
                    int y = 12 + 15 * skala * Depth * (l * h * n + t * m);
                    int o = x + 80 * y;
                    int N = 8 * ((f * e - c * cos-theta * g) * m - c * cos-theta * e - f * g - l * cos-theta * n);

                    if(22 > y && y > 0 && x > 0 && 80 > x && Depth > z[o]){
                        z[o] = Depth;
                        b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                    }
                }
            }
            printf("\x1b[H");
            for (int k = 0; k < 1761; k++){
                putchar(k%80 ? b[k] : 10);
                A += 0.0000025; // speed?
                B += 0.0000015; // speed.

                if (A > 2*pi){ A -= 2*pi; }
                if (B > 2*pi){ B -= 2*pi; }

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
