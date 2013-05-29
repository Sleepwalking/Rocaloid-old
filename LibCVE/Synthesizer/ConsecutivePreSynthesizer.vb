'    为PitchPreSynthesizer提供语音帧。
'    生成连续的语音帧，可以达到无限长度，支持元音和辅音音源。
'    ConsecutivePreSynthesizer prepares FrameBuffers for PitchPreSynthesizer.
'    It produces consecutive frames that can be infinitely long, from both vowels and consonants.
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
Friend Class ConsecutivePreSynthesizer
	Inherits Synthesizer
	Private CVDB As CVDBContainer
	Private Pointer As Integer
	Private SamplesPassed_ As Integer 'Used to synchronize.
	Public ReadOnly Property Symbol() As String
		Get
			Return CVDB.Symbol
		End Get
	End Property
	Public ReadOnly Property Pitch() As String
		Get
			Return CVDB.Pitch
		End Get
	End Property
	Public ReadOnly Property Info() As CVDBHeader
		Get
			Return CVDB.Info
		End Get
	End Property
	Public ReadOnly Property BaseFrame() As Integer
		Get
			Return CVDB.BaseFrame
		End Get
	End Property
	Public ReadOnly Property SamplesPassed() As Integer
		Get
			Return SamplesPassed_
		End Get
	End Property
	Public Sub New()
		CVDB = New CVDBContainer()
		Pointer = 0
		SamplesPassed_ = 0
	End Sub
	Public Sub ClearSymbol()
		CVDB.ClearSymbol()
	End Sub
	Public Sub Load(ByVal Name As String)
		If CVDB.Name <> Name Then
			CVDB.Load(Name)
			Pointer = 0
			SamplesPassed_ = 0
			#If DebugLevel > 0 Then
				CreateLog("ConsecutivePreSynthesizer: Load " & Name)
			#End If
		End If
	End Sub
	Public Overloads Sub Synchronize(ByVal _SamplesPassed As Integer)
		While SamplesPassed_ < _SamplesPassed
			SamplesPassed_ += CVDB.Buffer.Data(Pointer).Length
			Pointer += 1
		End While
	End Sub
	Public Overloads Sub Synchronize(ByVal _ConsPreSyn As ConsecutivePreSynthesizer)
		Synchronize(_ConsPreSyn.SamplesPassed)
	End Sub
	Public Sub SkipConsonant()
		Pointer = CVDB.BaseFrame + CInt(0.1 * SampleRate / CVDB.Info.AveragePeriod)
	End Sub
	Public Function Synthesize() As FrameBuffer
		#If DebugLevel > 2 Then
			CreateLog("ConsecutivePreSynthesizer: " & CVDB.Name & "  Pointer:" & Pointer)
		#End If
		Dim Frame As FrameBuffer
		Dim Pointer2 As Integer
		Dim Ratio As Double
		Dim CirculationBase As Integer, CirculationQuantity As Integer
		If CVDB.Info.Consonant Then
			CirculationQuantity = CInt(0.2 * SampleRate / CVDB.Info.AveragePeriod)
			CirculationBase = CInt((CVDB.Info.StartPoint + 0.1 * SampleRate) / CVDB.Info.AveragePeriod)
		Else
			CirculationQuantity = CInt(0.3 * SampleRate / CVDB.Info.AveragePeriod)
			CirculationBase = CInt(0.1 * SampleRate / CVDB.Info.AveragePeriod)
		End If
		If Pointer < CVDB.Buffer.Length - CirculationQuantity Then
			Frame = CVDB.Buffer.Data(Pointer)
			Pointer += 1
			SamplesPassed_ += Frame.Length
			Return Frame
		Else
			Pointer2 = Pointer - CVDB.Buffer.Length + CirculationQuantity
			Ratio = Pointer2 / CirculationQuantity
				#If DebugLevel > 1 Then
					CreateLog("ConsecutivePreSynthesizer:	" & CVDB.Name & " Ratio:" & Ratio)
				#End If
			SetStartMixRatio(Ratio)
			SetDestMixRatio(Ratio + 1 / CirculationQuantity)
			Frame = FrameMix(CVDB.Buffer.Data(Pointer), CVDB.Buffer.Data(Pointer2 + CirculationBase))
			Pointer += 1
			If Pointer2 >= CirculationQuantity Then
				Pointer = CirculationBase + 1
				#If DebugLevel > 1 Then
					CreateLog("ConsecutivePreSynthesizer:	Circulate at pointer:" & Pointer)
				#End If
			End If
			SamplesPassed_ += Frame.Length
			Return Frame
		End If
	End Function
End Class
