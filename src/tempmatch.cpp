#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[])
{
    Mat simg = imread( "images/tube.png" );
    Mat timg = imread( "images/tube_temp.png" );

    Mat d_simg = simg.clone();
    Mat d_timg = timg.clone();

    int n = 2;

    for(int i=0;i<n;i++)
    {
      cv::pyrDown( d_simg, d_simg, cv::Size( d_simg.cols/2, d_simg.rows/2 ));
      cv::pyrDown( d_timg, d_timg, cv::Size( d_timg.cols/2, d_timg.rows/2 ));
    }


    imshow("s image", simg );
    imshow("t image", timg );

    imshow("down s image", d_simg );
    imshow("down t image", d_timg );

    waitKey(0);

    return 0;
}
