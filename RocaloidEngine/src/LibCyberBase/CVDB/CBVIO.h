#ifndef CBVIO_H
#define CBVIO_H

class CVDBContainer;
class string;
class binaryStream;
namespace CBVFile
{
	extern binaryStream fStream;
	extern string DataDir;
	
	bool Open(string FileName, CVDBContainer& Dest);
	bool Save(string FileName, CVDBContainer& Source);

	void OpenCVDB05(CVDBContainer& Dest);
	void OpenCVDB06(CVDBContainer& Dest);
}

#endif