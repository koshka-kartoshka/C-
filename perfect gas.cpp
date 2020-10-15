#include "TXLib.h"
#include <iostream>
#include <cmath>
#include "sphere functions.h"

int main()
{
    int number_of_particals = 100;
    int height = 800;
    int width = 900;
    int k = 1;
    int j = 1;

    struct Sphere s [number_of_particals];
    for (int i=1; i<number_of_particals; i++)
    {
        s[i].radius =6;
        s[i].red = 255;
        s[i].green = 255;
        s[i].blue = 255;
        s[i].x = 10 + (3 * s[i].radius) * j;
        s[i].y = 10 + (3 * s[i].radius) * k;
        s[i].vx = 500 * pow((-1),rand());
        s[i].vy = 500 * pow((-1),rand());
        s[i].segment = 3;
        j ++;

        if ( (3 * s[i].radius) * j >= width - 20 )
            {
               k++;
               j = 1;
            }
        if ( (3 * s[i].radius) * k >= height - 20 )
            {
                std::cout << " too much spheres" << std::endl;
                break;
            }

    }

    txCreateWindow(width, height);
    txSetFillColor(RGB(255,255,255));
    float dt = 0.01;

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
