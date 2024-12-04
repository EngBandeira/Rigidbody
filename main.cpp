#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "render.hpp"
#include "utils.hpp"

#define NUMBEROFPARTICLE 20

const int SPACEX = 500;
const int SPACEY = 500;
const float c = 0.2;
const int d = 10;
const float dt = 0.1;
particle particles[NUMBEROFPARTICLE];
float kkk = 1;
vec camPosition;

std::ostream &
operator<< (std::ostream &os, const vec &vec)
{
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}

void
generateParticles ()
{
    std::random_device rd;
    std::mt19937 mt1 (rd ());
    std::normal_distribution<> dist_x (SPACEX / 2.0, SPACEX / 8.0);
    std::normal_distribution<> dist_y (SPACEY / 2.0, SPACEY / 8.0);
    for (int i = 0; i < NUMBEROFPARTICLE; i++)
        {
            particles[i].position
                = vec (std::clamp (dist_x (mt1), 0.0, (double)SPACEX),
                       std::clamp (dist_y (mt1), 0.0, (double)SPACEY));
            particles[i].mass = 1;
            particles[i].velocity = vec (0, 0);
        }
}
void
renderParticles ()
{

    for (int i = 0; i < NUMBEROFPARTICLE; i++)
        {
            glBegin (GL_LINE_LOOP);

            vec p = particles[i].position*kkk;
            p = p - camPosition;
            p = vec ((2 * p.x - SPACEX) / SPACEX, (2 * p.y - SPACEY) / SPACEY)
                * kkk;
            std::cout << p << '\n';
            glVertex2f (p.x + c, p.y + c);
            glVertex2f (p.x + c, p.y - c);
            glVertex2f (p.x - c, p.y - c);
            glVertex2f (p.x - c, p.y + c);
            glEnd ();
        }
}

void
atualizar (MyWindow *a)
{

    renderParticles ();
}
void
keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods)
{
    float abbb = 0.1;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        {
            camPosition = camPosition + vec (0, d);
        }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
        {
            camPosition = camPosition + vec (0, -d);
        }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
        {
            camPosition = camPosition + vec (d, 0);
        }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
        {
            camPosition = camPosition + vec (-d, 0);
        }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        {
                        kkk-= abbb ;

        }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        {
            kkk+= abbb ;
        }
}
int
main ()
{
    camPosition = vec (0, 0);
    generateParticles ();
    MyWindow w = MyWindow (&atualizar, &keyCallback);
    return 0;
}
