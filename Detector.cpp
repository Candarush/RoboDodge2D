#include "Detector.hpp"

namespace RoboDodge
{
    Detector::Detector(VideoCapture* icapture, float isurfaceX, float isurfaceY)
    {
        surfaceX = isurfaceX;
        surfaceY = isurfaceY;
        capture = icapture;
        namedWindow("RoboDodge2d Detector", WINDOW_AUTOSIZE);
        Mat firstFrame;
        capture->read(firstFrame);
        imshow("RoboDodge2d Detector", firstFrame);
    }

    void Detector::FindBall()
    {
        Mat frame, hsv;
        
        (*capture) >> frame;
        
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
        cout << "Найдено контуров: " << contours.size() << endl;
        
        vector<cv::Point> Centers;
        vector<Moments> mu(contours.size() );
        
        int i,j;
        
        for(i = 0; i < contours.size(); i++ )
        {
            mu[i] = moments(contours[i], false);
        }
        
        for(i = 0; i < contours.size(); i++ )
        {
            Point2f centerofmass = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
            cout<<"Центр: (" << centerofmass.x << ", " << centerofmass.y << ")"<<endl;
            circle( result, centerofmass, 1, Scalar(0,0,255), -1, 8, 0 );
            Centers.push_back(centerofmass);
        }
        
        //Поиск линии
        
        Mat1b linemask;
        inRange(hsv, Scalar(40, 40,40), Scalar(70, 255,255), linemask);
        Mat1b line = linemask;
        
        cv::findContours(line,contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        screenLineRight = Point(0, 0);
        screenLineLeft = Point(line.cols, 0);
        
        for( int i = 0; i< contours.size(); i++ )
        {
            cv::RotatedRect boundingBox = cv::minAreaRect(contours[i]);
            cv::Point2f corners[4];
            boundingBox.points(corners);

            cv::line(result, corners[0], corners[1], cv::Scalar(0,150,0));
            cv::line(result, corners[1], corners[2], cv::Scalar(0,150,0));
            cv::line(result, corners[2], corners[3], cv::Scalar(0,150,0));
            cv::line(result, corners[3], corners[0], cv::Scalar(0,150,0));
            
            for (j = 0; j < 2; j++)
            {
                float x = corners[j].x;
                float y = corners[j].y;
                
                if (x < screenLineLeft.x)
                {
                    screenLineLeft = Point(corners[j]);
                }
                
                if (x > screenLineRight.x)
                {
                    screenLineRight = Point(corners[j]);
                }
            }
        }
        
        circle( result, screenLineLeft, 3, Scalar(0,255,0), -1, 8, 0 );
        circle( result, screenLineRight, 3, Scalar(0,255,0), -1, 8, 0 );
        
        // Создание модели
        
        float screenWidth = frame.cols;
        float screenHeight = frame.rows;
        
        Point screenRobot(screenWidth/2, screenHeight);
        
        float screenWallHeight = (screenLineLeft.y+screenLineRight.y)/2;
        cout<< "screenWallHeight= " << screenWallHeight<<endl;
        
        robotPos.x = (screenWidth/2-screenLineLeft.x)/(screenLineRight.x - screenLineLeft.x) * surfaceX;
        robotPos.y = surfaceY;
        
        if (Centers.size()>0)
        {
            Point screenBall;
            
            screenBall = Centers[0];
            float screenCross = -(((screenBall.x-screenRobot.x)*screenWallHeight + (screenRobot.x * screenBall.y - screenBall.x * screenRobot.y))/(screenRobot.y - screenBall.y));
            
            cv::line(result, screenRobot, Point(screenCross, screenWallHeight), cv::Scalar(0,0,255), 1);
            
            float modelCrossX = ((screenCross)-screenLineLeft.x)/(screenLineRight.x - screenLineLeft.x) * surfaceX;
            float bpY = ((screenBall.y-screenWallHeight)/(screenHeight-screenWallHeight));
            ballPos.y =  bpY * surfaceY;
            ballPos.x = -((modelCrossX - robotPos.x) * ballPos.y + (robotPos.x*ballPos.y-modelCrossX*robotPos.y))/(robotPos.y);
            ballPos.y =  ((bpY+1)*(bpY+1)*(bpY+1)*(bpY+1)-1) * surfaceY;
            cout<<"Позиция шайбы: "<< ballPos <<endl;
            
        }
        
        cout<<"Позиция робота: "<< robotPos <<endl;
        
        Mat3b finalResult(frame.rows, frame.cols+result.cols, Vec3b(0,0,0));

        frame.copyTo(finalResult(Rect(0, 0, frame.cols, frame.rows)));
        result.copyTo(finalResult(Rect(frame.cols, 0, result.cols, result.rows)));
        
        imshow("RoboDodge2d Detector", finalResult);
        
        waitKey();

    }

    float Detector::GetBallX()
    {
        return ballPos.x;
    }

    float Detector::GetBallY()
    {
        return ballPos.y;
    }

    float Detector::GetRobotX()
    {
        return robotPos.x;
    }

    float Detector::GetRobotY()
    {
        return robotPos.y;
    }

}
