#include "TXLib.h"
#include <cmath>
#include "spherefunctions.h"

int main()
{
    std::cout << "Press space to start" << std::endl;
    std::cout << "Press space to exit" << std::endl;
    std::cout << "Arrow control left, up, right and down" << std::endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            std::cout << "Catch up with the blue sphere and run away from the red. You have 10 attempts. ";
            break;
        }
    }

    int height = 800;
    int width = 900;
    txCreateWindow(width, height);
    txSetFillColor(RGB(40,40,40));

    float acceleration = 4;
    float friction = 0.995;
    float dt = 0.1;
    int score = 0;

    Sphere s1 = {70, 255, 255, 255, 400, 400,  5., -6.0, 100};
    Sphere s2 = {70,  67, 110, 255, 600, 300,  4.,   5., 100};
    Sphere s3 = {70, 255,   0,   0, 200, 500, -5.,    6, 100};
    Sphere s4 = {70,   0, 255, 127, 200, 300,  3., -3.0, 100};
    Sphere s5 = {70, 255,   0, 255, 100, 200,  3., -3.0, 100};

    while(true)
    {
        txBegin();

        txClear();

        drawSphere(s1);
        wallCollision(&s1, height, width);

        drawSphere(s2);
        wallCollision(&s2, height, width);

        drawSphere(s3);
        wallCollision(&s3, height, width);

        drawSphere(s4);
        wallCollision(&s4, height, width);

        drawSphere(s5);
        wallCollision(&s5, height, width);

        txEnd();

        if (GetAsyncKeyState(VK_UP))
            s1.vy -= acceleration;
        if (GetAsyncKeyState(VK_LEFT))
            s1.vx -= acceleration;
        if (GetAsyncKeyState(VK_RIGHT))
            s1.vx += acceleration;
        if (GetAsyncKeyState(VK_DOWN))
            s1.vy += acceleration;


        if (collisionTwoSpheres(&s1, &s2))
        {
            resolveCollision(&s1, &s2);
            score--;
        }


        if (collisionTwoSpheres(&s1, &s3))
        {
            resolveCollision(&s1, &s3);
            score++;
        }


        if (collisionTwoSpheres(&s3, &s2))
        {
            resolveCollision(&s3, &s2);
        }


        if (collisionTwoSpheres(&s4, &s1))
        {
            resolveCollision(&s4, &s1);
        }


        if (collisionTwoSpheres(&s4, &s2))
        {
            resolveCollision(&s4, &s2);
        }


        if (collisionTwoSpheres(&s4, &s3))
        {
            resolveCollision(&s4, &s3);
        }


        if (collisionTwoSpheres(&s4, &s5))
        {
            resolveCollision(&s4, &s5);
        }


        if (collisionTwoSpheres(&s5, &s1))
        {
            resolveCollision(&s5, &s1);
        }


        if (collisionTwoSpheres(&s5, &s2))
        {
            resolveCollision(&s5, &s2);
        }


        if (collisionTwoSpheres(&s5, &s3))
        {
            resolveCollision(&s5, &s3);
        }


        moveSphere(&s1, dt);
        moveSphere(&s2, dt);
        moveSphere(&s3, dt);
        moveSphere(&s4, dt);
        moveSphere(&s5, dt);


        //race
        s2.vx += (s2.x - s1.x) * 0.005;
        s2.vy += (s2.y - s1.y) * 0.005;
        s3.vx += (s1.x - s3.x) * 0.005;
        s3.vy += (s1.y - s3.y) * 0.005;


        s1.vx *= 0.97;
        s1.vy *= 0.97;
        s2.vx *= friction;
        s2.vy *= friction;
        s3.vx *= friction;
        s3.vy *= friction;
        s4.vx *= friction;
        s4.vy *= friction;
        s5.vx *= friction;
        s5.vy *= friction;


        if (score == 100000)
        {
            std::cout << " You lose " << std::endl;
            txSetFillColor(RGB(150,7,7));
            txClear();
            break;
        }

        if (score == -100000)
        {
            std::cout << " You won " << std::endl;
            txSetFillColor(RGB(7,150,7));
            txClear();
            break;
        }

            if (GetAsyncKeyState(VK_SPACE))
            break;
        }

    return 0;
}

/*
Sphere particles [100];

 for (int i=0; i<100, i++)
    drawSphere(particle[i])


for (int i=0; i<100, i++)
    moveSphere(particle[i])

    particle!=0
    assert(particle);
    */
