#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image;
  cv::Vec3b val;

  image = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu imagem" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  int x1, y1, x2, y2;

  std::cout << "Coordenadas x1, x2, y1 e y2: " << std::endl;
  std::cin >> x1 >> x2 >> y1 >> y2;

  for(int i = x1; i <= x2; i++){
    for(int j = y1; j <= y2; j++){
      image.at<uchar>(i,j)=255 - image.at<uchar>(i,j);
    }
  }

  cv::imshow("janela", image);  
  cv::waitKey();
  return 0;
}