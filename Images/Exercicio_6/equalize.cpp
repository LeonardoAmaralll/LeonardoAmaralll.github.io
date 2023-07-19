#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image, imageGray, equalized;
  int width, height;
  cv::VideoCapture cap;
  int key;

	cap.open(0);
  
  if(!cap.isOpened()){
    std::cout << "cameras indisponiveis";
    return -1;
  }
  
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);  
  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "largura = " << width << std::endl;
  std::cout << "altura  = " << height << std::endl;

  while(1){
    cap >> image;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(imageGray, equalized);

    cv::imshow("image", equalized);
    key = cv::waitKey(30);
    if(key == 27) break;
  }
  return 0;
}
