'    时域波形效果器
'    Time-Domain Wave Effectors
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

Public Module WaveEffects
	Public Sub MovingAverage(ByRef WaveFrom As WaveBuffer, ByRef WaveTo As WaveBuffer, _
							 ByVal Length As Integer, ByVal Strength As Double)
		Dim i As Integer
		Dim buffer(Length) As Double
		Dim buffer_pointer As Integer = 0
		Dim index As Integer
		Dim DblSum As Double = 0
		For i = 0 To Length
			WaveTo.Data(i) = 0
		Next
		For i = Length + 1 To WaveFrom.Pointer
			DblSum -= WaveFrom.Data(i - Length)
			DblSum += WaveFrom.Data(i)
			index = i - CInt(Length / 2)
			WaveTo.Data(index) = WaveFrom.Data(index) * (1 - Strength) + _
							 	 DblSum / (Length + 1) * Strength
		Next
		WaveTo.Pointer = WaveFrom.Pointer
	End Sub
	
	Public Sub SelfMovingAverage(ByRef Wave As WaveBuffer, _
								 ByVal Length As Integer, ByVal Strength As Double, _
								 ByVal _From As Integer, ByVal _To As Integer)
		Dim i As Integer
		Dim index As Integer
		Dim DblSum As Double = 0
		If _From < CInt(Length / 2) Then _From = CInt(Length / 2)
		For i = _From To _To
			DblSum -= Wave.Data(i - Length)
			DblSum += Wave.Data(i)
			index = i - CInt(Length / 2)
			Wave.Data(index) = Wave.Data(index) * (1 - Strength) + _
							   DblSum / (Length + 1) * Strength
		Next
	End Sub
	
	Public Sub Balance(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer)
		Dim i, j, LevelCount As Integer
		Dim Min, Max, Offset As Double
		Dim Level(1000) As Double
		'1 Level = 0.05s = 4800 samples
		LevelCount = 0
		For i = _From - 500 To _To + 500 Step 1000
			Min = Wave.GetMin(i, i + 1000)
			Max = Wave.GetMax(i, i + 1000)
			Level(LevelCount) = (Min + Max)/2
			LevelCount += 1
		Next
		For i = 0 To LevelCount
			For j = i * 1000 + 1 To i * 1000 + 1000
				Offset = (Level(i) * (1 - (j - i * 1000) / 1000) + _
						  Level(i + 1) * (j - i * 1000) / 1000)
				Wave.Data(_From + j) -= Offset
			Next
		Next
	End Sub
	
	Public Sub Balance(ByRef Wave As WaveBuffer)
		Balance(Wave, 0, Wave.Pointer)
	End Sub
	
	Public Sub LowPassBalance(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer)
		Dim i As Integer
		Dim LowPassWave As WaveBuffer = New WaveBuffer(Wave.Pointer)
		MovingAverage(Wave, LowPassWave, 1000, 1)
		For i = _From To _To
			Wave.Data(i) -= LowPassWave.Data(i)
		Next
	End Sub
	
	Public Sub LowPassBalance(ByRef Wave As WaveBuffer)
		LowPassBalance(Wave, 0, Wave.Pointer)
	End Sub
	
	Public Sub Normalize(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer, _
						 ByVal Mul As Double)
		Dim i, j, LevelCount As Integer
		Dim Min, Max, Factor As Double
		Dim Level(1000) As Double
		'1 Level=0.025s=3400 samples
		LevelCount = 0
		For i = _From - 500 To _To + 500 Step 1000
			Min = Wave.GetMin(i, i + 1000)
			Max = Wave.GetMax(i, i + 1000)
			Level(LevelCount) = Max - Min
			LevelCount += 1
		Next
		For i = 0 To LevelCount
			For j = i * 1000 + 1 To i * 1000 + 1000
				Factor = Mul / (Level(i) * (1 - (j - i * 1000) / 1000) + _
								Level(i + 1) * (j - i * 1000) / 1000)
				If Factor < 1 Then Wave.Data(_From + j) *= Factor
			Next
		Next
	End Sub
	
	Public Sub Silence(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer, _
					   ByVal Fade As Integer)
		Dim i As Integer
		For i = _From - Fade To _From - 1
			Wave.Data(i) *= 1 - (i - _From + Fade) / Fade
		Next
		For i = _From To _To - 1
			Wave.Data(i) = 0
		Next
		For i = _To To _To + Fade
			Wave.Data(i) *= (i - _To) / Fade
		Next
	End Sub
	
	Public Sub FadeIn(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer, _
					  ByVal Fade As Integer, ByVal Low As Double)
		Dim i As Integer
		Dim ratio As Double
		For i = _From - Fade To _From - 1
			ratio = (i - _From + Fade) / Fade
			Wave.Data(i) *= (1 - ratio) + Low * ratio
		Next
		For i = _From To _To
			ratio = (i - _From) / (_To - _From)
			Wave.Data(i) *= ratio + Low * (1 - ratio)
		Next
	End Sub
	
	Public Sub Weaken(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer, _
					  ByVal Low As Double)
		Dim Quad() As Double
		Dim a As Double, b As Double, c As Double
		Dim i As Integer
		Quad = OverAll.GenerateQuadEquation(_From, 1, (_From + _To) / 2, Low, _To, 1)
		a = Quad(0)
		b = Quad(1)
		c = Quad(2)
		For i = _From To _To
			Wave.Data(i) *= a * i ^ 2 + b * i + c
		Next
	End Sub
	
	Public Sub EasyBalance(ByRef Wave As WaveBuffer)
		Dim min As Double, max As Double
		Dim shift As Double
		min = Wave.GetMin(0, Wave.Pointer)
		max = Wave.GetMax(0, Wave.Pointer)
		shift = (max + min) / 2
		Dim i As Integer
		For i = 0 To Wave.Pointer
			Wave.Data(i) -= shift
		Next
	End Sub
	
	Public Sub CutWave(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer)
		Dim i As Integer
		Dim MoveDest As Integer = Wave.Pointer - (_To - _From)
		Dim MoveLen As Integer = _To - _From
		For i = _From To MoveDest
			Wave.Data(i) = Wave.Data(i + MoveLen)
		Next
		Wave.Pointer = MoveDest
	End Sub
	
	Public Sub ChgVolume(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer, _
						 ByVal Mul As Double)
		Dim i As Integer
		For i = _From To _To
			Wave.Data(i) *= Mul
		Next
	End Sub
	
	Public Sub Shrink(ByRef Wave As WaveBuffer, ByVal _From As Integer, ByVal _To As Integer, _
					  ByVal ShrinkLen As Integer)
		Dim RemainingLen As Integer
		Dim OriginalLen As Integer = _To - _From
		If ShrinkLen > OriginalLen / 2 Then ShrinkLen = CInt(OriginalLen / 2)
		RemainingLen = OriginalLen - ShrinkLen
		
		Dim buffer1(RemainingLen) As Double
		Dim buffer2(RemainingLen) As Double
		Dim i As Integer
		
		For i = 0 To RemainingLen - 1
			buffer1(i) = Wave.Data(i + _From) * (1 - i / (RemainingLen - 1))
		Next
		For i = ShrinkLen To OriginalLen - 1
			buffer2(i - ShrinkLen) = Wave.Data(i + _From) * (i - ShrinkLen) / (RemainingLen - 1)
		Next
		
		'Left shift the wavebuffer
		For i = RemainingLen To Wave.Pointer - _From
			Wave.Data(i + _From) = Wave.Data(i + ShrinkLen + _From)
		Next
		Wave.Pointer -= ShrinkLen
		
		'Write back
		For i = 0 To RemainingLen - 1
			Wave.Data(i + _From) = buffer1(i) + buffer2(i)
		Next
	End Sub
	
	Private Function GetDblSum(ByRef _Array() As Double) As Double
		Dim i As Double
		Dim Sum As Double = 0
		For Each i In _Array
			Sum += i
		Next
		Return Sum
	End Function
End Module
