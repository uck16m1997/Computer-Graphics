#include"main.h"
#include"menu.h"
#include"display.h"
#include"util.h"
//main function:
//glutMainLoop never return;
int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("HW3");
    
        setup();
        
            // initializing callbacks
    glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutMouseFunc(mouse);
     glutMotionFunc(motion);
     
     glutSpecialFunc(specialKey); //register a special keyboard function.
    //Creates Menu on Right Click
     CreateMenu();

     glutMainLoop();
     return 0;

}
