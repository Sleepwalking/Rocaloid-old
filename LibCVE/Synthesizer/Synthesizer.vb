'    Synthesizer类是所有合成器的基类。它提供TDPSM的基本算法。
'    Synthesizer Class acts as the basic class of all synthesizers. It provides the basic algorisms of TDPSM.
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
Friend MustInherit Class Synthesizer
	Private MixRatio As Double = 0
	Private MixRatio2 As Double = 0
	Public Sub SetMixRatio(ByVal _MixRatio As Double)
		MixRatio = _MixRatio
		MixRatio2 = _MixRatio
	End Sub
	Public Sub SetStartMixRatio(ByVal _MixRatio As Double)
		MixRatio = _MixRatio
	End Sub
	Public Sub SetDestMixRatio(ByVal _MixRatio As Double)
		MixRatio2 = _MixRatio
	End Sub
	Public Function FrameMix(ByVal Frame1 As FrameBuffer, ByVal Frame2 As FrameBuffer) As FrameBuffer
		'This function adds two framebuffers together, each is multiplied by a certain ratio, which relates to MixRatio.
		'Returns the result of calculation.
		Dim i As Integer
		Dim Len1 As Integer, Len2 As Integer, Len As Integer
		Dim TransitionRatio As Double
		Dim InstantaneousRatio As Double
		Len1 = Frame1.Length
		Len2 = Frame2.Length
		Len = CInt(Len1 * (1 - MixRatio) + Len2 * MixRatio)
		If Len = 0 Then
			Throw New Exception("Overflow. Len = 0 in FrameMix procedure.")
		End If
		Dim Frame As FrameBuffer = New FrameBuffer(Len)
		For i = 0 To Len
			TransitionRatio = i / Len
			InstantaneousRatio = MixRatio * (1 - TransitionRatio) + MixRatio2 * TransitionRatio
			Frame.Data(i) = Frame1.Data(CInt(TransitionRatio * Len1)) * (1 - InstantaneousRatio) _
						  + Frame2.Data(CInt(TransitionRatio * Len2)) * InstantaneousRatio
		Next
		Return Frame
	End Function
	Public Function FrameStretch(ByVal Frame As FrameBuffer, ByVal Ratio As Double) As FrameBuffer
		'This function lengthen or shorten a framebuffer.
		Dim i As Integer
		Dim Len As Integer, RsutLen As Integer
		Dim TransitionRatio As Double
		Len = Frame.Length
		RsutLen = CInt(Len * Ratio)
		Dim RsutFrame As FrameBuffer = New FrameBuffer(RsutLen)
		For i = 0 To RsutLen
			TransitionRatio = i / RsutLen
			RsutFrame.Data(i) = Frame.Data(CInt(TransitionRatio * Len))
		Next
		Return RsutFrame
	End Function
	Public Function GenerateEmptyFrameBuffer() As FrameBuffer
		'Used to fill up during the remaining time.
		Dim Frame As FrameBuffer = New FrameBuffer(500)
		Return Frame
	End Function
End Class
