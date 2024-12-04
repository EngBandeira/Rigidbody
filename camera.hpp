#pragma once

class camera2D
{
  public:
    float zoom = 1.0f;
    vec position = vec (0.0f, 0.0f);
    float rotation = 0.0f;
    m4 camera2D::createOrthoMatrix (float l, float r, float b, float t,
                                    float f, float n);
    m4 camera2D::getViewMatrix () const;
};
