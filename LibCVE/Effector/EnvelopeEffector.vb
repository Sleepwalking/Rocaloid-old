'    一系列包络效果器。
'    A set of envelope effectors.
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
Public Class EnvelopeEffector
	Public Shared Overloads Sub ADSREnvelope(ByVal _WaveBuffer As WaveBuffer, _
											 ByVal Amp As Double, _
											 ByVal Attack As Integer, _
											 ByVal Decline As Integer, _
											 ByVal Release As Integer, _
											 ByVal EndTime As Integer)
		Dim i As Integer
		Dim T0 As Integer, T1 As Integer
		T0 = Attack
		T1 = EndTime - Release
		For i = 0 To Attack - 1
			_WaveBuffer.Data(i) *= Amp * (i / Attack)
		Next
		For i = 0 To Decline - 1
			_WaveBuffer.Data(i + T0) *= Amp * (1- i / Decline) + i / Decline
		Next
		For i = 0 To Release
			_WaveBuffer.Data(i + T1) *= 1 - i / Release
		Next
		'Maybe half framebuffer's data remains.
		For i = EndTime To EndTime + 1000
			_WaveBuffer.Data(i) = 0
		Next
	End Sub	
		
	Public Shared Overloads Sub ADSREnvelope(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment)
		Dim Amp As Double, Attack As Integer, Decline As Integer, Release As Integer
		Dim EndTime As Integer
		EndTime = _WaveBuffer.Pointer
		'EndTime = CInt(CVSCommon.GetSegmentTime(_Segment) * SampleRate)
		Amp = _Segment.Effects.ADSR.Amplitude
		Attack = CInt(_Segment.Effects.ADSR.Attack * SampleRate)
		Decline = CInt(_Segment.Effects.ADSR.Decline * SampleRate)
		Release = CInt(_Segment.Effects.ADSR.Release * SampleRate)
		If Release > EndTime Then
			Release = EndTime
		End If
		ADSREnvelope(_WaveBuffer, Amp, Attack, Decline, Release, EndTime)
	End Sub
	Public Shared Sub OpennessListRender(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment)
		Dim EList() As CVSCommon.EnvelopeSet
		Dim EListQ As Integer
		Dim i As Integer
		Dim TimeAcc As Double = 0
		
		EListQ = _Segment.TPhoneListQ + 1
		ReDim EList(EListQ)
		
		EList(0).Amplitude = _Segment.Effects.OpennessList(0)
		EList(0).Time = 0
		For i = 1 To EListQ
			TimeAcc += _Segment.TPhoneList(i - 1).Transition.Time
			EList(i).Amplitude = _Segment.Effects.OpennessList(i)
			EList(i).Time = TimeAcc
		Next
		EnvelopeListRender(_WaveBuffer, EList, EListQ)
	End Sub
	Public Shared Sub EnvelopeListRender(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment)
		EnvelopeListRender(_WaveBuffer, _Segment.Effects.EnvelopeList, _Segment.Effects.EnvelopeListQ)
	End Sub
	Public Shared Sub EnvelopeListRender(ByVal _WaveBuffer As WaveBuffer, ByVal EList() As CVSCommon.EnvelopeSet, ByVal EListQ As Integer)
		Dim i As Integer
		Dim a As Integer, b As Integer, t As Integer
		Dim Completeness As Double
		For i = 1 To EListQ
			a = CInt(EList(i - 1).Time * SampleRate)
			b = CInt(EList(i).Time * SampleRate) - 1
			For t = a To b
				Completeness = (t - a) / (b - a)
				_WaveBuffer.Data(t) *= (1 - Completeness) * EList(i - 1).Amplitude + _
					Completeness * EList(i).Amplitude
			Next
		Next
	End Sub
	Public Shared Sub ForwardCutter(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment)
		Dim i As Integer
		Dim CutSamples As Integer = CInt(_Segment.Effects.ForwardCut * SampleRate)
		Dim CutLength As Integer = _WaveBuffer.Pointer - CutSamples
		'Left Shift
		For i = 0 To CutLength
			_WaveBuffer.Data(i) = _WaveBuffer.Data(i + CutSamples)
		Next
		For i = 1 To 1000
			_WaveBuffer.Data(i + CutLength) = 0
		Next
		_WaveBuffer.Pointer -= CutSamples
		ADSREnvelope(_WaveBuffer, 1, Math.Min(CutSamples, 2000), 0, 0, _WaveBuffer.Pointer)
	End Sub
End Class
