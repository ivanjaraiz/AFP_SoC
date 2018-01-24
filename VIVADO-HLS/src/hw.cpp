#include "hw.h"
using namespace hls;
void median_filter_core(IMAGE_C1& src, IMAGE_C1& dst, int rows, int cols) {
    int min;
    int i, j;
    unsigned char aux;
    unsigned char aux2;
    PIXEL_C1 buffer[9];
    assert(rows <= MAX_HEIGHT);
    assert(cols <= MAX_WIDTH);
    for(int row = 0; row < rows; row++) {
       for(int col = 0; col < cols; col++) {
#pragma HLS pipeline II=1
    	   PIXEL_C1 p;
            src >> p;
            PIXEL_C1 t[9];
            t[8] = buffer[8] = buffer[7];
            t[7] = buffer[7] = buffer[6];
            t[6] = buffer[6] = buffer[5];
            t[5] = buffer[5] = buffer[4];
            t[4] = buffer[4] = buffer[3];
            t[3] = buffer[3] = buffer[2];
            t[2] = buffer[2] = buffer[1];
            t[1] = buffer[1] = buffer[0];
            t[0] = buffer[0] = p;
            for (i = 0; i < 5; i++)
            	{
            	min= i;// primera posición de arreglo al que se va
            	for(j=i+1;j<=8;j++){//comienza a revisar los  números restantes
					if(t[j].val[0]<t[min].val[0]){//comparar si el elemento mínimo es el menor de todos lo elementos
						min =j;
					}
		            aux = t[i].val[0]; //se realiza intercambio entre el valor mínimo y primera posición
		            t[i] = t[min];
		            t[min].val[0] = aux;
            	}
            }
        	   p= t[4];
        	   dst << p;
        }

      }
}
void image_filter(AXI_STREAM& video_in, AXI_STREAM& video_out, int rows, int cols) {
    //Create AXI streaming interfaces for the core
#pragma HLS INTERFACE axis port=video_in bundle=INPUT_STREAM
#pragma HLS INTERFACE axis port=video_out bundle=OUTPUT_STREAM

#pragma HLS INTERFACE s_axilite port=rows bundle=CONTROL_BUS offset=0x14
#pragma HLS INTERFACE s_axilite port=cols bundle=CONTROL_BUS offset=0x1C
#pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS

#pragma HLS INTERFACE ap_stable port=rows
#pragma HLS INTERFACE ap_stable port=cols
	IMAGE_C1 img_0(rows, cols);
	IMAGE_C1 img_1(rows, cols);
	IMAGE_C1_ img_2(rows, cols);
    hls::AXIvideo2Mat(video_in, img_0);
    median_filter_core(img_0, img_1,rows,cols);//Filtro de Mediana
    CornerHarris<4,5>(img_1, img_2, 0.04);
    hls::Mat2AXIvideo(img_2, video_out);
}

