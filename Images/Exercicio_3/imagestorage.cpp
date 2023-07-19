#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <fstream>

int SIDE = 256;
int PERIODOS = 4;

int main(int argc, char** argv) {
  std::stringstream ss_img, ss_yml;
  cv::Mat image;

  ss_yml << "senoide-" << SIDE << ".yml";
  image = cv::Mat::zeros(SIDE, SIDE, CV_32FC1);

  cv::FileStorage fs(ss_yml.str(), cv::FileStorage::WRITE);

  for (int i = 0; i < SIDE; i++) {
    for (int j = 0; j < SIDE; j++) {
      image.at<float>(i, j) = 63 * sin(2 * M_PI * PERIODOS * j / SIDE) + 64;
    }
  }

  fs << "mat" << image;
  fs.release();
  
  float diff[SIDE];
////////ofstream ymp//////////////////////////
  std::ofstream outfile("sen-ymp.txt");
  for(int i = 0; i < SIDE; i++){
    outfile << i << " " << image.at<float>(SIDE/2, i) << std::endl;
    diff[i] = image.at<float>(SIDE/2, i);
  }
  
  outfile.close();
////////////////////////////////////////////////
  image.convertTo(image, CV_8U);
////////////ofstream png//////////////////////////////
  std::ofstream outfile2("sen-png.txt");
  for(int i = 0; i < SIDE; i++){
    outfile2 << i << " " << int(image.at<uchar>(SIDE/2, i)) << std::endl;
    diff[i] = diff[i] - int(image.at<uchar>(SIDE/2, i));
  }
  
  outfile2.close();
//////////////////////////

  cv::normalize(image, image, 0, 255, cv::NORM_MINMAX);
  
  ss_img << "senoide-" << SIDE << ".png";
  cv::imwrite(ss_img.str(), image);


  fs.open(ss_yml.str(), cv::FileStorage::READ);
  fs["mat"] >> image;

  cv::normalize(image, image, 0, 255, cv::NORM_MINMAX);
  image.convertTo(image, CV_8U);

  cv::imshow("image", image);
  cv::waitKey();

////////////ofstream difference//////////////////////////////
  std::ofstream outfile3("sen-difference.txt");
  for(int i = 0; i < SIDE; i++){
    outfile3 << i << " " << abs(diff[i]) << std::endl;
  }
  
  outfile3.close();
//////////////////////////

  return 0;
}
