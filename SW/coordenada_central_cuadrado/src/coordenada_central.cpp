#include "opencv2/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/highgui.hpp"
#include "centrePoint.hpp"

using namespace cv;
using namespace std;

//median
int KERNEL_LENGTH = 7;
//harris
int blockSize = 3;
int apertureSize = 3;
double k = 0.05;

int thresh = 200;

vector<Point> measureZone;
vector<Point> aux;
vector<Point> aux2;

int main(int argc, char** argv)
{
   namedWindow("img_orig.png" , CV_WINDOW_AUTOSIZE);

   // Load the source image
   Mat src = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
   Mat src_aux = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
   // Create a destination Mat object
   Mat img_medianBlur;
   Mat img_cornerHarris;
   Mat img_cornerHarris_norm;
   Mat dst_norm_scaled;
   Mat dst;


   // display the source image
   imshow("img_orig.png", src);

      // Median smoothing
      medianBlur( src, img_medianBlur, KERNEL_LENGTH );
      // show the blurred image with the text
      imshow( "Filtro de mediana", img_medianBlur );
      imwrite(OUTPUT_IMAGE_MEDIANBLUR,img_medianBlur);

      cornerHarris(img_medianBlur, img_cornerHarris, blockSize, apertureSize, k, BORDER_DEFAULT );
      normalize( img_cornerHarris, img_cornerHarris_norm, 0, 255,  NORM_MINMAX, CV_32FC1, Mat() );
      convertScaleAbs( img_cornerHarris_norm, dst_norm_scaled );
      //imshow( "Detector de esquinas", img_cornerHarris_norm );
      for( int j = 0; j < img_cornerHarris_norm.rows ; j++ )
      { for( int i = 0; i < img_cornerHarris_norm.cols; i++ )
          {
            if( img_cornerHarris_norm.at<float>(j,i) > thresh )
              {
               circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
               circle( src, Point( i, j ), 5,  Scalar(125), 2, 8, 0 );
               measureZone.push_back(Point(i,j));    
              }
          }
      }
      imshow( "Detector de esquinas", dst_norm_scaled );
      imwrite(OUTPUT_IMAGE_CORNERHARRIS,dst_norm_scaled);
      imshow( "Esquinas detectadas", src );
      imwrite(OUTPUT_IMAGE_DETECTCORNER,src);

      aux.push_back(measureZone[0]);
      aux.push_back(measureZone[1]);
      aux.push_back(measureZone[3]);
      aux.push_back(measureZone[2]);
      cout<<"coordenada_esquina_izquierda_superior"<<aux[0]<<endl;   
      cout<<"coordenada_esquina_derecha_superior"<<aux[1]<<endl; 
      cout<<"coordenada_esquina_izquierda_inferior"<<aux[3]<<endl; 
      cout<<"coordenada_esquina_derecha_inferior"<<aux[2]<<endl; 


      aux2.push_back(aux[2]-aux[0]);
      aux2[0].x= aux2[0].x/2;
      aux2[0].y= aux2[0].y/2;
      aux2.push_back(aux2[0]);
      aux2.push_back(aux2[1]+aux[0]);
      cout<<"coordenada_central"<<aux2[2]<<endl;
      circle( src_aux, aux2[2], 5,  Scalar(125), 2, 8, 0 ); 
      imshow( "centro detectado", src_aux );
      imwrite(OUTPUT_IMAGE,src_aux);
      // wait for 5 seconds
      while( waitKey() != 27) ; //código ASCII de tecla Esc
}