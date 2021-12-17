#include<opencv2/opencv.hpp>

int main()
{
    //グレースケールで画像を読み込む
    cv::Mat img = cv::imread("images/template.jpg", 0);
    cv::Mat img_c, img_l, img_s_x, img_s_y, img_s;

    cv::Canny(img, img_c, 125, 255);

    cv::imshow("Canny", img_c);
    cv::waitKey(0);

    return 0;
}

