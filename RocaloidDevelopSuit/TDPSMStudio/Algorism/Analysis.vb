'    常用的时域DSP函数
'    Useful Time-Domain DSP Functions
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

Public Module Analysis
	Public Function SelfCorrelation(ByRef Wave As WaveBuffer, _
									ByVal Position As Integer, _
									ByVal Length As Integer, _
									ByVal CompareLength As Integer) As Double
		Dim i As Integer
		Dim dest As Integer = Position + CompareLength
		Dim acc As Double = 0
		For i = Position To dest
			acc += Wave.Data(i) * Wave.Data(i + Length)
		Next
		Return acc
	End Function
	Public Function SelfDifference(ByRef Wave As WaveBuffer, _
								   ByVal Position As Integer, _
								   ByVal Length As Integer, _
								   ByVal CompareLength As Integer) As Double
		Dim i As Integer
		Dim dest As Integer = Position + CompareLength
		Dim acc As Double = 0
		For i = Position To dest
			acc += Math.Abs(Wave.Data(i) - Wave.Data(i + Length))
		Next
		Return acc
	End Function
	Public Sub SelfCorrelationTo(ByRef WaveFrom As WaveBuffer, _
								 ByRef WaveTo As WaveBuffer, _
								 ByVal Position As Integer, _
								 ByVal MoveLength As Integer, _
								 ByVal CompareLength As Integer)
		Dim i As Integer
		For i = 0 To MoveLength
			WaveTo.Data(i) = SelfCorrelation(WaveFrom, Position, i, CompareLength) / CompareLength * 100
		Next
		WaveTo.Pointer = MoveLength
	End Sub
	Public Sub SelfDifferenceTo(ByRef WaveFrom As WaveBuffer, _
								ByRef WaveTo As WaveBuffer, _
								ByVal Position As Integer, _
								ByVal MoveLength As Integer, _
								ByVal CompareLength As Integer)
		Dim i As Integer
		For i = 0 To MoveLength
			WaveTo.Data(i) = SelfDifference(WaveFrom, Position, i, CompareLength) / CompareLength * 100
		Next
		WaveTo.Pointer = MoveLength
	End Sub
	
	Public Function FindBasePeriod(ByRef Wave As WaveBuffer, ByVal Position As Integer) As Double
		Dim Wave1 As WaveBuffer, Wave2 As WaveBuffer
		Wave1 = New WaveBuffer(CInt(3500))
		Wave2 = New WaveBuffer(CInt(3500))
		SelfCorrelationTo(Wave, Wave1, Position, 2000, 1000)
		SelfDifferenceTo(Wave1, Wave2, 0, 2000, 1000)
		WaveEffects.EasyBalance(Wave2)
		Dim min As Double = Wave2.Data(0)
		Dim i As Integer
		Dim a As Double, b As Double
		For i = 50 To 1000
			If Wave2.Data(i) < min * 0.85 Then
				'Possible
				a = Wave2.Data(i + 2) - Wave2.Data(i)
				b = Wave2.Data(i) - Wave2.Data(i - 2)
				If a > 0 AndAlso b < 0 Then
					Return i
				End If
			End If
		Next
		Return 0
	End Function
	
	Public Sub GenerateEnvelope(ByRef TargetList As PointList, _
								ByRef Wave As WaveBuffer, _
								ByVal Interval As Integer)
		Dim i As Integer, PointQ As Integer
		PointQ = CInt(Wave.Pointer / Interval)
		ReDim TargetList.Points(PointQ)
		For i = 1 To PointQ - 1
			With TargetList
				.Points(i).X = CSng(i * Interval - Interval / 2)
				.Points(i).Y = CSng(Wave.GetMax(CInt(.Points(i - 1).X), CInt(.Points(i).X)) - _
					 				Wave.GetMin(CInt(.Points(i - 1).X), CInt(.Points(i).X)))
			End	With
		Next
		TargetList.PointQ = PointQ
	End Sub
	
	Public Sub GenerateEnergyList(ByRef TargetList As PointList, _
								  ByRef Wave As WaveBuffer, _
								  ByVal Interval As Integer)
		Dim i As Integer, PointQ As Integer
		PointQ = CInt(Wave.Pointer / Interval)
		ReDim TargetList.Points(PointQ)
		For i = 1 To PointQ - 1
			With TargetList
				.Points(i).X = CSng(i * Interval - Interval / 2)
				.Points(i).Y = CSng(CalculateEnergy(Wave, CInt(.Points(i - 1).X), CInt(.Points(i).X))) _
							   / Interval * 100
			End	With
		Next
		TargetList.PointQ = PointQ
	End Sub
	
	Public Sub GenerateZeroPassRateList(ByRef TargetList As PointList, _
										ByRef Wave As WaveBuffer, _
										ByVal Interval As Integer)
		Dim i As Integer, PointQ As Integer
		PointQ = CInt(Wave.Pointer / Interval)
		ReDim TargetList.Points(PointQ)
		For i = 1 To PointQ - 1
			With TargetList
				.Points(i).X = CSng(i * Interval - Interval / 2)
				.Points(i).Y = CSng(CalculateZeroPass(Wave, CInt(.Points(i - 1).X), CInt(.Points(i).X))) _
							   / Interval
			End	With
		Next
		TargetList.PointQ = PointQ
	End Sub
	
	Public Function CalculateEnergy(ByRef Wave As WaveBuffer, _
									ByVal _From As Integer, _
									ByVal _To As Integer) As Double
		Dim i As Integer
		Dim acc As Double = 0
		For i = _From To _To
			acc += Wave.Data(i) ^ 2
		Next
		Return acc
	End Function
		
	Public Function CalculateZeroPass(ByRef Wave As WaveBuffer, _
									  ByVal _From As Integer, _
									  ByVal _To As Integer) As Integer
		Dim i As Integer
		Dim acc As Integer = 0
		For i = _From To _To
			If (Wave.Data(i) > 0 AndAlso Wave.Data(i - 1) < 0) OrElse _
			   (Wave.Data(i) < 0 AndAlso Wave.Data(i - 1) > 0) Then
				acc += 1
			End If
		Next
		Return acc
	End Function
	
	Public Sub GenerateRecoList(ByRef MainList As PointList, _
								ByRef EnvelopeList As PointList)
		Dim i As Integer
		ReDim MainList.Points(EnvelopeList.PointQ)
		For i = 3 To EnvelopeList.PointQ - 5
			MainList.Points(i).X = EnvelopeList.Points(i).X
			MainList.Points(i).Y =	- EnvelopeList.Points(i).Y _
									+ EnvelopeList.Points(i + 5).Y
			If MainList.Points(i).Y < 0 Then MainList.Points(i).Y = 0
		Next
		MainList.PointQ = EnvelopeList.PointQ - 3
	End Sub
	Public Function FindPeriodStartPosition(ByRef EnvelopeList As PointList, _
											ByRef Wave As WaveBuffer, _
											ByVal BasePeriod As Integer) As Integer
		Dim i As Integer
		Dim pos As Integer = 0
		Dim count As Integer = 0
		Dim forstep As Integer = 4
		For i = 0 To EnvelopeList.PointQ Step forstep
			If EnvelopeList.Points(i).Y > 0.005 Then
				If Math.Abs(FindBasePeriod(Wave, CInt(EnvelopeList.Points(i).X) + 4800) - BasePeriod) < BasePeriod * 0.1 Then
					pos = CInt(EnvelopeList.Points(i).X)
					count += 1
					forstep = 1
					If count > 2 Then Exit For
				Else
					count = 0
				End If
			End If
		Next
		Return pos
	End Function
	Public Function FindIdealAnalysisStartPoint(ByRef Wave As WaveBuffer, _
												ByVal ApproximatingPosition As Integer, _
												ByVal BasePeriod As Integer) As Integer
		Dim i As Integer, j As Integer
		Dim acc1 As Double, acc2 As Double
		Dim HalfPeriod As Integer = CInt(BasePeriod / 2)
		Dim min As Double = Wave.GetMin(ApproximatingPosition, ApproximatingPosition + BasePeriod)
		Dim max As Double = Wave.GetMax(ApproximatingPosition, ApproximatingPosition + BasePeriod)
		For i = ApproximatingPosition To ApproximatingPosition + BasePeriod * 2
			If (Wave.Data(i - 1) > 0 AndAlso Wave.Data(i) < 0) OrElse _
			   (Wave.Data(i) > 0 AndAlso Wave.Data(i - 1) < 0) Then
				acc1 = 0
				For j = i To i + HalfPeriod
					acc1 += Wave.Data(j)
				Next
				acc2 = 0
				For j = i + HalfPeriod To i +BasePeriod
					acc2 += Wave.Data(j)
				Next
				If acc2 < acc1 Then Return i
			End If
		Next
		Return -1
	End Function
	
	Public Function FindSilenceBreakPos(ByRef Wave As WaveBuffer) As Integer
		Dim max As Double, min As Double
		Dim position As Integer = 0
		max = 0
		min = 0
		While max - min < Setting_SilentThreshold
			position += 1000
			max = Wave.GetMax(position, position + 1000)
			min = Wave.GetMin(position, position + 1000)
		End While
		Return position
	End Function
	
	Public Function GetAverageVolume(ByRef Wave As WaveBuffer, _
									 ByVal _From As Integer, ByVal _To As Integer) As Double
		Dim max As Double, min As Double
		Dim position As Integer = _From
		Dim sum As Double = 0
		Dim quantity As Integer = 0
		While position < _To
			max = Wave.GetMax(position, position + 1000)
			min = Wave.GetMin(position, position + 1000)
			sum += max - min
			quantity += 1
			position += 1000
		End While
		Return sum / quantity
	End Function
	
	Public Function FindMaximumSlopeInEnvelopeList(ByRef Envelope As PointList, _
											   ByVal _From As Integer, ByVal _To As Integer) As Double
		Dim max As Double = -999
		Dim i As Integer = 0
		While Envelope.Points(i).X < _From
			i += 1
		End While
		While Envelope.Points(i).X < _To
			If Envelope.Points(i).Y - Envelope.Points(i - 1).Y > max Then
				max = Envelope.Points(i).Y - Envelope.Points(i - 1).Y
			End If
			i += 1
		End While
		Return max
	End Function
End Module
