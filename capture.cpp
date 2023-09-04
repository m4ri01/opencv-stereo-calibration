#include <opencv2/opencv.hpp>
#include <iostream>

int main(){
    int left_camera = 0; // change with the left id camera
    int right_camera = 1; // change with the right id camera
    cv::VideoCapture cap1(left_camera);
    if (!cap1.isOpened()) {
        std::cout << "Error: Could not open webcam 1" << std::endl;
        return -1;
    }
    cv::VideoCapture cap2(right_camera);
    if (!cap2.isOpened()) {
        std::cout << "Error: Could not open webcam 2" << std::endl;
        cap1.release();  // Release the first webcam
        return -1;
    }
    cap1.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G')); 
    cap2.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

    int i =0;
    while(true){
        cv::Mat frame1, frame2;
        bool ret1 = cap1.read(frame1);
        bool ret2 = cap2.read(frame2);
        if (!ret1 || !ret2) {
            std::cout << "Error reading frames from one of the webcams" << std::endl;
            break;
        }
        cv::imshow("frame1", frame1);
        cv::imshow("frame2", frame2);
        if (cv::waitKey(1) & 0xFF == 'c') {
                cv::imwrite("left_" + std::to_string(i) + ".jpg", frame1);
                cv::imwrite("right_" + std::to_string(i) + ".jpg", frame2);
                std::cout << "Captured" << std::endl;
                i++;
                if (i == 10) {
                    break;
                }
        }

    }
    

    cap1.release();
    cap2.release();
    cv::destroyAllWindows();

    return 0;
}