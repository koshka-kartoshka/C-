#define sphere functions
struct Sphere
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
void drawSphere(Sphere s)
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

void moveSphere(Sphere* s, float dt)
{
    s->x += s->vx * dt;
    s->y += s->vy * dt;
}

void wallCollision(Sphere* s, int height, int width)
{
    if (s->x < s->radius)
    {
        s->x += 2 * (- s->x + s->radius );
        s->vx *= -1;
    }

    if (s->x > width - s->radius)
    {
        s->x -= 2 * (- fabs(width - s->x) + s->radius);
        s->vx *= -1;
    }

    if (s->y < s->radius)
    {
        s->y += 2 * ((- s->y) + s->radius);
        s->vy *= -1;
    }

    if (s->y > height - s->radius)
    {
        s->y -= 2 * (- fabs(height - s->y) + s->radius);
        s->vy *= -1;
    }
}


bool collisionTwoSpheres(const Sphere* s1, const Sphere* s2)
{
    return (s1->radius + s2->radius >=
    sqrt(pow(s1->x - s2->x, 2) + pow(s1->y - s2->y, 2)));
}

void resolveCollision(Sphere* s1, Sphere* s2)
{
    float dx = s1->x - s2->x;
    float dy = s1->y - s2->y;

    float diagonal = sqrt(dx * dx + dy * dy);

    float cos = dx / diagonal;
    float sin = dy / diagonal;

    float vn2 = s2->vx * cos + s2->vy * sin;
    float vn1 = s1->vx * cos + s1->vy * sin;
    float vt2 = - s2->vx * sin + s2->vy * cos;
    float vt1 = - s1->vx * sin + s1->vy * cos;

    float speed = vn2;
    vn2 = vn1;
    vn1 = speed;

    s1->vx = vn1 * cos - vt1 * sin;
    s1->vy = vn1 * sin + vt1 * cos;
    s2->vx = vn2 * cos - vt2 * sin;
    s2->vy = vn2 * sin + vt2 * cos;

    if (s1->x < s2->x)
    {
        s1->x -= sqrt(2) * fabs((s1->radius - (diagonal/2))  * cos);
        s2->x += sqrt(2) * fabs((s2->radius - (diagonal/2))  * cos);
    }

    if (s2->x < s1->x)
    {
        s2->x -= sqrt(2) * fabs((s2->radius - (diagonal/2))  * cos);
        s1->x += sqrt(2) * fabs((s1->radius - (diagonal/2))  * cos);
    }

    if (s1->y < s2->y)
    {
        s1->y -= sqrt(2) * fabs((s1->radius - (diagonal/2))  * sin);
        s2->y += sqrt(2) * fabs((s2->radius - (diagonal/2))  * sin);
    }

    if (s2->y < s1->y)
    {
        s2->y -= sqrt(2) * fabs( (s2->radius - (diagonal/2))  * sin);
        s1->y += sqrt(2) * fabs( (s1->radius - (diagonal/2))  * sin);
    }
}

