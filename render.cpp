#include "render.hpp"
#include "camera.cpp"

MyWindow::  MyWindow(void(*callback_fun)(MyWindow*), void(*key_callback)(GLFWwindow*,int,int,int,int)){
    if (!glfwInit ())
        {
            std::cout << "FODEU : GLFW NÃO ABRIU" << '\n';
            exit (EXIT_FAILURE);
        }
    window= glfwCreateWindow (500, 500, "oaaa", NULL, NULL);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_RESIZABLE, GL_TRUE);
    // glClearColor(0.2, 0.3, 0.3, 1.0);
    if (!window)
        {
            std::cout << "FODEU : A JANELA NÃO ABRIU" << '\n';
            glfwTerminate ();
            exit (EXIT_FAILURE);
        }

    glfwMakeContextCurrent (window);
    glfwSetKeyCallback(window,key_callback);
    while (!glfwWindowShouldClose (window))
        {
            glClear (GL_COLOR_BUFFER_BIT);

            callback_fun(this);

            glfwSwapBuffers (window);
            glfwPollEvents ();
        }
    // glfwSwapInterval (0);
  }
  MyWindow::~MyWindow(){
    glfwDestroyWindow (window);
    glfwTerminate ();
    exit (EXIT_SUCCESS);
  }
