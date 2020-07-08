#include "OpenGLRenderer.hpp"

namespace RoboDodge
{
    float OpenGLRenderer::deltaTime = 0;
    float OpenGLRenderer::timer = 0;
    Surface* OpenGLRenderer::ground;
    Robot* OpenGLRenderer::robot;
    float OpenGLRenderer::movementDirection = 0;
    vector<Ball>* OpenGLRenderer::balls;
    void (*OpenGLRenderer::updateFuncPtr)(float, Mat frame);

    OpenGLRenderer::OpenGLRenderer(int argc, char** argv, float iwindowWidth, float iwindowHeight, void (*iupdateFuncPtr)(float, Mat), vector<Ball>* iballs, Robot* irobot, Surface* iground)
    {
        balls = iballs;
        robot = irobot;
        ground = iground;
        updateFuncPtr = iupdateFuncPtr;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize (iwindowWidth, iwindowHeight);
        glutInitWindowPosition(0,iwindowHeight);
        glutCreateWindow ("OpenGL");
        glutDisplayFunc(Draw);
        glutSpecialFunc(KeyboardControl);
        glutSpecialUpFunc(KeyboardButtonRelease);
        InitRendering();
        glutReshapeFunc(HandleResize);
        glutIdleFunc(OpenGLUpdate);
        glutMainLoop();
    }

    void OpenGLRenderer::InitRendering()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
    }

    void OpenGLRenderer::HandleResize(int iwidth, int iheight)
    {
        glViewport(0, 0, iwidth, iheight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.0, (double)iwidth / (double)iheight, 1.0, 200.0);
    }

    void OpenGLRenderer::DrawBox(float ox, float oy, float oz, float x, float y, float z)
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
        
        // Зеленая линия
        glBegin(GL_POLYGON);
        glColor3f(0, 1, 0);
        glVertex3f(ox-x, oy-y*0.95, oz-z*0.99);
        glVertex3f(ox-x, oy-y, oz-z*0.99);
        glVertex3f(ox+x, oy-y, oz-z*0.99);
        glVertex3f(ox+x, oy-y*0.95, oz-z*0.99);
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

    void OpenGLRenderer::DrawSphere(float radius, float x, float y, float z)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(x,y,z);
        glutSolidSphere(radius,20,20);
        glPopMatrix();
    }

    void OpenGLRenderer::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glTranslatef(0.0, 0.0, -5.0);

            GLfloat ambientColor[] = {0.5, 0.5, 0.5, 0.8};
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

            GLfloat lightColor0[] = {1, 1, 1, 1};
            GLfloat lightPos0[] = {0.4, 10, 0.8, 1};
            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        
            UpdateCameraPos();
        
            DrawBox(0,3,-5,10,4,10);
        
            for (int i = 0; i < balls->size(); i++)
            {
                DrawSphere(0.4,balls->at(i).GetX()/20-10,-0.6,(balls->at(i).GetY()/20-10)-5);
            }
        
            glFlush();
        
            glutSwapBuffers();
    }

    void OpenGLRenderer::OpenGLUpdate()
    {
        cv::Mat img(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), CV_8UC3,Scalar(0,0,255));
        glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
        glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
        glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
        
        flip(img, img, 0);
        
//        imshow("OpenCV", screenshot);
//        waitKey(1);
        
        deltaTime = ((float)clock()/ ( CLOCKS_PER_SEC / 1000 )) - timer;

        robot->Move(movementDirection,deltaTime, *ground);
        
        updateFuncPtr(deltaTime, img.clone());
        
        timer = ((float)clock()/ ( CLOCKS_PER_SEC / 1000 ));
        
        glutPostRedisplay();
    }

    void OpenGLRenderer::KeyboardControl(int key, int x, int y)
    {
        switch (key)
        {
            case 100:
            {
                if (robot->GetAP() == false)
                    movementDirection = -1;
                break;
            }
            case 102:
            {
                if (robot->GetAP() == false)
                    movementDirection = 1;
                break;
            }
            case 101:
            {
                if (robot->isCatching == false)
                {
                    robot->isCatching = true;
                }
                else
                {
                    robot->isCatching = false;
                }
                break;
            }
            default: break;
        }
    }

    void OpenGLRenderer::KeyboardButtonRelease(int key, int x, int y)
    {
        switch (key)
        {
            case 100:
            {
                movementDirection = 0;
                break;
            }
            case 102:
            {
                movementDirection = 0;
                break;
            }
            default: break;
        }
    }

    void OpenGLRenderer::UpdateCameraPos()
    {
        gluLookAt(robot->GetX()/20-10, 0.0f, 0.0f,
                  robot->GetX()/20-10, 0.0f, -1.0f,
                  0.0f, 1.0f,  0.0f);
    }
}
