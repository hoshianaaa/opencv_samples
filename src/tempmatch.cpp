#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[])
{
    Mat simg = imread( "images/tube.png" );
    Mat timg = imread( "images/tube_temp.png" );
    
    int x_sum = 0;
    int y_sum = 0;

    int width = timg.cols;
    int height = timg.rows;

    int noOfCordinates = 0;
    cv::Point *coordinates;
    coordinates =  new cv::Point[width * height];

    for (int j = 0; j < timg.rows; j++)
    {
        unsigned char *src = timg.ptr<unsigned char>(j);
        for (int i = 0; i < timg.cols; i++)
        {
            if(src[i] == 255){
              coordinates[noOfCordinates].x = i;
              coordinates[noOfCordinates].y = j;
              x_sum += i;
              y_sum += j;
              noOfCordinates++;
            } 
        }
    }

    double center_x = double(x_sum) / noOfCordinates;
    double center_y = double(y_sum) / noOfCordinates;

    Mat d_simg = simg.clone();
    Mat d_timg = timg.clone();

    int pyrdown_num = 3;

    for(int i=0;i<pyrdown_num;i++)
    {
      cv::pyrDown( d_simg, d_simg, cv::Size( d_simg.cols/2, d_simg.rows/2 ));
      cv::pyrDown( d_timg, d_timg, cv::Size( d_timg.cols/2, d_timg.rows/2 ));
    }

    double pyrdown_center_x = center_x / std::pow(2,pyrdown_num);
    double pyrdown_center_y = center_y / std::pow(2,pyrdown_num);
    
    imshow("s image", simg );
    imshow("t image", timg );

    imshow("down s image", d_simg );
    imshow("down t image", d_timg );

    waitKey(0);

    return 0;
}
