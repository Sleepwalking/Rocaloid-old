#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#define FrameBufferInitialSize 1000
class FrameBuffer
{
	public:
		double* Data;

		FrameBuffer();
		FrameBuffer(int _Size);
		~FrameBuffer();

		int Ubound;

		void Resize(int _Size);
		inline int GetSize();

		FrameBuffer& operator =(FrameBuffer& Source);
	protected:
		int Size;
};
inline int FrameBuffer::GetSize()
{
	return Size;
}
#endif