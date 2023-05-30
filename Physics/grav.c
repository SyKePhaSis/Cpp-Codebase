#include "include/raylib.h"
#include <math.h>

#define G pow(10, 0)

typedef struct
{
    float posx;
    float posy;
    float ux;
    float uy;
    float mass;
    int radius;
    float ax;
    float ay;
} planet;

float getDistance(planet p1, planet p2);
float getForce(planet p1, planet p2);
float getAngle(planet p1, planet p2);
float getAccX(planet p, float f, float theta);
float getAccY(planet p, float f, float theta);
Vector2 getAngleSign(planet pm, planet ps);
void updatePlanets(planet *p1, planet *p2);
void updateAcceleration(planet *p1, planet *p2);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    planet p1 = {400, screenHeight / 2, 0, 0, 5000, 10};
    planet p2 = {750, 400, 0, 0, 80, 2};

    InitWindow(screenWidth, screenHeight, "Gravity Simulator");

    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        updateAcceleration(&p1, &p2);
        updatePlanets(&p1, &p2);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("Distance: %fM", getDistance(p1, p2)), 20, 20, 20, LIGHTGRAY);
        DrawText(TextFormat("Force: %fN", getForce(p1, p2)), 20, 40, 20, LIGHTGRAY);
        DrawText(TextFormat("Angle: %f rad", getAngle(p1, p2)), 20, 60, 20, LIGHTGRAY);
        DrawText("Gravity Simulator", 300, 20, 20, LIGHTGRAY);

        DrawCircle(p1.posx, p1.posy, p1.radius, LIGHTGRAY);
        DrawCircle(p2.posx, p2.posy, p2.radius, GRAY);
        DrawLine(p1.posx, p1.posy, p2.posx, p2.posy, RED);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void updateAcceleration(planet *p1, planet *p2)
{
    float f = getForce(*p1, *p2);
    float theta = getAngle(*p1, *p2);

    Vector2 sign1 = getAngleSign(*p1, *p2);
    Vector2 sign2 = getAngleSign(*p2, *p1);

    p1->ax = getAccX(*p1, f, theta) * sign1.x;
    p1->ay = getAccY(*p1, f, theta) * sign1.y;

    p2->ax = getAccX(*p2, f, theta) * sign2.x;
    p2->ay = getAccY(*p2, f, theta) * sign2.y;
}

void updatePlanets(planet *p1, planet *p2)
{
    p1->posx = p1->ux + p1->posx;
    p1->posy = p1->uy + p1->posy;
    p1->ux = p1->ux + p1->ax;
    p1->uy = p1->uy + p1->ay;

    p2->posx = p2->ux + p2->posx;
    p2->posy = p2->uy + p2->posy;
    p2->ux = p2->ux + p2->ax;
    p2->uy = p2->uy + p2->ay;
}

float getDistance(planet p1, planet p2)
{
    return sqrt(pow(p1.posx - p2.posx, 2) + pow(p1.posy - p2.posy, 2));
}

float getForce(planet p1, planet p2)
{
    float d = getDistance(p1, p2);
    float f = G * (p1.mass * p2.mass) / pow(d, 2);
    return f;
}

float getAccX(planet p, float f, float theta)
{
    float a = f / p.mass * sin(theta);
    return a;
}

float getAccY(planet p, float f, float theta)
{
    float a = f / p.mass * cos(theta);
    return a;
}

float getAngle(planet p1, planet p2)
{
    float d = getDistance(p1, p2);
    float sin = abs(p1.posx - p2.posx) / d;
    float theta = asin(sin);
    return theta;
}

Vector2 getAngleSign(planet pm, planet ps)
{
    Vector2 sign;
    sign.x = (ps.posx - pm.posx) / abs(ps.posx - pm.posx);
    sign.y = (ps.posy - pm.posy) / abs(ps.posy - pm.posy);
    return sign;
}