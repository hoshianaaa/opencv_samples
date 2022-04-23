#include <opencv2/opencv.hpp>

using namespace cv;




double deg2rad(double degree)
{
  return degree * M_PI / 180;
}

cv::Point2f rotate(cv::Point2f p, double th)
{
  cv::Point2f rp;
  rp.x = std::cos(th) * p.x - std::sin(th) * p.y;
  rp.y = std::sin(th) * p.x + std::cos(th) * p.y;
  return rp;
}

cv::Point rotate(cv::Point p, double th)
{
  cv::Point rp;
  rp.x = std::cos(th) * p.x - std::sin(th) * p.y;
  rp.y = std::sin(th) * p.x + std::cos(th) * p.y;
  return rp;
}

void geomatch_from_center(cv::Point2f temp_points[],int temp_points_num, cv::Mat search_img,cv::Point& result_pos, double& result_angle)
{
return;
}

void geomatch(cv::Point2f temp_points[],int temp_points_num, cv::Mat search_img,cv::Point& result_pos, double& result_angle, double& match_ratio, double d_angle = 0.1, int angle_min = -1, int angle_max = -1, int x_min = -1, int x_max = -1, int y_min = -1, int y_max = -1)
{

  cv::Mat s_img = search_img;

  cv::Point2f *dot;
  dot =  new cv::Point2f[temp_points_num];

  double deg = 0;
  double deg_max_limit = 360;

  if (angle_min != -1)deg = angle_min;
  if (angle_max != -1)deg_max_limit = angle_max;

  int x_region_min = 0;
  int y_region_min = 0;
  int x_region_max = s_img.cols;
  int y_region_max = s_img.rows;

  //std::cout << "*** search image size ***" << std::endl;
  //std::cout << "w:" << x_region_max << std::endl;
  //std::cout << "h:" << y_region_max << std::endl;

  if (x_min != -1)x_region_min = x_min;
  if (y_min != -1)y_region_min = y_min;
  if (x_max != -1)x_region_max = x_max;
  if (y_max != -1)y_region_max = y_max;

  //std::cout << "*** region ***" << std::endl;
  //std::cout << "x:" << x_min << " - " << x_max << std::endl;
  //std::cout << "y:" << y_min << " - " << y_max << std::endl;

  int max_count = 0;
  cv::Point max_pos;
  double max_degree;

  double c1 = temp_points_num;
  double c2 = (deg_max_limit - deg) / d_angle;
  double c3 = x_region_max - x_region_min;
  double c4 = y_region_max - y_region_min;

/*
  std::cout << "temp points num:" << c1 << std::endl;
  std::cout << "angle num:" << c2 << std::endl;
  std::cout << "x num:" << c3 << std::endl;
  std::cout << "y num:" << c4 << std::endl;
*/
  std::cout << "calc cost:" << c1 * c2 * c3 * c4 / 1000000 << std::endl;

  while (deg <= deg_max_limit)
  {

    for (int i = 0; i < temp_points_num; i++)
    {
      dot[i] = rotate(temp_points[i], deg2rad(deg));
    }

    for (int j = y_region_min; j < y_region_max; j++)
    {
        for (int i = x_region_min; i < x_region_max; i++)
        {
          int counter = 0;
          for (int k=0;k<temp_points_num;k++)
           {
            int x = int(dot[k].x + i);
            int y = int(dot[k].y + j);
            if ((x > 0) && (y > 0) && (x < s_img.cols - 1) && ( y < s_img.rows - 1 ))
              if(s_img.at<unsigned char>(y,x) == 255)counter++;
            if ((temp_points_num - k) <= (max_count - counter))break;
           }
           if (counter > max_count)
           {
             max_count = counter;
             max_pos.x = i;
             max_pos.y = j;
             max_degree = deg;
           }
        }
    }
    deg += d_angle;
  }

  result_pos.x = max_pos.x;
  result_pos.y = max_pos.y;
  result_angle = max_degree;
  match_ratio = (double)max_count / temp_points_num;

  std::cout << "*** max pos ***" << std::endl;
  std::cout << "x:" << max_pos.x << std::endl;
  std::cout << "y:" << max_pos.y << std::endl;
  std::cout << "deg:" << max_degree << std::endl;
  std::cout << "count:" << max_count << std::endl;
  std::cout << "match ratio:" << match_ratio << std::endl;

  return;
}

cv::Mat write_points(cv::Point2f points[], int points_num, cv::Mat img, int center_x , int center_y  ,double degree)
{
  cv::Mat ret;
  if (img.type()==CV_8UC1){
    cv::cvtColor(img, ret, cv::COLOR_GRAY2RGB);
  }
  else{
    ret = img.clone();
  }

  for (int i = 0; i < points_num; i++)
  {
    cv::Point2f p =  rotate(points[i], deg2rad(degree));
    int x = p.x + center_x;
    int y = p.y + center_y;


    if ((x > 0) && (y > 0) && (x < img.cols - 1) && ( y < img.rows - 1 ))
    {
      ret.at<cv::Vec3b>(y,x) = cv::Vec3b(0,255,0);
    }
  }
  return ret;
}


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

    int pyrdown_num = 2;

    for(int i=0;i<pyrdown_num;i++)
    {
      cv::pyrDown( d_simg, d_simg, cv::Size( d_simg.cols/2, d_simg.rows/2 ));
      cv::pyrDown( d_timg, d_timg, cv::Size( d_timg.cols/2, d_timg.rows/2 ));
    }

    double pyrdown_center_x = center_x / std::pow(2,pyrdown_num);
    double pyrdown_center_y = center_y / std::pow(2,pyrdown_num);

    int width2 = d_timg.cols;
    int height2 = d_timg.rows;

    int noOfCordinates2 = 0;
    cv::Point2f *coordinates2;
    coordinates2 =  new cv::Point2f[width2 * height2];

    for (int j = 0; j < height2; j++)
    {
        unsigned char *src = d_timg.ptr<unsigned char>(j);
        for (int i = 0; i < width2; i++)
        {
            if(src[i] == 255){
              coordinates2[noOfCordinates2].x = (double)i - pyrdown_center_x;
              coordinates2[noOfCordinates2].y = (double)j - pyrdown_center_y;
              noOfCordinates2++;
            } 
        }
    }

    cv::Point max_pos;
    double max_degree;
    double match_ratio;

    //void geomatch(cv::Point2f temp_points[],int temp_points_num, cv::Mat search_img,cv::Point& result_pos, double& result_angle, double d_angle = 0.1, int angle_min = -1, int angle_max = -1, int x_min = -1, int x_max = -1, int y_min = -1, int y_max = -1)

    geomatch(coordinates2, noOfCordinates2, d_simg, max_pos, max_degree , match_ratio, 2);

    cv::Mat frame = write_points( coordinates2, noOfCordinates2, d_simg, max_pos.x, max_pos.y, max_degree);

    
    imshow("s image", simg );
    imshow("t image", timg );

    imshow("down s image", d_simg );
    imshow("down t image", d_timg );

    imshow("result", frame );

    waitKey(0);

    return 0;
}
