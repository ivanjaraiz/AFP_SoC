#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "medianBlur.hpp"

using namespace cv;
int KERNEL_LENGTH = 7;

int main(int argc, char** argv)
{
   namedWindow("img_orig.png" , CV_WINDOW_AUTOSIZE);

   // Load the source image
   Mat src = imread(INPUT_IMAGE, IMREAD_GRAYSCALE);
   // Create a destination Mat object
   Mat dst;

   // display the source image
   imshow("img_orig.png", src);

      // Median smoothing
      medianBlur( src, dst, KERNEL_LENGTH );
      imwrite(OUTPUT_IMAGE_MEDIANBLUR,dst);
      // show the blurred image with the text
      imshow( "Filtro de mediana", dst );

      // wait for 5 seconds
      while( waitKey() != 27) ; //código ASCII de tecla Esc
}