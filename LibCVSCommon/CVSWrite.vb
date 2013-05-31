'    CVS文件写入函数
'    Provides CVS writing functions.
'    Copyright (C) 2013 Sleepwalking
'
'    This program is free software: you can redistribute it and/or modify
'    it under the terms of the GNU General Public License as published by
'    the Free Software Foundation, either version 3 of the License, or
'    (at your option) any later version.
'
'    This program is distributed in the hope that it will be useful,
'    but WITHOUT ANY WARRANTY; without even the implied warranty of
'    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
'    GNU General Public License for more details.
'
'    You should have received a copy of the GNU General Public License
'    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Public Module Write
	'Module for outputing to CVS file.
	Dim Writer As RDLWriter
	
	Public Sub Writer_Save(ByVal File As String)
		Writer = New RDLWriter(File)
		Writer.WriteWord("#CVS")
		Writer.WriteWord("1.6")
		Writer.NewLine()
	End Sub
	
	Public Sub Writer_Close()
		Writer.Close()
	End Sub
	
	Public Sub CVS_Write(ByRef _CVS As CVS)
		Dim i As Integer
		Writer.WriteWord("CVS")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("SegmentListQ")
		Writer.WriteWord(_CVS.SegmentListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("SegmentList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _CVS.SegmentListQ
			Segment_Write(_CVS.SegmentList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		
		Writer.IndentPop()
		Writer.NewLine()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub Segment_Write(ByRef _Segment As Segment)
		Dim i As Integer
		Writer.WriteWord("Segment")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("TPhoneListQ")
		Writer.WriteWord(_Segment.TPhoneListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("TPhoneList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _Segment.TPhoneListQ
			TPhone_Write(_Segment.TPhoneList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
		
		Writer.WriteWord("FreqListQ")
		Writer.WriteWord(_Segment.FreqListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("FreqList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _Segment.FreqListQ
			Freq_Write(_Segment.FreqList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
		
		Effects_Write(_Segment.Effects)
		
		Writer.WriteWord("StartTime")
		Writer.WriteWord(_Segment.StartTime)
		
		Writer.IndentPop()
		Writer.NewLine()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub TPhone_Write(ByRef _TPhone As TPhone)
		Writer.WriteWord("TPhone")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("Start")
		Writer.WriteWord("Type")
		If _TPhone.Start.Type = True Then
			Writer.WriteWord("New")
			Writer.WriteWord("Symbol")
			Writer.WriteWord(_TPhone.Start.Symbol)
		Else
			Writer.WriteWord("Preserved")
			Writer.WriteWord("Preserved")
			Writer.WriteWord(_TPhone.Start.Preserved)
		End If
		Writer.WriteWord("End")
		Writer.NewLine()
		
		Writer.WriteWord("Dest")
		Writer.WriteWord("Type")
		If _TPhone.Dest.Type = True Then
			Writer.WriteWord("New")
			Writer.WriteWord("Symbol")
			Writer.WriteWord(_TPhone.Dest.Symbol)
		Else
			Writer.WriteWord("Preserved")
			Writer.WriteWord("Preserved")
			Writer.WriteWord(_TPhone.Dest.Preserved)
		End If
		Writer.WriteWord("End")
		Writer.NewLine()
		
		Writer.WriteWord("Transition")
		Writer.WriteWord("StartRatio")
		Writer.WriteWord(_TPhone.Transition.StartRatio)
		Writer.WriteWord("EndRatio")
		Writer.WriteWord(_TPhone.Transition.EndRatio)
		Writer.WriteWord("Time")
		Writer.WriteWord(_TPhone.Transition.Time)
		Writer.WriteWord("End")
		
		Writer.IndentPop()
		Writer.NewLine()			
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub Freq_Write(ByRef _Freq As FreqSet)
		Writer.WriteWord("FreqSet")
		
		Writer.WriteWord("Time")
		Writer.WriteWord(_Freq.Time)
		Writer.WriteWord("Freq")
		Writer.WriteWord(_Freq.Freq)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub Effects_Write(ByRef _Effects As EffectCollection)
		Dim i As Integer
		Writer.WriteWord("Effects")
		Writer.IndentPush()
		Writer.NewLine()
		
		If _Effects.Shrink <> 0 Then
			Writer.WriteWord("Shrink")
			Writer.WriteWord(_Effects.Shrink)
			Writer.NewLine()
		End If
		
		If _Effects.ForwardCut <> 0 Then
			Writer.WriteWord("ForwardCut")
			Writer.WriteWord(_Effects.ForwardCut)
			Writer.NewLine()
		End If
		
		Writer.WriteWord("ElistEnabled")
		Writer.WriteWord(_Effects.ElistEnabled)
		Writer.NewLine()
		
		Writer.WriteWord("PElopeEnabled")
		Writer.WriteWord(_Effects.PElopeEnabled)
		Writer.NewLine()
		
		If _Effects.ElistEnabled Then
			Writer.WriteWord("EnvelopeListQ")
			Writer.WriteWord(_Effects.EnvelopeListQ + 1)
			Writer.NewLine()
			Writer.WriteWord("EnvelopeList")
			Writer.IndentPush()
			Writer.NewLine()
			For i = 0 To _Effects.EnvelopeListQ
				EnvelopeSet_Write(_Effects.EnvelopeList(i))
			Next
			Writer.IndentPop()
			Writer.WriteWord("End")
			Writer.NewLine()
		End If
		
		If _Effects.PElopeEnabled Then
			Writer.WriteWord("PresetedEnvelope")
			Writer.WritePresetedEnvelope(_Effects.PresetedEnvelope)
			Writer.NewLine()
			Select Case _Effects.PresetedEnvelope
				Case Envelopes.ADSR
					ADSREnvelope_Write(_Effects.ADSR)
			End Select
		End If
		
		If _Effects.Breath.Magnitude <> 0 Then
			BreathStruct_Write(_Effects.Breath)
		End If
		
		Writer.WriteWord("OpennessList")
		For i = 0 To _Effects.OpennessList.GetUpperBound(0)
			Writer.WriteWord(_Effects.OpennessList(i))
		Next
		Writer.NewLine()
		
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub ADSREnvelope_Write(ByRef _ADSR As ADSREnvelope)
		Writer.WriteWord("ADSR")
		
		Writer.WriteWord("Amplitude")
		Writer.WriteWord(_ADSR.Amplitude)
		Writer.WriteWord("Attack")
		Writer.WriteWord(_ADSR.Attack)
		Writer.WriteWord("Decline")
		Writer.WriteWord(_ADSR.Decline)
		Writer.WriteWord("Release")
		Writer.WriteWord(_ADSR.Release)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub EnvelopeSet_Write(ByRef _EnvelopeSet As EnvelopeSet)
		Writer.WriteWord("EnvelopeSet")
		
		Writer.WriteWord("Time")
		Writer.WriteWord(_EnvelopeSet.Time)
		Writer.WriteWord("Amplitude")
		Writer.WriteWord(_EnvelopeSet.Amplitude)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub BreathStruct_Write(ByRef _Breath As BreathStruct)
		Writer.WriteWord("Breath")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("Magnitude")
		Writer.WriteWord(_Breath.Magnitude)
		
		Writer.IndentPop()
		Writer.NewLine()			
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
End Module
'Template
'
'		Public Sub Segment_Write(ByRef _Segment As Segment)
'			Dim i As Integer
'			Writer.WriteWord("Segment")
'			Writer.IndentPush()
'			Writer.NewLine()
'			
'			
'			
'			Writer.IndentPop()
'			Writer.NewLine()			
'			Writer.WriteWord("End")
'			Writer.NewLine()
'		End Sub