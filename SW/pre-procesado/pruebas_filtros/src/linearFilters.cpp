#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

int main(int argc, char** argv)
{
   namedWindow("img_orig.png" , CV_WINDOW_AUTOSIZE);

   // Load the source image
   Mat src = imread( "/home/ivan/TFG/desarrollo_algoritmo_software/pre-procesado/pruebas_filtros_pre-procesado/img_orig.png", 1);

   // Create a destination Mat object
   Mat dst;

   // display the source image
   imshow("img_orig.png", src);

   for (int i=1; i<50; i=i+2)
   { 
      // smooth the image in the "src" and save it to "dst"
       blur(src, dst, Size(i,i));
       imshow( "blur", dst );
       //imwrite("img_blur7.png",dst);

      // Gaussian smoothing
       GaussianBlur( src, dst, Size( i, i ), 0, 0 );
       imshow( "GaussianBlur", dst );
       imwrite("img_GaussianBlur7.png",dst);

      // Median smoothing
      medianBlur( src, dst, i );
      

      // show the blurred image with the text
      imshow( "Filtro de mediana", dst );

      // wait for 5 seconds
      while( waitKey() != 27) ; //código ASCII de tecla Esc
   }
}
