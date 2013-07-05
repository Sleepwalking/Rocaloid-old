#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
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
	private:
		int Size;
};
inline int FrameBuffer::GetSize()
{
	return Size;
}
#endif