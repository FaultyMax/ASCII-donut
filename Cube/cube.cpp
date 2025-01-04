#include <iostream>
#include <chrono> // czas
#include <thread> // multithreading mnie zabije
#include <cmath>
#include <vector>

using namespace std;

int screenWidth = 80;
int screenHeight = 22;
float K2 = 100;
float K1 = 50;
float cubeWidth = 10;
float resolution = 0.2;

bool luminosity = true;

float rotX,rotY,rotZ,ooz;

int xP,xY; 

vector <char> bufor(screenWidth * screenHeight, ' ');
vector <int> c(screenWidth * screenHeight, 33);
vector <float> buforZ(screenWidth * screenHeight, 0);

const float pi = 3.141;

float A = 0.0;
float B = 0.0;
float C = 0.0;

void plotplane(float x,float y,float z,char ch){

    rotX = y * (sin(A) * sin(B) * cos(C) + cos(A) * sin(C)) + z * (sin(A)*sin(C)-cos(A) * sin(B) * cos(C)) + x * cos(B)*cos(C);

    rotY = y * (cos(A) * cos(C) - sin(A) * sin(B) * sin(C)) + z * (cos(A) * sin(B) * sin(C) + sin(A) * cos(C)) - x * cos(B) * sin(C);

    rotZ = -y * sin(A) * cos(B) + z * cos(A) * cos(B) + x * sin(B) + K2;

    ooz = 1 / rotZ; // one over z

    int xP = int (screenWidth / 2 + K1 * ooz * rotX * 2);

    int yP = int (screenHeight / 2 - K1 * ooz * rotY);

    int position = xP +yP * screenWidth;

    float tmpColor = 33;

    if (luminosity){
        x = 0;
        y = 0;
        z = 0;
        if(ch == '@'){z = 1;}
        else if(ch == '#'){z = -1;}
        else if(ch == '$'){y = -1;}
        else if(ch == '?'){y = 1;}
        else if(ch == '*'){x = -1;}
        else if(ch == '&'){x = 1;}

        float lumY = y * (cos(A) * cos(C) - sin(A) * sin(B) * sin(C)) + z * (cos(A) * sin(B) * sin(C) + sin(A) * cos(C)) - x * cos(B) * sin(C);

        float lumZ = -y * sin(A) * cos(B) + z * cos(A) * cos(B) + x * sin(B);

        float lum = -1 * (lumY-lumZ);

        if(lum < 0){ lum = 0; }

        int luminance_index = lum * 8;

        ch = ".,-~:;=!*#$@"[luminance_index > 0 ? luminance_index:0];

    }

    if(position >= 0 && position < screenWidth * screenHeight){
        if(ooz > buforZ[position]){
            buforZ[position] = ooz;
            bufor[position] = ch;
            c[position] = tmpColor;
        }
    }
}

int main(){

    cout << "\x1b[2J";

    while(true){

        fill(bufor.begin() , bufor.end() , ' ');
        fill(buforZ.begin() , buforZ.end() , 0);
        fill(c.begin() , c.end() , 33);

        for( float i = -cubeWidth ; i < cubeWidth ; i += resolution){
            for( float j = -cubeWidth ; j < cubeWidth ; j += resolution){

                plotplane(i,j,-cubeWidth,'@');
                plotplane(i,j,cubeWidth,'#');
                plotplane(i,cubeWidth,j,'$');
                plotplane(i,-cubeWidth,j,'?');
                plotplane(cubeWidth,i,j,'*');
                plotplane(-cubeWidth,i,j,'&');
            }
        }
        cout << "\x1b[H";
        for ( int k = 0; k < screenWidth*screenHeight; ++k){
            cout.put(k%screenWidth ? bufor[k] : '\n');
        }

        A += 0.022;
        B += 0.013;
        C += 0.002;

        this_thread :: sleep_for(chrono::milliseconds(5));

    }

    return 0;
}