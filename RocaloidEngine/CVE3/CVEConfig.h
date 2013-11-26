//CVE Compile Configuration

//Width of formants in LCFECSOLA.
#define LCFECSOLA_L0 1000
#define LCFECSOLA_L1 1000
#define LCFECSOLA_L2 1000
#define LCFECSOLA_L3 2000

//The minimum formant strength in LCFECSOLA.
#define LCFECSOLA_SMinimum 0.03

//Any signal above this frequency will not be processed by LCFECSOLA.
#define LCFECSOLA_ResidualFreq 5000

//Length before the end of wave involved in cycle (uint: periods)
#define CSynth_CycleTail 30

//Position where wave loop starts (unit: samples).
#define CSynth_CycleDelay 15000

//Length of wave loop (unit: samples).
#define CSynth_CycleSample 20000

//[Debug Use] 0: maintain spectral envelope in FSynth, 1: Only resample in FSynth.
#define FSynth_SkipSynth 0

//Enable LCFECSOLA in FSynth, otherwise use FECSOLA.
#define FSynth_LCEnabled

//Length of samples to be smoothly transitted before VOT.
#define FSynth_ConsonantTransition 1000

//[Debug Use] 0: Use both FSynths in PitchMixer, 1: Only use one FSynth in PitchMixer.
#define PitchMixer_SkipSynth 0

//Enable LCFECSOLA in PitchMixer, otherwise use FECSOLA.
#define PitchMixer_LCEnabled

//Any pitch transition undergone whoose rate is above this value will be based on the results from both FSynths.
#define PitchMixer_TransitionRatio 0.3

//[Debug Use] 0: Use both PitchMixers in SpeechMixer, 1: Only use one PitchMixer in SpeechMixer.
#define SpeechMixer_SkipSynth 0

//Refer to CDT TransitionLayer when mixing phones.
#define SpeechMixer_TransitionLayerEnabled 0

//Use LCFECSOLA transition in SpeechMixer
#define SpeechMixer_FECSOLA

//Use Linear transition in SpeechMixer
//#define SpeechMixer_Linear
