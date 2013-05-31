'    生成特定频率下的连续语音帧。
'    Produces consecutive frames with a certain pitch.
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
Friend Class PitchPreSynthesizer
	Inherits Synthesizer
	Private PreSynthesizer1 As ConsecutivePreSynthesizer
	Private PreSynthesizer2 As ConsecutivePreSynthesizer
	Private Frame1 As FrameBuffer
	Private Frame2 As FrameBuffer
	Private Symbol As String
	Private ConsonantSkip As Boolean
	Private ConsonantPitchDeviateTo1 As Boolean
	Private ConsonantPitchDeviationGotten As Boolean
	Private PCalcLastDirection As Boolean
	Public Sub New()
		PreSynthesizer1 = New ConsecutivePreSynthesizer()
		PreSynthesizer2 = New ConsecutivePreSynthesizer()
		SetMixRatio(0)
		ConsonantPitchDeviationGotten = False
	End Sub
	Public Sub New(ByVal _Symbol As String)
		Symbol = _Symbol
		PreSynthesizer1 = New ConsecutivePreSynthesizer()
		PreSynthesizer2 = New ConsecutivePreSynthesizer()
		SetMixRatio(0)
		ConsonantPitchDeviationGotten = False
	End Sub
	Public Sub SetSymbol(ByVal _Symbol As String)
		Symbol = _Symbol
		PreSynthesizer1.ClearSymbol()
		PreSynthesizer2.ClearSymbol()
	End Sub
	Public ReadOnly Property Consonant() As Boolean
		Get
			Return PreSynthesizer1.Info.Consonant
		End Get
	End Property
	Public ReadOnly Property StartPoint() As Integer
		Get
			Return PreSynthesizer1.Info.StartPoint
		End Get
	End Property
	Public Function HLPitchSynth(ByVal PCalc As PitchCalculator) As FrameBuffer
		Dim Frame As FrameBuffer
		Frame = PreSynthesizer2.Synthesize
		Return FrameStretch(Frame, FreqToPeriod(PCalc.CurrentFreq) / PreSynthesizer2.Info.AveragePeriod)
	End Function
	Public Function Synthesize(ByVal PCalc As PitchCalculator, ByVal Time As Double) As FrameBuffer
		Dim SwapOccured As Boolean = False
		Dim PCalcDirectionUnchanged As Boolean
		Dim StartRatio As Double, EndRatio As Double
		
		PCalc.PitchCalc(Time)
		'If symbols of pre-synthesizers don't match, reload them.
		If PCalc.DirectionIsUp Then
			'Low Pitch -> High Pitch
			If PreSynthesizer1.Symbol <> Symbol Then
				PreSynthesizer1.Load(Symbol & "_" & PCalc.LowPitch)
				ConsonantPitchDeviationGotten = False
				#If DebugLevel > 0 Then
					CreateLog("PitchPreSynthesizer:	Load Symbol " & Symbol & "_" & PCalc.LowPitch)
				#End If
			End If
			If PreSynthesizer2.Symbol <> Symbol Then
				PreSynthesizer2.Load(Symbol & "_" & PCalc.HighPitch)
				ConsonantPitchDeviationGotten = False
				#If DebugLevel > 0 Then
					CreateLog("PitchPreSynthesizer:	Load Symbol " & Symbol & "_" & PCalc.HighPitch)
				#End If
			End If
		Else
			'High Pitch -> Low Pitch
			If PreSynthesizer1.Symbol <> Symbol Then
				PreSynthesizer1.Load(Symbol & "_" & PCalc.HighPitch)
				ConsonantPitchDeviationGotten = False
				#If DebugLevel > 0 Then
					CreateLog("PitchPreSynthesizer	Load Symbol " & Symbol & "_" & PCalc.HighPitch)
				#End If
			End If
			If PreSynthesizer2.Symbol <> Symbol Then
				PreSynthesizer2.Load(Symbol & "_" & PCalc.LowPitch)
				ConsonantPitchDeviationGotten = False
				#If DebugLevel > 0 Then
					CreateLog("PitchPreSynthesizer:	Load Symbol " & Symbol & "_" & PCalc.LowPitch)
				#End If
			End If
		End If
		'When a new transition starts, rearrange the synthesizers.
		PCalcDirectionUnchanged = (PCalc.DirectionIsUp = PCalcLastDirection) 'See [2]
		If PCalc.DirectionIsUp Then
			If PCalc.HighPitch <> PreSynthesizer2.Pitch Then
				If PCalcDirectionUnchanged Then
					'From ascending to ascending.
					If PCalc.LowPitch <> PreSynthesizer1.Pitch Then
						Swap(PreSynthesizer1, PreSynthesizer2)
					End If
					PreSynthesizer2.Load(Symbol & "_" & PCalc.HighPitch)
				Else
					'From descending to ascending.
					Swap(PreSynthesizer1, PreSynthesizer2)
					PreSynthesizer2.Load(Symbol & "_" & PCalc.HighPitch)
				End If
				#If DebugLevel > 0 Then
					CreateLog("PitchPreSynthesizer:	Transition " & Symbol & "_" & PCalc.LowPitch & " ->" _
						& Symbol & "_" & PCalc.HighPitch)
					SwapOccured = True
					#End If
				If PreSynthesizer1.Info.Consonant Then
					PreSynthesizer2.SkipConsonant()
				End If
			End If
		Else
			If PCalc.LowPitch <> PreSynthesizer2.Pitch Then
				If PCalcDirectionUnchanged Then
					'From descending to descending.
					If PCalc.HighPitch <> PreSynthesizer1.Pitch Then
						Swap(PreSynthesizer1, PreSynthesizer2)
					End If
					PreSynthesizer2.Load(Symbol & "_" & PCalc.LowPitch)
				Else
					'From ascending to descending.
					Swap(PreSynthesizer1, PreSynthesizer2)
					PreSynthesizer2.Load(Symbol & "_" & PCalc.LowPitch)
				End If
				#If DebugLevel > 0 Then
					CreateLog("PitchPreSynthesizer:	Transition " & Symbol & "_" & PCalc.HighPitch & " ->" _
														   & Symbol & "_" & PCalc.LowPitch)
					SwapOccured = True
				#End If
				If PreSynthesizer1.Info.Consonant Then
					PreSynthesizer2.SkipConsonant()
				End If
			End If
		End If
		PCalcLastDirection = PCalc.DirectionIsUp	'[2]
		'If frequency is beyond C2 - C5, stretch the frames.
		If PCalc.CurrentFreq >= FreqList(Pitch_C5) Then
			Return HLPitchSynth(PCalc)
		End If
		If PCalc.CurrentFreq <= FreqList(Pitch_C2) Then
			Return HLPitchSynth(PCalc)
		End If
		'MixRatio Prediction
		#If PeriodPredictionEnabled Then
			Dim TR1 As Double, TR2 As Double
			TR1 = PCalc.TransitionRatio
			SetStartMixRatio(TR1)
			PCalc.PitchCalc(Time + 1 / PCalc.GetFreqAt(Time))
			TR2 = PCalc.TransitionRatio
			If TR2 > 1 Then TR2 = 1
			If TR2 < TR1 Then TR2 = 1
			#If DebugLevel > 1 Then
				Console.WriteLine("PitchPreSynthesizer:	Ratio from " & TR1 & " to " & TR2)
			#End If
			StartRatio = TR1
			EndRatio = TR2
		#Else
			SetMixRatio(PCalc.TransitionRatio)
		#End If
		'Always change from Frame1 -> Frame2
		'Skip the consonants
		If PreSynthesizer1.Info.Consonant Then
			'If one of them is consonant, so is the other.
			If Time * SampleRate < PreSynthesizer1.Info.StartPoint + 1000 OrElse _
				Time * SampleRate < PreSynthesizer2.Info.StartPoint + 1000 Then
				'Synchronize
				If Not ConsonantPitchDeviationGotten Then
					If EndRatio > 0.5 Then
						ConsonantPitchDeviateTo1 = False
					Else
						ConsonantPitchDeviateTo1 = True
					End If
					ConsonantPitchDeviationGotten = True
				End If
				If ConsonantPitchDeviateTo1 Then
					PreSynthesizer2.Synchronize(PreSynthesizer1)
					ConsonantSkip = True 'Set up a flag here. Used at [1]
					Frame1 = PreSynthesizer1.Synthesize
					While Frame1.Length <= 0
						Frame1 = PreSynthesizer1.Synthesize
					End While
				Else
					PreSynthesizer1.Synchronize(PreSynthesizer2)
					ConsonantSkip = True 'Set up a flag here. Used at [1]
					Frame1 = PreSynthesizer2.Synthesize
					While Frame1.Length <= 0
						Frame1 = PreSynthesizer2.Synthesize
					End While					
				End If
				Return Frame1
			Else
				'[1]If just finished consonant part, make a smooth change to target pitch.
				If ConsonantSkip Then
					SetStartMixRatio(0)
					ConsonantSkip = False
				End If
			End If
		End If
		SetStartMixRatio(StartRatio)
		SetDestMixRatio(EndRatio)
		Frame1 = PreSynthesizer1.Synthesize()
		Frame2 = PreSynthesizer2.Synthesize()
		#If DebugLevel > 1 Then
			If SwapOccured Then
				Frame1.Data(0) = 0.5
			End If
		#End If
		Return FrameMix(Frame1, Frame2)
	End Function
End Class
