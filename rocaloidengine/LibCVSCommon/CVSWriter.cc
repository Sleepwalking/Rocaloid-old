 /*
  * CVSWriter.cc
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
//  CVS文件写入函数
//  Provides CVS writing functions.
#include <stdio.h>
#include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"

#include "Overall.h"
#include "CVSCommon.h"
#include "RDLIO.h"
#include "CVSWriter.h"

namespace CVSWriter
{
	using namespace CVSCommon;
	RDLWriter Writer;
	bool isOpen=false;
	void Save(string File)
	{
		Writer.Open(File);
		Writer.WriteWord("#CVS");
		Writer.WriteWord(CVS_VERSION);
		Writer.NewLine();
		isOpen=true;
	}
	
	void Close()
	{
		Writer.Close();
		isOpen=false;
	}
	
	void TPhone_Write(TPhone _TPhone)
	{
		if(isOpen != true) return;
		Writer.WriteWord("TPhone");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("Start");
		Writer.WriteWord("Type");
		if (_TPhone.Start.Type == true)
		{
			Writer.WriteWord("New");
			Writer.WriteWord("Symbol");
			Writer.WriteWord(_TPhone.Start.Symbol);
		}
		else
		{
			Writer.WriteWord("Preserved");
			Writer.WriteWord("Preserved");
			Writer.WriteWord(_TPhone.Start.Preserved);
		}
		Writer.WriteWord("End");
		Writer.NewLine();
		
		Writer.WriteWord("Dest");
		Writer.WriteWord("Type");
		if (_TPhone.Dest.Type == true) 
		{
			Writer.WriteWord("New");
			Writer.WriteWord("Symbol");
			Writer.WriteWord(_TPhone.Dest.Symbol);
		}
		else
		{
			Writer.WriteWord("Preserved");
			Writer.WriteWord("Preserved");
			Writer.WriteWord(_TPhone.Dest.Preserved);
		}
		Writer.WriteWord("End");
		Writer.NewLine();
		
		Writer.WriteWord("Transition");
		Writer.WriteWord("StartRatio");
		Writer.WriteWord(_TPhone.Transition.StartRatio);
		Writer.WriteWord("EndRatio");
		Writer.WriteWord(_TPhone.Transition.EndRatio);
		Writer.WriteWord("Time");
		Writer.WriteWord(_TPhone.Transition.Time);
		Writer.WriteWord("End");
		
		Writer.IndentPop();
		Writer.NewLine();		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	
	void Freq_Write(FreqSet _Freq)
	{
		if(isOpen != true) return;
		Writer.WriteWord("FreqSet");
		
		Writer.WriteWord("Time");
		Writer.WriteWord(_Freq.Time);
		Writer.WriteWord("Freq");
		Writer.WriteWord(_Freq.Freq);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	
	void ADSREnvelope_Write(ADSREnvelope _ADSR)
	{
		if(isOpen != true) return;
		Writer.WriteWord("ADSR");
		
		Writer.WriteWord("Amplitude");
		Writer.WriteWord(_ADSR.Amplitude);
		Writer.WriteWord("Attack");
		Writer.WriteWord(_ADSR.Attack);
		Writer.WriteWord("Decline");
		Writer.WriteWord(_ADSR.Decline);
		Writer.WriteWord("Release");
		Writer.WriteWord(_ADSR.Release);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	
	void EnvelopeSet_Write(EnvelopeSet _EnvelopeSet )
	{
		if(isOpen != true) return;
		Writer.WriteWord("EnvelopeSet");
		
		Writer.WriteWord("Time");
		Writer.WriteWord(_EnvelopeSet.Time);
		Writer.WriteWord("Amplitude");
		Writer.WriteWord(_EnvelopeSet.Amplitude);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	
	void BreathStruct_Write(BreathStruct _Breath )
	{
		if(isOpen != true) return;
		Writer.WriteWord("Breath");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("Magnitude");
		Writer.WriteWord(_Breath.Magnitude);
		
		Writer.IndentPop();
		Writer.NewLine();	
		Writer.WriteWord("End");
		Writer.NewLine();
	}

	void Effects_Write(EffectCollection _Effects)
	{
		int i;
		if(isOpen != true) return;
		Writer.WriteWord("Effects");
		Writer.IndentPush();
		Writer.NewLine();
		
		if (_Effects.Shrink != 0) 
		{
			Writer.WriteWord("Shrink");
			Writer.WriteWord(_Effects.Shrink);
			Writer.NewLine();
		}
		
		if (_Effects.ForwardCut == 0)
		{
			Writer.WriteWord("ForwardCut");
			Writer.WriteWord(_Effects.ForwardCut);
			Writer.NewLine();
		}
		
		Writer.WriteWord("ElistEnabled");
		Writer.WriteWord(_Effects.ElistEnabled);
		Writer.NewLine();
		
		Writer.WriteWord("PElopeEnabled");
		Writer.WriteWord(_Effects.PElopeEnabled);
		Writer.NewLine();
		
		if (_Effects.ElistEnabled)
		{
			Writer.WriteWord("EnvelopeListQ");
			Writer.WriteWord(_Effects.EnvelopeListQ + 1);
			Writer.NewLine();
			Writer.WriteWord("EnvelopeList");
			Writer.IndentPush();
			Writer.NewLine();
			for (i = 0 ;i<=_Effects.EnvelopeListQ;i++)
				EnvelopeSet_Write(_Effects.EnvelopeList[i]);
			Writer.IndentPop();
			Writer.WriteWord("End");
			Writer.NewLine();
		}
		
		if (_Effects.PElopeEnabled )
		{
			Writer.WriteWord("PresetedEnvelope");
			Writer.WritePresetedEnvelope(_Effects.PresetedEnvelope);
			Writer.NewLine();
			switch (_Effects.PresetedEnvelope)
			{
				case  E_ADSR:
					ADSREnvelope_Write(_Effects.ADSR);
					break;
			}
		}
		
		if (_Effects.Breath.Magnitude != 0) 
		{
			BreathStruct_Write(_Effects.Breath);
		}
		
		Writer.WriteWord("OpennessList");
		for(i = 0 ;i<= _Effects.OpennessList.pointer;i++)
			Writer.WriteWord(_Effects.OpennessList[i]);
		Writer.NewLine();
		
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	
	void Segment_Write (Segment _Segment)
	{
		if(isOpen != true) return;
		int i;
		Writer.WriteWord("Segment");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("TPhoneListQ");
		Writer.WriteWord(_Segment.TPhoneListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("TPhoneList");
		Writer.IndentPush();
		Writer.NewLine();
		for(i=0;i<= _Segment.TPhoneListQ;i++)
			TPhone_Write(_Segment.TPhoneList[i]);
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
		
		Writer.WriteWord("FreqListQ");
		Writer.WriteWord(_Segment.FreqListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("FreqList");
		Writer.IndentPush();
		Writer.NewLine();
		for(i=0;i<=_Segment.FreqListQ;i++)
			Freq_Write(_Segment.FreqList[i]);
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
		
		Effects_Write(_Segment.Effects);
		
		Writer.WriteWord("StartTime");
		Writer.WriteWord(_Segment.StartTime);
		
		Writer.IndentPop();
		Writer.NewLine();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void Write( CVS _CVS)
	{
		if(isOpen != true) return;
		int i;
		Writer.WriteWord("CVS");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("SegmentListQ");
		Writer.WriteWord(_CVS.SegmentListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("SegmentList");
		Writer.IndentPush();
		Writer.NewLine();
		for(i=0;i<= _CVS.SegmentListQ;i++)
		{
			Segment_Write(_CVS.SegmentList[i]);
		}
		Writer.IndentPop();
		Writer.WriteWord("End");
		
		Writer.IndentPop();
		Writer.NewLine();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
};
//Template
//
//		Public Sub Segment_Write(ByRef _Segment As Segment)
//			Dim i As Integer
//			Writer.WriteWord("Segment")
//			Writer.IndentPush()
//			Writer.NewLine()
//			
//			
//			
//			Writer.IndentPop()
//			Writer.NewLine()			
//			Writer.WriteWord("End")
//			Writer.NewLine()
//		End Sub
