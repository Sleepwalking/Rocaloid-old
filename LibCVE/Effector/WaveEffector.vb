'    一系列波形效果器。
'    A set of wave effectors.
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
Friend Class WaveEffector
	Public Shared Sub Blur(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment)
		'Blur the end of a word.
		Dim Temp(50) As Double
		Dim TempPointer As Integer = 0
		Dim EndTime As Integer = CInt(CVSCommon.GetSegmentTime(_Segment) * SampleRate)
		Dim Range As Integer = -10000
		Dim Equ(2) As Double, Ratio As Double
		If Range < -EndTime Then
			Range = -EndTime
		End If
		Equ = GenerateQuadEquation(0, 0, -Range, 1, -Range * 0.8, 0.5)
		For i = Range To 0
			If TempPointer = 50 Then
				TempPointer = 0
			Else
				TempPointer += 1
			End If
			Ratio = Equ(0) * i * i - Equ(1) * i + Equ(2)
			Temp(TempPointer) = _WaveBuffer.Data(i + EndTime)
			_WaveBuffer.Data(i + EndTime) = _WaveBuffer.Data(i + EndTime) * Ratio _
											+ GetDoubleSum(Temp) / 51 * (1 - Ratio)
		Next
	End Sub
	
	Public Shared Sub BreathNoise(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment)
		'Differentiate the wave, add the differences back to the buffer.
		Dim Magnitude As Double = _Segment.Effects.Breath.Magnitude
		For i = 0 To _WaveBuffer.Pointer - 1
			_WaveBuffer.Data(i) += (_WaveBuffer.Data(i) - _WaveBuffer.Data(i + 1)) * Magnitude
		Next
	End Sub
	
	Public Shared Sub Shrink(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment, ByRef SendBack As SpeechSynthesizerSendBack)
		Dim ShrinkLen As Integer = CInt(_Segment.Effects.Shrink * SampleRate)
		Dim RemainingLen As Integer
		Dim ConsonantLen As Integer = SendBack.VOT 'loaded in SpeechSynthesizer
		If ShrinkLen > ConsonantLen / 2 Then ShrinkLen = CInt(ConsonantLen / 2)
		If ConsonantLen <= 0 Then Exit Sub 'Vowels needn't shrinking.
		
		RemainingLen = ConsonantLen - ShrinkLen
		Dim buffer1(RemainingLen) As Double
		Dim buffer2(RemainingLen) As Double
		Dim i As Integer
		For i = 0 To RemainingLen - 1
			buffer1(i) = _WaveBuffer.Data(i) * (1 - i / (RemainingLen - 1))
		Next
		For i = ShrinkLen To ConsonantLen - 1
			buffer2(i - ShrinkLen) = _WaveBuffer.Data(i) * (i - ShrinkLen) / (RemainingLen - 1)
		Next
		
		'Left shift the wavebuffer
		For i = RemainingLen To _WaveBuffer.Pointer
			_WaveBuffer.Data(i) = _WaveBuffer.Data(i + ShrinkLen)
		Next
		
		_WaveBuffer.Pointer -= ShrinkLen
		
		'Write back
		For i = 0 To RemainingLen - 1
			_WaveBuffer.Data(i) = buffer1(i) + buffer2(i)
		Next
	End Sub
End Class
