#ifndef _programa_completo_h_
#define _programa_completo_h_
using namespace cv;
using namespace std;

#define INPUT_IMAGE           "img_orig.png"
#define OUTPUT_IMAGE_MEDIANBLUR          "img_medianBlur.png"

#define OUTPUT_IMAGE_CORNERHARRIS_HW "img_cornerHarris_hw.png"
#define OUTPUT_IMAGE_CORNERHARRIS_HW_ "img_cornerHarris_hw_.png"
#define OUTPUT_IMAGE_CORNERHARRIS_SW "img_cornerHarris_sw.png"
#define OUTPUT_IMAGE_CORNERHARRIS_SW_ "img_cornerHarris_sw_.png"
#define OUTPUT_IMAGE_DETECTCORNER "img_detectCorner.png"

extern Mat src;
extern Mat src_aux;
extern Mat src_aux2;
extern Mat src_aux3;
extern vector<Point> measureZone;
extern vector<Point> aux;
extern vector<Point> aux2;
extern vector<Point> measureZone2;
extern vector<Point> aux3;
extern vector<Point> aux4;

void medianBlur(Mat *_src ,Mat *_dst);
void cornerHarris(Mat *_src ,Mat *_dst,vector<Point>& measureZone );
void ordena_ptos_sw(vector<Point>& measureZone, vector<Point>& aux);
void calculo_centro_sw(vector<Point>& aux, vector<Point>& aux2);
void medianBlur_cornerHarris_sw(Mat *_src, Mat *_dst, vector<Point>& measureZone);

void obtencion_coordenadas(IplImage *_src, IplImage *_dst,vector<Point>& measureZone2);
void ordena_ptos_hw(vector<Point>& measureZone2, vector<Point>& aux3);
void calculo_centro_hw(vector<Point>& aux3, vector<Point>& aux4);
#ifdef __cplusplus
extern "C" {
#endif

void medianBlur_cornerHarris_hw(IplImage *src, IplImage *dst);


#ifdef __cplusplus
}
#endif
#endif
