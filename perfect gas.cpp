#include "TXLib.h"
#include <iostream>
#include <cmath>
#include "spherefunctions.h"

int main()
{
    int number_of_particals = 150;
    int height = 800;
    int width = 900;

    struct Sphere s [number_of_particals];
    for (int i=1; i<number_of_particals; i++)
    {
        s[i].radius = 9;
        s[i].red = 255;
        s[i].green = 255;
        s[i].blue = 255;
        s[i].x = 10 +  pow((-1),i) * ((i*1000) % (width-10));
        s[i].y = 10 + i * 5 * pow((-1),i);
        s[i].vx = 7 * pow((-1),rand());
        s[i].vy = - 7 * pow((-1),rand());
        s[i].segment = 10;
    }

    txCreateWindow(width, height);
    txSetFillColor(RGB(40,40,40));
    float dt = 0.7;

    while(true)
    {
        txBegin();
        txClear();

        for (int i=1; i<number_of_particals; i++)
        {
            drawSphere(s[i]);
        }

        txEnd();

        for (int i=1; i < number_of_particals; i++)
        {
            wallCollision(&(s[i]), height, width);
        }


        for (int i=1; i < number_of_particals; i++)
        {
           for (int j=1; j < number_of_particals; j++)
            {
                if ((i != j) and (collisionTwoSpheres(&(s[i]), &(s[j]))))
                {
                    resolveCollision(&(s[i]), &(s[j]));
                }
            }
         }


        for (int i=1; i<number_of_particals; i++)
        {
            moveSphere(&(s[i]), dt);
        }

    }
    return 0;
}

/*
Sphere particles [10];
 for (int i=0; i<10, i++)
    drawSphere(particle[i])
for (int i=0; i<10, i++)
    moveSphere(particle[i])
    particle!=0
    assert(particle);
    */
