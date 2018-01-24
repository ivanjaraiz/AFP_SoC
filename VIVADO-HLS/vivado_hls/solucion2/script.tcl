############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project centro_cuadrado.prj
set_top image_filter
add_files src/hw.cpp
add_files -tb src/test_centro_cuadrado.cpp
add_files -tb src/sw.cpp
add_files -tb img_orig.png
open_solution "solucion1_sin_directivas_10ns"
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
#source "./centro_cuadrado.prj/solucion1_sin_directivas_10ns/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
