//
//  main.cpp
//  Computer Graphics
//
//  Copyright © 2020 Umut Cem Kayaalti. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <OpenGL/gl.h>

#include <OpenGl/glu.h>

#include <GLUT/glut.h>

void display();
float width = 1200;
float size = 800;
int check =0;
int click=0;

struct Line{
    float x1;
    float y1;
    float x2;
    float y2;
};
struct Point{
    float x;
    float y;
};

std::vector<Line*> clipper;
std::vector<Line*> regfill;
std::vector<Line*> lines;
std::vector<Line*> viewport;
std::vector<Line*> vplines;

Point clipTR;
Point vpTR;
Point clipTM;
Point vpTM;

Point TopRight(std::vector<Line*> view){
    Point p;
    p.x = -1;
    p.y = -1;
    
    for(int i=0;i<view.size();i++){
        if(view.at(i)->x1>=p.x && view.at(i)->y1>=p.y){
            p.x = view.at(i)->x1;
            p.y = view.at(i)->y1;
        }
    }
    return p;
}

Point TopMiddle(std::vector<Line*> view){
    Point p;
    p.x = -1;
    p.y = -1;
    
    for(int i=0;i<view.size();i++){
        if(view.at(i)->y1>=p.y && view.at(i)->y1==view.at(i)->y2){
            if(view.at(i)->x1>view.at(i)->x2){
                p.x = view.at(i)->x2;

                float val = (view.at(i)->x1-view.at(i)->x2);
                if(val<0){
                    val*=-1;
                }
                p.x = view.at(i)->x2+(val)/2;
            }
            else{
                p.x = view.at(i)->x1;
                float val = (view.at(i)->x2-view.at(i)->x1);
                if(val<0){
                    val*=-1;
                }
                p.x+=val/2;
            }
            p.y = view.at(i)->y1;
        }
    }

    return p;
}


float x_intersect(float x1, float y1, float x2, float y2,
                float x3, float y3, float x4, float y4)
{
    float num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}
float y_intersect(float x1, float y1, float x2, float y2,
                float x3, float y3, float x4, float y4)
{
    float num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}


void ViewMapping(){
    vplines.clear();
    float xcmin = 1;
    float ycmin = 1;
    float ycmax = -1;
    float xcmax = -1;
    for(int i=0;i<clipper.size();i++){
        if(xcmin>clipper.at(i)->x1){
            xcmin = clipper.at(i)->x1;
        }
        if(xcmax<clipper.at(i)->x1){
            xcmax =clipper.at(i)->x1;
        }
        if(ycmax<clipper.at(i)->y1){
            ycmax =clipper.at(i)->y1;
        }
        if(ycmin>clipper.at(i)->y1){
            ycmin = clipper.at(i)->y1;
        }
    }
    float xvpmin = 1;
    float yvpmin = 1;
    float yvpmax = -1;
    float xvpmax = -1;

    for(int i=0;i<viewport.size();i++){
        if(xvpmax<viewport.at(i)->x1){
            xvpmax =viewport.at(i)->x1;
        }
        if(yvpmax<viewport.at(i)->y1){
            yvpmax =viewport.at(i)->y1;
        }
        if(xvpmin>viewport.at(i)->x1){
            xvpmin = viewport.at(i)->x1;
        }
        if(yvpmin>viewport.at(i)->y1){
            yvpmin = viewport.at(i)->y1;
        }
    }
    float vpwidth=xvpmax-xvpmin;
    float vpheight=yvpmax-yvpmin;
    float cwidth=xcmax-xcmin;
    float cheight=ycmax-ycmin;
    

    
    for(int i=0;i<lines.size();i++){
        float sy = lines.at(i)->y1;
        float sx = lines.at(i)->x1;
        float by = lines.at(i)->y2;
        float bx = lines.at(i)->x2;
        int siy = 0;
        int six = 0;
        if(lines.at(i)->x2<sx){bx=sx; sx=lines.at(i)->x2; six=1;}
        if(lines.at(i)->y2<sy){by=sy; sy=lines.at(i)->y2; siy=1;}


        float difx=sx-bx;
        difx = difx*vpwidth/cwidth;
      
        if(siy!=six){
            float tmp = by;
            by=sy;
            sy = tmp;
            
        }
        float difbx = sx-xcmin;
        float difby = sy-ycmin;
        difbx = difbx*vpwidth/cwidth;
        difby = difby*vpheight/cheight;
        float dify=sy-by;
        dify = dify*vpheight/cheight;
        

        Line* l = new Line{xvpmin+difbx,yvpmin+difby,xvpmin-difx+difbx,difby+yvpmin-dify};
        vplines.push_back(l);
    }
    display();
}

void WindowScaler(float xf,float yf){
    if(click==2){
        //float xdif = xf - clipTR.x;
        //float ydif = yf - clipTR.y;
        for(int i=0;i<clipper.size();i++){
            if(clipper.at(i)->x1==clipTR.x){
                clipper.at(i)->x1=xf;
            }
            if(clipper.at(i)->y1==clipTR.y){
                clipper.at(i)->y1=yf;
            }
            if(clipper.at(i)->x2==clipTR.x){
                clipper.at(i)->x2=xf;
            }
            if(clipper.at(i)->y2==clipTR.y){
                clipper.at(i)->y2=yf;
            }
            
        }
        clipTR=TopRight(clipper);
        clipTM = TopMiddle(clipper);
        ViewMapping();
        
    }
    if(click==3){
        //float xdif = xf - clipTR.x;
        //float ydif = yf - clipTR.y;
        for(int i=0;i<viewport.size();i++){
            if(viewport.at(i)->x1==vpTR.x){
                viewport.at(i)->x1=xf;
            }
            if(viewport.at(i)->y1==vpTR.y){
                viewport.at(i)->y1=yf;
            }
            if(viewport.at(i)->x2==vpTR.x){
                viewport.at(i)->x2=xf;
            }
            if(viewport.at(i)->y2==vpTR.y){
                viewport.at(i)->y2=yf;
            }
            
        }
        vpTR=TopRight(viewport);
        vpTM = TopMiddle(viewport);
        ViewMapping();
        
    }
    
}
void WindowMover(float xf,float yf){
    if(click==4){
        float xd= xf-clipTM.x;
        float yd = yf-clipTM.y;
        for(int i=0;i<clipper.size();i++){
            clipper.at(i)->x1+=xd;
            clipper.at(i)->x2+=xd;
            clipper.at(i)->y1+=yd;
            clipper.at(i)->y2+=yd;
        }
        clipTR=TopRight(clipper);
        clipTM = TopMiddle(clipper);
        ViewMapping();
    }
    if(click==5){
        float xd= xf-vpTM.x;
        float yd = yf-vpTM.y;
        for(int i=0;i<viewport.size();i++){
            viewport.at(i)->x1+=xd;
            viewport.at(i)->x2+=xd;
            viewport.at(i)->y1+=yd;
            viewport.at(i)->y2+=yd;
        }
        vpTR=TopRight(viewport);
        vpTM = TopMiddle(viewport);
        ViewMapping();
    }
}
void RegionFilling(){
    regfill.clear();
    float xmax = -1;
    float xmin = 1;
    float ymax = -1;
    float ymin = 1;
    for(int i=0;i<clipper.size();i++){
        if(xmax<clipper.at(i)->x1){
            xmax =clipper.at(i)->x1;
        }
        if(xmin>clipper.at(i)->x1){
            xmin = clipper.at(i)->x1;
        }
        if(ymax<clipper.at(i)->y1){
            ymax =clipper.at(i)->y1;
        }
        if(ymin>clipper.at(i)->y1){
            ymin = clipper.at(i)->y1;
        }
    }
    float incr = 0.001;
    for(float i=ymin;i<=ymax;i+=incr){

        std::vector<float> intersects;
        for(float j=0;j<lines.size();j++){
            float inters = x_intersect(lines.at(j)->x1, lines.at(j)->y1, lines.at(j)->x2, lines.at(j)->y2, xmin, i, xmax, i);
            
            float bx= lines.at(j)->x2;
            float sx= lines.at(j)->x1;
            float by = lines.at(j)->y2;
            float sy= lines.at(j)->y1;
            if(lines.at(j)->y1>lines.at(j)->y2){
                  by= sy;
                  sy = lines.at(j)->y2;
              }
            if(i>=by || i<sy){
                continue;
            }
            if(lines.at(j)->x1>lines.at(j)->x2){
                bx= sx;
                sx = lines.at(j)->x2;
            }
            if(xmin<=inters && xmax>=inters && inters<=bx && inters>=sx){
                intersects.push_back(inters);
                
            }
            for(int x=0;x<intersects.size();x++){
                for(int y=0;y<intersects.size()-x-1;y++){
                    if(intersects.at(y)>intersects.at(y+1)){
                        float tmp = intersects.at(y+1);
                        intersects.at(y+1)=intersects.at(y);
                        intersects.at(y)=tmp;
                    }
                }
            }
        }
        //glBegin(GL_LINES);
           
           //glColor3f(0.0f, 1.0f, 0.0f);
        for(int k=0;k<intersects.size();k+=2){
            Line* l = new Line{intersects.at(k),i,xmax,i};
            //glVertex2f(intersects.at(k),i);
            if(k+1<intersects.size()){

                //glVertex2f(xmax,i);
                l->x2=intersects.at(k+1);
                
            }
            //if(intersects.size()==1){break;}
            regfill.push_back(l);
            
        }
          // glEnd();
    }

    display();
    
}

void Sutherland(){

    std::vector<Point*> polyPoints;
    for(int i=0;i<lines.size();i++){
        Point* p = new Point {lines.at(i)->x1,lines.at(i)->y1};
        polyPoints.push_back(p);

    }
    if(lines.size()==1){
        Point* p = new Point {lines.at(0)->x2,lines.at(0)->y2};
        polyPoints.push_back(p);
    }
    if(lines.size()==2){
        Point* p = new Point {lines.at(1)->x2,lines.at(1)->y2};
        polyPoints.push_back(p);
    }
    Point smallest = {1,1};
    float y= 0;
    for(int i=0;i<clipper.size();i++){
        if(clipper.at(i)->x1<smallest.x){
            smallest.x = clipper.at(i)->x1;
            smallest.y = clipper.at(i)->y1;
        }
        else if(clipper.at(i)->x1==smallest.x){
            y = clipper.at(i)->y1;
        }
    }
    std::vector<Point*> tmp;
    for(int i=0;i<polyPoints.size();i++){ //left

        int next = i+1;
        if(next==polyPoints.size()){
            next=0;
        }
        if(polyPoints.at(i)->x<smallest.x){
            if(polyPoints.at(next)->x<smallest.x){
                
            }
            else{
               // printf("%d I O\n",i);
                float inters = y_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, smallest.x, y);
                Point* p = new Point {smallest.x,inters};
                tmp.push_back(p);
                p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
                tmp.push_back(p);
            }
        }
        else if(polyPoints.at(next)->x<smallest.x){
            //printf("%d I O\n",i);

            float inters = y_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, smallest.x, y);
            Point* p = new Point {smallest.x,inters};
            tmp.push_back(p);
        }
        else{
            Point* p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
            tmp.push_back(p);
        }
    }
    polyPoints = (tmp);
    tmp.clear();
    
    for(int i=0;i<clipper.size();i++){
    
        if(clipper.at(i)->x1>smallest.x){
            smallest.x = clipper.at(i)->x1;
            smallest.y = clipper.at(i)->y1;
        }
        else if(clipper.at(i)->x1==smallest.x){
            y = clipper.at(i)->y1;
        }
    }
    
    for(int i=0;i<polyPoints.size();i++){ //right

           int next = i+1;
           if(next==polyPoints.size()){
               next=0;
           }
           if(polyPoints.at(i)->x>smallest.x){
               if(polyPoints.at(next)->x>smallest.x){
               }
               else{
                   float inters = y_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, smallest.x, y);
                   Point* p = new Point {smallest.x,inters};
                   tmp.push_back(p);
                   p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
                   tmp.push_back(p);
               }
           }
           else if(polyPoints.at(next)->x>smallest.x){
               float inters = y_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, smallest.x, y);
               Point* p = new Point {smallest.x,inters};
               tmp.push_back(p);
           }
           else{
               Point* p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
               tmp.push_back(p);
           }
       }
    polyPoints = (tmp);
    tmp.clear();
    
    for(int i=0;i<clipper.size();i++){
    
        if(clipper.at(i)->y1<smallest.y){
            smallest.x = clipper.at(i)->x1;
            smallest.y = clipper.at(i)->y1;
        }
        else if(clipper.at(i)->y1==smallest.y){
            y = clipper.at(i)->x1;
        }
    }
    
    for(int i=0;i<polyPoints.size();i++){ //bottom

           int next = i+1;
           if(next==polyPoints.size()){
               next=0;
           }
           if(polyPoints.at(i)->y<smallest.y){
               if(polyPoints.at(next)->y<smallest.y){}
               else{
    
                   float inters = x_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, y, smallest.y);
                   Point* p = new Point {inters,smallest.y};
                   tmp.push_back(p);
                   p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
                   tmp.push_back(p);
               }
           }
           else if(polyPoints.at(next)->y<smallest.y){

               
               float inters = x_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, y, smallest.y);
               Point* p = new Point {inters,smallest.y};
               tmp.push_back(p);
           }
           else{
 
               
               Point* p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
               tmp.push_back(p);
           }
       }
    polyPoints = (tmp);
    tmp.clear();
    
    for(int i=0;i<clipper.size();i++){
    
        if(clipper.at(i)->y1>smallest.y){
            smallest.x = clipper.at(i)->x1;
            smallest.y = clipper.at(i)->y1;
        }
        else if(clipper.at(i)->y1==smallest.y){
            y = clipper.at(i)->y1;
        }
    }
    
    for(int i=0;i<polyPoints.size();i++){ //top

           int next = i+1;
           if(next==polyPoints.size()){
               next=0;
           }
           if(polyPoints.at(i)->y>smallest.y){
               if(polyPoints.at(next)->y>smallest.y){
               
               }
               else{
                
                   
                   float inters = x_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, y, smallest.y);
                   Point* p = new Point {inters,smallest.y};
                   tmp.push_back(p);
                   p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
                   tmp.push_back(p);
               }
           }
           else if(polyPoints.at(next)->y>smallest.y){

               
               float inters = x_intersect(polyPoints.at(i)->x, polyPoints.at(i)->y, polyPoints.at(next)->x, polyPoints.at(next)->y, smallest.x, smallest.y, y, smallest.y);
               Point* p = new Point {inters,smallest.y};
               tmp.push_back(p);
           }
           else{

               
               Point* p = new Point {polyPoints.at(next)->x,polyPoints.at(next)->y};
               tmp.push_back(p);
           }
       }
    lines.clear();
    polyPoints = (tmp);
    for(int i=0;i<polyPoints.size();i++){
        int next = i+1;
        if(next==polyPoints.size()){
            next=0;
        }
        Line *l = new Line{polyPoints.at(i)->x,polyPoints.at(i)->y,polyPoints.at(next)->x,polyPoints.at(next)->y};
        lines.push_back(l);
        
        
    }
    
    display();

}

void mouse(int button, int state, int x, int y) {
   
    float xf,yf;
    xf = x/width;
    xf-=0.5;
    xf*=2;
    yf = y/size;
    yf -=0.5;
    yf *=-2;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {                 // if left button is clicked, that is the start point
           
        if(xf>=clipTR.x-0.02 && xf<=clipTR.x+0.02 && yf>=clipTR.y-0.02 && yf<=clipTR.y+0.02){
        click=2;
            
           }
        else if(xf>=vpTR.x-0.02 && xf<=vpTR.x+0.02 && yf>=vpTR.y-0.02 && yf<=vpTR.y+0.02){
            click=3;
        }
        else if(xf>=clipTM.x-0.05 && xf<=clipTM.x+0.05 && yf>=clipTM.y-0.02 && yf<=clipTM.y+0.02){
            click=4;
        }
        else if(xf>=vpTM.x-0.05 && xf<=vpTM.x+0.05 && yf>=vpTM.y-0.02 && yf<=vpTM.y+0.02){
            click=5;
        }
        
        else if(check == 1){
                         lines.clear();
                         regfill.clear();
                         vplines.clear();
                         display();
                         check=0;
                         click=0;
                         glutDetachMenu(GLUT_RIGHT_BUTTON);
        
           }
           else{
           Line *l = new Line{xf,yf,xf,yf};
           lines.push_back(l);
               click = 1;
               
           }
           
    

       }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {                   // once they lift the mouse, thats the finish point
        if(click==2 || click==3 || click==4 || click==5){
            click =0;
            check=1;
        }
        else if(click==1){
            int last = lines.size()-1;
            lines.at(last)->x2=xf;
            lines.at(last)->y2=yf;
            
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        check =1;
        click = 0;
        lines.pop_back();
        glutAttachMenu(GLUT_RIGHT_BUTTON);

    }
    display();

}

void menu(int value)
{

    switch(value) {

  case 1:
            Sutherland();
     break;
  case 2:
            Sutherland();
            RegionFilling();
     break;
  case 3:
            Sutherland();
            ViewMapping();
    break;
  }

}


void make_menu(void)
{
   glutCreateMenu(menu);
    glutAddMenuEntry("Polygon Clipping", 1);
    glutAddMenuEntry("Region Filling", 2);
     glutAddMenuEntry("Window-to-Viewport Mapping", 3);


}
void actmotiton(int x,int y){
    if(click==2 || click==3){
        float xf,yf;
        xf = x/width;
        xf-=0.5;
        xf*=2;
        yf = y/size;
        yf -=0.5;
        yf *=-2;
        WindowScaler(xf, yf);
    }
    else if(click==4 || click==5){
        float xf,yf;
        xf = x/width;
        xf-=0.5;
        xf*=2;
        yf = y/size;
        yf -=0.5;
        yf *=-2;
        WindowMover(xf, yf);
    }
}
void motion(int x, int y) {
    if(click==2 || click==3){
        return;
    }
    int last = lines.size()-1;
    float xf,yf;
    xf = x/width;
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
    glutReshapeWindow( width, size);

    glBegin(GL_LINES);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    
    for(int i=0;i<lines.size();i++){
        glVertex2f((float)(lines.at(i)->x1),(float)(lines.at(i)->y1));
        glVertex2f((float)(lines.at(i)->x2),(float)(lines.at(i)->y2));
    }
    glEnd();
    glBegin(GL_LINES);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    
    for(int i=0;i<vplines.size();i++){
        glVertex2f((float)(vplines.at(i)->x1),(float)(vplines.at(i)->y1));
        glVertex2f((float)(vplines.at(i)->x2),(float)(vplines.at(i)->y2));
    }
    glEnd();
    glBegin(GL_LINES);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    
    for(int i=0;i<regfill.size();i++){
        glVertex2f((float)(regfill.at(i)->x1),(float)(regfill.at(i)->y1));
        glVertex2f((float)(regfill.at(i)->x2),(float)(regfill.at(i)->y2));
    }
    glEnd();
    
    glLineWidth(1.0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        for(int i=0;i<clipper.size();i++){
            glVertex2f((float)(viewport.at(i)->x1),(float)(viewport.at(i)->y1));
            glVertex2f((float)(viewport.at(i)->x2),(float)(viewport.at(i)->y2));
            glVertex2f((float)(clipper.at(i)->x1),(float)(clipper.at(i)->y1));
            glVertex2f((float)(clipper.at(i)->x2),(float)(clipper.at(i)->y2));
        }
    glEnd();

    glDisable(GL_LINE_STIPPLE);
  
   //glEnd();

   glFlush();  // Render now
}
 
int main(int argc, char** argv) {
    clipper.clear();
    Line *l = new Line{(float)(0)/width,(float)(400)/size,(float)(800)/width,(float)(400)/size};
    clipper.push_back(l);
    l = new Line{(float)(800)/width,(float)(400)/size,(float)(800)/width,(float)(-400)/size};
    clipper.push_back(l);
    l = new Line{(float)(800)/width,(float)(-400)/size,(float)(0)/width,(float)(-400)/size};
    clipper.push_back(l);
    l = new Line{(float)(0)/width,(float)(-400)/size,(float)(0)/width,(float)(400)/size};
    clipper.push_back(l);
    
    l = new Line{(float)(-800)/width,(float)(250)/size,(float)(-300)/width,(float)(250)/size};
    viewport.push_back(l);
    l = new Line{(float)(-300)/width,(float)(250)/size,(float)(-300)/width,(float)(-250)/size};
    viewport.push_back(l);
    l = new Line{(float)(-300)/width,(float)(-250)/size,(float)(-800)/width,(float)(-250)/size};
    viewport.push_back(l);
    l = new Line{(float)(-800)/width,(float)(-250)/size,(float)(-800)/width,(float)(250)/size};
    viewport.push_back(l);
    clipTR = TopRight(clipper);
    vpTR = TopRight(viewport);
    clipTM = TopMiddle(clipper);
    vpTM = TopMiddle(viewport);

    lines.clear();
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("Clipper"); // Create a window with the given title
   glutInitWindowSize(width, size);   // Set the window's initial width & height
   glutInitWindowPosition(200, 200); // Position the window's initial top-left corner

    make_menu();
    glutDisplayFunc(display);// Register display callback handler for window re-paint
    glutMouseFunc(mouse);
    glutMotionFunc(actmotiton);
    glutPassiveMotionFunc(motion);
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}

