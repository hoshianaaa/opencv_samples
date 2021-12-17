#include<opencv2/opencv.hpp>

int main()
{
    //グレースケールで画像を読み込む
    cv::Mat img = cv::imread("images/template.jpg", 0);
    cv::Mat img_c, img_l, img_s_x, img_s_y, img_s;
    //Canny法を用いてエッジ検出
    //閾値は0 ~ 255で任意で決める
    //第１引数が入力, 第2引数が出力
    cv::Canny(img, img_c, 125, 255);

    //Laplacianでエッジ検出
    //第3引数は検出範囲
    cv::Laplacian(img, img_l, 3);
    cv::convertScaleAbs(img_l, img_l, 1, 0);
    //2値化
    cv::threshold(img_l, img_l, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

    //Sobelでエッジ検出
    //x, y方向の微分
    cv::Sobel(img, img_s_x, CV_8UC1, 1, 0, 3);
    cv::Sobel(img, img_s_y, CV_8UC1, 0, 1, 3);
    //x, y方向に微分をした画像を合成
    img_s = abs(img_s_x) + abs(img_s_y);
    cv::convertScaleAbs(img_s, img_s, 1, 0);
    //2値化
    cv::threshold(img_s, img_s, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

    //画像の保存と出力
    cv::imshow("Canny", img_c);
    cv::imshow("Laplace", img_l);
    cv::imshow("Sobel", img_s);
    cv::waitKey(0);

    return 0;
}

