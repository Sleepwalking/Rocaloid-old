 /*
  * CDTCommon.h
  *
  * Copyright (C) 2013 - Rocaloid Development Group (RDG)
  *
  * Created by rgwan 
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  */
 #ifndef CDTCOMMON_H
 #define CDTCOMMON_H
namespace CDTCommon
{
	struct Phonetic;
	struct PhoneticInfo;
	struct DB;
	struct OpennessSet;
	struct PhoneSet;
	struct DBSet;
	struct PTransition;
	//struct DEF;
	
	struct PTransition
	{
		string TFrom;
		string TTo;
	};
	
	enum DEFType
	{
		V,
		VV,	
		VVV,
		CV,
		CVV,	
		CAV,
		CAVV,
	};
	enum PhoneType
	{
		Consonant ,
		Vowel ,
		Semi 
	};
	
	enum PEnvelopeType
	{
		PLO ,
		FRC ,
		SEM ,
		VOW 
	};	
	struct PhoneticInfo
	{
		int OpennessListQ;
		array<OpennessSet> OpennessList;
		int PhoneListQ;
		array<PhoneSet> PhoneList;
	};
	
	struct OpennessSet
	{
		string Phone;
		double Ope;
	};
	
	struct PhoneSet
	{
		string Phone;
		PhoneType Type;
		PEnvelopeType PType;
		int DataPointQ;
		//double Offset[4];
		//double Multiple[4];
		array<double> DataPoint;
		//setUbound注意X*Y
	};
	
	struct DBInfo
	{
		int DBListQ;
		array<DBSet> DBList;
	};
	
	struct DBSet
	{
		string Phone;
		string Pitch;
		int VOT;
		int PreShrink;
	};
	
 	enum CaseComparison 
	{
		Non,
		Less ,
		More ,
		Equal ,
		LessOrEqual ,
		MoreOrEqual 
	};
	
	enum CaseParameter
	{
		None,
		Time 
	};
	struct DEF
	{
		string Name;
		DEFType Type;
		double TRatio;
		int TListQ;
		array<PTransition> TList; 
		bool Extended;
	};
	struct CDT
	{
		string Version;
		string CDTVersion;
		string Language;
		int DEFListQ;
		//Dim DEFList_0233() As DEF_0233 'Obsoleted
		array<DEF> DEFList;
		PhoneticInfo Phonetic;
		DBInfo DB;
	};
	
	using namespace RSC;
	
	class CDTOperation
	{
		public:
		double GetOpe(CDT& _CDT, string Phone);
		DEF CreateDEFCopy(DEF& _DEF);
		
		void ReplaceDEF(DEF& _DEF, string Name);
		int FindDEFNum(CDT& _CDT, string Name);
		int FindDEFNum(CDT& _CDT, RSC::Segment _Segment);
		
		string ToSingleNotation(string Str);
		DBSet GetDBSet(CDT& _CDT,string Phone, string Pitch);
			
		PhoneSet GetPhoneSet(CDT& _CDT, char PhoneChar);
		PhoneSet GetPhoneSet(CDT& _CDT, string Phone);
		};
	extern PhoneType TestIfIsPhoneType(string _String);
	extern PEnvelopeType TestIfIsPType(string _String);
#define CDT_VERSION "2.41" //2.41版本CDT
#define DP(x,y) x * 4 + y //模拟二位数组
};

#endif 
 