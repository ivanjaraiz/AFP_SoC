#ifndef _programa_completo_h_
#define _programa_completo_h_
using namespace cv;
using namespace std;

#define INPUT_IMAGE           "img_orig.png"
#define OUTPUT_IMAGE_MEDIANBLUR          "img_medianBlur.png"

#define OUTPUT_IMAGE_CORNERHARRIS "img_cornerHarris.png"
#define OUTPUT_IMAGE_DETECTCORNER "img_detectCorner.png"
#define OUTPUT_IMAGE_DETECTCORNER_CENTREPOINT "img_detectCorner_centrepoint.png"
#define OUTPUT_IMAGE_CENTREPOINT "img_centrepoint.png"

void medianBlur(Mat *_src ,Mat *_dst);
void cornerHarris(Mat *_src ,Mat *_dst,vector<Point>& measureZone ); 
void ordena_ptos_sw(vector<Point>& measureZone, vector<Point>& aux);
void calculo_centro_sw(vector<Point>& aux, vector<Point>& aux2);
#endif
