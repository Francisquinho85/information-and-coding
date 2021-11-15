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
    vector<Mat> bgr_planes;
    split( src, bgr_planes );
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }

    Mat grayimg;
    cvtColor(src , grayimg, cv::COLOR_BGR2GRAY);
    Mat gray_hist;
    histSize = 256;
    calcHist( &grayimg, 1, 0, Mat(), gray_hist, 1, &histSize, histRange, uniform, accumulate );
    Mat histImageGray( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
    normalize(gray_hist, gray_hist, 0, histImageGray.rows, NORM_MINMAX, -1, Mat() );
    for(int k = 1; k<histSize; k++){
        line( histImageGray, Point( bin_w*(k-1), hist_h - cvRound(gray_hist.at<float>(k-1)) ),
              Point( bin_w*(k), hist_h - cvRound(gray_hist.at<float>(k)) ),
              Scalar( 255, 255, 255), 2, 8, 0  );
    }
    imshow("Source image", src );
    imshow("Gray image",grayimg);
    imshow("calcHist", histImage );
    imshow("calcHist Gray", histImageGray);
    waitKey();
    return EXIT_SUCCESS;
}