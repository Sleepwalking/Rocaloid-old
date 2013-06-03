'    一个EnvelopeEffector和WaveEffector的控制器。
'    A controller for EnvelopeEffectors and WaveEffectors.
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
Public Class Effector
	Public Shared Sub Render(ByVal _WaveBuffer As WaveBuffer, ByRef _Segment As CVSCommon.Segment, ByRef SendBack As SpeechSynthesizerSendBack)
		EnvelopeEffector.OpennessListRender(_WaveBuffer, _Segment)
		If _Segment.Effects.Shrink <> 0 Then
			WaveEffector.Shrink(_WaveBuffer, _Segment, SendBack)
		End If
		If _Segment.Effects.ForwardCut <> 0 Then
			EnvelopeEffector.ForwardCutter(_WaveBuffer, _Segment)
		End If
		WaveEffector.Blur(_WaveBuffer, _Segment)
		If _Segment.Effects.PElopeEnabled Then
			'Use preseted envelope
			Select Case _Segment.Effects.PresetedEnvelope
			    Case CVSCommon.Envelopes.ADSR
			    	'Apply ADSREnvelope
			    	EnvelopeEffector.ADSREnvelope(_WaveBuffer, _Segment)
			    Case Else
					Throw New Exception("Invalid Preseted Envelope As " & _Segment.Effects.PresetedEnvelope)
			End Select
		End If
		If _Segment.Effects.ElistEnabled Then
			'Use envelope list
			EnvelopeEffector.EnvelopeListRender(_WaveBuffer, _Segment)
		End If
		If _Segment.Effects.Breath.Magnitude <> 0 Then
			WaveEffector.BreathNoise(_WaveBuffer, _Segment)
		End If
	End Sub
End Class
