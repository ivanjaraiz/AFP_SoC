

#ifndef _TOP_H_
#define _TOP_H_

#include "hls_video.h"
//#define HW
// maximum image size
#define MAX_WIDTH  400
#define MAX_HEIGHT 388

// I/O Image Settings
#define INPUT_IMAGE           "img_orig.png"
#define OUTPUT_IMAGE_SW          "result_img_orig_sw.png"
#define OUTPUT_IMAGE_HW   "result_img_orig_hw.png"


// typedef video library core structures
typedef hls::stream<ap_axiu<32,1,1,1> >               AXI_STREAM;
typedef hls::Scalar<1, unsigned char>                 PIXEL_C1;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC1>     IMAGE_C1;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_32FC1>     IMAGE_C1_;

// top level function for HW synthesis
void image_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM, int rows, int cols);
void median_filter_core(IMAGE_C1& src, IMAGE_C1& dst, int rows, int cols);

#endif

