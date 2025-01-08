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

char cont;

int main(){

    do {

        cout << "Utworzyć donuta? ( y )" << endl;

        cin >> cont; if (cont != 'y'){break;}

        // potrzebne zmienne

        const float pi = 3.1415;

        int inc = 0;
        int inc_goal;

        int screenwidth=80,screenheight=22,screen_area=screenwidth*screenheight;

        float A_val = 0;
        float B_val = 0;

        float theta_spacing = 0;
        float phi_spacing = 0;

        int scale = 1;

        int debug_info;

        int def = 0;

        // wprowadzenie danych użytkownika

        cout << "Ilość iteracji pętli?" << endl; cin >> inc_goal;

        cout << "użyć wartości domyślnych? (1/0)" << endl; cin >> def;

        if (def == 1){

            A_val = 0.0000025;
            B_val = 0.0000015;
            theta_spacing = 0.09;
            phi_spacing = 0.03;

        }else{

            cout << "wartości zwiększenia A i B?" << endl; cin >> A_val; cin >> B_val;

            cout << "wartości zwiększenia thety i phi? ( zalecane 0.09 i 0.03 )" << endl; cin >> theta_spacing; cin >> phi_spacing;

            cout << "skala? ( liczba całkowita )" << endl; cin >> scale;

        }

        cout << "Debug info? (1/0)" << endl; cin >> debug_info;

        // generowanie donuta

        system(CLEAR_SCREEN); // wczesniej uzywałem printf(\x1b[2J) ale tworzyło to dziwne błędy.

        float A = 0,B = 0;

        float phi,theta; // <-- dwie zmienne potrzebne do stworzenia torusu

        float z[1760]; // 22 * 80 rozmiar terminala
        char b[1760];
        while(inc < inc_goal){
            memset(b,32,1760);
            memset(z,0,1760*4); // to jest 1760 * 4 bo float ma 4 bity
            float fff;
            for(theta=0 ; theta < 2 * pi ; theta += theta_spacing){ 

                float cos_theta = cos(theta);
                float sin_theta = sin(theta);

                for(phi=0 ; phi < 2 * pi ; phi += phi_spacing){

                    float cos_phi = cos(phi);
                    float sin_phi = sin(phi);

                    float e = sin(A);

                    float g = cos(A);

                    float h = 2 + cos_theta; //

                    float K2 = 5.5; // chyba to jest K2?

                    float Depth = 1 / (K2 + sin_phi * h * e + sin_theta * g);

                    float m = cos(B);
                    float n = sin(B);

                    float t = sin_phi * h * g - sin_theta * e; // A PO CHUJ TO TUTAJ JEST?

                    int x = 40 + 30 * scale * Depth * (cos_phi * h * m - t * n);
                    int y = 12 + 15 * scale * Depth * (cos_phi * h * n + t * m);

                    int pos = x + y * 80;
                    int N = 8 * ((sin_theta * e - sin_phi * cos_theta * g) * m - sin_phi * cos_theta * e - sin_theta * g - cos_phi * cos_theta * n);

                    fff = (cos_phi * cos_theta * n - g * cos_theta * sin_phi - e * sin_theta + m * (g * sin_theta - cos_theta * e * sin_phi)); 

                    if(22 > y && y > 0 && x > 0 && 80 > x && Depth > z[pos]){
                        z[pos] = Depth;
                        b[pos] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                    }
                }
            }
            printf("\x1b[H");
            for (int k = 0; k < 1761; k++){
                putchar(k%80 ? b[k] : 10);
                A += A_val; // speed?
                B += B_val; // speed.

                if (A > 2*pi){ A -= 2*pi; }
                if (B > 2*pi){ B -= 2*pi; }

            }
            inc++;
            if(debug_info == 1){
                cout << "wartość A i B: " << A << " " << B << endl;
                cout << "inc: " << inc << endl;
            }
            usleep(5000);
        }

    } while (cont == 'y');

    return 0;
}
