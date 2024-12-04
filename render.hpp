#ifndef RENDER
#define RENDER
#include <GLFW/glfw3.h>
#include <iostream>

class MyWindow
{
  public:
  GLFWwindow *window;
  MyWindow(void(*callback_fun)(MyWindow*), void(*key_callback)(GLFWwindow*,int,int,int,int));
  ~MyWindow();
};
#endif

