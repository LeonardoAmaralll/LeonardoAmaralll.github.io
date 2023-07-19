#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
  cv::Mat image;
  int width, height;
  int nobjects, nbubbles, nopen;
  bool open;

  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "imagem nao carregou corretamente\n";
    return (-1);
  }

  width = image.cols;
  height = image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x = 0;
  p.y = 0;

  ////////////Border Objects Remover//////////////
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255 && (i == 0 || j == 0 || i == height-1 || j == width-1)){
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, 0);
      }
    }
  }

  p.x = 0;
  p.y = 0;
  cv::floodFill(image, p, 127);

  // busca objetos presentes
  nobjects = 0;
  nbubbles = 0;
  nopen = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255) {
        nobjects++;
        // x e y são trocadas.
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, 254);
        open = false;
        for (int i = p.y; i < height; i++) {
            for (int j = p.x; j < width; j++) {
                if(image.at<uchar>(i, j) == 0 && image.at<uchar>(i, j-1) < 254){
                    nopen++;
                    p.x = j;
                    p.y = i;
                    cv::floodFill(image, p, 1);
                    open = true;
                }
                if(open) break;
            }
            if(open) break;
        }
        if(open == false) nbubbles++;
      }
    }
  }
  std::cout << "a figura tem " << nobjects << " bolhas" << std::endl;
  std::cout << "com " << nopen << " bolhas com buracos" << std::endl;
  std::cout << "e " << nbubbles << " bolhas sem buracos" << std::endl;
  cv::imshow("image", image);
  cv::imwrite("improvedlabelling.png", image);
  cv::waitKey();
  return 0;
}
