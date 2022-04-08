#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[])
{
    Mat s_img = imread( "images/tube.png" );
    Mat t_img = imread( "images/tube_temp.png" );

    imshow("s image", s_img );
    imshow("t image", t_img );

    waitKey(0);

    return 0;
}
