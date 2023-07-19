#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char ** argv){
    cv::Mat codifiedImage, hiddenImage;
    cv::Vec3b codifiedVal, hiddenVal;
    int bitn = 3;
    std::string archivename;

    std::cout << "Digite o nome da imagem codificada: ";
    std::cin >> archivename;

    codifiedImage = cv::imread(archivename, cv::IMREAD_COLOR);
    if(codifiedImage.empty()){
        std::cout << "Imagem nao carregou corretamente" << std::endl;
        return (-1);
    }

    hiddenImage = codifiedImage.clone();

    for(int i = 0; i < codifiedImage.rows; i++){
        for(int j = 0; j < codifiedImage.cols; j++){
            
            codifiedVal = codifiedImage.at<cv::Vec3b>(i,j);
            
            codifiedVal[0] = codifiedVal[0] << (8-bitn);
            codifiedVal[1] = codifiedVal[1] << (8-bitn);
            codifiedVal[2] = codifiedVal[2] << (8-bitn);

            hiddenImage.at<cv::Vec3b>(i,j) = codifiedVal;
        }
    }

    cv::imshow("hiddenimage", hiddenImage);
    cv::waitKey();
    cv::imwrite("hiddenimage.png", hiddenImage);

    return 0;
}