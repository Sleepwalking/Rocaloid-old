'    把所有合成器、缓冲器、效果器和CVS读写汇聚在一起的调度器。
'    The final class which puts all of the Synthesizers, Buffers, Effectors & CVS together.
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
Imports CybervoiceEngine
#Const DebugLevel = 1
Public Class Scheduler
	Public Shared CVS_ As CVSCommon.CVS
	Public Shared NowSynthesizing As Integer
	Public Shared StartSynthesize As Integer
	Private Shared Synth1 As SpeechSynthesizer
	'May enable Synth2 to achieve multi-thread in future.
	'Public Shared Synth2 As SpeechSynthesizer
	Private Shared Wave1 As WaveBuffer
	Private Shared Wave2 As WaveBuffer
	Private Shared SSSendBack As SpeechSynthesizerSendBack
	
	Public Shared Sub Init()
		Synth1 = New SpeechSynthesizer()
		'Synth2 = New SpeechSynthesizer()
		Wave1 = New WaveBuffer(30.0)
		Wave2 = New WaveBuffer(30.0)
		NowSynthesizing = 0
		StartSynthesize = 0
	End Sub
	Public Shared Sub OpenCVS(ByVal File As String)
		CVSCommon.Reader_Open(File)
		CVSCommon.CVS_Read(CVS_)
		CVSCommon.Reader_Close()
		#If DebugLevel > 0 Then
			CreateLog("Scheduler:	" & File & " loaded. " & CVS_.SegmentListQ + 1 & " segments in all.")
		#End If
	End Sub
	Public Shared Sub SetMemoryOutput(ByVal Buffer() As Byte)
		MixerWriterEffector.SetMemoryOutput(Buffer)
	End Sub
	Public Shared Sub RunSynthesizer()
		Dim S1 As Integer, S2 As Integer
		Dim i As Integer
		Dim T1 As Integer, T2 As Integer
		Dim Overlap As Integer
		T1 = SegmentSynthesize(Synth1, CVS_.SegmentList(NowSynthesizing), Wave1)
		S1 = CInt(CVS_.SegmentList(NowSynthesizing).StartTime * SampleRate) - StartSynthesize
		Overlap = 0
		MixerWriterEffector.WriteBlank(S1)
		For i = NowSynthesizing To CVS_.SegmentListQ - 1
			#If DebugLevel > 0 Then
				CreateLog("Scheduler:	Synthesizing segment " & i & ".")
			#End If
			S2 = CInt(CVS_.SegmentList(i + 1).StartTime * SampleRate) - StartSynthesize
			'Write to S2
			MixerWriterEffector.Write(Wave1, Overlap, S2 - S1)
			T2 = SegmentSynthesize(Synth1, CVS_.SegmentList(i + 1), Wave2)
			If S2 < S1 + T1 Then
				'Mix & Write to S1 + T1 if Overlapped
				MixerWriterEffector.MixAndWrite(Wave1, Wave2, S2 - S1, 0, S1 + T1 - S2)
				Overlap = S1 + T1 - S2
			Else
				Overlap = 0
			End If
			Swap(S1, S2)
			Swap(T1, T2)
			Swap(Wave1, Wave2)
		Next
		MixerWriterEffector.Write(Wave1, Overlap, T1 - Overlap)
		#If DebugLevel > 0 Then
			CreateLog("Scheduler:	Synthesis finished.")
		#End If
	End Sub
	Public Shared Function SegmentSynthesize(ByVal Synth As SpeechSynthesizer, _
										 ByVal _Segment As CVSCommon.Segment, _
										 ByVal Wave As WaveBuffer) As Integer
		Synth.SetSegment(_Segment)
		Wave.Pointer = 0
		Dim Frame As FrameBuffer
		Dim i As Integer = CInt(_Segment.StartTime * SampleRate)
		Dim j As Integer = CInt(CVSCommon.GetSegmentTime(_Segment) * SampleRate) + i
		While i < j
			Frame = Synth.Synthesize(i / SampleRate)
			Wave.Write(Frame)
			i += Frame.Length + 1
		End While
		SSSendBack = GlobalSendBack
		Effector.Render(Wave, _Segment, SSSendBack)
		Return Wave.Pointer
	End Function
End Class
