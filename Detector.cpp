#include "Detector.hpp"

namespace RoboDodge
{
    Detector::Detector(float isurfaceX, float isurfaceY, vector<Ball>* irealBalls, Robot* irealRobot)
    {
        surfaceX = isurfaceX;
        surfaceY = isurfaceY;
        realBalls = irealBalls;
        realRobot = irealRobot;
    }

    Mat Detector::Get2DResult()
    {
        Mat3b outimg(surfaceX, surfaceY, Vec3b(150,150,150));
        
        for (int i = 0; i<realBalls->size(); i++)
        {
            circle(outimg, Point(realBalls->at(i).GetX(), realBalls->at(i).GetY()), 10, Scalar(0,50,205), 1);
            line(outimg, Point(realBalls->at(i).GetX(), realBalls->at(i).GetY()), Point(realBalls->at(i).GetX()+realBalls->at(i).GetSpeedX()*1000, realBalls->at(i).GetY()+realBalls->at(i).GetSpeedY()*1000), Scalar(0,65,190), 1);
        }
        
        for (int i = 0; i<balls.size(); i++)
        {
            circle(outimg, Point(balls[i].GetX(), balls[i].GetY()), 10, Scalar(0,10,245), -1);
            line(outimg, Point(balls[i].GetX(), balls[i].GetY()), Point(balls[i].GetX()+balls[i].GetSpeedX()*100, balls[i].GetY()+balls[i].GetSpeedY()*100), Scalar(0,0,255), 1);
        }
        
        Point realRobotPos = Point(realRobot->GetX(), realRobot->GetY());
        
        rectangle(outimg, realRobotPos-cv::Point(realRobot->GetWidth()/2,realRobot->GetHeight()/2), realRobotPos+cv::Point(realRobot->GetWidth()/2,0), Scalar(150,0,0), 1);
        
        rectangle(outimg, robotPos-cv::Point(realRobot->GetWidth()/2,realRobot->GetHeight()/2), robotPos+cv::Point(realRobot->GetWidth()/2,0), Scalar(255,0,0), -1);
        
        
        
        return outimg;
    }

    void Detector::FindBall(cv::Mat frame, float deltaTime)
    {
        Mat hsv;
        
        if (frame.empty())
        {
            cout<<"Видео закончилось."<<endl;
            return;
        }
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        
        //Поиск шара
        Mat1b mask1, mask2;
        inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
        inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);

        Mat1b ball = mask1 | mask2;
        Mat3b result;
        cvtColor(ball, result, COLOR_GRAY2RGB);
        
        Mat ballCopy = ball.clone();
        
        blur( ballCopy, ballCopy, Size(3,3));
        
        vector<vector<Point> > contours;
        vector<cv::Point> contPoly;
        vector<cv::Vec4i> hierarchy;
        cv::findContours(ballCopy,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        
        vector<cv::Point> Centers;
        vector<Moments> mu(contours.size() );
        
        int i,j;
        
        for(i = 0; i < contours.size(); i++ )
        {
            mu[i] = moments(contours[i], false);
        }
        
        for(i = 0; i < contours.size(); i++ )
        {
            Point2f bottomPoint = *max_element(contours[i].begin(), contours[i].end(),
                [](const Point& lhs, const Point& rhs) {
                    return lhs.y < rhs.y;
            });
            Point2f centerofmass = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
            
            Point2f bottomCenter = Point2f(centerofmass.x, bottomPoint.y);
            circle( result, bottomCenter, 1, Scalar(0,0,255), -1, 8, 0 );
            Centers.push_back(bottomCenter);
        }
        
        //Поиск линии
        
        Mat1b linemask;
        inRange(hsv, Scalar(40, 40,40), Scalar(70, 255,255), linemask);
        Mat1b line = linemask;
        
        cv::findContours(line,contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        screenLineRight = cv::Point(0, 0);
        screenLineLeft = cv::Point(line.cols, 0);
        
        for( int i = 0; i< contours.size(); i++ )
        {
            cv::RotatedRect boundingBox = cv::minAreaRect(contours[i]);
            cv::Point2f corners[4];
            boundingBox.points(corners);

            cv::line(result, corners[0], corners[1], cv::Scalar(0,150,0));
            cv::line(result, corners[1], corners[2], cv::Scalar(0,150,0));
            cv::line(result, corners[2], corners[3], cv::Scalar(0,150,0));
            cv::line(result, corners[3], corners[0], cv::Scalar(0,150,0));
            
            for (j = 0; j < 4; j++)
            {
                float x = corners[j].x;
                float y = corners[j].y;
                
                if (x < screenLineLeft.x)
                {
                    screenLineLeft = corners[j];
                }
                
                if (x > screenLineRight.x)
                {
                    screenLineRight = corners[j];
                }
            }
        }
        
        circle( result, screenLineLeft, 3, Scalar(0,255,0), -1, 8, 0 );
        circle( result, screenLineRight, 3, Scalar(0,255,0), -1, 8, 0 );
        
        // Создание модели
        
        float screenWidth = frame.cols;
        float screenHeight = frame.rows;
        
        float screenWallHeight = (screenLineLeft.y+screenLineRight.y)/2;
        
        robotPos.x = (screenWidth/2-screenLineLeft.x)/(screenLineRight.x - screenLineLeft.x) * surfaceX;
        robotPos.y = surfaceY;
        
        vector<Ball> approximateBalls;
        
        for (i = 0; i < Centers.size(); i++)
        {
            Point2f ballPos;
            
            Point2f screenBall = Centers[i];
                    
            Point screenRobot(screenBall.x, screenHeight);
            
            //float screenCross = -(((screenBall.x-screenRobot.x)*screenWallHeight + (screenRobot.x * screenBall.y - screenBall.x * screenRobot.y))/(screenRobot.y - screenBall.y));
            
            float screenCross = screenBall.x;
            
            cv::line(result, screenRobot, Point(screenCross, screenWallHeight), cv::Scalar(0,0,255), 1);
            
            float modelCrossX = ((screenCross)-screenLineLeft.x)/(screenLineRight.x - screenLineLeft.x) * surfaceX;
            float bpY = ((screenBall.y-screenWallHeight)/(screenHeight-screenWallHeight));
            ballPos.y =  bpY * surfaceY;
            ballPos.x = -((modelCrossX - robotPos.x) * ballPos.y + (robotPos.x*ballPos.y-modelCrossX*robotPos.y))/(robotPos.y);
            ballPos.y =  ((bpY+1)*(bpY+1)*(bpY+1)*(bpY+1)*(bpY+1)*(bpY+1)-1) * surfaceY;
            
            int minIndex = 0;
            float minDistance = 10000, mindx, mindy;
            
            for (j = 0; j < balls.size(); j++)
            {
                float dx = ballPos.x-balls[i].GetX();
                float dy = ballPos.y-balls[i].GetY();
                float distance = sqrt(dx*dx+dy*dy);
                
                if (distance<minDistance)
                {
                    minIndex = j;
                    minDistance = distance;
                    mindx = dx;
                    mindy = dy;
                }
            }
            
            if (minDistance < 1000)
            {
                Ball approximateBall(10, ballPos.x, ballPos.y, (balls[minIndex].GetSpeedX()+mindx*deltaTime)/2, (balls[minIndex].GetSpeedY()+mindy*deltaTime)/2);
                approximateBalls.push_back(approximateBall);
            }
            else
            {
                Ball approximateBall(10, ballPos.x, ballPos.y, 0, 0);
                approximateBalls.push_back(approximateBall);
            }
        }
        
        balls.clear();
        
        for (int i =0; i< approximateBalls.size(); i++)
        {
            balls.push_back(approximateBalls[i]);
        }
        
        Mat3b result2D = Get2DResult();
        
        Mat3b finalResult(result2D.rows, result2D.cols+result.cols, Vec3b(0,0,0));
        
        result2D.copyTo(finalResult(cv::Rect(result.cols, 0, result2D.cols, result2D.rows)));
        result.copyTo(finalResult(cv::Rect(0, 0, result.cols, result.rows)));
        
        resultMat = finalResult.clone();
    }

    vector<Ball>* Detector::GetBalls()
    {
        return &balls;
    }

    float Detector::GetRobotX()
    {
        return robotPos.x;
    }

    float Detector::GetRobotY()
    {
        return robotPos.y;
    }

    Mat Detector::GetResult()
    {
        return resultMat;
    }
}
