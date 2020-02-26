//
//  main.cpp
//  Computer Graphics
//
//  Created by Umut Cem Kayaalti on 2/5/20.
//  Copyright © 2020 Umut Cem Kayaalti. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <OpenGL/gl.h>

#include <OpenGl/glu.h>

#include <GLUT/glut.h>
/*
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}*/
void display();
float size = 600;
int check =0;
int click=0;

struct Line{
    float x1;
    float y1;
    float x2;
    float y2;
};

std::vector<Line*> lines;

void mouse(int button, int state, int x, int y) {
   
    float xf,yf;
    xf = x/size;
    xf-=0.5;
    xf*=2;
    yf = y/size;
    yf -=0.5;
    yf *=-2;
    if(check == 1){
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {                 lines.clear();
            display();
           }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {check=0;}
        return;

    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {                 // if left button is clicked, that is the start point

        Line *l = new Line{xf,yf,xf,yf};
        lines.push_back(l);
        click = 1;

    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {                   // once they lift the mouse, thats the finish point
        int last = lines.size()-1;
        lines.at(last)->x2=xf;
        lines.at(last)->y2=yf;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        check =1;
        click = 0;
    }
    display();

}

void motion(int x, int y) {
    int last = lines.size()-1;
    float xf,yf;
    xf = x/size;
    xf-=0.5;
    xf*=2;
    yf = y/size;
    yf -=0.5;
    yf *=-2;
    if(click==1){
        lines.at(last)->x2=xf;
        lines.at(last)->y2=yf;
        display();
    }


}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glutReshapeWindow( size, size);

    glBegin(GL_LINES);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    
    for(int i=0;i<lines.size();i++){
        glVertex2f((float)(lines.at(i)->x1),(float)(lines.at(i)->y1));
        glVertex2f((float)(lines.at(i)->x2),(float)(lines.at(i)->y2));
    }
    glEnd();

  
   //glEnd();

   glFlush();  // Render now
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("LineDrawing"); // Create a window with the given title
   glutInitWindowSize(size, size);   // Set the window's initial width & height
   glutInitWindowPosition(200, 200); // Position the window's initial top-left corner


    glutDisplayFunc(display);// Register display callback handler for window re-paint
   glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

