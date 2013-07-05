#include "SPKit/structure/string.h"
#include "MultiFrameBuffer.h"
#include "FrameBuffer.h"
#include "CVDB.h"

CVDBContainer::CVDBContainer()
{
	Buffer = new MultiFrameBuffer(3000, 1000);
	Name = "";
	BaseFrame = 0;
}
CVDBContainer::~CVDBContainer()
{
	delete Buffer;
}

string CVDBContainer::GetSymbol()
{
	if(Name[1] == '_')
		return left(Name, 1);
	else if(Name[2] == '_')
		return left(Name, 2);
	else
		return "";
}
string CVDBContainer::GetPitch()
{
	if(Name[1] == '_')
		return mid(Name, 2);
	else if(Name[2] == '_')
		return mid(Name, 3);
	else
		return "";
}
int CVDBContainer::GetCirculationBase()
{
	int i;
	int acc = 0;
	for(i = 0;i < Buffer -> GetSize();i ++)
	{
		acc += Buffer -> Data[i] -> GetSize();
		if(acc > Info.StartPosition)
			return i + 1;
	}
	return 0;
}