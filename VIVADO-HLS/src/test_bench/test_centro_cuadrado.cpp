#include "hls_opencv.h"
#include "hw.h"
#include "image_utils.h"
#include <stdio.h>
#include <time.h>
#include "sw.hpp"

using namespace cv;
using namespace std;


Mat src;
Mat src_aux;
Mat src_aux2;
Mat src_aux3;
vector<Point> measureZone;
vector<Point> aux;
vector<Point> aux2;



int main (int argc, char** argv) {
	src = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
	src_aux = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
	src_aux2 = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
	src_aux3 = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
	Mat img_cornerHarris(src.rows, src.cols, CV_8UC1);
    Mat dst_gray_h(src.rows, src.cols, CV_8UC1);
    Mat dst_gray_h_s(src.rows, src.cols, CV_8UC1);

    IplImage src_hls = src;
    IplImage dst_h_hls = dst_gray_h;
    IplImage dst_gray_h_s_hls = dst_gray_h_s;

    medianBlur_cornerHarris_hw(&src_hls, &dst_h_hls);
    obtencion_coordenadas(&dst_h_hls, &dst_gray_h_s_hls, measureZone2);
    ordena_ptos_hw(measureZone2,aux3);
    calculo_centro_hw(aux3, aux4);
    imwrite(OUTPUT_IMAGE_HW, src_aux3);

    medianBlur_cornerHarris_sw(&src, &img_cornerHarris, measureZone);
    ordena_ptos_sw(measureZone, aux);
    calculo_centro_sw(aux, aux2);
    imwrite(OUTPUT_IMAGE_SW, src_aux2);

    return image_compare(OUTPUT_IMAGE_HW, OUTPUT_IMAGE_SW);

}

