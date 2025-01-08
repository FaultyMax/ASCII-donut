// własny kod donuta bo cudzy mnie pokonał

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <vector>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

// wszelkie zmienne

const float pi = 3.14159;

int screen_width = 80, screen_height = 22; // szerokość i wysokość ekranu terminala.

float angle_A , angle_B; // dwa kąty wokól których będziemy obracać. Kąt A obraca wokół osi Z a B wokół osi X

float A_val = 0.000006; float B_val = 0.000003; // oryginalnie 0.000005 i 0.0000025

float radius = 1,origin = 2; // R1 i R2

float K2 = 8; // dystans od donuta ( początkowo obserwator znajduje się na początku układu)

float K1 = (screen_width * K2 * 2)/(8*(radius+origin)); // z' 

float theta = 0,phi = 0; // dwa kąty których obrót będzie tworzyć torus

float theta_spacing = 0.06 ,phi_spacing = 0.03; // ilość rozmieszczenia punktów torusu

int main(){

    //int screen_area = screen_width*screen_height;

    system(CLEAR_SCREEN); // czyszczenie ekranu

    while(true){

        vector <char> characterbuffer(screen_width*screen_height,' ');
        vector <float> zbuffer(screen_width*screen_height, 0); 

        float cosA = cos(angle_A), sinA = sin(angle_A);
        float cosB = cos(angle_B), sinB = sin(angle_B);

        for(theta = 0 ; theta < 2*pi ; theta += theta_spacing){

            float cos_theta = cos(theta), sin_theta = sin(theta);

            for(phi = 0 ; phi < 2*pi ; phi += phi_spacing){

                float cos_phi = cos(phi), sin_phi = sin(phi);

                float circlex = origin + radius*cos_theta;
                float circley = radius*sin_theta;

                // obliczanie współrzędnych punktów w 3D (x y z) po obróceniu...

                float x = circlex * (cosB * cos_phi + sinA * sinB * sin_phi) - circley * cosA * sinB;

                float y = circlex * (cos_phi * sinB - cosB * sinA * sin_phi) + circley * cosA * cosB;

                float z = circlex * cosA * sin_phi + circley * sinA + K2; // oprócz pomnożonej macierzy dodajemy stałą K2

                float ooz = 1/z; // "one over z"

                // projekcja x i y

                int xp = int(screen_width/2 + K1*ooz*x); 
                int yp = int(screen_height/2 - K1*ooz*y*0.5); // w 3D y idzie w "góre", ale nie w 2D więc y jest zanegowana

                // efekt oświetlenia

                double luminance = (cos_phi * cos_theta * sinB) - (cosA * cos_theta * cos_phi) - (sinA * sin_theta) + (cosB * ((cosA * sin_theta) - (cos_theta * sinA * sin_phi)));

                // zmienna luminance wacha się od -sqrt(2) do sqrt(2), ale jeśli jest < 0 to powierzchnia nie jest skierowana do nas, więc ją pomijamy.

                if ( luminance < 0){ luminance = 0;}

                int pos = xp + yp * screen_width;

                if ( pos >= 0 && pos < screen_width*screen_height){

                    if(ooz > zbuffer[pos]){ // większe ooz oznacza że pixel jest bliżej obserwatora niż to co poprzednio tam stało.
                        zbuffer[pos] = ooz;

                        int luminance_index = int(luminance*8);

                        //if (luminance_index > 11){luminance_index = 11;}

                        characterbuffer[pos] = ".,-~:;=!*#$@12"[luminance_index > 0 ? luminance_index : 0];

                    }

                }

            }
        }

        cout << "\x1b[H";

        for(int p = 0 ; p < screen_width*screen_height ; p++){
            cout.put( p % screen_width ? characterbuffer[p] : '\n');
            angle_A += A_val;
            angle_B += B_val;
        }

        usleep(5000);

    }

    return 0;
}

