#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{ 
    CommandLineParser parser( argc, argv, "{@input | lena.jpg | input image}" );
    Mat src = imread( samples::findFile( parser.get<String>( "@input" ) ), IMREAD_COLOR );
    if( src.empty() )
    {
        return EXIT_FAILURE;
    }
    int bits = atoi(argv[2]);
    Mat img = Mat::zeros(Size(src.cols,src.rows),CV_8UC3);
    for(int y=0; y<src.cols; y++){
        for(int x=0; x<src.rows; x++){
            Vec3b a = src.at<Vec3b>(x,y);
            a[0] = (a[0]>>bits)<<bits; 
            a[1] = (a[1]>>bits)<<bits;
            a[2] = (a[2]>>bits)<<bits;
            img.at<Vec3b>(x,y) = a;
        }
    }
    // int div = 64;
    // for(int y=0; y<src.cols; y++){
    //     uchar* data = src.ptr<uchar>(y);
    //     uchar* data2 = img.ptr<uchar>(y);
    //     for(int x=0; x<(src.rows*src.channels()) ; x++){
    //         data2[x] = data[x] / div * div + div / 2;
    //     }
    // }
    imshow("Image", src);
    imshow("Image reduce", img);
    waitKey();
    return EXIT_SUCCESS;
}