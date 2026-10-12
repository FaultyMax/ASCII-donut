// Let there be a donut

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <vector>

// Set clearing for different operating systems
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;


const float pi = 3.14; // We do not need much accuracy

int screen_width = 80, screen_height = 22; 

float angle_A, angle_B; // those two will rotate around X and Z axis, in that order
float A_val = 0.004, B_val = 0.002; // higher value, bigger angle

float radius = 1, origin = 2; // radius of the circle that rotates around the Y axis and distance from the origin (0,0)

const float K2 = 5; // currently the viewer is @ the origin so we need to move him back a little, this constant helps
const float K1 = screen_width*K2*3/(8*(radius+origin)); // z'  

float theta = 0,phi = 0; // these angles will create the torus
float theta_spacing = 0.09 ,phi_spacing = 0.03; // how many points are we calculating? Lesser value means more dense

int main(){

    system(CLEAR_SCREEN);

    while(true){

        // Hic sunt pixilla
        vector <char> characterbuffer(screen_width*screen_height,' ');
        // This however will be used to store the z coordinate of everything we draw
        vector <float> zbuffer(screen_width*screen_height, 0); 


        float cosA = cos(angle_A), sinA = sin(angle_A);
        float cosB = cos(angle_B), sinB = sin(angle_B);

        for(theta = 0 ; theta < 2*pi ; theta += theta_spacing){

            float cos_theta = cos(theta), sin_theta = sin(theta);

            for(phi = 0 ; phi < 2*pi ; phi += phi_spacing){

                float cos_phi = cos(phi), sin_phi = sin(phi);

                float circlex = origin + radius*cos_theta;
                float circley = radius*sin_theta;

                // obliczanie współrzędnych punktów w 3D (x y z) 

                float x = circlex * (cosB * cos_phi + sinA * sinB * sin_phi) - circley * cosA * sinB;

                float y = circlex * (cos_phi * sinB - cosB * sinA * sin_phi) + circley * cosA * cosB;

                float z = 8 + circlex * cosA * sin_phi + circley * sinA; // we add constant K2

                float ooz = 1/z; // "one over z"

                // x & y projection
                // y is negated because although it goes up in 3D space, it's not the case in 2D.
                int xp = int(screen_width/2 + K1*ooz*x); 
                int yp = int(screen_height/2 - K1*ooz*y * 0.5); 

                // throwing some light, we multiply our surface normal matrice by some chosen light, here it was (0, 1, -1)

                double luminance = (cos_phi * cos_theta * sinB) - (cosA * cos_theta * cos_phi) - (sinA * sin_theta) + (cosB * ((cosA * sin_theta) - (cos_theta * sinA * sin_phi)));

                // zmienna luminance waha się od -sqrt(2) do sqrt(2), ale jeśli jest < 0 to powierzchnia nie jest skierowana do nas, więc ją pomijamy.

                if (luminance < 0){ luminance = 0; }

                int pos = xp + yp * screen_width;

                if ( pos >= 0 && pos < screen_width*screen_height){

                    if(ooz > zbuffer[pos]){ // większe ooz oznacza że pixel jest bliżej obserwatora niż to co poprzednio tam stało.
                        zbuffer[pos] = ooz;

                        int luminance_index = int(luminance*8);

                        if (luminance_index > 11){luminance_index = 11;}

                        characterbuffer[pos] = ".,-~:;=!*#$@"[luminance_index > 0 ? luminance_index : 0];
                        //characterbuffer[pos] = ".,-~:;*=+!|#$@"[luminance_index > 0 ? luminance_index : 0];
                    }

                }

            }
        }

        // this will bring the cursor to "home" location
        cout << "\x1b[H";

        for(int p = 0 ; p < screen_width*screen_height ; p++){
            // clever usage of the conditional operator
            cout.put(p % screen_width ? characterbuffer[p] : '\n');
        }

        angle_A += A_val;
        angle_B += B_val;

        usleep(5000);

    }

    return 0;
}

