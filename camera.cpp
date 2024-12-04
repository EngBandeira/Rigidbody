#include <GLFW/glfw3.h>
#include <array>
#include "render.hpp"
#include "utils.hpp"
#include "camera.hpp"
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


m4 camera2D::
 getViewMatrix () const
    {
        m4 view = m4 ({ 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f });
        view[0] = zoom;
        view[5] = zoom;

        float radians = -rotation * 3.1415f / 180.0f;
        float cosR = cos (radians);
        float sinR = sin (radians);

        view[0,0] *= cosR;
        view[0,1] = sinR;
        view[0,4] = -sinR;
        view[1,1] *= cosR;

        view[3,0] = -position.x;
        view[3,1] = -position.y;

        return view;
    }
m4 camera2D::createOrthoMatrix (float l, float r, float b, float t, float f, float n)
{
    return m4 ({ 2.0f / (r - l), 0.0f, 0.0f, 0.0f, 0.0f, 2.0f / (t - b), 0.0f,
                 0.0f, 0.0f, 0.0f, 2.0f / (f - n), 0.0f, -(-r + l) / (r - l),
                 -(t + b) / (t - b), -(f + n) / (f - n), 1.0f });
}

// class camera2D_
// {
//   public:
//     float zoom = 1.0f;
//     vec position = vec (0.0f, 0.0f);
//     float rotation = 0.0f;

//     std::array<float, 16>
//     getViewMatrix () const
//     {
//         std::array<float, 16> view
//             = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

//         view[0] = zoom;
//         view[5] = zoom;

//         float radians = -rotation * 3.1415f / 180.0f;
//         float cosR = cos (radians);
//         float sinR = sin (radians);

//         view[0] *= cosR;
//         view[1] = sinR;
//         view[4] = -sinR;
//         view[5] *= cosR;

//         view[12] = -position.x;
//         view[13] = -position.y;

//         return view;
//     }
//     std::array<float, 16>
//     createOrthoMatrix (float l, float r, float b, float t, float f, float n)
//     {
//         return { 2.0f / (r - l),
//                  0.0f,
//                  0.0f,
//                  0.0f,
//                  0.0f,
//                  2.0f / (t - b),
//                  0.0f,
//                  0.0f,
//                  0.0f,
//                  0.0f,
//                  2.0f / (f - n),
//                  0.0f,
//                  -(-r + l) / (r - l),
//                  -(t + b) / (t - b),
//                  -(f + n) / (f - n),
//                  1.0f };
//     }
//     std::array<float, 16>
//     multiplyMatrices (std::array<float, 16> &a, std::array<float, 16> &b)
//     {
//         std::array<float, 16> result = { 0.0f };
//         for (int n = 0; n < 4; n++)
//             {
//                 for (int m = 0; m < 4; m++)
//                     {
//                         for (int k = 0; k < 4; k++)
//                             {
//                                 a[n * 4 + k] * b[k * 4 + m];
//                             }
//                     }
//             }
//         return result;
//     }
// };