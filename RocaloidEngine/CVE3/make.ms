set_exec ./cve3
set_tmp /tmp/cve3build
set_cflags -O3 -lm
set_lflags -Wl -lm -L ../../CVEDSP -lCVEDSP
set_gcc gcc
set_g++ g++
ccdir .
ccdir ./RUtil
ccdir ./RUtil/IO
ccdir ./RUtil/Misc
ccdir ./RUtil/Structure
ccdir ./Debug
ccdir ./DSPEx
ccdir ./Synthesizer
ccdir ./RFILE3
ccdir ./RFILE3/CDT3
ccdir ./RFILE3/CVDB3
ccdir ./RFILE3/CVS3
link

