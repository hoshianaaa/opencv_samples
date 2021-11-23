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
    Sobel(img, gx, CV_16S, 1, 0, 3, 1);
    Sobel(img, gy, CV_16S, 0, 1, 3, 1);

    //絶対値を計算し符号なし8-bitへ変換(参考: https://stackoverflow.com/questions/17815690/compute-absolute-values-of-x-and-y-derivatives-using-opencv)
    //convertScaleAbs(gx, gx);
    //convertScaleAbs(gy, gy);

    mat_infos(gx);

    imshow("gx", gx );
    imshow("gy", gy );

    waitKey(0);

    return 0;
}
