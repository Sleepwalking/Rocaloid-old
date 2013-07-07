#ifndef PITCHCALC_H
#define PITCHCALC_H
#include "LibCyberBase/Overall.h"

using namespace Overall;
class string;
class PitchCalculator
{
	public:
		PitchCalculator();

		void PitchCalc(double Time);
		double GetFreqAt(double Time);

		void Restore();
		void SetTarget(double _StartFreq, double _StartTime, double _TargetFreq, double _TargetTime);
		void SetResolution(double _TimeResolution);
		string GetLowPitch();
		string GetHighPitch();
		double GetTransitionRatio();
		double GetCurrentFreq();
		bool DirectionIsUp();

		static int GetPitch(double Freq);
		static int GetFloorPitch(double Freq);
	private:
		double TargetFreq;
		double TargetTime;
		double StartFreq;
		double StartTime;
		double TimeResolution;
		int LowPitch;
		int HighPitch;
		double TransitionRatio;
		double CurrentFreq;
};
#endif