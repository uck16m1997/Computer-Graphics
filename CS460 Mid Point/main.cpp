//
//  main.cpp
//  Computer Graphics
//
//  Created by Umut Cem Kayaalti on 2/5/20.
//  Copyright © 2020 Umut Cem Kayaalti. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <OpenGL/gl.h>

#include <OpenGl/glu.h>

#include <GLUT/glut.h>
/*
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}*/
int size = 1000;
float fc(int x,int y,int r){
    float fy = y-0.5;
    return x*x + fy*fy - r*r;
}
void midpointCircle(int xc,int yc,int r){
    int x=0;
    int y=r;
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f((float)(x+xc)/size,(float)(y+yc)/size);
    glEnd();
    x++;
    float p= fc(x,y,r);
    int sign=1;
    if((xc>0 && yc <0)||(xc<0 && yc>0)){ sign=-1;}
        
        
    
    while(x<y){
        
        if(p<0){
            p = p+2*x+3;
        }
        else{
            p = p+ 2*x - 2*y +5;
            y=y-1;
        }
        x++;
        
    

       
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x+xc)/size,(float)(y+yc)/size);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(y+yc)/size*sign,(float)(x+xc)/size*sign);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x*-1+xc)/size,(float)(y+yc)/size);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(y*-1+yc)/size*sign,(float)(x+xc)/size*sign);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x+xc)/size,(float)(y*-1+yc)/size);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(y+yc)/size*sign,(float)(x*-1+xc)/size*sign);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x*-1+xc)/size,(float)(y*-1+yc)/size);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(y*-1+yc)/size*sign,(float)(x*-1+xc)/size*sign);
        glEnd();
    
    }
}
float fe(int x,int y,float rx,float ry){
    float fy = y-0.5;
    return ry*ry*x*x + fy*fy*rx*rx - rx*rx - ry*ry;
}
void midpointEllipse(int xc,int yc,int rx, int ry){
    int x=0;
    int y=ry;
    /*
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f((float)(x+xc)/size,(float)(y+yc)/size);
    glEnd();*/
    x++;
    float p= ry*ry-rx*rx*ry+(rx*rx/4);
    int sign=1;
    if((xc>0 && yc <0)||(xc<0 && yc>0)){ sign=-1;}
    
    //int dfdx = 2*ry*ry*x;
    //int dfdy = 2*rx*rx*y;
    
    while(2*ry*ry*x<=2*rx*rx*y){
        
        if(p<0){
            p = p+2*ry*ry*x + ry*ry;
        }
        else{
            p = p+2*ry*ry*x + ry*ry -2*rx*rx*y;
            y=y-1;
        }
        x++;
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x*-1+xc)/size,(float)(y*-1+yc)/size);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x+xc)/size,(float)(y*-1+yc)/size);
        glEnd();
    }
    p=fe(x,y,rx+0.5,ry-1.5);
    while(y>=0){
        
        if(p>0){
            p = p-2*rx*rx*y+rx*rx;
        }
        else{
            p = p+2*ry*ry*x + rx*rx -2*rx*rx*y;
            x+=1;;
        }
        y--;
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x*-1+xc)/size,(float)(y*-1+yc)/size);
        glEnd();
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((float)(x+xc)/size,(float)(y*-1+yc)/size);
        glEnd();
    }
    

}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
    // Define shapes enclosed within a pair of glBegin and glEnd
  
    midpointCircle(0, 0,500);
    midpointCircle(200, 200,100);
    midpointCircle(-200, 200,100);
    midpointEllipse(0, -200, 200, 50);

    glEnd();
   //glEnd();

   glFlush();  // Render now
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("Midpoint"); // Create a window with the given title
   glutInitWindowSize(size, size);   // Set the window's initial width & height
   glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

