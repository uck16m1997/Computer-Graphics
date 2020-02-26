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
int size = 1200;
void DrawLine(int x1,int y1,int x2,int y2){
    

    if(x1>x2){
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
        
        tmp = y2;
        y2 = y1;
        y1 = tmp;
        

    }

    int cX=x1;
    int cY=y1;

    x1 -= cX;
    y1 -= cY;
    x2 -= cX;
    y2 -= cY;
    
        
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    

    
    int shift = 1;
    if(y2>0 && dy>dx){
        shift = 2;
        int tmp = x2;
        x2 = y2;
        y2 = tmp;
    }
    else if(y2<0 && dx>=dy){
        shift = 8;
        y2 *=-1;
    }
    else if(y2<0 && dy>dx){
        shift = 7;
        int tmp = x2;
        x2 = y2*-1;
        y2 = tmp;
    }
    

     
    
    dx = x2 - x1;
    dy = y2 - y1;
    //int sign = 1;
    if(dy<0){
      //  sign = -1;
        dy *=-1;
    }

    
    
    int d = 2*dy - dx;
    int deltaD1 = 2* dy;
    int deltaD2 = 2 * (dy - dx);



    

    int y = y1;
 

    for (int x=0;x<=x2;x++){
        int globalX = x;
        int globalY = y;
        if(shift==2){
            globalX = y;
            globalY = x;
        }
        else if(shift==8){
            globalY = y*-1;
        }
        else if(shift==7){
            globalX =y;
            globalY =x*-1;
        }

        //std::cout << "GlobalY " << globalY << std::endl;
        
         glBegin(GL_POINTS);
         glColor3f(0.0f, 1.0f, 0.0f);
         glVertex2f((float)(globalX+cX)/size,(float)(globalY+cY)/size);
         glEnd();
     
     if (d < 0){
         d = d + deltaD1;
         
     }
     else{
         d = d + deltaD2;
         y = y + 1;
     }
    }
   
}

float fl(int x,int y,int dx,int dy,int b){
    float fy = y-0.5;

    return dy*x - dx*fy + dx*b;
}

void MidpointLine(int x1,int y1,int x2,int y2){
    
    if(x1>x2){
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
        
        tmp = y2;
        y2 = y1;
        y1 = tmp;
        

    }

    int cX=x1;
    int cY=y1;

    x1 -= cX;
    y1 -= cY;
    x2 -= cX;
    y2 -= cY;
    
        
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int b =0;
    if(dy!=0){
     b = y1 - (dx/dy)*x1;
    }
    
    int shift = 1;
    if(y2>0 && dy>dx){
        shift = 2;
        int tmp = x2;
        x2 = y2;
        y2 = tmp;
    }
    else if(y2<0 && dx>=dy){
        shift = 8;
        y2 *=-1;
    }
    else if(y2<0 && dy>dx){
        shift = 7;
        int tmp = x2;
        x2 = y2*-1;
        y2 = tmp;
    }
    
    int d = fl(x1,y1,dx,dy,b);
     
    
    dx = x2 - x1;
    dy = y2 - y1;
    //int sign = 1;
    if(dy<0){
        dy *=-1;
    }

    int y = y1;

    for (int x=0;x<=x2;x++){
        int globalX = x;
        int globalY = y;
        if(shift==2){
            globalX = y;
            globalY = x;
        }
        else if(shift==8){
            globalY = y*-1;
        }
        else if(shift==7){
            globalX =y;
            globalY =x*-1;
        }

        
         glBegin(GL_POINTS);
         glColor3f(0.0f, 1.0f, 0.0f);
         glVertex2f((float)(globalX+cX)/size,(float)(globalY+cY)/size);
         glEnd();

     if (d <= 0){
         d = d + dy;
         
     }
     else{
         d = d + dy-dx;
         y = y + 1;
     }
    }
   

    
   
    
}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
// Define shapes enclosed within a pair of glBegin and glEnd
   //glBegin(GL_POINTS);
    //DrawLine(-500,0,500,0);
    //DrawLine(0,-500,0,500);

    //DrawLine(0,0,-100,-100);
    
    DrawLine(-1000, 800, -900, 600);// 2k+x 4k-y k=50  W
    DrawLine(-900, 600, -850,700); // k+x 2k+y
    DrawLine(-850, 700, -800,600);// k+x 2k-y
    DrawLine(-800, 600, -700,800);// 2k+x 4k+y
    
    
    glBegin(GL_LINES); //W
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f((float)(150)/size,(float)(800)/size);
    glVertex2f((float)(250)/size,(float)(600)/size);
    glVertex2f((float)(250)/size,(float)(600)/size);
    glVertex2f((float)(300)/size,(float)(700)/size);
    glVertex2f((float)(300)/size,(float)(700)/size);
    glVertex2f((float)(350)/size,(float)(600)/size);
    glVertex2f((float)(350)/size,(float)(600)/size);
    glVertex2f((float)(450)/size,(float)(800)/size);
    glEnd();
    

    
    DrawLine(-700, 600, -600,800);// 2k+x 4k+y  k=50 A
    DrawLine(-650, 700, -550, 700);// Middle Line
    DrawLine(-600, 800, -500, 600);// 2k+x 4k-y
    
    glBegin(GL_LINES); //A
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f((float)(450)/size,(float)(600)/size);
    glVertex2f((float)(550)/size,(float)(800)/size);
    glVertex2f((float)(500)/size,(float)(700)/size);
    glVertex2f((float)(600)/size,(float)(700)/size);
    glVertex2f((float)(550)/size,(float)(800)/size);
    glVertex2f((float)(650)/size,(float)(600)/size);
    glEnd();
    
    DrawLine(-450, 800, -450, 600); //K
    DrawLine(-450, 700, -350, 800);
    DrawLine(-450, 700, -350, 600);
    
    glBegin(GL_LINES); //K
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f((float)(700)/size,(float)(600)/size);
    glVertex2f((float)(700)/size,(float)(800)/size);
    glVertex2f((float)(700)/size,(float)(700)/size);
    glVertex2f((float)(800)/size,(float)(800)/size);
    glVertex2f((float)(700)/size,(float)(700)/size);
    glVertex2f((float)(800)/size,(float)(600)/size);
    glEnd();

    DrawLine(-300, 800, -300, 600); //E
    DrawLine(-300, 800, -200, 800);
    DrawLine(-300, 700, -240, 700);
    DrawLine(-300, 600, -200, 600);

    glBegin(GL_LINES); //E
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f((float)(850)/size,(float)(800)/size);
    glVertex2f((float)(850)/size,(float)(600)/size);
    glVertex2f((float)(850)/size,(float)(800)/size);
    glVertex2f((float)(950)/size,(float)(800)/size);
    glVertex2f((float)(850)/size,(float)(700)/size);
    glVertex2f((float)(910)/size,(float)(700)/size);
    glVertex2f((float)(850)/size,(float)(600)/size);
    glVertex2f((float)(950)/size,(float)(600)/size);
    glEnd();
    
    
    DrawLine(0, 300, 0, -300); // Y Line
    
    DrawLine(50, 350, 125, 250);// Y
    DrawLine(125, 250, 200, 350);
    DrawLine(125, 250, 125, 100);
    
    DrawLine(0, -300, 600, -300); // X Line
    
    DrawLine(650, -200, 800, -400);//X
    DrawLine(650, -400, 800, -200);
    
    DrawLine(-400, -600, 0, -300);// Z Line 4kx 3ky
    
    DrawLine(50, -400, 175, -400);//5
    DrawLine(-50, -475, 50, -400);
    DrawLine(-50, -475, 75, -475);
    DrawLine(-25, -550, 75, -475);
    DrawLine(-150, -550, -25, -550);
    
    DrawLine(225, -400, 350, -400);// 6
    DrawLine(25, -550, 225, -400);
    DrawLine(25, -550, 150, -550);
    DrawLine(150, -550, 250, -475);
    DrawLine(125, -475, 250, -475);
    
    DrawLine(400, -400, 525, -400);//0
    DrawLine(200, -550, 400, -400);
    DrawLine(200, -550, 325, -550);
    DrawLine(325, -550, 525, -400);


    
    DrawLine(-600, -700, -450, -700);//Z
    DrawLine(-450, -700,-600,-900);
    DrawLine(-600, -900, -450, -900);
    
    DrawLine(-400, -200, -300, -125);//C in Z
    DrawLine(-400, -200, -400, -350);
    DrawLine(-400, -350, -300, -275);
    
    DrawLine(-250, -100, -150, -25);//S in Z
    DrawLine(-250, -100, -250, -175);
    DrawLine(-250, -175, -150, -100);
    DrawLine(-150, -100, -150, -175);
    DrawLine(-250, -250, -150, -175);
    

    
    DrawLine(150,-200,150,-50);//4
    DrawLine(100, -125, 175, -125);
    DrawLine(100, -125, 150, -50);
    
    DrawLine(200, -200, 200, -50);//6
    DrawLine(200, -50, 250, -50);
    DrawLine(200, -200, 250, -200);
    DrawLine(250, -200, 250, -125);
    DrawLine(250, -125, 200, -125);

    DrawLine(300, -200, 300, -50);//0
    DrawLine(300, -200, 350, -200);
    DrawLine(300, -50, 350, -50);
    DrawLine(350, -200, 350, -50);

    int x=-1000;
       int y= -950;
       for(int i=0;i<14;i++){
           MidpointLine(x, y, x+20, y);
           x+=50;
       }
       x=-1000;
       y+=-40;
       for(int i=0;i<14;i++){
           MidpointLine(x, y, x+40, y);
           x+=50;
       }
       x=-1000;
       y -=40;
       for(int i=0;i<14;i++){
           MidpointLine(x, y, x+30, y);
           MidpointLine(x, y+1, x+30, y+1);
           MidpointLine(x, y+2, x+30, y+2);
           MidpointLine(x, y+3, x+30, y+3);
           MidpointLine(x, y+4, x+30, y+4);
           x+=50;
       }
       x=-1100;
       y -=40;
       for(int i=0;i<8;i++){
           MidpointLine(x, y, x+40, y);
           x+=60;
           MidpointLine(x, y, x+10, y);
           x+=30;
           MidpointLine(x, y, x+10, y);
           x+=30;
       }
       x=-1000;
       y -=40;
       for(int i=0;i<10;i++){
           MidpointLine(x, y, x+50, y);
           MidpointLine(x, y+1, x+50, y+1);
           MidpointLine(x, y+2, x+50, y+2);
           MidpointLine(x, y+3, x+50, y+3);
           MidpointLine(x, y+4, x+50, y+4);
           MidpointLine(x, y+5, x+50, y+5);
           MidpointLine(x, y+6, x+50, y+6);
           MidpointLine(x, y+7, x+50, y+7);
           MidpointLine(x, y+3, x+50, y+8);
           MidpointLine(x, y+9, x+50, y+9);
           MidpointLine(x, y+10, x+50, y+10);
           MidpointLine(x, y+11, x+50, y+11);
           MidpointLine(x, y+12, x+50, y+12);
          MidpointLine(x, y+13, x+50, y+13);
          MidpointLine(x, y+14, x+50, y+14);
          MidpointLine(x, y+15, x+50, y+15);
          MidpointLine(x, y+16, x+50, y+16);
          MidpointLine(x, y+17, x+50, y+17);
          MidpointLine(x, y+18, x+50, y+18);

           x+=70;
       }
    
       
      
        glLineWidth(1.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
        glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f((float)(100)/size,(float)(-950)/size);
            glVertex2f((float)(900)/size,(float)(-950)/size);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
    
        glLineWidth(1.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2, 0x0FFF);
        glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f((float)(0)/size,(float)(-990)/size);
            glVertex2f((float)(1000)/size,(float)(-990)/size);
        glEnd();
    
    glDisable(GL_LINE_STIPPLE);
    
        glLineWidth(2.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x1F1F);
        glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f((float)(100)/size,(float)(-1030)/size);
            glVertex2f((float)(900)/size,(float)(-1030)/size);
        glEnd();
    
    glDisable(GL_LINE_STIPPLE);

        glLineWidth(1.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2, 0x0CCF);
        glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f((float)(0)/size,(float)(-1070)/size);
            glVertex2f((float)(1100)/size,(float)(-1070)/size);
        glEnd();

    glDisable(GL_LINE_STIPPLE);
    
    glDisable(GL_LINE_STIPPLE);

        glLineWidth(4.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0xBFBF);
        glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f((float)(0)/size,(float)(-1110)/size);
            glVertex2f((float)(1100)/size,(float)(-1110)/size);
        glEnd();

    glDisable(GL_LINE_STIPPLE);

    
    glEnd();
   //glEnd();

   glFlush();  // Render now
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("Bresenham"); // Create a window with the given title
   glutInitWindowSize(size, size);   // Set the window's initial width & height
   glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

