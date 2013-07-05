#ifndef MULTIFRAMEBUFFER_H
#define MULTIFRAMEBUFFER_H
class FrameBuffer;
class MultiFrameBuffer
{
	public:
		FrameBuffer** Data;

		MultiFrameBuffer();
		MultiFrameBuffer(int _Size);
		MultiFrameBuffer(int _Size, int _InnerSize);
		~MultiFrameBuffer();

		int Ubound;

		void Resize(int _Size);
		inline int GetSize();
	private:
		int Size;
};
inline int MultiFrameBuffer::GetSize()
{
	return Size;
}
#endif