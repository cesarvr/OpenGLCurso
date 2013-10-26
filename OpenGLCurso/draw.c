//
//  draw.c
//  OpenGLCurso
//
//  Created by Cesar Luis Valdez on 25/10/13.
//  Copyright (c) 2013 Cesar Luis Valdez. All rights reserved.
//


#include <stdio.h>
#include "draw.h"
#include "glfw3.h"
#include "graphic_engine.h"
#include "matrixUtil.h"
#include <assert.h>
#include "tga.h"



#define PATH_TEXTURA    "/Users/cesarvr/Desktop/Desarrollo/Curso/OpenGLCurso/TGA_IMG/boxg4.tga"

void crear_buffers();
void draw();
void init();
void destroy();

GLuint getParametro(char *param);
GLuint getUniform(char * param);

GLuint vbo;
GLuint indice;

GLuint _shd_posicion;
GLuint _shd_color;
GLuint _shd_textura;
GLuint _shd_mvp;
GLuint _shd_text;

GLuint textura_id;
GLfloat modelView[16];
GLfloat projection[16];
GLfloat mvp[16];
GLfloat mv[16];
GLfloat look[16] = {0.59999996, -0.4115966,  0.68599439, 0.0f,
                    0.0f,        0.85749292, 0.51449579, 0.0f,
                   -0.79999995, -0.30869746, 0.51449579, 0.0f,
                    0.0f      ,  0.0f,       -5.8309526, 1.0f};





int cantidad_vertices = 0;
int tamano_total = 0;

static const int POSICION_DATA_TAMANO = 3;
static const int COLOR_DATA_TAMANO = 3;
static const int TEXTURA_DATA_TAMANO = 2;


typedef struct _Vertex{
    float Position[3];
    float Color[4];
    float TexCoord[2]; // New
} Vertex;


/*
    Inicializamos las variables GLSL
    
    creamos los objetos buffers para OpenGL.
 
 
 */



void inciarlizar_motor_render(float m_viewWidth, float m_viewHeight){

    glClearColor(0.1f, 0.2f, 0.0f, 1.0f);
    
    glUseProgram(_program);
    
    
    _shd_posicion = getParametro( "position");
    _shd_color    = getParametro( "color");
    _shd_textura  = getParametro("textura_cord");
    _shd_mvp      = getUniform( "MVP");
    _shd_text     = getUniform("textura");
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    
    
    
    mtxLoadPerspective(projection, 45, (float)m_viewWidth / (float)m_viewHeight,1.0,10000);
    mtxLoadIdentity(modelView);
    
	mtxTranslateApply(modelView, 0.0f, 0.0f, 0.0f);
	mtxMultiply(mvp, projection, look);

    
    crear_buffers();
    
    long witdh = 0.0f, height = 0.0f;
    textura_id = load_texture_TGA(PATH_TEXTURA, &witdh, &height, GL_REPEAT, GL_REPEAT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textura_id);
    glUseProgram(0);
    
}


void crear_buffers(){

#define TEX_COORD_MAX   1.0f
#define TEX_COORD_MIN   0.0f
    
    
    float vertx1 =  1.5;
    float vertx2 = -0.5;
    float verty1 =  1.5;
    float verty2 = -1.5;
    
    float vertz1 =  1.0;
    float vertz2 = -1.0;
    
    
    float vertices[]= {
        
        //0-3
        vertx1, verty1, vertz1, 0.0f, 0.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MIN, //0
        vertx2, verty1, vertz1, 0.1f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MIN, //1
        vertx1, verty2, vertz1, 0.0f, 0.1f, 0.1f, TEX_COORD_MIN, TEX_COORD_MAX, //2
        vertx2, verty2, vertz1, 0.0f, 0.1f, 0.1f, TEX_COORD_MAX, TEX_COORD_MAX, //3
        
        //4-7
        vertx1, verty1, vertz2, 0.0f, 1.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MIN, //4
        vertx2, verty1, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MIN, //5
        vertx1, verty2, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MAX, //6
        vertx2, verty2, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MAX, //7
        
        //8-11
        vertx1, verty1, vertz1, 0.0f, 1.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MIN, //8
        vertx1, verty2, vertz1, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MIN, //9
        vertx1, verty1, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MAX, //10
        vertx1, verty2, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MAX, //11
        
        //12-15
        vertx2, verty1, vertz1, 0.0f, 1.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MIN, //12
        vertx2, verty2, vertz1, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MIN, //13
        vertx2, verty1, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MAX, //14
        vertx2, verty2, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MAX, //15
        
        //16-19
        vertx1, verty1, vertz1, 0.0f, 1.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MIN, //12
        vertx2, verty1, vertz1, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MIN, //13
        vertx1, verty1, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MAX, //14
        vertx2, verty1, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MAX, //15
        
        
        //20-23
        vertx1, verty2, vertz1, 0.0f, 1.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MIN, //12
        vertx2, verty2, vertz1, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MIN, //13
        vertx1, verty2, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MIN, TEX_COORD_MAX, //14
        vertx2, verty2, vertz2, 0.0f, 0.0f, 0.0f, TEX_COORD_MAX, TEX_COORD_MAX, //15
        

    };
      //               FRENTE       DETRAS          DERECHA             IZQUIERDA           ARRIBA                ABAJO
     short indices[]={0,1,2,3,3,  4,4,5,6,7,7,  8,8,9,10,11,11,    12,12,13,14,15,15, 16,16,17,18,19,19,  20,20,21,22,23,23};
    
    cantidad_vertices = sizeof(indices) / sizeof(unsigned short);
    
    //definimos un pack de float para que sea leido secuencialmente por OpenGL.
    //                      3                   3                   2
    
    tamano_total = (POSICION_DATA_TAMANO + COLOR_DATA_TAMANO + TEXTURA_DATA_TAMANO) * sizeof(float);
    
    
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    glGenBuffers(1, &indice);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    
}

float rot = 1.0f;


void draw() {
    
    
    rot+=0.1f;
   
   
    mtxRotateApply(modelView, 1.0f, 0.1f, 0.1f, 0.0f);

    mtxMultiply(mv, look, modelView);
	mtxMultiply(mvp, projection, mv);

    
    glUseProgram(_program);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniformMatrix4fv(_shd_mvp, 1, GL_FALSE, mvp);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    
    //                    SHADER VALUE          3              TIPO     NORMALIZADO?       PACK        LOCALIZACION
    glVertexAttribPointer(_shd_posicion, POSICION_DATA_TAMANO, GL_FLOAT, GL_FALSE,     tamano_total,       0);
    glEnableVertexAttribArray(_shd_posicion);
    
    
   
    //                    SHADER VALUE          3         TIPO    NORMALIZADO?             PACK                         LOCALIZACION
    glVertexAttribPointer(_shd_color, COLOR_DATA_TAMANO, GL_FLOAT, GL_FALSE,          tamano_total, (GLvoid*) (sizeof(float) * POSICION_DATA_TAMANO));
    glEnableVertexAttribArray(_shd_color);
    
    
    
     //                    SHADER VALUE          3             TIPO    NORMALIZADO?   PACK                         LOCALIZACION
    glVertexAttribPointer(_shd_textura, TEXTURA_DATA_TAMANO, GL_FLOAT, GL_FALSE, tamano_total,   (GLvoid*) (sizeof(float) * (POSICION_DATA_TAMANO + COLOR_DATA_TAMANO)));
    glEnableVertexAttribArray(_shd_textura);
    
    //glDrawArrays(GL_TRIANGLES, 0, cantidad_vertices );
    
    
    
    //Usamos indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice);
    
    glDrawElements(GL_TRIANGLE_STRIP, cantidad_vertices, GL_UNSIGNED_SHORT, 0);

    
    
    glUseProgram(0);
}

GLuint getParametro(char *param){
    //NSLog(@"SHADER parametros: %@",param);
    
    GLuint temp =  glGetAttribLocation(_program, param);
    assert(temp != 0xFFFFFFFF);
    
    return temp;
}

GLuint getUniform(char * param){
    //NSLog(@"Uniform parametros: %@",param);
    GLuint temp =  glGetUniformLocation(_program, param);
    
    
    assert(temp != 0xFFFFFFFF);
    
    return temp;
    
}



void destroy(){

    glDeleteBuffers(1, &vbo);
}




