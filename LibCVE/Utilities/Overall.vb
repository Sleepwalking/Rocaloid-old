'    包括一些公共变量、常数和函数，在哪可能都会用到。
'    Some common variables, constants and funcitons, might be used anywhere.
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
Friend Module OverAll
	Public Const SampleRate = 96000
	Public Const INFINITY = 99999
	Public Const PitchListQ = 59
	Public Const Pitch_C5 = 48
	Public Const Pitch_C2 = 12
	Public GlobalSendBack As SpeechSynthesizerSendBack
	Public ReadOnly WaveHead() As Byte =
	{
		&H52,&H49,&H46,&H46,&H24,&H10,&H1F,&H00, _
		&H57,&H41,&H56,&H45,&H66,&H6D,&H74,&H20, _
		&H10,&H00,&H00,&H00,&H01,&H00,&H01,&H00, _
		&H00,&H77,&H01,&H00,&H00,&HEE,&H02,&H00, _
		&H02,&H00,&H10,&H00,&H64,&H61,&H74,&H61, _
		&H00,&H10,&H1F,&H00
	}
	Public ReadOnly WaveHeadLength As Integer = 44
	Public ReadOnly PitchList() As String =
	{
		"C1","C#1","D1","D#1","E1","F1","F#1","G1","G#1","A1","A#1","B1",
		"C2","C#2","D2","D#2","E2","F2","F#2","G2","G#2","A2","A#2","B2", _
		"C3","C#3","D3","D#3","E3","F3","F#3","G3","G#3","A3","A#3","B3", _
		"C4","C#4","D4","D#4","E4","F4","F#4","G4","G#4","A4","A#4","B4", _
		"C5","C#5","D5","D#5","E5","F5","F#5","G5","G#5","A5","A#5","B5"
	}
	'Here's the frequency table derived from "a".
	'Tired of writing frequency calculation functions...(So Weird...)
	Public ReadOnly FreqList() As Double =
	{
		65.40639, 69.29565, 73.41619, 77.78175, 82.40689, 87.30706, _
		92.4986, 97.99886, 103.8262, 110, 116.5409, 123.4708, 129.9053, _
		137.7331, 145.8967, 154.5894, 163.8225, 173.5986, _
		183.9081, 194.7262, 206.4516, 218.6788, 231.8841, 245.5243, _
		260.1626, 275.8621, 291.7933, 308.6817, 327.6451, 346.5704, _
		366.4122, 388.664, 412.0172, 436.3636, 463.7681, 489.7959, _
		518.9189, 551.7241, 581.8182, 619.3549, 653.0612, 695.6522, _
		732.8244, 780.4878, 827.5862, 872.7273, 923.0769, 979.5919, _
		1043.478, 1108.73, 1174.659, 1244.508, 1318.51, 1396.913, _
		1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533
	}
	Public Sub Swap(Of T)(ByRef S1 As T, ByRef S2 As T)
		Dim Temp As T
		Temp = S1
		S1 = S2
		S2 = Temp
	End Sub
	Public Function GetDoubleSum(ByVal Arr() As Double) As Double
		Dim Acc As Double
		Dim i As Double
		For Each i In Arr
			Acc += i
		Next
		Return Acc
	End Function
	Public Function FreqToPeriod(ByVal Freq As Double) As Integer
		Return CInt(1 / Freq * SampleRate)
	End Function
	Public Function GetFreqByPitch(ByVal Pitch As String) As Double
		Dim i As Integer
		For i = 0 To PitchListQ
			If Pitch = PitchList(i) Then
				Return FreqList(i)
			End If
		Next
		Return 0
	End Function
	Public Function GenerateQuadEquation(ByVal x1 As Double, ByVal y1 As Double, _
										 ByVal x2 As Double, ByVal y2 As Double, _
										 ByVal x3 As Double, ByVal y3 As Double) As Double()
		Dim a As Double, b As Double, c As Double
		a = ((y1 - y2) / (x1 - x2) - (y2 - y3) / (x2 - x3)) / (x1 - x3)
		b = (y1 - y2) / (x1 - x2) - a * (x1 + x2)
		c = y1 - b * x1 - a * x1 * x1
		Return {a, b, c}
	End Function
End Module
Public Structure SpeechSynthesizerSendBack
	Dim VOT As Integer
End Structure