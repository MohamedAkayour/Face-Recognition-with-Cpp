#include "opencv2/opencv.hpp"
#include <vector>

using namespace cv;
using namespace std;

int main(void){

    double scale= 1.0;
    
    CascadeClassifier faceCascade, bodyCascade;
    faceCascade.load("/opt/homebrew/Cellar/opencv/4.5.5/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml");
    bodyCascade.load("/opt/homebrew/Cellar/opencv/4.5.5/share/opencv4/haarcascades/haarcascade_upperbody.xml");
    
    //Openning the camera
    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;
    system("<mybrowser> http://google.com");


    //Infinite loop that keeps getting frames from the camera
    for(;;)
    {
        cv::Mat frame;
        cap >> frame;
        
        //grayscaling the pictures from the cam to be analyzed by the haarcascade
        cv::Mat grayscale;
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);
        
        //Putting the picture to scale
        resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));
        
        //rectangle vector to draw around the faces
        //minimum detection size of image is 30x30px
        vector<Rect> faces;
        faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));
        
        for(Rect area : faces)
        {
            Scalar drawColor = Scalar(0, 0, 255);
            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),Point(cvRound((area.x + area.width - 1)*scale), cvRound((area.y+area.height -1)*scale)), drawColor);
        }
        
        vector<Rect> bodies;
        bodyCascade.detectMultiScale(grayscale, bodies, 1.1, 3, 0, Size(30, 30));
        
        for(Rect area : bodies)
        {
            Scalar drawColor = Scalar(0, 255, 0);
            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),Point(cvRound((area.x + area.width - 1)*scale), cvRound((area.y+area.height -1)*scale)), drawColor);
        }
        imshow("Webcam Frame", frame);
 
        if (waitKey(30) == 27)
            break;
    }

    return 0;
    
}
