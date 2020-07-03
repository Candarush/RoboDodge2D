#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include "SfSurface.hpp"
#include "SfRobot.hpp"
#include "SfBall.hpp"
#include "Detector.hpp"

#include <GL/glut.h>

using namespace RoboDodge;
using namespace std;
using namespace sf;
using namespace cv;

float width = 300;
float height = 300;

Surface ground(width, height, 0, 0);
SfRobot robot(15,15,50, height,0,0);
Ball ball(15,50,50, 0.1,0.2);

float deltaTime, timer;

//sf::Texture texture;
//sf::Sprite sprite;
//sf::Image image;
//
//cv::Mat frameRGB;
//
//sf::RenderWindow window(sf::VideoMode(500, 500), "SFML");

void resetTransforms()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void drawBox(float ox, float oy, float oz, float x, float y, float z)
{
    
    // Задняя стена
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(ox+x, oy-y, oz+z);
    glVertex3f(ox+x, oy+y, oz+z);
    glVertex3f(ox-x, oy+y, oz+z);
    glVertex3f(ox-x, oy-y, oz+z);
    glEnd();

    // Передняя стена
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(ox-x, oy+y, oz-z);
    glVertex3f(ox-x, oy-y, oz-z);
    glVertex3f(ox+x, oy-y, oz-z);
    glVertex3f(ox+x, oy+y, oz-z);
    glEnd();

    // Левая стена
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(ox-x, oy-y, oz-z);
    glVertex3f(ox-x, oy-y, oz+z);
    glVertex3f(ox-x, oy+y, oz+z);
    glVertex3f(ox-x, oy+y, oz-z);
    glEnd();


    // Правая стена
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(ox+x, oy-y, oz-z);
    glVertex3f(ox+x, oy-y, oz+z);
    glVertex3f(ox+x, oy+y, oz+z);
    glVertex3f(ox+x, oy+y, oz-z);
    glEnd();


    // Пол
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(ox-x, oy-y, oz-z);
    glVertex3f(ox-x, oy-y, oz+z);
    glVertex3f(ox+x, oy-y, oz+z);
    glVertex3f(ox+x, oy-y, oz-z);
    glEnd();
}

void drawSphere(float radius, float x, float y, float z)
{
    glColor3f(1, 0, 0);
    glTranslatef(x,y,z);
    glutSolidSphere(radius,20,20);
    resetTransforms();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0.0, 0.0, -5.0);

        GLfloat ambientColor[] = {0.2, 0.2, 0.2, 0.8};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

        GLfloat lightColor0[] = {0.5, 0.5, 0.5, 0.8};
        GLfloat lightPos0[] = {0.4, 0.0, 0.8, 0.6};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
        drawBox(0,3,-5,10,4,10);
        drawSphere(0.4,ball.GetX()/20-10,-0.4,ball.GetY()/20-10);
    
        cv::Mat img(height, width, CV_8UC3);
        glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
        glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
        glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
    
        imshow("OpenCV", img);
    
        glutSwapBuffers();
}

void initRendering()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);

        // Фон
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
}


void handleResize(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.0, (double)w / (double)h, 1.0, 200.0);
}

void Update ()
{
    
    deltaTime = ((float)clock()/ ( CLOCKS_PER_SEC / 1000 )) - timer;
    
    ball.UpdatePosition(deltaTime, ground);
    
    timer = ((float)clock()/ ( CLOCKS_PER_SEC / 1000 ));
    
    glutPostRedisplay();
}

void RunOpenGL(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    initRendering();
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (300, 0);
    glutCreateWindow ("OpenGL");
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);
    glutIdleFunc(Update);
    glutMainLoop();
    
}

int main(int argc, char **argv)
{
    timer = 0; deltaTime = 0;
    
    cv::Mat frame(600, 600, CV_8UC3);
    namedWindow("OpenCV", WINDOW_AUTOSIZE);
    imshow("OpenCV", frame);
    
    waitKey();
    
    RunOpenGL(argc, argv);
    
    waitKey();
    return 0;
}
