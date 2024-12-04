#ifndef UTILS
#define UTILS
#include <cmath>
#include <iostream>
class vec
{
  public:
    float x, y;

    vec (float x_, float y_)
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
    operator* (float r)
    {
        return vec (x * r, y * r);
    }
    vec
    operator/ (float r)
    {
        return vec (x / r, y / r);
    }

    float
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

template <std::size_t x, std::size_t y> class matrix
{
  public:
    std::array<float, x * y> data;
    float &
    operator[] (std::size_t x_, std::size_t y_)
    {
        // static_assert (x_ = < x and y_ = < y);
        return data[x * x_ + y_];
    }
    float &
    operator[] (std::size_t x_)
    {
        // static_assert (x_ = < x *y);
        return data[x_];
    }
    matrix<x, y> operator* (matrix<x, y> a);
    matrix () {}
    matrix (std::array<float, x * y> data_) { data = data_; }
};

typedef matrix<4, 4> m4;



class particle
{
  public:
    vec velocity;
    float mass;

    vec position;
    particle () {}
    particle (vec position_, vec velocity_, float mass_)
    {
        position = position_;
        velocity = velocity_;
        mass = mass_;
    }
    void
    newVel (float time, vec acc)
    {
        velocity = velocity + acc * time;
    }
    void
    NewPos (float time)
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

#endif