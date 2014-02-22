//
//  main.m
//  OpenGLCurso
//
//  Created by Cesar Luis Valdez on 25/10/13.
//  Copyright (c) 2013 Cesar Luis Valdez. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "glfw3.h"
#include "graphic_engine.h"
#include "draw.h"


#define SCREEN_ANCHO 800
#define SCREEN_ALTO 600

#define PATH_VERTEX     "/Users/cesarvr/Desktop/Desarrollo/Curso/OpenGLCurso/Shaders/prueba.vsh"
#define PATH_FRAGMENT   "/Users/cesarvr/Desktop/Desarrollo/Curso/OpenGLCurso/Shaders/prueba.fsh"


void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


int main(int argc, const char * argv[])
{
    @autoreleasepool {
        

        if (!glfwInit())
        {
            printf("Error iniciando GLFW");
            exit(EXIT_FAILURE);
        }
        
        
        //manejador de errores;
        
       /*
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);1
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        */
        
        
        glfwSetErrorCallback(error_callback);
        
        GLFWwindow* window = glfwCreateWindow(SCREEN_ANCHO, SCREEN_ALTO, "Taller", NULL, NULL);
        
        
        if (!window)
        {
            
            printf("error al crear ventana.");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        
        // Make the window's context current
        glfwMakeContextCurrent(window);
        
        //  printf("\n version: %s \n", glfwGetVersionString());
        NSLog(@"\n OpenGL [render]:  %s ", glGetString(GL_RENDERER));
        printf("\n OpenGL [version]: %s ", glGetString(GL_VERSION));
        printf("\n OpenGL [vendor]: %s \n",glGetString(GL_VENDOR));
        
        
        
        // Cargar shaders
        cargarShaders(PATH_VERTEX, PATH_FRAGMENT);
        
        
       // GLKMatrix4 matCam =  GLKMatrix4MakeLookAt(4.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        
        
        // Iniciar
        inciarlizar_motor_render(SCREEN_ANCHO, SCREEN_ALTO);
        
        
        
        while (!glfwWindowShouldClose(window))
        {
            update();
            draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
        
        destroy();
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);

        
        
    } // remover
    return 0;
}

