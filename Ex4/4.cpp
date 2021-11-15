#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char** argv){
    Mat img1;
    img1 = imread(argv[1],IMREAD_COLOR);
    Mat img2 = Mat::zeros(Size(img1.cols,img1.rows),CV_8UC3);
    for(int y=0; y<img1.cols; y++){
        for(int x=0; x<img1.rows; x++){
            img2.at<Vec3b>(x,y) = img1.at<Vec3b>(x,y);
        }
    }
    imwrite(argv[2],img2);
    return 0;
}

// g++ 4.cpp -o 4 `pkg-config --cflags --libs opencv4`