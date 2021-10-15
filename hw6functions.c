#include "hw6functions.h"
// a bunch of includes
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif
#include <time.h>

// some global variables I need
// ground level
double gr = -3;
double dm = 50.0; // size of world
// if we have initialized grass or not
int grassmade = 0;

int emission  =   0;  // Emission intensity (%)
float shny   =   1;  // Shininess (value)
int inc       =  10;  // Ball increment

// so, glut draws everytime and grass
// is random, but I don't want it to be random
// so first make all the grass and save it
// so the grass is consitent with the scene
struct grass_pos {
   double x;
   double y;
   int rotation;
};
int grasscount = 900;
int grasscount2 = 900;
// won't let you modify at scope so
// remember to make this same as grasscount
struct grass_pos grasses[900];
struct grass_pos grasses2[900];
void save_grass() {
   int i;
   for(i = 0; i < grasscount; i++) {
      struct grass_pos pos;
      pos.x = (rand()%((int)dm*20)-dm/.1)/10.0;
      pos.y = (rand()%((int)dm*20)-dm/.1)/10.0;
      pos.rotation = rand()%120;

      grasses[i] = pos;
   }
   for(i = 0; i < grasscount; i++) {
      struct grass_pos pos;
      pos.x = (rand()%((int)dm*20)-dm/.1)/10.0;
      pos.y = (rand()%((int)dm*20)-dm/.1)/10.0;
      pos.rotation = rand()%120;

      grasses2[i] = pos;
   }
}

// draw some GRAAAASSSSSSS
void grass() {
   if(!grassmade) {
      save_grass();
      grassmade = 1;
   }
   int i;
   // idk why but I don't think this is working...
   // it's enabled everywhere it should be?
   // IG the grass is too close together so bits
   // aren't accurate enough
   // oh hehe, it's because arrows were going opposite
   // direction, so z was opposite direction I thought it
   // was, oops lol. that makes a lot of sense
   glEnable(GL_DEPTH_TEST);
   for(i = 0; i < grasscount; i++) {
      // first, the blade, then, the blade
      glPushMatrix();
      float green[]   = {1.0,1.0,1.0,1.0};
      float Emission[] = {0.0,0.0,0.0,1.0};
      glMaterialf(GL_FRONT,GL_SHININESS,shny);
      glMaterialfv(GL_FRONT,GL_SPECULAR,green);
      glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
      // draw all the grasses
      glTranslatef(grasses[i].x, gr, grasses[i].y);
      glRotatef(grasses[i].rotation, 0, 1, 0);
      // funny effect, wigglin grass :)
      glRotatef(rand()%30/5.0, 0, 0, 1);
      glRotatef(rand()%30/5.0, 1, 0, 0);

      //glScalef(5, 5, 5);
      // now just draw some grass
      Color(234, 85, 16);

      // I want each bit of grass to have some randomness
      // so the texture gets offset a bit by its x,y placement
      double texx = grasses[i].x;
      double texy = grasses[i].y;

      // they are so small the texture doesn't really come out
      // but whatever, you can kinda see it on some of them

      glBegin(GL_QUADS);
      glNormal3f(0, +1, -.25);
      glTexCoord2f(0+texx,0+texy); glVertex3f(-.1, 0, 0);
      glTexCoord2f(1+texx,0+texy); glVertex3f(.1, 0, 0);
      glTexCoord2f(1+texx,1+texy); glVertex3f(.1, .5, 0);
      glTexCoord2f(0+texx,1+texy); glVertex3f(-.1, .5, 0);
      glEnd();

      //glRotatef(1, 1, 0, 0);
      glBegin(GL_TRIANGLES);
      glTexCoord2f(1+texx,.1+texy); glVertex3f(.1, .5, 0);
      glTexCoord2f(.5+texx,2+texy); glVertex3f(0, 1, .1);
      glTexCoord2f(0+texx,1+texy); glVertex3f(-.1, .5, 0);
      glEnd();

      glColor3f(0, 0, 0);
      glLineWidth(1);
      glBegin(GL_LINE_STRIP);
      glVertex3f(-.1, 0, 0);
      glVertex3f(-.1, .5, 0);
      glVertex3f(0, 1, .1);
      glVertex3f(.1, .5, 0);
      glVertex3f(.1, 0, 0);
      glEnd();

      glPopMatrix();
   }
   for(i = 0; i < grasscount; i++) {
      // first, the blade, then, the blade
      glPushMatrix();
      float green[]   = {0.0,1.0,0.0,1.0};
      float Emission[] = {0.0,0.0,0.01*emission,1.0};
      glMaterialf(GL_FRONT,GL_SHININESS,shny);
      glMaterialfv(GL_FRONT,GL_SPECULAR,green);
      glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
      // draw all the grasses
      glTranslatef(grasses2[i].x, gr, grasses2[i].y);
      glRotatef(grasses2[i].rotation, 0, 1, 0);
      // funny effect, wigglin grass :)
      glRotatef(rand()%30/5.0, 0, 0, 1);
      glRotatef(rand()%30/5.0, 1, 0, 0);

      //glScalef(5, 5, 5);
      // now just draw some grass
      Color(85, 234, 16);

      glBegin(GL_QUADS);
      glNormal3f(0, +1, -.25);
      glVertex3f(-.1, 0, 0);
      glVertex3f(.1, 0, 0);
      glVertex3f(.1, .5, 0);
      glVertex3f(-.1, .5, 0);
      glEnd();

      //glRotatef(1, 1, 0, 0);
      glBegin(GL_TRIANGLES);
      glVertex3f(.1, .5, 0);
      glVertex3f(0, 1, .1);
      glVertex3f(-.1, .5, 0);
      glEnd();

      glColor3f(0, 0, 0);
      glLineWidth(1);
      glBegin(GL_LINE_STRIP);
      glVertex3f(-.1, 0, 0);
      glVertex3f(-.1, .5, 0);
      glVertex3f(0, 1, .1);
      glVertex3f(.1, .5, 0);
      glVertex3f(.1, 0, 0);
      glEnd();

      glPopMatrix();
   }
}

// um, outer rim thingy...idk what these are called
// wow, this is getting really long
// I'mma move it to the bottom
// there was definitely a better way to do this
void picket() {
   glPushMatrix();
   glEnable(GL_CULL_FACE);

   float white[]   = {1.0,1.0,1.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shny/5);
   glMaterialfv(GL_FRONT,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   glTranslatef(0, gr, 0);
   glColor3f(1, 1, 1);
   glBegin(GL_QUADS);

   // front of the fence
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(9.5, 1, -9.5);
   glTexCoord2f(0,1); glVertex3f(9.5, 1.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 1.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(9.5, 1, 9.5);

   glTexCoord2f(0,0); glVertex3f(9.5, 2, -9.5);
   glTexCoord2f(0,1); glVertex3f(9.5, 2.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 2.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(9.5, 2, 9.5);
   
   glNormal3f(0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(-9.5, 2, -9.5);
   glTexCoord2f(0,1); glVertex3f(-9.5, 2.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 2.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(9.5, 2, -9.5);

   glTexCoord2f(0,0); glVertex3f(-9.5, 1, -9.5);
   glTexCoord2f(0,1); glVertex3f(-9.5, 1.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 1.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(9.5, 1, -9.5);

   glNormal3f(0, 0, +1);
   glTexCoord2f(0,0); glVertex3f(9.5, 2, 9.5);
   glTexCoord2f(0,1); glVertex3f(9.5, 2.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 2.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(-9.5, 2, 9.5);

   glTexCoord2f(0,0); glVertex3f(9.5, 1, 9.5);
   glTexCoord2f(0,1); glVertex3f(9.5, 1.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 1.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(-9.5, 1, 9.5);

   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-9.5, 2, 9.5);
   glTexCoord2f(0,1); glVertex3f(-9.5, 2.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 2.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(-9.5, 2, -9.5);

   glTexCoord2f(0,0); glVertex3f(-9.5, 1, 9.5);
   glTexCoord2f(0,1); glVertex3f(-9.5, 1.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 1.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(-9.5, 1, -9.5);

   // back of the fence

   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-9, 1, -9);
   glTexCoord2f(0,1); glVertex3f(-9, 1.5, -9);
   glTexCoord2f(1,1); glVertex3f(-9, 1.5, 9);
   glTexCoord2f(1,0); glVertex3f(-9, 1, 9);

   glTexCoord2f(0,0); glVertex3f(-9, 2, -9);
   glTexCoord2f(0,1); glVertex3f(-9, 2.5, -9);
   glTexCoord2f(1,1); glVertex3f(-9, 2.5, 9);
   glTexCoord2f(1,0); glVertex3f(-9, 2, 9);

   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(9, 1, 9);
   glTexCoord2f(0,1); glVertex3f(9, 1.5, 9);
   glTexCoord2f(1,1); glVertex3f(9, 1.5, -9);
   glTexCoord2f(1,0); glVertex3f(9, 1, -9);
   
   glTexCoord2f(0,0); glVertex3f(9, 2, 9);
   glTexCoord2f(0,1); glVertex3f(9, 2.5, 9);
   glTexCoord2f(1,1); glVertex3f(9, 2.5, -9);
   glTexCoord2f(1,0); glVertex3f(9, 2, -9);
   
   glNormal3f(0, 0, +1);
   glTexCoord2f(0,0); glVertex3f(9, 2, -9);
   glTexCoord2f(0,1); glVertex3f(9, 2.5, -9);
   glTexCoord2f(1,1); glVertex3f(-9, 2.5, -9);
   glTexCoord2f(1,0); glVertex3f(-9, 2, -9);
   
   glTexCoord2f(0,0); glVertex3f(9, 1, -9);
   glTexCoord2f(0,1); glVertex3f(9, 1.5, -9);
   glTexCoord2f(1,1); glVertex3f(-9, 1.5, -9);
   glTexCoord2f(1,0); glVertex3f(-9, 1, -9);
   
   glNormal3f(0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(-9, 2, 9);
   glTexCoord2f(0,1); glVertex3f(-9, 2.5, 9);
   glTexCoord2f(1,1); glVertex3f(9, 2.5, 9);
   glTexCoord2f(1,0); glVertex3f(9, 2, 9);
   
   glTexCoord2f(0,0); glVertex3f(-9, 1, 9);
   glTexCoord2f(0,1); glVertex3f(-9, 1.5, 9);
   glTexCoord2f(1,1); glVertex3f(9, 1.5, 9);
   glTexCoord2f(1,0); glVertex3f(9, 1, 9);

   // top of the fence

   glNormal3f(0, 1, 0);
   glTexCoord2f(0,0); glVertex3f(-9, 1.5, 9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 1.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 1.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(9, 1.5, 9);

   glTexCoord2f(0,0); glVertex3f(-9, 2.5, 9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 2.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 2.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(9, 2.5, 9);

   glTexCoord2f(0,0); glVertex3f(-9, 1.5, -9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 1.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 1.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 1.5, 9);

   glTexCoord2f(0,0); glVertex3f(-9, 2.5, -9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 2.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 2.5, 9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 2.5, 9);

   glTexCoord2f(0,0); glVertex3f(9, 1.5, -9);
   glTexCoord2f(0,1); glVertex3f(9.5, 1.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 1.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 1.5, -9);

   glTexCoord2f(0,0); glVertex3f(9, 2.5, -9);
   glTexCoord2f(0,1); glVertex3f(9.5, 2.5, -9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 2.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 2.5, -9);

   glTexCoord2f(0,0); glVertex3f(9, 2.5, 9);
   glTexCoord2f(0,1); glVertex3f(9.5, 2.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 2.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(9, 2.5, -9);

   glTexCoord2f(0,0); glVertex3f(9, 1.5, 9);
   glTexCoord2f(0,1); glVertex3f(9.5, 1.5, 9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 1.5, -9.5);
   glTexCoord2f(1,0); glVertex3f(9, 1.5, -9);

   // bottom of the fence

   glNormal3f(0, -1, 0);
   glTexCoord2f(0,0); glVertex3f(9, 1, 9);
   glTexCoord2f(0,1); glVertex3f(9.5, 1, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 1, 9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 1, 9);
   
   glTexCoord2f(0,0); glVertex3f(9, 2, 9);
   glTexCoord2f(0,1); glVertex3f(9.5, 2, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 2, 9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 2, 9);
   
   glTexCoord2f(0,0); glVertex3f(-9, 1, 9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 1, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 1, -9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 1, -9);
   
   glTexCoord2f(0,0); glVertex3f(-9, 2, 9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 2, 9.5);
   glTexCoord2f(1,1); glVertex3f(-9.5, 2, -9.5);
   glTexCoord2f(1,0); glVertex3f(-9, 2, -9);
   
   glTexCoord2f(0,0); glVertex3f(-9, 1, -9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 1, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 1, -9.5);
   glTexCoord2f(1,0); glVertex3f(9, 1, -9);
   
   glTexCoord2f(0,0); glVertex3f(-9, 2, -9);
   glTexCoord2f(0,1); glVertex3f(-9.5, 2, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 2, -9.5);
   glTexCoord2f(1,0); glVertex3f(9, 2, -9);
   
   glTexCoord2f(0,0); glVertex3f(9, 2, -9);
   glTexCoord2f(0,1); glVertex3f(9.5, 2, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 2, 9.5);
   glTexCoord2f(1,0); glVertex3f(9, 2, 9);
   
   glTexCoord2f(0,0); glVertex3f(9, 1, -9);
   glTexCoord2f(0,1); glVertex3f(9.5, 1, -9.5);
   glTexCoord2f(1,1); glVertex3f(9.5, 1, 9.5);
   glTexCoord2f(1,0); glVertex3f(9, 1, 9);

   glEnd();

   glLineWidth(3);
   glColor3f(0, 0, 0);
   glBegin(GL_LINE_STRIP);

   glVertex3f(9.5, 2.5, 9.5);
   glVertex3f(9.5, 2.5, -9.5);
   glVertex3f(-9.5, 2.5, -9.5);
   glVertex3f(-9.5, 2.5, 9.5);
   glVertex3f(9.5, 2.5, 9.5);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9, 2.5, 9);
   glVertex3f(9, 2.5, -9);
   glVertex3f(-9, 2.5, -9);
   glVertex3f(-9, 2.5, 9);
   glVertex3f(9, 2.5, 9);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9.5, 1.5, 9.5);
   glVertex3f(9.5, 1.5, -9.5);
   glVertex3f(-9.5, 1.5, -9.5);
   glVertex3f(-9.5, 1.5, 9.5);
   glVertex3f(9.5, 1.5, 9.5);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9, 1.5, 9);
   glVertex3f(9, 1.5, -9);
   glVertex3f(-9, 1.5, -9);
   glVertex3f(-9, 1.5, 9);
   glVertex3f(9, 1.5, 9);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9.5, 2, 9.5);
   glVertex3f(9.5, 2, -9.5);
   glVertex3f(-9.5, 2, -9.5);
   glVertex3f(-9.5, 2, 9.5);
   glVertex3f(9.5, 2, 9.5);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9, 2, 9);
   glVertex3f(9, 2, -9);
   glVertex3f(-9, 2, -9);
   glVertex3f(-9, 2, 9);
   glVertex3f(9, 2, 9);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9.5, 1, 9.5);
   glVertex3f(9.5, 1, -9.5);
   glVertex3f(-9.5, 1, -9.5);
   glVertex3f(-9.5, 1, 9.5);
   glVertex3f(9.5, 1, 9.5);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(9, 1, 9);
   glVertex3f(9, 1, -9);
   glVertex3f(-9, 1, -9);
   glVertex3f(-9, 1, 9);
   glVertex3f(9, 1, 9);

   glEnd();
   glBegin(GL_LINES);

   glVertex3f(9.5, 2.5, 9.5);
   glVertex3f(9.5, 2, 9.5);

   glVertex3f(9.5, 1.5, 9.5);
   glVertex3f(9.5, 1, 9.5);

   glVertex3f(-9.5, 2.5, 9.5);
   glVertex3f(-9.5, 2, 9.5);

   glVertex3f(-9.5, 1.5, 9.5);
   glVertex3f(-9.5, 1, 9.5);

   glVertex3f(-9.5, 2.5, -9.5);
   glVertex3f(-9.5, 2, -9.5);

   glVertex3f(-9.5, 1.5, -9.5);
   glVertex3f(-9.5, 1, -9.5);

   glVertex3f(9.5, 2.5, -9.5);
   glVertex3f(9.5, 2, -9.5);

   glVertex3f(9.5, 1.5, -9.5);
   glVertex3f(9.5, 1, -9.5);

   glEnd();

   glPopMatrix();
}

// draw a nice fence
void fence() {
   glPushMatrix();
   glEnable(GL_CULL_FACE);

   glTranslatef(10, gr, 9);
   fence_line();
   glTranslatef(18, 0, -18);
   fence_line();
   glTranslatef(-1, 0, -1);
   glRotatef(90, 0, 1, 0);
   fence_line();
   glTranslatef(18, 0, 18);
   fence_line();
   /*
   glTranslatef(dim, ground, dim-1);
   fence_line();
   glTranslatef(dim*2-2, 0, -dim*2+2);
   fence_line();
   glTranslatef(-1, 0, -1);
   glRotatef(90, 0, 1, 0);
   fence_line();
   glTranslatef(dim*2-2, 0, dim*2-2);
   fence_line();*/

   glDisable(GL_CULL_FACE);
   glPopMatrix();
}

void fence_line() {
   int i;
   for(i = 0; i < 9; i++) {
      glTranslatef(-2, 0, 0);
      fence_post();
   }
}

// so I could, go around, figuring out normals
// /where even all these things are
// honestly too many objects for me to even
// figure out what is where.
// or, I could, just calculate surface normals 
// using math, which sounds much easier
// linear algebra is great
// actually, trees are generated randomly so normals aren't even consitent
void doanormal(double one[3], double two[3], double three[3]) {
   // this takes in 3 points then
   // sets the vector to point out
   // first, make a vector
   // this is one of our edges
   // using 0,1,2 is confusing
   int x = 0, y = 1, z = 2;
   double firstvector[3];
   firstvector[x] = one[x] - two[x];
   firstvector[y] = one[y] - two[y];
   firstvector[z] = one[z] - two[z];
   // then, make a vector
   // another of our edges
   // did three - two so that both vectors point
   // away from the point two
   // but not sure it actually matters
   double secondvector[3];
   secondvector[x] = three[x] - two[x];
   secondvector[y] = three[y] - two[y];
   secondvector[z] = three[z] - two[z];
   // then do a cross product
   double normal[3];
   normal[x] = firstvector[y]*secondvector[z] - firstvector[z]*secondvector[y];
   normal[y] = firstvector[z]*secondvector[x] - firstvector[x]*secondvector[z];
   normal[z] = firstvector[x]*secondvector[y] - firstvector[y]*secondvector[x];
   // then, set normal
   // mmm, math makes things so much easier
   glNormal3f(normal[x], normal[y], normal[z]);
}

void fence_post() {
   glColor3f(1, 1, 1);
   glBegin(GL_QUADS);

   // nice thing about having working face culling,
   // you can throw your three points into your normal 
   // setter and it'll just work since
   // your vectors are all clockwise/counterclockwise
   // ie: the normal will point same way for all of them

   // bottom
   glNormal3f(0, -1, 0);
   glTexCoord2f(0,0); glVertex3f(-.5, 0, .25);
   glTexCoord2f(0,1); glVertex3f(-.5, 0, -.25);
   glTexCoord2f(1,1); glVertex3f(.5, 0, -.25);
   glTexCoord2f(0,1); glVertex3f(.5, 0, .25);

   // sides
   glNormal3f(0, 0, +1);
   glTexCoord2f(0,0); glVertex3f(-.5, 0, .25);
   glTexCoord2f(.5,0); glVertex3f(.5, 0, .25);
   glTexCoord2f(.5,.75); glVertex3f(.5, 3, .25);
   glTexCoord2f(0,.75); glVertex3f(-.5, 3, .25);

   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(.5, 0, .25);
   glTexCoord2f(.5,0); glVertex3f(.5, 0, -.25);
   glTexCoord2f(.5,.75); glVertex3f(.5, 3, -.25);
   glTexCoord2f(0,.75); glVertex3f(.5, 3, .25);

   glNormal3f(0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(.5, 0, -.25);
   glTexCoord2f(.5,0); glVertex3f(-.5, 0, -.25);
   glTexCoord2f(.5,.75); glVertex3f(-.5, 3, -.25);
   glTexCoord2f(0,.75); glVertex3f(.5, 3, -.25);

   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-.5, 0, -.25);
   glTexCoord2f(.5,0); glVertex3f(-.5, 0, .25);
   glTexCoord2f(.5,.75); glVertex3f(-.5, 3, .25);
   glTexCoord2f(0,.75); glVertex3f(-.5, 3, -.25);

   // top pointer part
   glNormal3f(-.5, +.5, 0);
   glTexCoord2f(0,.75); glVertex3f(-.5, 3, -.25);
   glTexCoord2f(.5,.75); glVertex3f(-.5, 3, .25);
   glTexCoord2f(.5,1); glVertex3f(0, 4, .25);
   glTexCoord2f(0,1); glVertex3f(0, 4, -.25);

   // top pointer part
   glNormal3f(+.5, +.5, 0);
   glTexCoord2f(0,.75); glVertex3f(0, 4, -.25);
   glTexCoord2f(.5,.75); glVertex3f(0, 4, .25);
   glTexCoord2f(.5,1); glVertex3f(.5, 3, .25);
   glTexCoord2f(0,1); glVertex3f(.5, 3, -.25);

   glEnd();

   glBegin(GL_TRIANGLES);

   // fill in the top pointer part

   glNormal3f(0, 0, +1);
   glTexCoord2f(1,.75); glVertex3f(-.5, 3, .25);
   glTexCoord2f(0,.75); glVertex3f(.5, 3, .25);
   glTexCoord2f(.5,1); glVertex3f(0, 4, .25);

   glNormal3f(0, 0, -1);
   glTexCoord2f(1,.75); glVertex3f(0, 4, -.25);
   glTexCoord2f(0,.75); glVertex3f(.5, 3, -.25);
   glTexCoord2f(.5,1); glVertex3f(-.5, 3, -.25);

   glEnd();

   glColor3f(0, 0, 0);
   glLineWidth(3);
   glBegin(GL_LINE_STRIP);

   glVertex3f(.5, 0, .25);
   glVertex3f(.5, 3, .25);
   glVertex3f(0, 4, .25);
   glVertex3f(-.5, 3, .25);
   glVertex3f(-.5, 0, .25);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(.5, 0, -.25);
   glVertex3f(.5, 3, -.25);
   glVertex3f(0, 4, -.25);
   glVertex3f(-.5, 3, -.25);
   glVertex3f(-.5, 0, -.25);

   glEnd();
   glBegin(GL_LINE_STRIP);

   glVertex3f(-.5, 0, .25);
   glVertex3f(.5, 0, .25);
   glVertex3f(.5, 0, -.25);
   glVertex3f(-.5, 0, -.25);

   glEnd();
   glBegin(GL_LINES);

   glVertex3f(.5, 3, .25);
   glVertex3f(.5, 3, -.25);

   glVertex3f(-.5, 3, .25);
   glVertex3f(-.5, 3, -.25);

   glVertex3f(0, 4, .25);
   glVertex3f(0, 4, -.25);

   glEnd();
}

// I forgot the openGL method and this is easier
// than finding it
void Color(double r, double g, double b) {
   glColor3f(r/255, g/255, b/255);
}

/*
 *  Check for OpenGL errors
 */
void ErrCheck(const char* where) {
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...) {
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...) {
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void Vertex(double thet, double dis) {
   glNormal3d(Sin(thet)*Cos(dis), Sin(dis), Cos(thet)*Cos(dis));
   glTexCoord2f(Sin(thet)*Cos(dis), Cos(thet)*Cos(dis));
   glVertex3f(Sin(thet)*Cos(dis), Sin(dis), Cos(thet)*Cos(dis));
}

void Vertexflat(double thet, double height) {
   //glTexCoord2f(Sin(thet), height/5);
   glVertex3f(Sin(thet), height, Cos(thet));
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0,0.0,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

// this is obviously stolen from ex15

//
//  Load texture from BMP file
//

//
//  Reverse n bytes
//
static void Reverse(void* x,const int n)
{
   int k;
   char* ch = (char*)x;
   for (k=0;k<n/2;k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n-1-k];
      ch[n-1-k] = tmp;
   }
}

//
//  Load texture from BMP file
//
unsigned int LoadTexBMP(const char* file)
{
   unsigned int   texture;    // Texture name
   FILE*          f;          // File pointer
   unsigned short magic;      // Image magic
   unsigned int   dx,dy,size; // Image dimensions
   unsigned short nbp,bpp;    // Planes and bits per pixel
   unsigned char* image;      // Image data
   unsigned int   off;        // Image offset
   unsigned int   k;          // Counter
   unsigned int   max;        // Maximum texture dimensions

   //  Open file
   f = fopen(file,"rb");
   if (!f) Fatal("Cannot open file %s\n",file);
   //  Check image magic
   if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic from %s\n",file);
   if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP in %s\n",file);
   //  Read header
   if (fseek(f,8,SEEK_CUR) || fread(&off,4,1,f)!=1 ||
       fseek(f,4,SEEK_CUR) || fread(&dx,4,1,f)!=1 || fread(&dy,4,1,f)!=1 ||
       fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
     Fatal("Cannot read header from %s\n",file);
   //  Reverse bytes on big endian hardware (detected by backwards magic)
   if (magic==0x424D)
   {
      Reverse(&off,4);
      Reverse(&dx,4);
      Reverse(&dy,4);
      Reverse(&nbp,2);
      Reverse(&bpp,2);
      Reverse(&k,4);
   }
   //  Check image parameters
   glGetIntegerv(GL_MAX_TEXTURE_SIZE,(int*)&max);
   //printf("%d\n", max);
   if (dx<1 || dx>max) Fatal("%s image width %d out of range 1-%d\n",file,dx,max);
   if (dy<1 || dy>max) Fatal("%s image height %d out of range 1-%d\n",file,dy,max);
   if (nbp!=1)  Fatal("%s bit planes is not 1: %d\n",file,nbp);
   if (bpp!=24) Fatal("%s bits per pixel is not 24: %d\n",file,bpp);
   if (k!=0)    Fatal("%s compressed files not supported\n",file);
#ifndef GL_VERSION_2_0
   //  OpenGL 2.0 lifts the restriction that texture size must be a power of two
   for (k=1;k<dx;k*=2);
   if (k!=dx) Fatal("%s image width not a power of two: %d\n",file,dx);
   for (k=1;k<dy;k*=2);
   if (k!=dy) Fatal("%s image height not a power of two: %d\n",file,dy);
#endif

   //  Allocate image memory
   size = 3*dx*dy;
   image = (unsigned char*) malloc(size);
   if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
   //  Seek to and read image
   if (fseek(f,off,SEEK_SET) || fread(image,size,1,f)!=1) Fatal("Error reading data from image %s\n",file);
   fclose(f);
   //  Reverse colors (BGR -> RGB)
   for (k=0;k<size;k+=3)
   {
      unsigned char temp = image[k];
      image[k]   = image[k+2];
      image[k+2] = temp;
   }

   //  Sanity check
   ErrCheck("LoadTexBMP");
   //  Generate 2D texture
   glGenTextures(1,&texture);
   glBindTexture(GL_TEXTURE_2D,texture);
   //  Copy image
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
   if (glGetError()) Fatal("Error in glTexImage2D %s %dx%d\n",file,dx,dy);
   //  Scale linearly when image size doesn't match
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

   //  Free image memory
   free(image);
   //  Return texture name
   return texture;
}