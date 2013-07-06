## Process this file with automake to produce Makefile.in


lib_LTLIBRARIES =  \
	libCVE.la

libCVE_la_SOURCES =  \
	PitchCalc.cc \
	PitchCalc.h \
	Scheduler.cc \
	Scheduler.h \
	Effector/WaveEffector.cc \
	Effector/WaveEffector.h \
	Effector/EnvEffector.cc \
	Effector/EnvEffector.h \
	Effector/Effector.cc \
	Effector/Effector.h \
	Synthesizer/PitchPreSynthesizer.cc \
	Synthesizer/PitchPreSynthesizer.h \
	Synthesizer/ConsecutivePreSynthesizer.cc \
	Synthesizer/ConsecutivePreSynthesizer.h \
	Synthesizer/SpeechSynthesizer.cc \
	Synthesizer/Synthesizer.cc \
	Synthesizer/Synthesizer.h \
	Synthesizer/SpeechSynthesizer.h

libCVE_la_CXXFLAGS = -I@top_srcdir@/src/ \
	-I@top_srcdir@/src/LibCyberBase/ \
	-O2 
