#ifndef CBVIO_H
#define CBVIO_H

class CVDBContainer;
class string;
class binaryStream;
class memoryStream;
namespace CBVFile
{
	extern void* buffer;
	extern memoryStream* mStream;
	extern binaryStream fStream;
	extern string DataDir;
	
	bool Open(string FileName, CVDBContainer& Dest);
	bool Save(string FileName, CVDBContainer& Source);

	void OpenCVDB05(CVDBContainer& Dest);
	void OpenCVDB06(CVDBContainer& Dest);
}

#endif