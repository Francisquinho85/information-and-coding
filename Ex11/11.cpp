#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char** argv){
    Mat img1,img2;
    img1 = imread(argv[1],IMREAD_COLOR);
    img2 = imread(argv[2],IMREAD_COLOR);
    Mat s1;
    absdiff(img1, img2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    Scalar s = sum(s1);         // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        std::cout << 0 << std::endl;
    else
    {
        double  mse =sse /(double)(img1.channels() * img1.total());
        double psnr = 10.0*log10((255*255)/mse);
        std::cout << psnr << std::endl;
    }
}