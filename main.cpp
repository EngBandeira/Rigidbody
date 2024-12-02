#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

const int SPACEX = 500;
const int SPACEY = 500;
const double c = 0.002;
const double GRAVITYCONSTANT = 0.001;
const double dt = 0.1;
const double EPSILON = 10;
#define NUMBEROFPARTICLE 1000

class vec
{
  public:
    double x, y;

    vec (double x_, double y_)
    {
        x = x_;
        y = y_;
    }
    vec () {}
    vec
    operator= (vec v)
    {
        x = v.x;
        y = v.y;
        return v;
    }
    vec
    operator+ (vec v)
    {
        return vec (x + v.x, y + v.y);
    }
    vec
    operator- (vec v)
    {
        return vec (x - v.x, y - v.y);
    }
    vec
    operator* (double r)
    {
        return vec (x * r, y * r);
    }
    vec
    operator/ (double r)
    {
        return vec (x / r, y / r);
    }

    double
    module ()
    {
        return sqrt (x * x + y * y);
    }
    vec
    unify ()
    {
        return *this / this->module ();
    }
};

std::ostream &
operator<< (std::ostream &os, const vec &vec)
{
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}

class particle
{
  public:
    vec velocity;
    double mass;

    vec position;
    particle () {}
    particle (vec position_, vec velocity_, double mass_)
    {
        position = position_;
        velocity = velocity_;
        mass = mass_;
    }
    void
    newVel (double time, vec acc)
    {
        velocity = velocity + acc * time;
    }
    void
    NewPos (double time)
    {
        position = position + velocity * time;
        // if(position.x > 500)
        //   velocity.x = -1 * velocity.x;
        // if(position.x < 0)
        //   velocity.x = -1 * velocity.x;
        //   if(position.y > 500)
        //   velocity.y = -1 * velocity.y;
        // if(position.y < 0)
        //   velocity.y = -1 * velocity.y;
    }
};
vec
accBetweenParticles (particle p1, particle p2)
{ /// aceleracão da particula 1 devida a particula 2
    // F=MmGunity/r^2
    vec r = p2.position - p1.position;
    return r * p2.mass * GRAVITYCONSTANT / sqrt(std::pow(std::pow(r.module(), 2)+EPSILON * EPSILON, 3.0));
}

void
renderParticle (particle p, GLFWwindow *w)
{
    vec normalizedPosition = vec ((2 * p.position.x - SPACEX) / SPACEX,
                                  (2 * p.position.y - SPACEY) / SPACEY);
    glBegin (GL_LINE_LOOP);
    // glVertex2d(0,0);
    //     glVertex2d(.5,0);
    //             glVertex2d(0,0.5);

    //     glVertex2d(.5,.5);

    glVertex2d (normalizedPosition.x - c, normalizedPosition.y - c);
    glVertex2d (normalizedPosition.x + c, normalizedPosition.y - c);
    glVertex2d (normalizedPosition.x + c, normalizedPosition.y + c);
    glVertex2d (normalizedPosition.x - c, normalizedPosition.y + c);

    glEnd ();
}

particle particles[];
std::vector<particle> generateParticles(int n, double width, double height) {
    std::vector<particle> particles;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Distribuições
    std::normal_distribution<> dist_x(width / 2.0, width / 8.0);  
    std::normal_distribution<> dist_y(height / 2.0, height / 8.0); 
    std::uniform_real_distribution<> dist_mass(1.0, 1.0);        
    std::uniform_real_distribution<> dist_vel(0.0, 0.0);

    for (int i = 0; i < n; ++i) {
        double x = std::clamp(dist_x(gen), 0.0, width);
        double y = std::clamp(dist_y(gen), 0.0, height);
        vec position(x, y);
        vec velocity(0.0, 0.0);
        double mass = dist_mass(gen);
        particles.emplace_back(position, velocity, mass);
    }
    
    return particles;
}
// std::vector<particle> particles
int
main ()
{


    if (!glfwInit ())
        {
            std::cout << "FODEU : GLFW NÃO ABRIU" << '\n';
            exit (EXIT_FAILURE);
        }
    GLFWwindow *window
        = glfwCreateWindow (1920, 1080, "oaaa", glfwGetPrimaryMonitor (), NULL);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_RESIZABLE, GL_FALSE);
    if (!window)
        {
            std::cout << "FODEU : A JANELA NÃO ABRIU" << '\n';
            glfwTerminate ();
            exit (EXIT_FAILURE);
        }

    glfwMakeContextCurrent (window);
    glfwSwapInterval (0);
    while (!glfwWindowShouldClose (window))
        {
            glfwPollEvents ();
            glClear (GL_COLOR_BUFFER_BIT);
            int width, height;
            glfwGetFramebufferSize (window, &width, &height);
            // const float ratio = width / (float)height;
            glViewport (0, 0, width, height);

            for (int i = 0; i < NUMBEROFPARTICLE; i++)
                {
                    vec accOfParticleI = vec (0, 0);
                    for (int j = 0; j < NUMBEROFPARTICLE; j++)
                        {
                            if (i == j)
                                continue;
                            accOfParticleI = accOfParticleI
                                             + accBetweenParticles (
                                                 particles[i], particles[j]);
                        }
                    particles[i].NewPos (dt);
                    particles[i].newVel (dt, accOfParticleI);
                    renderParticle (particles[i], window);
                }

            glEnd ();
            glfwSwapBuffers (window);
        }
    glfwDestroyWindow (window);
    glfwTerminate ();
    exit (EXIT_SUCCESS);
}
