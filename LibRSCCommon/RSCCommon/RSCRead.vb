'    提供RSC读取函数
'    Provides reading functions of RSC.
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

Module RDLIOExtend
	Public Function TestIfIsViewType(ByVal _String As String) As ViewTypes
		Select Case _String
			Case "NotesEditor"
				Return ViewTypes.NotesEditor
			Case "FreqEditor"
				Return ViewTypes.FreqEditor
			Case "EnvelopEditor"
				Return ViewTypes.EnvelopeEditor
			Case "BreathEditor"
				Return ViewTypes.BreathEditor
			Case Else
				Throw New Exception(_String & " is not a valid View Type!")
		End Select
		Return ViewTypes.Other
	End Function
End Module
Public Module RSCRead
	'Module for reading RSC file
	Private Reader As RDLReader
	
	Public Sub Reader_Open(ByVal File As String)
		Reader = New RDLReader(File)
		If Reader.Read() <> "#RSC" Then
			'Not Cybervoice Script
			Throw New Exception("The file is not a Rocaloid Script !")
		End If
		If Reader.Read() <> "2.0" Then
			Throw New Exception("Wrong RSC version.")
		End If
	End Sub
	
	Public Sub Reader_Close()
		Reader.Close()
	End Sub
	
	Public Sub RSC_Read(ByRef _RSC As RSC)
		_RSC.Version = "2.0"
		Dim StrBuff As String
		Dim ResizeQ As Integer
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Author"
					_RSC.Author = Reader.Read()
				Case "Information"
					Information_Read(_RSC.Information)
				Case "SegmentListQ"
					StrBuff = Reader.Read()
					_RSC.SegmentListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ResizeQ = CInt(_RSC.SegmentListQ / 1000 + 1) * 1000
					Array.Resize(_RSC.SegmentList, ResizeQ + 1)
					_RSC.InitSegmentList(0, ResizeQ)
				Case "SegmentList"
					Dim i As Integer
					For i = 0 To _RSC.SegmentListQ
						Segment_Read(_RSC.SegmentList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case "FreqListQ"
					StrBuff = Reader.Read()
					_RSC.FreqListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ResizeQ = CInt(_RSC.FreqListQ / 1000 + 1) * 1000
					Array.Resize(_RSC.FreqList, _RSC.FreqListQ + 1)
				Case "FreqList"
					Dim i As Integer
					For i = 0 To _RSC.FreqListQ
						FreqSet_Read(_RSC.FreqList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case "Effects"
					Effects_Read(_RSC.Effects)
				Case "TempoListQ"
					StrBuff = Reader.Read()
					_RSC.TempoListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ResizeQ = CInt(_RSC.TempoListQ / 1000 + 1) * 1000
					Array.Resize(_RSC.TempoList, _RSC.TempoListQ + 1)
				Case "TempoList"
					Dim i As Integer
					For i = 0 To _RSC.TempoListQ
						TempoSet_Read(_RSC.TempoList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case "BeatListQ"
					StrBuff = Reader.Read()
					_RSC.BeatListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ResizeQ = CInt(_RSC.BeatListQ / 1000 + 1) * 1000
					Array.Resize(_RSC.BeatList, _RSC.BeatListQ + 1)
				Case "BeatList"
					Dim i As Integer
					For i = 0 To _RSC.BeatListQ
						BeatSet_Read(_RSC.BeatList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case "InteractionSave"
					Interaction_Read(_RSC.InteractionSave)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub Information_Read(ByRef _Info As String)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			If StrBuff <> "\0" Then
				_Info += StrBuff & " "
			End If
		Loop While StrBuff <> "\0"
		_Info = StringUtil.Trim(_Info)
	End Sub
	
	Public Sub Segment_Read(ByRef _Segment As Segment)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Position"
					StrBuff = Reader.Read()
					_Segment.Position = TestIfIsDouble(StrBuff)
				Case "Lyric"
					StrBuff = Reader.Read()
					_Segment.Lyric = StrBuff
				Case "Duration"
					StrBuff = Reader.Read()
					_Segment.Duration = TestIfIsDouble(StrBuff)
				Case "Effects"
					SegmentEffects_Read(_Segment.Effects)
				Case "StartFreq"
					StrBuff = Reader.Read()
					_Segment.StartFreq = TestIfIsDouble(StrBuff)
				Case "EndFreq"
					StrBuff = Reader.Read()
					_Segment.EndFreq = TestIfIsDouble(StrBuff)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub FreqSet_Read(ByRef _FreqSet As FreqSet)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Position"
					StrBuff = Reader.Read()
					_FreqSet.Position = TestIfIsDouble(StrBuff)
				Case "Freq"
					StrBuff = Reader.Read()
					_FreqSet.Freq = TestIfIsDouble(StrBuff)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub Effects_Read(ByRef _Effects As EffectsStruct)
		Dim ResizeQ As Integer
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "EnvelopeListQ"
					StrBuff = Reader.Read()
					_Effects.EnvelopeListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ResizeQ = CInt(_Effects.EnvelopeListQ / 1000 + 1) * 1000
					Array.Resize(_Effects.EnvelopeList, _Effects.EnvelopeListQ + 1)
				Case "EnvelopeList"
					Dim i As Integer
					For i = 0 To _Effects.EnvelopeListQ
						EnvelopeSet_Read(_Effects.EnvelopeList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub TempoSet_Read(ByRef _TempoSet As TempoSet)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Position"
					StrBuff = Reader.Read()
					_TempoSet.Position = TestIfIsDouble(StrBuff)
				Case "Tempo"
					StrBuff = Reader.Read()
					_TempoSet.Tempo = TestIfIsDouble(StrBuff)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub BeatSet_Read(ByRef _BeatSet As BeatSet)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "BarPosition"
					StrBuff = Reader.Read()
					_BeatSet.BarPosition = TestIfIsInt(StrBuff)
				Case "Factor"
					StrBuff = Reader.Read()
					_BeatSet.Beat_Factor = TestIfIsIntAndPositive(StrBuff)
				Case "Denominator"
					StrBuff = Reader.Read()
					_BeatSet.Beat_Denominator = TestIfIsIntAndPositive(StrBuff)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub Interaction_Read(ByRef _Interaction As UserInteraction)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "LastUserPosition"
					StrBuff = Reader.Read()
					_Interaction.LastUserPosition = TestIfIsDouble(StrBuff)
				Case "LastUserScale"
					StrBuff = Reader.Read()
					_Interaction.LastUserScale = TestIfIsDoubleAndPositive(StrBuff)
				Case "ViewType"
					StrBuff = Reader.Read()
					_Interaction.ViewType = TestIfIsViewType(StrBuff)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub SegmentEffects_Read(ByRef _SEffects As SegmentEffects)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "PElopeEnabled"
					StrBuff = Reader.Read()
					_SEffects.PElopeEnabled = TestIfIsBoolean(StrBuff)
				Case "PresetedEnvelope"
					StrBuff = Reader.Read()
					_SEffects.PresetedEnvelope = CType(TestIfIsPresetedEnvelope(StrBuff), _
						CVSCommon.Envelopes)
				Case "ADSR"
					ADSR_Read(_SEffects.ADSR)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub EnvelopeSet_Read(ByRef _EnvelopeSet As EnvelopeSet)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Position"
					StrBuff = Reader.Read()
					_EnvelopeSet.Position = TestIfIsDouble(StrBuff)
				Case "Magnitude"
					StrBuff = Reader.Read()
					_EnvelopeSet.Amplitude = TestIfIsDouble(StrBuff)
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub ADSR_Read(ByRef _ADSREnvelope As CVSCommon.ADSREnvelope)
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
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
		
End Module
'Template
'	Public Sub RSC_Read(ByRef _RSC As RSC)
'		Dim StrBuff As String
'		Do
'			StrBuff = Reader.Read()
'			Select Case StrBuff
'				Case ""
'				Case Else
'					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
'			End Select
'		Loop While StrBuff <> "End"
'	End Sub