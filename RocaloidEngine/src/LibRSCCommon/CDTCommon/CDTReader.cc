 /*
  * CDTRead.cc
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
#include "SPKit/defs.h"
#include "SPKit/io/terminal.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/converter.h"
#include "SPKit/structure/array.h"
#include "SPKit/io/fileStream.h"

#include "LibCyberBase/Overall.h"
#include "LibCyberBase/RDLIO.h"
#include "LibCVSCommon/CVSCommon.h"
#include "../RSCCommon.h"
#include "CDTCommon.h"
#include "CDTReader.h"

namespace CDTCommon
{
	using namespace converter;
	using namespace Overall;
	using namespace RDLIO;
	CaseParameter TestIfIsCaseParameter(string _String)
	{
		if (_String == "Time")
			return Time;
		else
			Exception(_String + " is not a valid Parameter!");
		return None;
	}
	CaseComparison TestIfIsCaseComparison(string _String)
	{
		if ( _String == ">" )
			return More;
		else if ( _String == "<")
			return Less;
		else if ( _String == "=")
			return Equal;
		else if ( _String == ">=")
			return MoreOrEqual;
		else if ( _String == "<=")
			return LessOrEqual;
		else
			Exception(_String + " is not a valid else Comparison!");
		return Non;
	}
	DEFType TestIfIsDEFType(string _String) 
	{
			if ( _String =="V")
				return V;
			else if ( _String =="VV")
				return VV;
			else if ( _String =="VVV")
				return VVV;
			else if ( _String =="CV")
				return CV;
			else if ( _String =="CVV")
				return CVV;
			else if ( _String =="CAV")
				return CAV;
			else if ( _String =="CAVV")
				return CAVV;
			else
				Exception(_String + " is not a valid Comparison!");
		return V;
	}
	
	//class CDT Reader
		void CDTReader::Open(string FileName)
		{
			Reader.Open(FileName);
			if (Reader.Read() != "#CDT")
				Exception("This File is not a Rocaloid Dict!");
				CDTVersion=Reader.Read();
			if ( CDTVersion !=CDT_VERSION )
			{//2.33版本已经摘除
				wLine( CStr("CDT Version : ") + CDTVersion);
				Exception("Wrong CDT Version");
			}
			Reader.Read();
		}

		void CDTReader::Close()
		{
			Reader.Close();
		}

		
		void CDTReader::Read(CDT& _CDT)
		{
			string StrBuff;
			_CDT.CDTVersion=CDTVersion;//版本
			while(StrBuff != "End")
			{
				StrBuff = Reader.Read();
				if (StrBuff == "Version")
				{
					StrBuff=Reader.Read();
					//wLine ( StrBuff );
					_CDT.Version=StrBuff;
				}
				else if(StrBuff == "Language")
				{
					StrBuff=Reader.Read();
					_CDT.Language=StrBuff;
				}
				else if(StrBuff == "DEFList")
				{
					//wLine("DEFList");
					DEFList_Read(_CDT);
					//wLine("EndDEFList");
				}
				else if(StrBuff == "PhoneticInfo")
				{
					//wLine("PhoneticInfo");
					PhoneticInfo_Read(_CDT.Phonetic);
					//wLine("End PhoneticInfo");
				}
				else if ( StrBuff == "DBInfo")
				{
					//wLine("DBInfo");
					DBInfo_Read(_CDT.DB);
					//wLine("End DBInfo");
				}
				else if ( StrBuff == "End")
					break;
				else
				{
					Exception( CStr("Invalid identifier as ") + StrBuff + ".");
				}
			}
		}

		
		void CDTReader::DEFList_Read(CDT& _CDT)
		{
			string StrBuff;
			int Count = 0;
			_CDT.DEFList.setUbound (5000);
				do{
					StrBuff = Reader.Read();
					if (StrBuff == "DEF")
					{
						DEF_Read(_CDT.DEFList[Count]);
						Count++;
					}
					else
					{
						//Throw New Exception("Invalid identifier as " & StrBuff & ".")
					}
				}while(StrBuff != "End");
				_CDT.DEFListQ = Count - 1;
		}

		void CDTReader::DEF_Read(DEF& _DEF)
		{
			string StrBuff;
			int i=0;
			StrBuff=Reader.Read();
			_DEF.Name=StrBuff;
			_DEF.Extended=false;
				do{
					StrBuff = Reader.Read();
					if (StrBuff == "Type")
					{
						StrBuff=Reader.Read();
						_DEF.Type=TestIfIsDEFType(StrBuff);
					}
					else if(StrBuff ==  "TRatio" )
					{
						StrBuff = Reader.Read();
						_DEF.TRatio = TestIfIsDoubleNotNegative(StrBuff);
					}
					else if (StrBuff == "TList" )
					{
						_DEF.TList.setUbound (10);
						i = 0;
						while(true)
						{
							StrBuff = Reader.Read();
							if (StrBuff == "T" )
							{
								_DEF.TList[i].TFrom = Reader.Read();
								_DEF.TList[i].TTo = Reader.Read();
							}
							else
							{
								//End
								_DEF.TListQ = i - 1;
								StrBuff = "-";
								break;
							}
							i ++;
						}
					}
					else
					{
						//Throw New Exception("Invalid identifier as " & StrBuff & ".")
					}
				}while(StrBuff != "End");			
		}

		void CDTReader::PhoneticInfo_Read(PhoneticInfo& _PhoneticInfo)
		{
			string StrBuff;
			int i;
			while(StrBuff!="End")
			{
				StrBuff = Reader.Read();
				if (StrBuff == "OpennessListQ")
				{
						StrBuff = Reader.Read();
						_PhoneticInfo.OpennessListQ = TestIfIsIntNotNegative(StrBuff) - 1;
						_PhoneticInfo.OpennessList.setUbound (_PhoneticInfo.OpennessListQ);
				}
				else if (StrBuff == "OpennessList")
				{
					for  (i=0 ;i <= _PhoneticInfo.OpennessListQ; i ++)
					{
						StrBuff = Reader.Read();
						_PhoneticInfo.OpennessList[i].Phone = StrBuff;
						StrBuff = Reader.Read();
						_PhoneticInfo.OpennessList[i].Ope = TestIfIsDoubleNotNegative(StrBuff);
					}
				}
				else if (StrBuff =="PhoneListQ")
				{
					StrBuff = Reader.Read();
					_PhoneticInfo.PhoneListQ = TestIfIsIntNotNegative(StrBuff) - 1;
					_PhoneticInfo.PhoneList.setUbound (_PhoneticInfo.PhoneListQ + 1);
				}
				else if (StrBuff == "PhoneList")
				{
					for( i = 0 ; i <=_PhoneticInfo.PhoneListQ ; i++)
					{
						PhoneSet_Read(_PhoneticInfo.PhoneList[i]);
					}
					Reader.Read();
				}
			}
		}

		void CDTReader::PhoneSet_Read(PhoneSet& _PhoneSet)
		{
			string StrBuff;
			int i,j;
			double Multiple[3]; 
			double Offset[3]; 
			for (i=0;i<=2;i++) {
				Multiple[i]=1;
				Offset[i]=0;
			}
			while(StrBuff!="End")
			{
				StrBuff = Reader.Read();
				if ( StrBuff == "Phone")
				{
						StrBuff = Reader.Read();
						_PhoneSet.Phone = StrBuff;
				}
				else if (StrBuff =="Type")
				{
						StrBuff = Reader.Read();
						_PhoneSet.Type = TestIfIsPhoneType(StrBuff);
				}
				else if (StrBuff =="PType")
				{
						StrBuff = Reader.Read();
						_PhoneSet.PType = TestIfIsPType(StrBuff);
				}
				else if (StrBuff =="#DataOffset")
				{
						StrBuff = Reader.Read();
						Offset[0] = TestIfIsDouble(StrBuff);
						StrBuff = Reader.Read();
						Offset[1] = TestIfIsDouble(StrBuff);
						StrBuff = Reader.Read();
						Offset[2] = TestIfIsDouble(StrBuff);
				}
				else if (StrBuff =="#DataMultiple")
				{
						StrBuff = Reader.Read();
						Multiple[0] = TestIfIsDouble(StrBuff);
						StrBuff = Reader.Read();
						Multiple[1] = TestIfIsDouble(StrBuff);
						StrBuff = Reader.Read();
						Multiple[2] = TestIfIsDouble(StrBuff);
				}
				else if (StrBuff =="DataPointQ")
				{
						StrBuff = Reader.Read();
						_PhoneSet.DataPointQ = TestIfIsIntNotNegative(StrBuff) - 1;
						_PhoneSet.DataPoint.setUbound ( ( _PhoneSet.DataPointQ + 1) * 4);
				}
				else if (StrBuff =="DataPoint")
				{
					for ( i=0 ; i<= _PhoneSet.DataPointQ ; i++)
					{// 1 * i
						/*_PhoneSet.DataPoint[i] = (_PhoneSet.DataPointQ + 1 - i) * 0.025;*/
						_PhoneSet.DataPoint[DP(i,0)] = (_PhoneSet.DataPointQ + 1 - i) * 0.025;
						for (j = 1;j <= 3;j++) 
						{
							StrBuff = Reader.Read();
							_PhoneSet.DataPoint[DP(i,j)] = TestIfIsDouble(StrBuff) * Multiple[j-1] + Offset[j-1]; 
						}
					}
				}
			}
		}

		void CDTReader::DBInfo_Read(DBInfo& _DBInfo)
		{
			string StrBuff;
			int i;
			while(StrBuff != "End")
			{
				StrBuff = Reader.Read();
				if ( StrBuff == "DBListQ")
				{
					StrBuff = Reader.Read();
					_DBInfo.DBListQ = TestIfIsIntNotNegative(StrBuff) - 1;
					_DBInfo.DBList.setUbound (_DBInfo.DBListQ + 1);
					//wLine( CStr ("DBListQ:") + CStr (_DBInfo.DBListQ ));
				}
				else if ( StrBuff ==  "DBList")
				{
					//wLine( CStr ("DBListQ:") + CStr (_DBInfo.DBListQ ));
					for ( i=0 ; i<= _DBInfo.DBListQ ; i++)
						DBSet_Read(_DBInfo.DBList[i]);
					StrBuff = Reader.Read();
					if ( StrBuff != "End") 
						Exception("List without an End.");
				}
				
			}
		}

		void CDTReader::DBSet_Read(DBSet& _DBSet)
		{
			string StrBuff;
			_DBSet.PreShrink = 0;
			while ( StrBuff !="End")
			{
				StrBuff = Reader.Read();
				if (StrBuff== "Pho")
				{
					StrBuff = Reader.Read();
					_DBSet.Phone = StrBuff;
				}
				else if ( StrBuff == "Pit")
				{
					StrBuff = Reader.Read();
					_DBSet.Pitch = StrBuff;
				}
				else if ( StrBuff ==  "VOT")
				{
					StrBuff = Reader.Read();
					_DBSet.VOT = TestIfIsIntNotNegative(StrBuff);
				}
				else if ( StrBuff == "PSnk")
				{
					StrBuff = Reader.Read();
					_DBSet.PreShrink = TestIfIsIntNotNegative(StrBuff);
				}
			}
		}

};