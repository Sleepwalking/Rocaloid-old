#ifndef CVDB_H
#define CVDB_H
#include "../SPKit/structure/string.h"
class string;
class MultiFrameBuffer;

struct CVDBHeader
{
	short int Version;
	bool Consonant;
	int StartPosition;
	int AveragePeriod;

	//CVDB 0.6
	int PeriodStartPosition;
	short int ChunkNumber;
};

class CVDBContainer
{
	public:
		CVDBHeader Info;
		MultiFrameBuffer* Buffer;

		CVDBContainer();
		~CVDBContainer();

		inline void ClearSymbol();

		inline void SetName(string _Name);
		inline string GetName();
		inline int GetBaseFrame();
		string GetSymbol();
		string GetPitch();
	private:
		string Name;
		int BaseFrame;
		
		int GetCirculationBase();
};

inline void CVDBContainer::ClearSymbol()
{
	Name = "nx_C3";
}

inline void CVDBContainer::SetName(string _Name)
{
	Name = _Name;
}
inline string CVDBContainer::GetName()
{
	return Name;
}
inline int CVDBContainer::GetBaseFrame()
{
	return BaseFrame;
}
#endif