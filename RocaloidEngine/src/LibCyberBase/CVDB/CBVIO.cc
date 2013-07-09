#include "CBVIO.h"
#include "SPKit/defs.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/converter.h"
#include "SPKit/misc/memopr.h"
#include "SPKit/io/fileStream.h"
#include "SPKit/io/memoryStream.h"
#include "SPKit/io/terminal.h"

#include "CVDB.h"
#include "MultiFrameBuffer.h"
#include "FrameBuffer.h"
using namespace converter;

void* CBVFile::buffer;
binaryStream CBVFile::fStream;
memoryStream* CBVFile::mStream;
string CBVFile::DataDir;

bool CBVFile::Open(string FileName, CVDBContainer& Dest)
{
	bool OpenState = fStream.open(DataDir + FileName, READONLY);
	if(! OpenState)
		return false;

	buffer = mem_malloc(fStream.getLength());
	mStream = new memoryStream(buffer);
	fStream.readBuffer(buffer, fStream.getLength());
	
	char* CVDBChars = new char[5];
	string CVDBStr;

	mStream -> readBuffer(CVDBChars, 4);
	CVDBChars[4] = 0;
	CVDBStr = CVDBChars;

	if(CVDBStr != "CVDB")
	{
		fStream.close();
		mem_free(buffer);
		delete mStream;
		return false;
	}
	
	Dest.Info.Version = mStream -> readShort();
	Dest.SetName(left(FileName, FileName.getLength() - 4));

	if(Dest.Info.Version == 1)
		OpenCVDB05(Dest);
	else if(Dest.Info.Version == 2)
		OpenCVDB06(Dest);
	else
	{
		fStream.close();
		mem_free(buffer);
		delete mStream;
		return false;
	}

	delete []CVDBChars;
	fStream.close();
	mem_free(buffer);
	delete mStream;
	return true;
}

void CBVFile::OpenCVDB05(CVDBContainer& Dest)
{
	Dest.Info.Consonant = (mStream -> readByte() == 255);
	Dest.Info.StartPosition = mStream -> readInt();
	Dest.Info.PeriodStartPosition = Dest.Info.StartPosition; //Fill up
	Dest.Info.AveragePeriod = mStream -> readInt();
	mStream -> setPosition(256); //Skip Information

	int DataSize = fStream.getLength() - mStream -> getPosition();
	int DataNum = DataSize / 2 - 3000; //Safe limit for stability
	int PeriodCount, SampleCount, DataCount;
	short int TmpData;

	PeriodCount = 0; SampleCount = 0; DataCount = 0;
	while(DataCount < DataNum)
	{
		TmpData = mStream -> readShort();
		if(TmpData == 32766 || TmpData == 32767)
		{
			Dest.Buffer -> Data[PeriodCount] -> Ubound = SampleCount;
			DataCount += SampleCount + 1;
			PeriodCount ++;
			SampleCount = 0;
			if(TmpData == 32767)
				break;
			else
				continue;
		}
		//TmpData != 32766 or 32767, Normal Data
		Dest.Buffer -> Data[PeriodCount] -> Data[SampleCount] = CDbl(TmpData) / 32767;
		SampleCount ++;
	}

	Dest.Buffer -> Ubound = PeriodCount - 1;
}

void CBVFile::OpenCVDB06(CVDBContainer& Dest)
{	
	Dest.Info.Consonant = (mStream -> readByte() == 255);
	Dest.Info.StartPosition = mStream -> readInt();
	Dest.Info.PeriodStartPosition = mStream -> readInt();
	mStream -> readByte();
	Dest.Info.ChunkNumber = mStream -> readShort();
	Dest.Buffer -> Ubound = Dest.Info.ChunkNumber;

	int i, j;
	int PeriodSize;
	int TotalPeriod = 0;
	for(i = 0;i <= Dest.Info.ChunkNumber;i ++)
	{
		Dest.Buffer -> Data[i] -> Ubound = mStream -> readShort() - 1;
		TotalPeriod += Dest.Buffer -> Data[i] -> Ubound + 1;
	}

	Dest.Info.AveragePeriod = TotalPeriod / (Dest.Info.ChunkNumber + 1);

	for(i = 0;i <= Dest.Info.ChunkNumber;i ++)
	{
		PeriodSize = Dest.Buffer -> Data[i] -> Ubound;
		for(j = 0;j <= PeriodSize;j ++)
			Dest.Buffer -> Data[i] -> Data[j] = CDbl(mStream -> readShort()) / 32767;
	}
}