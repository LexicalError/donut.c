#include <iostream>
#include <vector>
#include <windows.h>
#include <math.h>
#define PI 3.1415

int screenWidth = 120;
int screenHeight = 40;
const float r = 1;
const float R = 2;
const float k2 = 5;
const float k1 =  screenHeight * k2 * 3 / (8 * (r + R));
const float dTheta = 0.06;
const float dPhi = 0.01;
const float dA = 0.05;


void writeFrame(float A, float B, wchar_t *buff){
    float cosA = cos(A);
    float sinA = sin(A);
    float cosB = cos(B);
    float sinB = sin(B);

    float zBuff[screenHeight][screenWidth];
    for(int i = 0; i < screenHeight; i++)
        for(int j = 0; j < screenWidth; j++)
            zBuff[i][j] = 0;
    for(float theta = 0; theta < 2 * PI; theta += dTheta){
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);
        for(float phi = 0; phi < 2 * PI; phi += dPhi){
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            //x y z in space
            float x = cosB * cosPhi * (R + r * cosTheta) + sinB * (r * cosA * sinTheta + sinA * sinPhi * (R + r * cosTheta));
            float y = cosB * (r * cosA * sinTheta + sinA * sinPhi * (R+r * cosTheta)) - sinB * cosPhi * (R + r * cosTheta);
            float z = cosA * sinPhi * (R + r * cosTheta) - r * sinA * sinTheta;
            z += k2;
            float oneOverZ = 1 / z;

            int pX = (int)(screenWidth / 2 + k1 * oneOverZ * x);
            int pY = (int)(screenHeight / 2 + k1 * oneOverZ * y);

            float Luminance = cosB * cosTheta * cosPhi + sinB * cosA * sinTheta + sinB * sinA * cosTheta * sinPhi - cosA * cosTheta * sinPhi + sinA * sinTheta;

            if((pX >= 0 && pX < screenWidth && pY >= 0 && pY < screenHeight) && Luminance > 0 && oneOverZ > zBuff[pY][pX]){
                zBuff[pY][pX] = oneOverZ;
                //sqrt(2) * 8 < 12
                int index = Luminance * 8;
                buff[pY * screenWidth + pX] = L".,-~:;=!*#$@"[index];
            }
        }
    }

}

int main(){
    wchar_t *screen = new wchar_t[screenWidth * screenHeight];
    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(console);
    DWORD dwBytesWritten;


    bool running = true;
    while(running){
        for(float A = 0; A < 2 * PI; A += dA){
            for(int i = 0; i < screenWidth * screenHeight; i++)
                screen[i] = ' ';
            writeFrame(A, A, screen);
            screen[screenWidth * screenHeight - 1] = '\0';
            WriteConsoleOutputCharacterW(console, screen, screenWidth * screenHeight, {0, 0}, &dwBytesWritten);
        }
    }
}