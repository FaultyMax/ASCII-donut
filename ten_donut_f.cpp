// własny kod donuta bo cudzy mnie pokonał

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

// wszelkie zmienne

const float pi = 3.14159;

int screen_width , screen_height; // szerokość i wysokość ekranu terminala.

float angle_A , angle_B; // dwa kąty wokól których będziemy obracać. Kąt A obraca wokół osi Z a B wokół osi X

float K1; // z'

float K2; // dystans od donuta ( początkowo obserwator znajduje się na początku układu)

float radius,origin; // R1 i R2

float theta,phi; // dwa kąty których obrót będzie tworzyć torus

float theta_spacing = 0.09 ,phi_spacing = 0.03; // ilość rozmieszczenia punktów torusu

int main(){

    radius = 1;
    origin = 2;
    K2 = 5;

    screen_width = 80;
    screen_height = 22;

    K1 = (screen_width * K2 * 3)/(8*(radius+origin));

    int screen_area = screen_width*screen_height;

    system(CLEAR_SCREEN); // czyszczenie ekranu

    while(true){

        char characterbuffer[screen_area];
        float zbuffer[screen_area]; 

        memset(characterbuffer,32,screen_area); // 32 to ' '
        memset(zbuffer,0,screen_area);

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

                int xp = (int) (screen_width/2 + K1*ooz*x); 
                int yp = (int) (screen_height/2 - K1*ooz*y); // w 3D y idzie w "góre", ale nie w 2D więc y jest zanegowana

                // efekt oświetlenia

                float luminance = cos_phi * cos_theta * sinB - cosA * cos_theta * cos_phi - sinA * sin_theta + cosB * (cosA * sin_theta - cos_theta * sinA * sin_phi);

                // zmienna luminance wacha się od -sqrt(2) do sqrt(2), ale jeśli jest < 0 to powierzchnia nie jest skierowana do nas, więc ją pomijamy.

                if ( luminance > 0){

                    if(ooz > zbuffer[xp*yp]){ // większe ooz oznacza że pixel jest bliżej obserwatora niż to co poprzednio tam stało.
                    zbuffer[xp*yp] = ooz;

                    int luminance_index = luminance*8;

                    characterbuffer[xp*yp] = ".,-~:;=!*#$@"[luminance_index];

                    }

                }

            }
        }

        printf("\x1b[H");
        for(int i = 0 ; i < screen_area+1 ; i++){
            putchar(characterbuffer[i]);
        }

    }

    return 0;
}

