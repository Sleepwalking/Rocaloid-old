'    最终的合成器，生成可以被写入WaveBuffer的最终的帧。
'    The final synthesizer, produces the final frames which is written into WaveBuffers.
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
#Const DebugLevel = 1
#Const PeriodPredictionEnabled = True
Friend Class SpeechSynthesizer
	Inherits Synthesizer
	Private PitchSynth1 As PitchPreSynthesizer
	Private PitchSynth2 As PitchPreSynthesizer
	Private PCalc As PitchCalculator
	Private Segment As CVSCommon.Segment
	Private LastTime As Double
	Public Sub New()
		PitchSynth1 = New PitchPreSynthesizer()
		PitchSynth2 = New PitchPreSynthesizer()
		PCalc = New PitchCalculator()
		LastTime = -1
	End Sub
	Public Sub SetSegment(ByRef _Segment As CVSCommon.Segment)
		Segment = _Segment
		LastTime = -1
		PCalc.Restore
	End Sub
	Private Sub RegulatePitch(ByVal Time As Double)
		Dim Last_NextFreqSetNum As Integer, NextFreqSetNum As Integer
		Dim NextFreqSet As CVSCommon.FreqSet, LastFreqSet As CVSCommon.FreqSet
		Last_NextFreqSetNum = GetNextFreqNumByTime(LastTime)
		NextFreqSetNum = GetNextFreqNumByTime(Time)
		If NextFreqSetNum = -1 Then
			'After FreqList
			NextFreqSetNum = Segment.FreqListQ + 1
			NextFreqSet = Segment.FreqList(Segment.FreqListQ)
		Else
			NextFreqSet = Segment.FreqList(NextFreqSetNum)
		End If
		If Last_NextFreqSetNum = -1 Then
			Last_NextFreqSetNum = NextFreqSetNum
		End If
		'Only regulates when entering new FreqSet
		If NextFreqSetNum = Last_NextFreqSetNum Then
			'No Change.
		ElseIf NextFreqSetNum = Last_NextFreqSetNum + 1 Then
			'Entering new FreqSet
			If NextFreqSetNum = Segment.FreqListQ + 1 Then
				'After FreqList
				PCalc.SetTarget( _
					NextFreqSet.Freq, _
					NextFreqSet.Time, _
					NextFreqSet.Freq, _
					INFINITY)
				#If DebugLevel > 0 Then
					CreateLog("Speech Synthesizer:	PCalc exceeds target.")
				#End If
			Else
				LastFreqSet = Segment.FreqList(Last_NextFreqSetNum)
				PCalc.SetTarget( _
					LastFreqSet.Freq, _
					LastFreqSet.Time, _
					NextFreqSet.Freq, _
					NextFreqSet.Time)
				#If DebugLevel > 0 Then
					CreateLog("Speech Synthesizer:	PCalc target set:" & _
						LastFreqSet.Freq & ", " & _
						LastFreqSet.Time & ", " & _
						NextFreqSet.Freq & ", " & _
						NextFreqSet.Time)
				#End If
			End If
		Else
			'Error
			Throw New Exception("Invalid FreqSet.")
		End If
	End Sub
	Public Function Synthesize(ByVal Time As Double) As FrameBuffer
		Time = GetTimePassed(Time) 'Absolute time is useless in Syllables.
		
		If Time < LastTime Then
			Throw New Exception("Time of Synthesis is smaller than that of the last time!")
		End If
		
		RegulatePitch(Time)
		
		Dim LastSyllableNum As Integer, CurrentSyllableNum As Integer
		Dim CurrentSyllable As CVSCommon.Syllable
		LastSyllableNum = GetSyllableNumByTime(LastTime)
		CurrentSyllableNum = GetSyllableNumByTime(Time)
		If CurrentSyllableNum = -1 Then
			'After all Syllables
			Return GenerateEmptyFrameBuffer()
		End If
		CurrentSyllable = Segment.SyllableList(CurrentSyllableNum)
		Dim Frame1 As FrameBuffer, Frame2 As FrameBuffer
		If CurrentSyllableNum = LastSyllableNum Then
			'Just continue synthesizing
		ElseIf CurrentSyllableNum = LastSyllableNum + 1 Then
			'After a transition
			'First seek for "Preserved"
			If Not CurrentSyllable.Start.Type Then
				If CurrentSyllable.Start.Preserved = 1 Then
					'Preserves the Start of LastSyllable. No real effects.
					LastSyllableNum = LastSyllableNum
				ElseIf CurrentSyllable.Start.Preserved = 2 Then
					'Preserves the End of LastSyllable.
					Swap(PitchSynth1, PitchSynth2)
					#If DebugLevel > 0 Then
						CreateLog("Speech Synthesizer:	PitchSynth Swaps.")
					#End If
				Else
					Throw New Exception("Invalid Preserve Target as " & CurrentSyllable.Start.Preserved)
				End If
			End If
			If Not CurrentSyllable.Dest.Type Then
				If CurrentSyllable.Dest.Preserved = 2 Then
					'Preserves the End of LastSyllable. No real effects.
				ElseIf CurrentSyllable.Dest.Preserved = 1 Then
					'Preserves the Start of LastSyllable, though no real use.
					Swap(PitchSynth1, PitchSynth2)
					#If DebugLevel > 0 Then
						CreateLog("Speech Synthesizer:	PitchSynth Swaps.")
					#End If
				Else
					Throw New Exception("Invalid Preserve Target as " & CurrentSyllable.Dest.Preserved)
				End If
				If CurrentSyllable.Dest.Preserved = CurrentSyllable.Start.Preserved Then
					Throw New Exception("Same Preserve Target as " & CurrentSyllable.Start.Preserved)
				End If
			End If
			'Second seek for "New"
			If CurrentSyllable.Start.Type Then
				PitchSynth1.SetSymbol(CurrentSyllable.Start.Symbol)
				#If DebugLevel > 0 Then
					CreateLog("Speech Synthesizer:	" & CurrentSyllable.Start.Symbol & " -> " & _
								"PitchSynth1")
				#End If
			End If
			If CurrentSyllable.Dest.Type Then
				PitchSynth2.SetSymbol(CurrentSyllable.Dest.Symbol)
				#If DebugLevel > 0 Then
					CreateLog("Speech Synthesizer:	" & CurrentSyllable.Start.Symbol & " -> " & _
								"PitchSynth2")
				#End If
			End If
		Else
			'Error
			'Throw New Exception("Uncorrect time for synthesis process. Syllable(s) may be skipped.")
		End If
		
		'Synthesize
		PCalc.PitchCalc(Time)
		Frame1 = PitchSynth1.Synthesize(PCalc, Time)
		Frame2 = PitchSynth2.Synthesize(PCalc, Time)
		Dim TR1 As Double, TR2 As Double
		#If PeriodPredictionEnabled Then
			'MixRatio Prediction
			TR1 = GetTransitionRatio(CurrentSyllableNum, Time)
			SetStartMixRatio(TR1)
			TR2 = GetTransitionRatio(CurrentSyllableNum, Time + Frame2.Length / SampleRate)
			'In very rare cases, especially when approaching the next syllable, GetTransitionRatio may be different
			'from the real situation (TR2 -> 0, or TR2 > 1).
			If Math.Abs(TR2 - TR1) > 0.3 AndAlso TR2 < TR1 Then	TR2 = 1
			If TR2 > 1 Then	TR2 = 1
			SetDestMixRatio(TR2)
			#If DebugLevel > 1 Then
				If TR1 < 0 Then
					TR1 = TR1
				End If
				Console.WriteLine("SpeechSynthesizer:	Ratio from " & TR1 & " to " & TR2)
			#End If
		#Else
			SetMixRatio(GetTransitionRatio(CurrentSyllableNum, Time))
		#End If	
		#If DebugLevel > 1 Then
			Dim TempWB1 As WaveBuffer = New WaveBuffer(0.1)
			TempWB1.Write(Frame1)
			TempWB1.OutputToWave("Z:\F1.wav")
			Dim TempWB2 As WaveBuffer = New WaveBuffer(0.1)
			TempWB2.Write(Frame2)
			TempWB2.OutputToWave("Z:\F2.wav")
			Dim TempWB3 As WaveBuffer = New WaveBuffer(0.1)
			TempWB3.Write(FrameMix(Frame1, Frame2))
			TempWB3.OutputToWave("Z:\F.wav")
		#End If
		'Get prepared for the next synthesis
		LastTime = Time
		Return FrameMix(Frame1, Frame2)
	End Function
	Private Function GetNextFreqNumByTime(ByVal Time As Double) As Integer
		Dim i As Integer
		For i = 0 To Segment.FreqListQ
			If Segment.FreqList(i).Time > Time Then
				Return i
			End If
		Next
		'Time after FreqSets
		Return -1
	End Function
	Private Function GetLastFreqNumByTime(ByVal Time As Double) As Integer
		Dim i As Integer
		For i = 0 To Segment.FreqListQ
			If Segment.FreqList(i).Time > Time Then
				Return i - 1
			End If
		Next
		'Time after FreqSets
		Return Segment.FreqListQ
	End Function
	Private Function GetTransitionRatio(ByVal SyllableNum As Integer, _
										ByVal Time As Double) As Double
		Dim Completeness As Double
		Dim ConsonantLen As Double = 0
		'Skip the consonant part.
		If PitchSynth1.Consonant And Segment.SyllableList(SyllableNum).Transition.StartRatio = 0 Then
			GlobalSendBack.VOT = PitchSynth1.StartPoint
			ConsonantLen = PitchSynth1.StartPoint / SampleRate
		End If
		If PitchSynth2.Consonant Then
			ConsonantLen = Math.Max(PitchSynth2.StartPoint, ConsonantLen) / SampleRate
		End If
		Time -= ConsonantLen
		If Time < 0 Then
			Return 0
		End If
		Completeness = GetTimePassedInSyllable(SyllableNum, Time) / _
					   (Segment.SyllableList(SyllableNum).Transition.Time - ConsonantLen)
		
		Return Completeness * Segment.SyllableList(SyllableNum).Transition.EndRatio + _
			   (1 - Completeness) * Segment.SyllableList(SyllableNum).Transition.StartRatio
	End Function
	Private Function GetTimePassedInSyllable(ByVal SyllableNum As Integer, _
											 ByVal Time As Double) As Double
		Dim i As Integer
		Dim acc As Double
		For i = 0 To SyllableNum - 1
			acc += Segment.SyllableList(i).Transition.Time
		Next
		Return Time - acc
	End Function
	Private Function GetTimePassed(ByVal Time As Double) As Double
		Return Time - Segment.StartTime
	End Function
	Private Function GetSyllableNumByTime(ByVal Time As Double) As Integer
		If Time < 0 Then
			Return -1
		End If
		Dim i As Integer
		Dim acc As Double
		For i = 0 To Segment.SyllableListQ
			acc += Segment.SyllableList(i).Transition.Time
			If acc >= Time Then
				Return i
			End If
		Next
		Return -1
	End Function
	Private Function GetSyllableByTime(ByVal Time As Double) As CVSCommon.Syllable
		Dim i As Integer = GetSyllableNumByTime(Time)
		If  i > 0 Then
			Return Segment.SyllableList(i)
		End If
		'Time longer than Syllables
		Dim EmptySyllable As CVSCommon.Syllable
		EmptySyllable.Start.Type = True
		EmptySyllable.Start.Symbol = "NULL"
		EmptySyllable.Dest.Type = True
		EmptySyllable.Dest.Symbol = "NULL"
		Return EmptySyllable
	End Function
End Class
