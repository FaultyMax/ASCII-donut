// własny kod donuta bo cudzy mnie pokonał

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <unistd.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

// wszelkie zmienne

const float pi = 3.14159;

int screen_width = 100, screen_height = 80; // szerokość i wysokość ekranu terminala.

float angle_A , angle_B; // dwa kąty wokól których będziemy obracać. Kąt A obraca wokół osi Z a B wokół osi X

float radius = 1,origin = 2; // R1 i R2

float K2 = 5; // dystans od donuta ( początkowo obserwator znajduje się na początku układu)

float K1 = (screen_width * K2 * 3)/(8*(radius+origin)); // z'

float theta = 0,phi = 0; // dwa kąty których obrót będzie tworzyć torus

float theta_spacing = 0.09 ,phi_spacing = 0.03; // ilość rozmieszczenia punktów torusu

int main(){

    

    K1 = 50;

    //int screen_area = screen_width*screen_height;

    system(CLEAR_SCREEN); // czyszczenie ekranu

    while(true){

        char characterbuffer[screen_width*screen_height];
        float zbuffer[screen_width*screen_height]; 

        memset(characterbuffer,32,screen_width*screen_height); // 32 to ' '
        memset(zbuffer,0,screen_width*screen_height);

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

                float luminance = cos_phi * cos_theta * sinB - cosA * cos_theta * cos_phi - sinA * sin_theta + cosB * (cosA * sin_theta - cos_theta * sinA * sin_phi);

                // zmienna luminance wacha się od -sqrt(2) do sqrt(2), ale jeśli jest < 0 to powierzchnia nie jest skierowana do nas, więc ją pomijamy.

                if ( luminance < 0){ luminance = 0;}

                int pos = xp + yp * screen_width;

                if ( pos >= 0 && pos < screen_width*screen_height){

                    if(ooz > zbuffer[pos]){ // większe ooz oznacza że pixel jest bliżej obserwatora niż to co poprzednio tam stało.
                    zbuffer[pos] = ooz;

                    int luminance_index = int(luminance*8);

                     if (luminance_index > 11){luminance_index = 11;}

                    characterbuffer[pos] = ".,-~:;=!*#$@"[luminance_index];

                    }

                }

            }
        }

        printf("\x1b[H");

        for(int i = 0 ; i < screen_width*screen_height ; i++){
            putchar(i % screen_width ? characterbuffer[i] : '\n');
            angle_A += 0.000005;
            angle_B += 0.0000025;
        }
        usleep(50000);

    }

    return 0;
}

