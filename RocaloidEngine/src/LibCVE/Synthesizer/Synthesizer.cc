#include "Synthesizer.h"
#include "LibCyberBase/FrameBuffer.h"
#include "LibCyberBase/Overall.h"

void Synthesizer::SetMixRatio(double _MixRatio)
{
	MixRatio = _MixRatio;
	MixRatio2 = _MixRatio;
}
void Synthesizer::SetStartMixRatio(double _MixRatio)
{
	MixRatio = _MixRatio;
}
void Synthesizer::SetDestMixRatio(double _MixRatio)
{
	MixRatio2 = _MixRatio;
}

void Synthesizer::FrameMix(FrameBuffer& Frame1, FrameBuffer& Frame2, FrameBuffer& Dest)
{
	int i;
	int Len1, Len2;
	double TransitionRatio;
	double InstantaneousRatio;
	Len1 = Frame1.Ubound;
	Len2 = Frame2.Ubound;
	Dest.Ubound = (int)(((double)Len1) * (1 - MixRatio) + ((double)Len2) * MixRatio);
	if(Dest.Ubound <= 0)
		Overall::Exception("Len <= 0 in FrameMix.");
	for(i = 0;i <= Dest.Ubound;i ++)
	{
		TransitionRatio = ((double)i) / Dest.Ubound;
		InstantaneousRatio = MixRatio * (1 - TransitionRatio) + MixRatio2 * TransitionRatio;
		Dest.Data[i] = Frame1.Data[(int)(TransitionRatio * Len1)] * (1 - InstantaneousRatio)
					 + Frame2.Data[(int)(TransitionRatio * Len2)] * InstantaneousRatio;
	}
}
void Synthesizer::FrameStretch(FrameBuffer& Frame, double Ratio, FrameBuffer& Dest)
{
	int i;
	int Len;
	Len = Frame.Ubound;
	Dest.Ubound = (int)((double)(Len) * Ratio);
	for(i = 0;i <= Dest.Ubound;i ++)
	{
		Dest.Data[i] = Frame.Data[(int)(((double)i) * Ratio)];
	}
}
void Synthesizer::EmptyFrame(FrameBuffer& Dest)
{
	Dest.Ubound = 0;
}