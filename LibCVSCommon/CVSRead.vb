'    CVS文件读取函数
'    Provides CVS reading functions.
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

Public Module Read
	'Module for reading CVS file
	Dim Reader As RDLReader
	
	Public Sub Reader_Open(ByVal File As String)
		Reader = New RDLReader(File)
		If Reader.Read() <> "#CVS" Then
			'Not Cybervoice Script
			Throw New Exception("The file is not a Cybervoice Script !")
		End If
		If Reader.Read() <> "1.6" Then
			Throw New Exception("Wrong CVS version.")
		End If
	End Sub
	
	Public Sub Reader_Close()
		Reader.Close()
	End Sub
	
	Public Sub CVS_Read(ByRef _CVS As CVS)
		Dim StrBuff As String
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
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub Segment_Read(ByRef _Segment As Segment)
		Dim StrBuff As String
		Dim i As Integer
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "SyllableListQ"
					StrBuff = Reader.Read()
					_Segment.SyllableListQ = TestIfIsIntAndPositive(StrBuff) - 1
					ReDim _Segment.Effects.OpennessList(_Segment.SyllableListQ + 1)
					For i = 0 To _Segment.SyllableListQ + 1
						_Segment.Effects.OpennessList(i) = 1
					Next
					Array.Resize(_Segment.SyllableList, _Segment.SyllableListQ + 1)
				Case "SyllableList"
					For i = 0 To _Segment.SyllableListQ
						Syllable_Read(_Segment.SyllableList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case "FreqListQ"
					StrBuff = Reader.Read()
					_Segment.FreqListQ = TestIfIsIntAndPositive(StrBuff) - 1
					Array.Resize(_Segment.FreqList, _Segment.FreqListQ + 1)
				Case "FreqList"
					For i = 0 To _Segment.FreqListQ
						FreqSet_Read(_Segment.FreqList(i))
					Next
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
				Case "Effects"
					Effects_Read(_Segment.Effects)
				Case "StartTime"
					_Segment.StartTime = TestIfIsDoubleNotNegative(Reader.Read())
				Case Else
					'Throw New Exception("Invalid identifier as " & StrBuff & ".")
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub Syllable_Read(ByRef _Syllable As Syllable)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Start"
					SyllableStart_Read(_Syllable.Start)
				Case "Dest"
					SyllableDest_Read(_Syllable.Dest)
				Case "Transition"
					SyllableTransition_Read(_Syllable.Transition)
				Case Else
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub SyllableStart_Read(ByRef _Start As SyllableStart)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Type"
					StrBuff = Reader.Read().ToLower()
					If StrBuff = "new" Then
						_Start.Type = True
					ElseIf StrBuff = "preserved" Then
						_Start.Type = False
					Else
						Throw New Exception("Invalid syllable type identifier as " & StrBuff & ".")
					End If
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
					If _Start.Preserved <> 1 AndAlso _Start.Preserved <> 2 Then
						Throw New Exception("Invalid preserved buffer as " & StrBuff & ".")							
					End If
				Case Else
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub SyllableDest_Read(ByRef _Dest As SyllableDest)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Type"
					StrBuff = Reader.Read().ToLower()
					If StrBuff = "new" Then
						_Dest.Type = True
					ElseIf StrBuff = "preserved" Then
						_Dest.Type = False
					Else
						Throw New Exception("Invalid syllable type identifier as " & StrBuff & ".")
					End If
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
					If _Dest.Preserved <> 1 AndAlso _Dest.Preserved <> 2 Then
						Throw New Exception("Invalid preserved buffer as " & StrBuff & ".")							
					End If
				Case Else
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub SyllableTransition_Read(ByRef _Transition As SyllableTransition)
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
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub FreqSet_Read(ByRef _FreqSet As FreqSet)
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
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub Effects_Read(ByRef _Effects As EffectCollection)
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
					If Reader.Read() <> "End" Then
						Throw New Exception("List without an End.")
					End If
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
					'Preserved
				Case "Breath"
					BreathStruct_Read(_Effects.Breath)
				Case Else
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub EnvelopeSet_Read(ByRef _EnvelopeSet As EnvelopeSet)
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
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
	Public Sub ADSREnvelope_Read(ByRef _ADSREnvelope As ADSREnvelope)
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
	
	Public Sub BreathStruct_Read(ByRef _Breath As BreathStruct)
		Dim StrBuff As String
		Do
			StrBuff = Reader.Read()
			Select Case StrBuff
				Case "Magnitude"
					StrBuff = Reader.Read()
					_Breath.Magnitude = TestIfIsDouble(StrBuff)
				Case Else
					'Error
			End Select
		Loop While StrBuff <> "End"
	End Sub
	
End Module


