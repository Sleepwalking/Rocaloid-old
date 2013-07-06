#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H
class FrameBuffer;
class Synthesizer
{
	public:
		void SetMixRatio(double _MixRatio);
		void SetStartMixRatio(double _MixRatio);
		void SetDestMixRatio(double _MixRatio);

		void FrameMix(FrameBuffer& Frame1, FrameBuffer& Frame2, FrameBuffer& Dest);
		void FrameStretch(FrameBuffer& Frame1, double Ratio, FrameBuffer& Dest);
		void EmptyFrame(FrameBuffer& Dest);
	private:
		double MixRatio;
		double MixRatio2;
};
#endif