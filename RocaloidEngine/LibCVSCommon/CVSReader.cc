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
#include "../SPKit/defs.h"
#include "../SPKit/io/terminal.h"
#include "../SPKit/structure/string.h"
#include "../SPKit/misc/converter.h"
#include "../SPKit/structure/array.h"
#include "../SPKit/io/fileStream.h"

#include "Overall.h"
#include "CVSCommon.h"
#include "RDLIO.h"
#include "CVSReader.h"

 /*namespace CVSReader
{
	RDLReader Reader;
	
	void Reader_Open(string File)
	{
		Reader.Open(File);
		if (!(Reader.Read() == converter::CStr("#CVS")))
		{
			//Not Cybervoice Script
			Exception("The file is not a Cybervoice Script !");
		}
		if (!(Reader.Read() == converter::CStr(CVS_VERSION)) )
		{//Version mismatch
			Exception("Wrong CVS version.");
		}
	}
	
	void Reader_Close()
	{
		Reader.Close();
	}
	
	void CVS_Read(CVS  _CVS)
	{
		string StrBuff
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "SegmentListQ"
					StrBuff = Reader.Read()
					_CVS.SegmentListQ = TestIfIsIntAndPositive(StrBuff) - 1
					Array.Resize(_CVS.SegmentList, _CVS.SegmentListQ + 1)
				Case "SegmentList"
					Dim i As Integer
					For i = 0 To _CVS.SegmentListQ
						Segment_Read(_CVS.SegmentList(i))
					Next
					if (Reader.Read() != "End" )
		{
						Throw New Exception("List without an End.")
		}
				Case Else
					//Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff != "End"
}
	
	void Segment_Read(ByRef _Segment As Segment)
		Dim StrBuff As String
		Dim i As Integer
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "TPhoneListQ"
					StrBuff = Reader.Read()
					_Segment.TPhoneListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ReDim _Segment.Effects.OpennessList(_Segment.TPhoneListQ + 1)
					For i = 0 To _Segment.TPhoneListQ + 1
						_Segment.Effects.OpennessList(i) = 1
					Next
					Array.Resize(_Segment.TPhoneList, _Segment.TPhoneListQ + 1)
				Case "TPhoneList"
					For i = 0 To _Segment.TPhoneListQ
						TPhone_Read(_Segment.TPhoneList(i))
					Next
					if (Reader.Read() != "End" )
		{
						Throw New Exception("List without an End.")
		}
				Case "FreqListQ"
					StrBuff = Reader.Read()
					_Segment.FreqListQ = TestIfIsIntAndPositive(StrBuff) - 1
					Array.Resize(_Segment.FreqList, _Segment.FreqListQ + 1)
				Case "FreqList"
					For i = 0 To _Segment.FreqListQ
						FreqSet_Read(_Segment.FreqList(i))
					Next
					if (Reader.Read() != "End" )
		{
						Throw New Exception("List without an End.")
		}
				Case "Effects"
					Effects_Read(_Segment.Effects)
				Case "StartTime"
					_Segment.StartTime = TestIfIsDoubleNotNegative(Reader.Read())
				Case Else
					//Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff != "End"
}
	
	void TPhone_Read(ByRef _TPhone As TPhone)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Start"
					TStart_Read(_TPhone.Start)
				Case "Dest"
					TDest_Read(_TPhone.Dest)
				Case "Transition"
					TTransition_Read(_TPhone.Transition)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
	
	void TStart_Read(ByRef _Start As TStart)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Type"
					StrBuff = Reader.Read().ToLower()
					if (StrBuff = "new" )
		{
						_Start.Type = True
					Elseif (StrBuff = "preserved" )
		{
						_Start.Type = False
					Else
						Throw New Exception("Invalid syllable type identifier as " & StrBuff & ".")
		}
				Case "Symbol"
					StrBuff = Reader.Read()
					_Start.Symbol = StrBuff
				Case "Preserved"
					StrBuff = Reader.Read()
					Try
						_Start.Preserved = CInt(StrBuff)
					Catch
						Throw New Exception("Invalid preserved buffer as " & StrBuff & ".")
					End Try
					if (_Start.Preserved != 1 AndAlso _Start.Preserved != 2 )
		{
						Throw New Exception("Invalid preserved buffer as " & StrBuff & ".")							
		}
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
		}
	
	void TDest_Read(ByRef _Dest As TDest)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Type"
					StrBuff = Reader.Read().ToLower()
					if (StrBuff = "new" )
		{
						_Dest.Type = True
					Elseif (StrBuff = "preserved" )
		{
						_Dest.Type = False
					Else
						Throw New Exception("Invalid syllable type identifier as " & StrBuff & ".")
		}
				Case "Symbol"
					StrBuff = Reader.Read()
					_Dest.Symbol = StrBuff
				Case "Preserved"
					StrBuff = Reader.Read()
					Try
						_Dest.Preserved = CInt(StrBuff)
					Catch
						Throw New Exception("Invalid preserved buffer as " & StrBuff & ".")
					End Try
					if (_Dest.Preserved != 1 AndAlso _Dest.Preserved != 2 )
		{
						Throw New Exception("Invalid preserved buffer as " & StrBuff & ".")							
		}
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
		}
	
	void TTransition_Read(ByRef _Transition As TTransition)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "StartRatio"
					StrBuff = Reader.Read()
					_Transition.StartRatio = TestIfIsDoubleNotNegative(StrBuff)
				Case "EndRatio"
					StrBuff = Reader.Read()
					_Transition.EndRatio = TestIfIsDoubleNotNegative(StrBuff)
				Case "Time"
					StrBuff = Reader.Read()
					_Transition.Time = TestIfIsDoubleAndPositive(StrBuff)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
	
	void FreqSet_Read(ByRef _FreqSet As FreqSet)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Time"
					StrBuff = Reader.Read()
					_FreqSet.Time = TestIfIsDoubleNotNegative(StrBuff)
				Case "Freq"
					StrBuff = Reader.Read()
					_FreqSet.Freq = TestIfIsDoubleAndPositive(StrBuff)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
	
	void Effects_Read(ByRef _Effects As EffectCollection)
		Dim StrBuff As String
		Dim i As Integer
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Shrink"
					StrBuff = Reader.Read()
					_Effects.Shrink = TestIfIsDoubleNotNegative(StrBuff)
				Case "ForwardCut"
					StrBuff = Reader.Read()
					_Effects.ForwardCut = TestIfIsDoubleNotNegative(StrBuff)
				Case "EnvelopeListQ"
					StrBuff = Reader.Read()
					_Effects.EnvelopeListQ = TestIfIsIntAndPositive(StrBuff) - 1
					Array.Resize(_Effects.EnvelopeList, _Effects.EnvelopeListQ + 1)
				Case "EnvelopeList"
					For i = 0 To _Effects.EnvelopeListQ
						EnvelopeSet_Read(_Effects.EnvelopeList(i))
					Next
					if (Reader.Read() != "End" )
		{
						Throw New Exception("List without an End.")
		}
				Case "ElistEnabled"
					StrBuff = Reader.Read()
					_Effects.ElistEnabled = TestIfIsBoolean(StrBuff)
				Case "PElopeEnabled"
					StrBuff = Reader.Read()
					_Effects.PElopeEnabled = TestIfIsBoolean(StrBuff)
				Case "PresetedEnvelope"
					StrBuff = Reader.Read()
					_Effects.PresetedEnvelope = TestIfIsPresetedEnvelope(StrBuff)
				Case "ADSR"
					ADSREnvelope_Read(_Effects.ADSR)
				Case "OpennessList"
					For i = 0 To _Effects.OpennessList.GetUpperBound(0)
						StrBuff = Reader.Read()
						_Effects.OpennessList(i) = TestIfIsDoubleNotNegative(StrBuff)
					Next
				Case "Vibration"
					//Preserved
				Case "Breath"
					BreathStruct_Read(_Effects.Breath)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
	
	void EnvelopeSet_Read(ByRef _EnvelopeSet As EnvelopeSet)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Time"
					StrBuff = Reader.Read()
					_EnvelopeSet.Time = TestIfIsDoubleNotNegative(StrBuff)
				Case "Amplitude"
					StrBuff = Reader.Read()
					_EnvelopeSet.Amplitude = TestIfIsDoubleNotNegative(StrBuff)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
	
	void ADSREnvelope_Read(ByRef _ADSREnvelope As ADSREnvelope)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Amplitude"
					StrBuff = Reader.Read()
					_ADSREnvelope.Amplitude = TestIfIsDoubleNotNegative(StrBuff)
				Case "Attack"
					StrBuff = Reader.Read()
					_ADSREnvelope.Attack = TestIfIsDoubleNotNegative(StrBuff)
				Case "Decline"
					StrBuff = Reader.Read()
					_ADSREnvelope.Decline = TestIfIsDoubleNotNegative(StrBuff)
				Case "Release"
					StrBuff = Reader.Read()
					_ADSREnvelope.Release = TestIfIsDoubleNotNegative(StrBuff)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
	
	void BreathStruct_Read(ByRef _Breath As BreathStruct)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Magnitude"
					StrBuff = Reader.Read()
					_Breath.Magnitude = TestIfIsDouble(StrBuff)
				Case Else
					//Error
			End Select
		Loop While StrBuff != "End"
}
};*/