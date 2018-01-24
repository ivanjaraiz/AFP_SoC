#include "opencv2/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/highgui.hpp"
#include "cornerHarris.hpp"

using namespace cv;
using namespace std;

//median
int KERNEL_LENGTH = 7;
//harris
int blockSize = 3;
int apertureSize = 3;
double k = 0.05;

int thresh = 200;

int main(int argc, char** argv)
{
   namedWindow("img_orig.png" , CV_WINDOW_AUTOSIZE);

   // Load the source image
   Mat src = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
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
      imwrite(OUTPUT_IMAGE_MEDIANBLUR, img_medianBlur);

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
                   
              }
          }
      }
      imshow( "Detector de esquinas", dst_norm_scaled );
      imwrite(OUTPUT_IMAGE_CORNERHARRIS,dst_norm_scaled);
      imshow( "Esquinas detectadas", src );
      imwrite(OUTPUT_IMAGE_DETECTCORNER,src);

      // wait for 5 seconds
      while( waitKey() != 27) ; //código ASCII de tecla Esc
}