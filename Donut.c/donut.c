#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define PI 3.1415
const int screenWidth = 50;
const int screenHeight = 29;
const float r = 1;
const float R = 2;
const float k2 = 5;
const float k1 =  screenHeight * k2 * 3 / (8 * (r + R));
const float dTheta = 0.06;
const float dPhi = 0.01;
const float dA = 0.05;

void writeFrame(float A, float B, char buff[screenHeight][screenWidth]){
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
                buff[pY][pX] = ".,-~:;=!*#$@"[index];
            }
        }
    }

}

int main(){
    char output[screenHeight][screenWidth];
    while(1){
        for(float A = 0; A < 2 * PI; A += dA){
            for(int i = 0; i < screenHeight; i++)
                for(int j = 0; j < screenWidth; j++)
                    output[i][j] = ' ';
            writeFrame(A, A, output);
            system("cls");
            for(int i = 0; i < screenHeight; i++){
                for(int j = 0; j < screenWidth; j++)
                    printf("%c", output[i][j]);
                printf("\n");        
            }
            // usleep(10000);
        }
    }
}
/*
x = (R + rcos(theta))
y = (rsin(theta))
z = (0)

rotate around y:
-> (cos(phi)(R + rcos(theta)), rsin(theta), sin(phi)(R+rcos(theta)))

animate:
rotate around x & z by A and B:
-> 
x = cos(B)cos(phi)(R + rcos(theta)) + sin(B)[rcos(A)sin(theta) + sin(A)sin(phi)(R + rcos(theta))]
y = cos(B)[rcos(A)sin(theta) + sin(A)sin(phi)(R+rcos(theta))] - sin(B)cos(phi)(R+rcos(theta))
z = cos(A)sin(phi)(R+rcos(theta))-rsin(A)sin(theta)

normal vectors:
(cos(theta), sin(theta), 0)
rotate with phi, A, B:
->
x = cos(B)cos(theta)cos(phi) + sin(B)[cos(A)sin(theta) + sin(A)cos(theta)sin(phi)]
y = cos(B)[cos(A)sin(theta) + sin(A)cos(theta)sin(phi)] - sin(B)cos(theta)cos(phi)
z = cos(A)cos(theta)sin(phi) - sin(A)sin(theta)
light direction:
(1, 0, -1)
-> luminace value:
cos(B)cos(theta)cos(phi) + sin(B)cos(A)sin(theta) + sin(B)sin(A)cos(theta)sin(phi) - cos(A)cos(theta)sin(phi) + sin(A)sin(theta)

*/