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
    //単色画像の生成(参考:http://opencv.jp/cookbook/opencv_mat.html の 「cv::vecを使う」
    //cv::Mat_<cv::Vec3b> img(300, 300, cv::Vec3b(0,200,0)); // 追加

    // Mat::type()の値 https://koshinran.hateblo.jp/entry/2017/10/30/200250

    mat_infos(img);

    imshow("img", img );
    waitKey(0);

    return 0;
}
