/*
 * CDTCommon.cc
 *
 * Copyright (C) 2013 - Rocaloid Development Group(RDG)
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

//   CDT数据结构
//   Data Structure of CDT files
//   Copyright (C) 2013 Sleepwalking
#include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"

#include "LibCyberBase/Overall.h"
#include "LibCVSCommon/CVSCommon.h"
#include "../RSCCommon.h"
#include "CDTCommon.h"

namespace CDTCommon
{
	using namespace RSCCommon;
	using namespace converter;
	using namespace Overall;
	double GetOpe(CDT& _CDT, string Phone)
	{
		int i;
		for ( i=0 ; i <= _CDT.Phonetic.OpennessListQ ; i++ )
		{
			if ( _CDT.Phonetic.OpennessList[i].Phone == Phone )
			{
				return _CDT.Phonetic.OpennessList[i].Ope;
			}
		}
		return 1;
	}
	/*		DEF CreateDEFCopy(DEF& _DEF)
	{
		DEF* Ret = new DEF;
		int i;
		Ret->TListQ = _DEF.TListQ;
		Ret->TList.setUbound (Ret->TListQ);
		for ( i =0 ; i <= Ret->TListQ ; i ++ )
		{
			Ret->TList[i].TFrom = _DEF.TList[i].TFrom;
			Ret->TList[i].TTo = _DEF.TList[i].TTo;
}
Ret->Extended = _DEF.Extended;
Ret->TRatio = _DEF.TRatio;
Ret->Type = _DEF.Type;
Ret->Name = _DEF.Name;
return *Ret;
}*/
	void ReplaceDEF(DEF& _DEF, string Name)
	{
		if ( _DEF.Name[0] != '/' ) return ;
		int i;
		char SPhone = _DEF.Name[0];
		for(i=0 ; i<=_DEF.TListQ ; i++)
		{
			if (_DEF.TList[i].TFrom[0] == '/' ) 
				_DEF.TList[i].TFrom	= CStr(SPhone) + mid(_DEF.TList[i].TFrom, 2);
			if (_DEF.TList[i].TTo[0] == '/' ) 
				_DEF.TList[i].TTo	= CStr(SPhone) + mid(_DEF.TList[i].TTo, 2);
		}
	}
	int FindDEFNum(CDT& _CDT, string Name)
	{
		int i ;
		for ( i=0 ; i <= _CDT.DEFListQ ; i++)
		{
			if (_CDT.DEFList[i].Name == Name ) 
			{
				return i;
			}
			if (_CDT.DEFList[i].Name[0] == '/' && mid(_CDT.DEFList[i].Name, 2) == mid(Name, 2) ) 
			{
				return i;
			}
		}
		return -1;
	}
	int FindDEFNum(CDT& _CDT, RSCCommon::Segment _Segment)
	{
		int i ;
		string SingleNotation  = ToSingleNotation(_Segment.Lyric);
		if ( SingleNotation[0] == '&' )
		{
			i = i;
		}
		for ( i=0 ; i<= _CDT.DEFListQ ; i++)
		{
			if ( ( ( _CDT.DEFList[i].Name[0] == '/') && mid(_CDT.DEFList[i].Name, 2) == mid(SingleNotation, 2) ) || _CDT.DEFList[i].Name == SingleNotation )
			{
				if ( _CDT.DEFList[i].Extended == true )
				{
					if ( _Segment.DurTime > 0.3 ) return i;
				}
				else
				{
					return i;
				}
			}
		}
		return -1;
	}
	string ToSingleNotation(string Str)
	{
		if ( left(Str, 2) == "zh" ){
			return CStr("%") + mid(Str, 3);
		}
		if ( left(Str, 2) == "ch" ){
			return CStr("^") + mid(Str, 3);
		}
		if ( left(Str, 2) == "sh" ){
			return CStr("&") + mid(Str, 3);
		}
		return Str;
	}
	DBSet GetDBSet(CDT& _CDT,string Phone, string Pitch)
	{
		int i;
		DBSet res;
		for ( i = 0 ; i<=_CDT.DB.DBListQ ; i++)
		{
			res=_CDT.DB.DBList[i];
			if ( res.Phone == Phone && res.Pitch == Pitch )
			{
				return res;
			}
		}
		res.VOT = 0;
		return res;
	}
	PhoneSet GetPhoneSet(CDT& _CDT, string Phone)
	{
		return GetPhoneSet(_CDT, Phone[0]);
	}
	PhoneSet GetPhoneSet(CDT& _CDT, char PhoneChar)
	{
		PhoneSet PhoneSet_;
		int i;
		for ( i = 0 ; i<=_CDT.Phonetic.PhoneListQ ; i++)
		{
			PhoneSet_ = _CDT.Phonetic.PhoneList[i];
			if ( PhoneSet_.Phone[0] == PhoneChar )
			{
				return PhoneSet_;
			}
		}

		PhoneSet_.Type = Vowel;
		return PhoneSet_;
	}

	PhoneType TestIfIsPhoneType(string _String) 
	{
		if (_String ==  "Consonant")
			return Consonant;
		else if (_String == "Vowel")
			return Vowel;
		else if (_String == "Semi")
			return Semi;
		else
			Exception(_String + " is not a valid PhoneType!");
		return Consonant;
	}
	PEnvelopeType TestIfIsPType(string _String)
	{
		if (_String ==  "PLO")
			return PLO;
		else if (_String ==  "FRC")
			return FRC;
		else if (_String ==  "SEM")
			return SEM;
		else if (_String ==  "VOW")
			return VOW;
		else
			Exception(_String + " is not a valid PType!");
		return FRC;
	}

	Transition GetTransitionRate(double Time,PhoneSet& _PhoneSet)
	{
		int i;
		Transition ret;
		for ( i =  _PhoneSet.DataPointQ ; i !=0 ; i--)
		{
			if ( Time >= _PhoneSet.DataPoint[DP(i, 0)] && Time < _PhoneSet.DataPoint[DP(i + 1, 0)])
			{
				ret.Ratio =  ( Time - _PhoneSet.DataPoint[DP(i, 0)] ) / (_PhoneSet.DataPoint[DP(i + 1, 0)] 
				                                                         - _PhoneSet.DataPoint[DP(i, 0)] );
				ret.StartNum = i;
				ret.EndNum = i + 1;
				return ret;
			}
		}
		if ( Time < _PhoneSet.DataPoint[DP(_PhoneSet.DataPointQ, 0)] )
		{
			ret.StartNum = _PhoneSet.DataPointQ - 1;
			ret.EndNum = _PhoneSet.DataPointQ;
			ret.Ratio = 1;
			return ret;
		}
		if ( Time >= _PhoneSet.DataPoint[DP(0, 0)] ) 
		{
			ret.StartNum = 0;
			ret.EndNum = 1;
			ret.Ratio = 0;
		}
		return ret;
	}
	PhoneticData GetData(Transition& _Transition, PhoneSet& _PhoneSet) 
	{
		PhoneticData ret;
		ret.LastEnd = _PhoneSet.DataPoint[DP(_Transition.StartNum, 1)] *
			(1 - _Transition.Ratio) + _PhoneSet.DataPoint[DP(_Transition.EndNum, 1)] * _Transition.Ratio;
		ret.ForwardOffset = _PhoneSet.DataPoint[DP(_Transition.StartNum, 2)] * 
			(1 - _Transition.Ratio) + _PhoneSet.DataPoint[DP(_Transition.EndNum, 2)] * _Transition.Ratio;
		ret.VOT = _PhoneSet.DataPoint[DP(_Transition.StartNum, 3)] * (1 - _Transition.Ratio) +
			_PhoneSet.DataPoint[DP(_Transition.EndNum, 3)] * _Transition.Ratio;
		return ret;
	}
	PhoneticData GetData(double Time, PhoneSet& _PhoneSet ) 
	{
		Transition Trans;
		Trans = GetTransitionRate(Time, _PhoneSet);
		return GetData(Trans, _PhoneSet);
	}
	PhoneSet& PhoneSet::operator =(PhoneSet rhs)
	{
		Phone = rhs.Phone;
		Type = rhs.Type;
		PType = rhs.PType;
		DataPointQ = rhs.DataPointQ;
		DataPoint.setUbound ( 4*DataPointQ );
		for (int i = 0;i <= 4 * DataPointQ ; i ++)
		{
			DataPoint[i] = rhs.DataPoint[i];
		}
	}
};
