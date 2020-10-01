#include "TXLib.h"
#include <cmath>

struct sphere
{
    int radius;
    int red;
    int green;
    int blue;
    float x;
    float y;
    float vx;
    float vy;
    int segment;
};

void drawSphere(sphere s)
{
    COLORREF color = txGetFillColor();

    for (int i = 0; i < s.segment; i++)
    {
        txSetFillColor(RGB(i * s.red / s.segment, i * s.green / s.segment, i * s.blue / s.segment));
        txSetColor(RGB(i * s.red / s.segment, i * s.green / s.segment, i * s.blue / s.segment));
        txCircle(s.x + i * 35 * s.radius / 100 / s.segment, s.y - i * 30 * s.radius / 100 / s.segment, s.radius - s.radius * i / s.segment);
    }

    txSetFillColor(color);
}

void moveSphere(sphere* s, float dt)
{
    (*s).x += (*s).vx * dt;
    (*s).y += (*s).vy * dt;
}

void wallCollision(sphere* s, int height, int width)
{
    if ((*s).x < (*s).radius)
    {
        (*s).x += - (*s).x + (*s).radius;
        (*s).vx *= -1;
    }

    if ((*s).x > width - (*s).radius)
    {
        (*s).x -= - fabs(width - (*s).x) + (*s).radius;
        (*s).vx *= -1;
    }

    if ((*s).y < (*s).radius)
    {
        (*s).y += - (*s).y + (*s).radius;
        (*s).vy *= -1;
    }

    if ((*s).y > height - (*s).radius)
    {
        (*s).y -= - fabs(height - (*s).y) + (*s).radius;
        (*s).vy *= -1;
    }
}


bool CollisionTwoSpheres(const sphere* s1, const sphere* s2)
{
    return ((*s1).radius + (*s2).radius >=
    sqrt(pow((*s1).x - (*s2).x, 2) + pow((*s1).y - (*s2).y, 2)));
}

void resolveCollision(sphere* s1, sphere* s2)
{
    float dx = (*s1).x - (*s2).x;
    float dy = (*s1).y - (*s2).y;

    float diagonal = sqrt(dx * dx + dy * dy);

    float cos = dx / diagonal;
    float sin = dy / diagonal;

    float vn2 = (*s2).vx * cos + (*s2).vy * sin;
    float vn1 = (*s1).vx * cos + (*s1).vy * sin;
    float vt2 = - (*s2).vx * sin + (*s2).vy * cos;
    float vt1 = - (*s1).vx * sin + (*s1).vy * cos;

    float speed = vn2;
    vn2 = vn1;
    vn1 = speed;

    (*s1).vx = vn1 * cos - vt1 * sin;
    (*s1).vy = vn1 * sin + vt1 * cos;
    (*s2).vx = vn2 * cos - vt2 * sin;
    (*s2).vy = vn2 * sin + vt2 * cos;

    if ((*s1).x <= (*s2).x)
    {
        (*s1).x -= fabs(((*s1).radius - (diagonal/2))  * cos);
        (*s2).x += fabs(((*s2).radius - (diagonal/2))  * cos);
    }

    if ((*s2).x < (*s1).x)
    {
        (*s2).x -= fabs(((*s2).radius - (diagonal/2))  * cos);
        (*s1).x += fabs(((*s1).radius - (diagonal/2))  * cos);
    }

    if ((*s1).y <= (*s2).y)
    {
        (*s1).y -= fabs(((*s1).radius - (diagonal/2))  * sin);
        (*s2).y += fabs(((*s2).radius - (diagonal/2))  * sin);
    }

    if ((*s2).y < (*s1).y)
    {
        (*s2).y -= fabs( ((*s2).radius - (diagonal/2))  * sin);
        (*s1).y += fabs( ((*s1).radius - (diagonal/2))  * sin);
    }
}

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


    sphere s1 = {70, 255, 255, 255, 400, 400,  5., -6.0, 100};
    sphere s2 = {70,  67, 110, 255, 600, 300,  4.,   5., 100};
    sphere s3 = {70, 255,   0,   0, 200, 500, -5.,    6, 100};
    sphere s4 = {70,   0, 255, 127, 200, 300,  3., -3.0, 100};
    sphere s5 = {70, 255,   0, 255, 100, 200,  3., -3.0, 100};



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


        if (CollisionTwoSpheres(&s1, &s2))
        {
            resolveCollision(&s1, &s2);
            score--;
        }


        if (CollisionTwoSpheres(&s1, &s3))
        {
            resolveCollision(&s1, &s3);
            score++;
        }


        if (CollisionTwoSpheres(&s3, &s2))
        {
            resolveCollision(&s3, &s2);
        }


        if (CollisionTwoSpheres(&s4, &s1))
        {
            resolveCollision(&s4, &s1);
        }


        if (CollisionTwoSpheres(&s4, &s2))
        {
            resolveCollision(&s4, &s2);
        }


        if (CollisionTwoSpheres(&s4, &s3))
        {
            resolveCollision(&s4, &s3);
        }


        if (CollisionTwoSpheres(&s4, &s5))
        {
            resolveCollision(&s4, &s5);
        }


        if (CollisionTwoSpheres(&s5, &s1))
        {
            resolveCollision(&s5, &s1);
        }


        if (CollisionTwoSpheres(&s5, &s2))
        {
            resolveCollision(&s5, &s2);
        }


        if (CollisionTwoSpheres(&s5, &s3))
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
