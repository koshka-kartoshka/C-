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
{   COLORREF color = txGetFillColor();
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

void inWindowCheck(sphere* s, int height, int width)
{
   if ((*s).x < (*s).radius)
    {
        (*s).x += 2;
        (*s).vx += 20;
    }

    if ((*s).x > width - (*s).radius)
    {
        (*s).x -= 2;
        (*s).vx -= 20;
    }

    if ((*s).y < (*s).radius)
    {
        (*s).y += 2;
        (*s).vy += 20;
    }

    if ((*s).y > height - (*s).radius)
    {
        (*s).y -= 2;
        (*s).y -= 20;
    }
}
void wallCollision(sphere* s, int height, int width)
{
    if ((*s).x <= (*s).radius or (*s).x >= width - (*s).radius)
    {
        (*s).vx *= -1,2;
    }

    if ((*s).y <= (*s).radius or (*s).y >= height - (*s).radius)
    {
        (*s).vy *= -1,2;
    }
}

bool CollisionTwoSpheres(sphere* s1, sphere* s2)
{

    return ((*s1).radius + (*s2).radius >= sqrt(pow((*s1).x - (*s2).x, 2) + pow((*s1).y - (*s2).y, 2)));

}

void resolveCollision(sphere* s1, sphere* s2)
{
    float dx = (*s1).x - (*s2).x;
    float dy = (*s1).y - (*s2).y;

    float diagonal = sqrt(dx * dx + dy * dy);

    float sin = dx / diagonal;
    float cosin = dy / diagonal;

    float vn2 = (*s2).vx * sin + (*s2).vy * cosin + 10;
    float vn1 = (*s1).vx * sin + (*s1).vy * cosin + 10;
    float vt2 = - (*s2).vx * cosin + (*s2).vy * sin + 10;
    float vt1 = - (*s1).vx * cosin + (*s1).vy * sin + 10;

    float speed = vn2;
    vn2 = vn1;
    vn1 = speed;

    (*s1).vx = vn1 * sin - vt1 * cosin;
    (*s1).vy = vn1 * cosin + vt1 * sin;
    (*s2).vx = vn2 * sin - vt2 * cosin;
    (*s2).vy = vn2 * cosin + vt2 * sin;
}

int main()
{
    std::cout << "Press space to start" << std::endl;
    std::cout << "Press space to exit" << std::endl;
    std::cout << "Arrow control left, up, right and down" << std::endl;
    while (true)
    {
        if (GetAsyncKeyState(VK_SPACE)){std::cout << "Catch up with the blue sphere and run away from the red. You have 10 attempts. "; break;}
    }

    int height = 800;
    int width = 900;
    txCreateWindow(width, height);
    txSetFillColor(RGB(40,40,40));


    float acceleration = 4;
    float friction = 0.995;
    float dt = 0.1;
    int win = 0;


    sphere s1 = {70, 255, 255, 255, 400, 400, 5., -6.0, 100};

    sphere s2 = {70, 67, 110,  255, 600, 300, 4., 5., 100};

    sphere s3 = {70, 255, 0, 0, 200, 500, -5., 6, 100};

    sphere s4 = {70, 0, 255, 127, 200, 300, 3., -3.0, 100};

    sphere s5 = {70, 255, 0, 255, 100, 200, 3., -3.0, 100};



    while(true)
    {
        txBegin();

        txClear();

        drawSphere(s1);
        wallCollision(&s1, height, width);
        inWindowCheck(&s1, height, width);

        drawSphere(s2);
        wallCollision(&s2, height, width);
        inWindowCheck(&s2, height, width);

        drawSphere(s3);
        wallCollision(&s3, height, width);
        inWindowCheck(&s3, height, width);

        drawSphere(s4);
        wallCollision(&s4, height, width);
        inWindowCheck(&s4, height, width);

        drawSphere(s5);
        wallCollision(&s5, height, width);
        inWindowCheck(&s5, height, width);


        if (GetAsyncKeyState(VK_UP)) s1.vy -= acceleration;
        if (GetAsyncKeyState(VK_LEFT)) s1.vx -= acceleration;
        if (GetAsyncKeyState(VK_RIGHT)) s1.vx += acceleration;
        if (GetAsyncKeyState(VK_DOWN)) s1.vy += acceleration;


        if (CollisionTwoSpheres(&s1, &s2))
        {
            resolveCollision(&s1, &s2);
            win -- ;
        }


        if (CollisionTwoSpheres(&s1, &s3))
        {
            resolveCollision(&s1, &s3);
            win ++;
        }


        if (CollisionTwoSpheres(&s3, &s2))
        {
            resolveCollision(&s3, &s2);
        }

        //not in game spheres number 4 and 5 check collision
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



        txEnd();

            if (win == 100)
        {
            { std::cout << " You Lose " << std::endl ;}
                txSetFillColor(RGB(7,150,7));
                txClear();
                break;
        }

            if (win == -100)
        {
            { std::cout << " You Win " << std::endl ;}
                txSetFillColor(RGB(150,7,7));
                txClear();
                break;
        }

            if (GetAsyncKeyState(VK_SPACE))
            break;
        }

    return 0;
}

