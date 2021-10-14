#ifndef HW6FUNCTIONS_H
#define HW6FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// GLEW _MUST_ be included first
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  Get all GL prototypes
#define GL_GLEXT_PROTOTYPES
//  Select SDL, SDL2, GLFW or GLUT
#if defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#elif defined(SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#elif defined(GLFW)
#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//  Make sure GLU and GL are included
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

// Cosine and Sine in degrees
// copying this from ex8 bc it's pretty useful
#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))

// All the convenience functions from ex8
void Fatal(const char* format , ...);
void ErrCheck(const char* where);
void Print(const char* format, ...);

// I like using rgb from 0-255
// so this is just a function that does that
void Color(double r, double g, double b);

// nice function for changing projection
// basically copied from..idk which but an example
//void Project();

// I want a nice picket fence, no reason why really
void fence();
void fence_line();
void fence_post();
void picket();

// grass stuff
void grass();
void save_grass();

// I'mma need vertex for this
void Vertex(double theta, double dis);
// vertex flat is vertex but for cylinder making
void Vertexflat(double theta, double dis);

// copied from ex13
void ball(double x, double y, double z, double r);

// this function calculates and sets normals
void doanormal(double one[3], double two[3], double three[3]);

// texture function
unsigned int LoadTexBMP(const char* file);

#endif