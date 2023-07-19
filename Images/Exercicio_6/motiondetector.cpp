#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>

int main(int argc, char** argv){
  cv::Mat image;
  int width, height;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes;
  cv::Mat histB, histB2;
  int control, counter;
  float diff;
  bool enabler;
  int nbins = 64;
  float range[] = {0, 255};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
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

  int histw = nbins, histh = nbins/2;
  cv::Mat histImgB(histh, histw, CV_8UC3, cv::Scalar(0,0,0));

  enabler = false;

  while(1){
    cap >> image;
    cv::split (image, planes);
    cv::calcHist(&planes[0], 1, 0, cv::Mat(), histB, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    
    counter = 0;
    control = 0;

    if(enabler == true){
        for(int i = 0; i < nbins; i++){
            float max = std::max(histB.at<float>(i), histB2.at<float>(i));
            float min = std::min(histB.at<float>(i), histB2.at<float>(i));
            diff = min/max;
            if(abs(diff) <= 0.9) counter++;
        }
    }

    if(counter >= nbins/2) control = 1;

    histB2 = histB.clone();
    
    for(int i=0; i<nbins; i++){
      cv::line(histImgB,
               cv::Point(i, histh),
               cv::Point(i, 0),
               cv::Scalar(255*control, 255*control, 255*control), 1, 8, 0);
    }
    histImgB.copyTo(image(cv::Rect(0, 0 ,nbins, histh)));
    cv::imshow("image", image);
    enabler = true;
    key = cv::waitKey(30);
    if(key == 27) break; 
  }

  return 0;
}
