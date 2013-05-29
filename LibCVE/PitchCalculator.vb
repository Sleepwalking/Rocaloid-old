'    处理时间、频率、音调间的计算。被PitchPreSynthesizer使用。
'    This class deals with the relationship between time, frequency and pitch.
'    Used by PitchPreSynthesizer.
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
#Const DebugLevel = 0
Friend Class PitchCalculator
	Private TargetFreq As Double
	Private TargetTime As Double
	Private StartFreq As Double
	Private StartTime As Double
	Private TimeResolution As Double 'time to change from one pitch to another.
	Private LowPitch_ As Integer
	Private HighPitch_ As Integer
	Private TransitionRatio_ As Double
	Private CurrentFreq_ As Double
	Public ReadOnly Property LowPitch() As String
		Get
			If LowPitch_ > Pitch_C5 Then
				Return PitchList(Pitch_C5)
			ElseIf LowPitch_ < Pitch_C2 Then
				Return PitchList(Pitch_C2)
			Else
				Return PitchList(LowPitch_)				
			End If
		End Get
	End Property
	Public ReadOnly Property HighPitch() As String
		Get
			If HighPitch_ > Pitch_C5 Then
				Return PitchList(Pitch_C5)
			ElseIf HighPitch_ < Pitch_C2 Then
				Return PitchList(Pitch_C2)	
			Else
				Return PitchList(HighPitch_)				
			End If
		End Get
	End Property
	Public ReadOnly Property TransitionRatio() As Double
		Get
			Return TransitionRatio_
		End Get
	End Property
	Public ReadOnly Property DirectionIsUp() As Boolean
		Get
			If TargetFreq > StartFreq Then
				Return True
			Else
				Return False
			End If
		End Get
	End Property
	Public ReadOnly Property CurrentFreq() As Double
		Get
			Return CurrentFreq_
		End Get
	End Property
	Public Sub New()
		TargetFreq = 0
		TargetTime = 0
		StartFreq = 0
		StartTime = 0
		TimeResolution = 0.03
	End Sub
	Public Sub Restore()
		TargetFreq = 0
		TargetTime = 0
		StartFreq = 0
		StartTime = 0
		TimeResolution = 0.03
		LowPitch_ = 0
		HighPitch_ = 0
		TransitionRatio_ = 0
	End Sub
	Public Sub SetTarget(ByVal _StartFreq As Double, ByVal _StartTime As Double, _
		ByVal _TargetFreq As Double, ByVal _TargetTime As Double)
		If _TargetTime = _StartTime Then
			Throw New Exception("TargetTime equals to StartTime!")
		End If
		TargetFreq = _TargetFreq
		StartFreq = _StartFreq
		TargetTime = _TargetTime
		StartTime = _StartTime
	End Sub
	Public Sub SetResolution(ByVal _TimeResolution As Double)
		TimeResolution = _TimeResolution
	End Sub
	Public Sub PitchCalc(ByVal Time As Double)
		Dim Freq As Double = GetFreqAt(Time)
		Dim Quantity As Integer = CInt((TargetTime - StartTime) / TimeResolution) + 1
		Dim Range As Integer
		Dim Interval As Double
		Dim i As Double
		CurrentFreq_ = Freq
		'Choose quantity out of targetpitch - startpitch
		If DirectionIsUp Then
			'Low Pitch -> High Pitch
			Range = GetFloorPitch(TargetFreq) - GetFloorPitch(StartFreq) + 2
			Interval = Range / Quantity
			For i = GetFloorPitch(StartFreq) To GetFloorPitch(TargetFreq) + 1 Step Interval
				If Freq >= FreqList(CInt(Fix(i))) AndAlso Freq < FreqList(CInt(Fix(i + Interval))) Then
					LowPitch_ = CInt(Fix(i))
					HighPitch_ = CInt(Fix(i + Interval))
					If HighPitch_ > GetFloorPitch(TargetFreq) + 1 Then
						HighPitch_ = GetFloorPitch(TargetFreq) + 1
					End If
					Exit For
				End If
			Next
			TransitionRatio_ = (Freq - FreqList(LowPitch_)) / (FreqList(HighPitch_) - FreqList(LowPitch_))
		Else
			'High Pitch -> Low Pitch
			Range = GetFloorPitch(StartFreq) - GetFloorPitch(TargetFreq) + 2
			Interval = Range / Quantity
			For i = GetFloorPitch(StartFreq) + 1 To GetFloorPitch(TargetFreq) Step -Interval
				If Freq < FreqList(CInt(Fix(i))) AndAlso Freq >= FreqList(CInt(Fix(i - Interval))) Then
					HighPitch_ = CInt(Fix(i))
					LowPitch_ = CInt(Fix(i - Interval))
					If LowPitch_ < GetFloorPitch(TargetFreq) Then
						LowPitch_ = GetFloorPitch(TargetFreq)
					End If
					Exit For
				End If
			Next
			TransitionRatio_ = (FreqList(HighPitch_) - Freq) / (FreqList(HighPitch_) - FreqList(LowPitch_))
		End If
		#If DebugLevel > 0 Then
			CreateLog("PitchCalc:	Freq:" & Freq & " Quantity:" & Quantity & _
					  " Range:" & Range)
			CreateLog("			LowPitch:" & LowPitch & " HighPitch:" & HighPitch)
		#End If
	End Sub
	
	Public Function GetFreqAt(ByVal Time As Double) As Double
		Return StartFreq + (TargetFreq - StartFreq) * (Time - StartTime) / (TargetTime - StartTime)
	End Function
	
	
	'Get pitch by frequency or pitch string
	Public Shared Overloads Function GetPitch(ByVal Freq As Double) As Integer
		Dim i As Integer
		If Freq < (FreqList(1) + FreqList(2)) / 2 Then
			Return 0
		End If
		If Freq >= (FreqList(PitchListQ - 1) + FreqList(PitchListQ)) / 2 Then
			Return PitchListQ
		End If
		For i = 1 To PitchListQ - 1
			If Freq < (FreqList(i) + FreqList(i + 1)) / 2 AndAlso _
				Freq >= (FreqList(i) + FreqList(i - 1)) / 2 Then
				Return i
			End If
		Next
		Return -1
	End Function
	Public Shared Overloads Function GetPitch(ByVal Pitch As String) As Integer
		Dim i As Integer
		For i = 0 To PitchListQ
			If Pitch = PitchList(i) Then
				Return i
			End If
		Next
		Return -1
	End Function
	Public Shared Function GetFloorPitch(ByVal Freq As Double) As Integer
		Dim i As Integer
		For i = 0 To PitchListQ
			If Freq < FreqList(i) Then
				Return i - 1
			End If
		Next
		Return -1
	End Function
End Class
