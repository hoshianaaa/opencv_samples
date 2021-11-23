#include <opencv2/opencv.hpp>

using namespace cv;

void mat_infos(Mat img)
{
  std::cout << "rows:" << img.rows << std::endl;
  std::cout << "cols:" << img.cols << std::endl;
  std::cout << "type:" << img.type() << std::endl;

  return;
}

int main(int argc, const char * argv[])
{
    Mat img = imread( "images/template.jpg" );

    mat_infos(img);

    imshow("img", img );

    Mat gx,gy;
    Sobel(img, gx, CV_16S, 1, 0);
    Sobel(img, gy, CV_16S, 0, 1);

    mat_infos(gx);

    imshow("gx", gx );
    imshow("gy", gy );

    waitKey(0);

    return 0;
}
