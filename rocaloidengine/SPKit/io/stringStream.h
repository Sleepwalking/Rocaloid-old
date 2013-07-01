#ifndef STRINGSTREAM_H
#define STRINGSTREAM_H

class string;
class stringStream: public memoryStream
{
	public:	
		template <class T> stringStream(T* ptr);

		string readWord();
		string readLine();
		string readAll();
		void skipWord();
		void skipLine();

		#define nextLine() skipLine()
		void prevLine();

		inline void writeLine(string data);
};
inline void stringStream::writeLine(string data)
{
	write(data + "\n");
}
void split(string& source, array<string>& dest);
#endif