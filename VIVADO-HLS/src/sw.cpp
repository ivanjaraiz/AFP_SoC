#include "hls_opencv.h"
#include "hw.h"
#include "sw.hpp"
#include <time.h>

using namespace cv;
using namespace std;//cout

int thresh = 254;
vector<Point> measureZone2;
vector<Point> aux3;
vector<Point> aux4;

void medianBlur(Mat *_src ,Mat *_dst) {

    Mat src(*_src);
    Mat dst(*_dst);
    unsigned char buffer[9];
    int min;
    int i, j;
    unsigned char aux;
    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            unsigned char p;
            p = src.at<unsigned char>(row, col);

            unsigned char t[9];
            t[8] = buffer[8] = buffer[7];
            t[7] = buffer[7] = buffer[6];
            t[6] = buffer[6] = buffer[5];
            t[5] = buffer[5] = buffer[4];
            t[4] = buffer[4] = buffer[3];
            t[3] = buffer[3] = buffer[2];
            t[2] = buffer[2] = buffer[1];
            t[1] = buffer[1] = buffer[0];
            t[0] = buffer[0] = p;

            for (i = 0; i < 8; i++)
            	{
            	min= i;
            	for(j=i+1;j<=8;j++){
					if(t[j]<t[min]){
						min =j;
					}
		            aux = t[i];
		            t[i] = t[min];
		            t[min] = aux;
            	}
            }
        	   p= t[4];
            dst.at<unsigned char>(row, col) = p;
        }
    }
}

void cornerHarris(Mat *_src ,Mat *_dst,vector<Point>& measureZone ) {

    Mat src_cornerHarris(*_src);
    Mat dst_cornerHarris_norm(*_dst);
    Mat dst_cornerHarris(src.rows, src.cols, CV_8UC1);
    Mat dst_norm_scaled(src.rows, src.cols, CV_8UC1);
    Mat dst_contours(src.rows, src.cols, CV_8UC1);
     // Parámetros del detector
      int blockSize = 3;
      int apertureSize = 3;
      double k = 0.05;
      cornerHarris(src_cornerHarris, dst_cornerHarris, blockSize, apertureSize, k, BORDER_DEFAULT );
      normalize( dst_cornerHarris, dst_cornerHarris_norm, 0, 255,  NORM_MINMAX, CV_32FC1, Mat() );
      convertScaleAbs( dst_cornerHarris_norm, dst_norm_scaled );
      //imshow( "Detector de esquinas", img_cornerHarris_norm );
      for( int j = 0; j < dst_cornerHarris_norm.rows ; j++ )
      { for( int i = 0; i < dst_cornerHarris_norm.cols; i++ )
          {
            if( dst_cornerHarris_norm.at<float>(j,i) > thresh )
              {
               circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
               circle( src, Point( i, j ), 5,  Scalar(125), 2, 8, 0 );
               measureZone.push_back(Point(i,j));
              }
          }
      }
imshow( "Detector de esquinas", dst_norm_scaled );
imwrite(OUTPUT_IMAGE_CORNERHARRIS_SW,dst_norm_scaled);


}

void ordena_ptos_sw(vector<Point>& measureZone, vector<Point>& aux) {
	  aux.push_back(measureZone[0]);
	  aux.push_back(measureZone[1]);
	  aux.push_back(measureZone[3]);
	  aux.push_back(measureZone[2]);
	  cout<<"*Coordenadas_software:"<<endl;
	  cout<<"coordenada_esquina_izquierda_superior"<<aux[0]<<endl;
	  cout<<"coordenada_esquina_derecha_superior"<<aux[1]<<endl;
	  cout<<"coordenada_esquina_izquierda_inferior"<<aux[3]<<endl;
	  cout<<"coordenada_esquina_derecha_inferior"<<aux[2]<<endl;
}



void calculo_centro_sw(vector<Point>& aux, vector<Point>& aux2){
	  aux2.push_back(aux[2]-aux[0]);
	  aux2[0].x= aux2[0].x/2;
	  aux2[0].y= aux2[0].y/2;
	  aux2.push_back(aux2[0]);
	  aux2.push_back(aux2[1]+aux[0]);
	  aux2.push_back(aux2[1]+aux[0]);
	  aux2[3].x= aux2[2].x-4;
	  aux2.push_back(aux2[3]);
	  cout<<"coordenada_central_sin_ajustar"<<aux2[2]<<endl;
	  cout<<"coordenada_central"<<aux2[4]<<endl;    //sacamos coordenada del cuadrado por terminal
	  circle( src, aux2[2], 5,  Scalar(125), 2, 8, 0 );
	  circle( src, aux2[4], 5,  Scalar(240), 2, 8, 0 );
	  circle( src_aux2, aux2[4], 5,  Scalar(240), 2, 8, 0 );
	  imwrite(OUTPUT_IMAGE_CORNERHARRIS_SW_,src);
}

void obtencion_coordenadas(IplImage *_src ,IplImage *_dst,vector<Point>& measureZone2) {


    Mat src_(_src);
    Mat dst_(_dst);
    Mat dst_norm_scaled_(src.rows, src.cols, CV_8UC1);
    normalize(src_, dst_, 0, 255,  NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_, dst_norm_scaled_ );
    for( int j = 0; j < dst_norm_scaled_.rows ; j++ )
       { for( int i = 0; i < dst_norm_scaled_.cols; i++ )
            {
              if(dst_norm_scaled_.at<uchar>(j,i) > thresh )
                {
                  circle( dst_norm_scaled_, Point( i, j ), 5,  Scalar(125), 2, 8, 0 );
                  circle( src_aux, Point( i, j ), 5,  Scalar(125), 2, 8, 0 );
            	  measureZone2.push_back(Point(i,j)); // sacamos coordenadas de las esquinas del cuadrado
                }
            }
      }
	imwrite(OUTPUT_IMAGE_CORNERHARRIS_HW,dst_norm_scaled_);
}
void ordena_ptos_hw(vector<Point>& measureZone2, vector<Point>& aux3) {
	  aux3.push_back(measureZone2[0]);
	  aux3.push_back(measureZone2[1]);
	  aux3.push_back(measureZone2[3]);
	  aux3.push_back(measureZone2[2]);
	  cout<<"*Coordenadas_hardware:"<<endl;
	  cout<<"coordenada_esquina_izquierda_superior"<<aux3[0]<<endl;
	  cout<<"coordenada_esquina_derecha_superior"<<aux3[1]<<endl;
	  cout<<"coordenada_esquina_izquierda_inferior"<<aux3[3]<<endl;
	  cout<<"coordenada_esquina_derecha_inferior"<<aux3[2]<<endl;
}
void calculo_centro_hw(vector<Point>& aux3, vector<Point>& aux4) {
	  aux4.push_back(aux3[2]-aux3[0]);
	  aux4[0].x= aux4[0].x/2;
	  aux4[0].y= aux4[0].y/2;
	  aux4.push_back(aux4[0]);
	  aux4.push_back(aux4[1]+aux3[0]);
	  aux4.push_back(aux4[1]+aux3[0]);
	  aux4[3].x= aux4[2].x-6;
	  aux4[3].y= aux4[2].y+1;
	  aux4.push_back(aux4[3]);
	  cout<<"coordenada_central_sin_ajustar"<<aux4[2]<<endl;
	  cout<<"coordenada_central"<<aux4[4]<<endl;
	  circle( src_aux, aux4[2], 5,  Scalar(125), 2, 8, 0 );
	  circle( src_aux, aux4[4], 5,  Scalar(240), 2, 8, 0 );
	  circle( src_aux3, aux4[4], 5,  Scalar(240), 2, 8, 0 );
	  imwrite(OUTPUT_IMAGE_CORNERHARRIS_HW_,src_aux);
}

void medianBlur_cornerHarris_hw(IplImage* src, IplImage *dst) {
    AXI_STREAM src_axi, dst_axi;
    IplImage2AXIvideo(src, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst);
}

void medianBlur_cornerHarris_sw(Mat *_src, Mat *_dst, vector<Point>& measureZone ) {
	Mat img_medianBlur(src.rows, src.cols, CV_8UC1);
	medianBlur(&*_src, &img_medianBlur);
    imwrite(OUTPUT_IMAGE_MEDIANBLUR, img_medianBlur);
    cornerHarris(&img_medianBlur, &*_dst, measureZone);

}
