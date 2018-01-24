
#include "opencv2/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/highgui.hpp"
#include "app_soft.hpp"
#include <time.h>
#include "cv.h"
#include "highgui.h"

using namespace cv;
using namespace std;

#define TIME_MEDIAMBLUR(X)                                         \
  {                                                          \
    struct timespec ts1, ts2;                                \
    clock_gettime( CLOCK_REALTIME, &ts1 );                   \
    X;                                                       \
    clock_gettime( CLOCK_REALTIME, &ts2 );                   \
    printf( #X "time_medianBlur: %f segundos\n",                              \
      (float) ( 1.0*(1.0*ts2.tv_nsec - ts1.tv_nsec*1.0)*1e-9 \
      + 1.0*ts2.tv_sec - 1.0*ts1.tv_sec ) );                 \
  }

  #define TIME_CORNERHARRIS(X)                                         \
  {                                                          \
    struct timespec ts1, ts2;                                \
    clock_gettime( CLOCK_REALTIME, &ts1 );                   \
    X;                                                       \
    clock_gettime( CLOCK_REALTIME, &ts2 );                   \
    printf( #X "time_cornerHarris: %f segundos\n",                              \
      (float) ( 1.0*(1.0*ts2.tv_nsec - ts1.tv_nsec*1.0)*1e-9 \
      + 1.0*ts2.tv_sec - 1.0*ts1.tv_sec ) );                 \
  }

Mat src;
Mat src_aux;
int thresh = 220;
vector<Point> aux;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
vector<Point> aux2;
vector<Point> measureZone;

int main (int argc, char** argv) {

src = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
src_aux = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
Mat img_medianBlur(src.rows, src.cols, CV_8UC1);
Mat img_cornerHarris(src.rows, src.cols, CV_8UC1);
imshow("img_orig.png", src);
TIME_MEDIAMBLUR(medianBlur(&src, &img_medianBlur));//mediana
imshow( "Filtro de Mediana", img_medianBlur );
imwrite(OUTPUT_IMAGE_MEDIANBLUR,img_medianBlur);
cornerHarris(&img_medianBlur, &img_cornerHarris, measureZone);
imwrite(OUTPUT_IMAGE_DETECTCORNER,src);
ordena_ptos_sw(measureZone, aux);
calculo_centro_sw(aux, aux2);
imshow( "Esquinas detectadas y centro", src );
imwrite(OUTPUT_IMAGE_DETECTCORNER_CENTREPOINT,src);
imwrite(OUTPUT_IMAGE_CENTREPOINT,src_aux);

while( waitKey() != 27) ; //código ASCII de tecla Esc
}
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
            	min= i;// primera posición de arreglo al que vamos
            	for(j=i+1;j<=8;j++){//comienza a revisar los  números restantes
					if(t[j]<t[min]){//comparar si el elemento mínimo es el menor de todos lo elementos
						min =j;
					}
		            aux = t[i]; //se realiza intercambio entre el valor mínimo y primera posición
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
      double k = 0.02;
      TIME_CORNERHARRIS(cornerHarris(src_cornerHarris, dst_cornerHarris, blockSize, apertureSize, k, BORDER_DEFAULT ));
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
findContours( dst_norm_scaled, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );      
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( dst_contours, contours, idx, color, CV_FILLED, 8, hierarchy );
    }
imshow( "Detector de esquinas", dst_norm_scaled );
imshow( "Contornos detectados", dst_contours );
imwrite(OUTPUT_IMAGE_CORNERHARRIS,dst_norm_scaled);

}
void ordena_ptos_sw(vector<Point>& measureZone, vector<Point>& aux) { 

      aux.push_back(measureZone[0]);
      aux.push_back(measureZone[1]);
      aux.push_back(measureZone[3]);
      aux.push_back(measureZone[2]);
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
      circle( src, aux2[2], 5,  Scalar(125), 2, 8, 0 );
      circle( src, aux2[4], 5,  Scalar(240), 2, 8, 0 );
      circle( src_aux, aux2[4], 5,  Scalar(240), 2, 8, 0 );
      cout<<"coordenada_central_sin_ajustar"<<aux2[2]<<endl; 
      cout<<"coordenada_central"<<aux2[4]<<endl;    //sacamos coordenada del cuadrado por terminal
      imshow( "centro_cuadrado_software", src );
      imshow( "centro_cuadrado_software", src_aux );


}
