 /*
  * CVSReader.cc
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
  * along with this program. if (not, see <http://www.gnu.org/licenses/>.
  */
#include <stdio.h>
#include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"

#include "Overall.h"
#include "RDLIO.h"
#include "CVSCommon.h"
#include "CVSReader.h"

namespace CVSReader
{
	using namespace CVSCommon;
	RDLReader Reader;
	bool isOpen=false;
	#define Exception(x)    Reader.Close();Overall::Exception(x)
	void Open(string File)
	{
		Reader.Open(File);
		if (!(Reader.Read() == CStr("#CVS")))
		{
			//Not Cybervoice Script
			Exception("The file is not a Cybervoice Script !");
		}
		if (!(Reader.Read() == CStr(CVS_VERSION)) )
		{//Version mismatch
			Exception("Wrong CVS version.");
		}
		isOpen=true;
	}
	
	void Close()
	{
		Reader.Close();
		isOpen=false;
	}

	void inline Detect_WrongEnd()
	{
		if ( ! (Reader.Read() == "End" ) )
		{
			Exception("List without an End.");
		}
	}

	void BreathStruct_Read(BreathStruct & _Breath)
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Magnitude" )
			{
					StrBuff = Reader.Read();
					_Breath.Magnitude = RDLIO::TestIfIsDouble(StrBuff);
			}
		}
	}	

	void EnvelopeSet_Read( EnvelopeSet & _EnvelopeSet)
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Time")
			{
					StrBuff = Reader.Read();
					_EnvelopeSet.Time = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "Amplitude" )
			{
					StrBuff = Reader.Read();
					_EnvelopeSet.Amplitude = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else
			{
					//Error
			}
		}
	}
	
	void ADSREnvelope_Read(ADSREnvelope & _ADSREnvelope  )
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Amplitude" )
			{
					StrBuff = Reader.Read();
					_ADSREnvelope.Amplitude = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "Attack" )
			{
					StrBuff = Reader.Read();
					_ADSREnvelope.Attack = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "Decline" )
			{
					StrBuff = Reader.Read();
					_ADSREnvelope.Decline = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "Release" )
			{
					StrBuff = Reader.Read();
					_ADSREnvelope.Release = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else
			{
					//Error
			}
		}
	}
	
	void Effects_Read(EffectCollection & _Effects)
	{
		string StrBuff;
		int i ;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Shrink" )
			{
				StrBuff = Reader.Read();
				_Effects.Shrink = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "ForwardCut" )
			{
					StrBuff = Reader.Read();
					_Effects.ForwardCut = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "EnvelopeListQ")
			{
				StrBuff = Reader.Read();
				_Effects.EnvelopeListQ = RDLIO::TestIfIsIntAndPositive(StrBuff) - 1;
				_Effects.EnvelopeList.setUbound ( _Effects.EnvelopeListQ );
			}
			else if ( StrBuff == "EnvelopeList" )
			{
				for ( i=0 ; i<= _Effects.EnvelopeListQ ; i++)
					EnvelopeSet_Read(_Effects.EnvelopeList[i]);
				Detect_WrongEnd ();
			}
			else if ( StrBuff == "ElistEnabled" )
			{
					StrBuff = Reader.Read();
					_Effects.ElistEnabled = RDLIO::TestIfIsBoolean(StrBuff);
			}
			else if ( StrBuff == "PElopeEnabled" )
			{
					StrBuff = Reader.Read();
					_Effects.PElopeEnabled = RDLIO::TestIfIsBoolean(StrBuff);
			}
			else if ( StrBuff == "PresetedEnvelope" )
			{
					StrBuff = Reader.Read();
					_Effects.PresetedEnvelope = RDLIO::TestIfIsPresetedEnvelope(StrBuff);
			}
			else if ( StrBuff == "ADSR" )
			{
				ADSREnvelope_Read(_Effects.ADSR);
			}
			else if ( StrBuff == "OpennessList" )
			{
#ifdef CVSCOMMON_DEBUG	
				printf("			OpennessList upper = %d\n",_Effects.OpennessList.getUbound ());
#endif
				for ( i=0 ; i<= _Effects.OpennessList.getUbound () ; i++ )
				{
						StrBuff = Reader.Read();
						_Effects.OpennessList[i] = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
#ifdef CVSCOMMON_DEBUG
						printf("			O:%f\n",_Effects.OpennessList[i]);
#endif
				}
			}
			else if ( StrBuff == "Vibration")
			{
					//Preserved
			}
			else if ( StrBuff == "Breath")
			{
					BreathStruct_Read(_Effects.Breath);
			}
			else
			{
					//Error
			}
		}
	}
	
	void FreqSet_Read( FreqSet & _FreqSet )
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Time" )
			{
					StrBuff = Reader.Read();
					_FreqSet.Time = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "Freq" )
			{
					StrBuff = Reader.Read();
					_FreqSet.Freq = RDLIO::TestIfIsDoubleAndPositive(StrBuff);
			}
			else 
			{
					//Error
			}
		}
	}
	
	void TStart_Read(TStart & _Start)
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Type" ) 
			{
				StrBuff = Reader.Read();
				StrBuff = lowerCase(StrBuff);
				if (StrBuff == "new" )
				{
					_Start.Type = true;
				}
				else if (StrBuff == "preserved" )
				{
						_Start.Type = false;
				}
				else
				{
						Exception( CStr ("Invalid syllable type identifier as ") + StrBuff + ".");
				}
			}
			else if ( StrBuff ==  "Symbol" )
			{
					StrBuff = Reader.Read();
					_Start.Symbol = StrBuff;
			}
			else if ( StrBuff ==  "Preserved" )
			{
				StrBuff = Reader.Read();
	
				if ( RDLIO::TestIfIsNumber(StrBuff) )
				{
					_Start.Preserved = CInt(StrBuff);
					
				}
				else
				{
					
					Exception( CStr ("Invalid preserved buffer as ") + StrBuff + ".");
				}
				if ( (_Start.Preserved != 1) && (_Start.Preserved != 2) )
				{
					Exception( CStr ("Invalid preserved buffer as " ) + StrBuff + ".");			
				}
			}
			else
			{
				//Error
			}
		}
	}
	
	void TDest_Read(TDest & _Dest)
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Type" ) 
			{
				StrBuff = Reader.Read();
				StrBuff = lowerCase(StrBuff);
				if (StrBuff == "new" )
				{
					_Dest.Type = true;
				}
				else if (StrBuff == "preserved" )
				{
						_Dest.Type = false;
				}
				else
				{
						Exception( CStr ("Invalid syllable type identifier as ") + StrBuff + ".");
				}
			}
			else if ( StrBuff ==  "Symbol" )
			{
					StrBuff = Reader.Read();
					_Dest.Symbol = StrBuff;
			}
			else if ( StrBuff ==  "Preserved" )
			{
				StrBuff = Reader.Read();
				if ( RDLIO::TestIfIsNumber(StrBuff) )
				{
					_Dest.Preserved = CInt(StrBuff);
				}
				else
				{
					Exception( CStr ("Invalid preserved buffer as ") + StrBuff + ".");
				}
				if ( (_Dest.Preserved != 1) && (_Dest.Preserved != 2) )
				{
					Exception( CStr ("Invalid preserved buffer as " ) + StrBuff + ".");			
				}		
			}
			else
			{
				//Error
			}
		}
	}
	
	void TTransition_Read(TTransition &  _Transition)
	{
		string StrBuff ;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "StartRatio")
			{
					StrBuff = Reader.Read();
					_Transition.StartRatio = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "EndRatio")
			{
					StrBuff = Reader.Read();
					_Transition.EndRatio = RDLIO::TestIfIsDoubleNotNegative(StrBuff);
			}
			else if ( StrBuff == "Time" )
			{
					StrBuff = Reader.Read();
					//printf("%s",StrBuff.toChars ());
					_Transition.Time = RDLIO::TestIfIsDoubleAndPositive(StrBuff);
			}
			else
			{
					//Error
			}
		}
	}
	
	void TPhone_Read(TPhone & _TPhone)
	{
		string StrBuff;
		if(isOpen != true) return;
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Start")
			{
				TStart_Read(_TPhone.Start);
			}
			else if ( StrBuff == "Dest" )
			{
				TDest_Read(_TPhone.Dest);
			}
			else if ( StrBuff == "Transition" ) 
			{
				TTransition_Read(_TPhone.Transition);
			}
			else
			{
				//Error
			}
		}
	}
	
	void Segment_Read(Segment & _Segment )
	{
		string StrBuff;
		int i;
		if(isOpen != true) return;
#ifdef CVSCOMMON_DEBUG
					printf("	Seg Start\n");
#endif
		while( ! (StrBuff == "End") )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "TPhoneListQ" )
			{
#ifdef CVSCOMMON_DEBUG
					printf("	    TPhoneListQ\n");
#endif
				StrBuff = Reader.Read();
				_Segment.TPhoneListQ =RDLIO::TestIfIsIntAndPositive(StrBuff) - 1;
				
				_Segment.Effects.OpennessList.setUbound (_Segment.TPhoneListQ + 1);
				for (i = 0 ; i <=  (_Segment.TPhoneListQ + 1) ; i++ )
				{
					_Segment.Effects.OpennessList[i] = 1;
				}
				_Segment.TPhoneList.setUbound ( _Segment.TPhoneListQ );
#ifdef CVSCOMMON_DEBUG
					printf("	    End TPhoneListQ\n");
#endif
			}
			else if ( StrBuff == "TPhoneList")
			{
#ifdef CVSCOMMON_DEBUG
					printf("	    TPhoneList\n");
#endif
				for ( i=0 ; i <=  _Segment.TPhoneListQ ; i++)
					TPhone_Read(_Segment.TPhoneList[i]);
				Detect_WrongEnd();
#ifdef CVSCOMMON_DEBUG
					printf("	    End TPhoneList\n");
#endif
			}
			else if ( StrBuff == "FreqListQ" )
			{
#ifdef CVSCOMMON_DEBUG
					printf("	    FreqListQ\n");
#endif
				StrBuff = Reader.Read();
				_Segment.FreqListQ = RDLIO::TestIfIsIntAndPositive(StrBuff) - 1;
				_Segment.FreqList.setUbound (_Segment.FreqListQ );
#ifdef CVSCOMMON_DEBUG
					printf("	    End FreqListQ\n");
#endif
			}
			else if ( StrBuff == "FreqList" )
			{
#ifdef CVSCOMMON_DEBUG
					printf("		FreqList\n");
#endif
				for ( i=0 ; i<= _Segment.FreqListQ ; i++)
					FreqSet_Read(_Segment.FreqList[i]);
				Detect_WrongEnd();
#ifdef CVSCOMMON_DEBUG
					printf("		End FreqList\n");
#endif
			}
			else if ( StrBuff == "Effects" )
			{
#ifdef CVSCOMMON_DEBUG
					printf("		Effects\n");
#endif
				Effects_Read(_Segment.Effects);
#ifdef CVSCOMMON_DEBUG
					printf("		End Effects\n");
#endif
			}
			else if( StrBuff == "StartTime")
			{
#ifdef CVSCOMMON_DEBUG
					printf("		StartTime\n");
#endif
				_Segment.StartTime = RDLIO::TestIfIsDoubleNotNegative(Reader.Read());
#ifdef CVSCOMMON_DEBUG
					printf("		End StartTime\n");
#endif
			}
			else
			{
				//Throw New Exception("Invalid identifier as " & StrBuff & ".")
			}
		}
#ifdef CVSCOMMON_DEBUG
		printf("	End Seg\n");
#endif
	}
	
	void Read(CVS & _CVS)
	{
		string StrBuff;
		if(isOpen != true) return ;
		while(!(  StrBuff == CStr("End") ) )
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "SegmentListQ")
			{
#ifdef CVSCOMMON_DEBUG
					printf("SegListQ\n");
#endif
				StrBuff = Reader.Read();
				_CVS.SegmentListQ = RDLIO::TestIfIsIntAndPositive(StrBuff) - 1;
				_CVS.SegmentList.setUbound ( _CVS.SegmentListQ );
#ifdef CVSCOMMON_DEBUG
					printf("End SegListQ\n");
#endif
			}
			else if ( StrBuff ==  "SegmentList")
			{
				int i;
#ifdef CVSCOMMON_DEBUG
					printf("Seg List\n");
#endif
				for ( i=0 ; i<=_CVS.SegmentListQ ; i++)
					Segment_Read(_CVS.SegmentList[i]);
				if ( ! (Reader.Read() == "End" ) )
				{
					Exception("List without an End.");
				}
#ifdef CVSCOMMON_DEBUG
					printf("End Seg List\n");
#endif
			}
			else
			{
					//Throw New Exception("Invalid identifier as " & StrBuff & ".")
			}
		}
#ifdef CVSCOMMON_DEBUG
		printf("All done.\n");
#endif
	}
	
};