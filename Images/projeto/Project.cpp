#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
    cv::Mat image, lixo, acumulador, media;
    cv::VideoCapture cap(argv[1]);
    int width, height;


    if(!cap.isOpened()){
        std::cout << "Error to load video" << std::endl;
        return -1;
    }

    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    int fourcc = cv::VideoWriter::fourcc('P', 'I', 'M', '1');
    cv::Size framesize(static_cast<int>(width), static_cast<int>(height));
    cv::VideoWriter video("traces.avi",fourcc, 20, framesize, true);

    acumulador = cv::Mat::zeros(height,width, CV_8UC3);

    while(cap.isOpened()){
        cap >> image;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < 3*width; j++){
                acumulador.at<uchar>(i,j) = std::max(acumulador.at<uchar>(i,j), image.at<uchar>(i,j));
            }
        }

        video.write(acumulador);
        if(cap.get(cv::CAP_PROP_POS_FRAMES) == cap.get(cv::CAP_PROP_FRAME_COUNT)) break;
    }

    cap.release();
    video.release();
    
    return 0;
}