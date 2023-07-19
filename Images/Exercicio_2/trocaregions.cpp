#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image;
  cv::Vec3b val;

  image = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu imagem" << std::endl;

  cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("trocada", cv::WINDOW_AUTOSIZE);

  int rows = image.rows;
  int cols = image.cols;

  cv::imshow("original", image);  

  cv::Mat image2(rows, cols, CV_8U);

  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(i < rows/2 && j <= cols/2){
        image2.at<uchar>(i,j)=image.at<uchar>((rows/2) + i,(cols/2) + j);
      }
      if(i > rows/2 && j <= cols/2){
        image2.at<uchar>(i,j)=image.at<uchar>(i - (rows/2),(cols/2) + j);
      }
      if(i < rows/2 && j > cols/2){
        image2.at<uchar>(i,j)=image.at<uchar>((rows/2) + i,j - (cols/2));
      }
      if(i > rows/2 && j > cols/2){
        image2.at<uchar>(i,j)=image.at<uchar>(i - (rows/2),j - (cols/2));
      }
    }
  }

  cv::imshow("trocada", image2);  
  cv::waitKey();

  return 0;
}