'    提供RSC写入函数
'    Provides writing functions of RSC
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
Public Module RSCWrite
	Friend Writer As RDLWriter
	
	Public Sub Writer_Save(ByVal File As String)
		Writer = New RDLWriter(File)
		Writer.WriteWord("#RSC")
		Writer.WriteWord("2.0")
		Writer.NewLine()
	End Sub
	
	Public Sub Writer_Close()
		Writer.Close()
	End Sub
	
	Public Sub RSC_Write(ByRef _RSC As RSC)
		Dim i As Integer
		Writer.WriteWord("RSC")
		Writer.IndentPush()
		Writer.NewLine()
		'Author
		Writer.WriteWord("Author")
		Writer.WriteWord(_RSC.Author)
		Writer.NewLine()
		'Information
		Writer.WriteWord("Information")
		Writer.WriteWord(_RSC.Information)
		Writer.WriteWord("\0")
		Writer.NewLine()
		'SegmentList
		Writer.WriteWord("SegmentListQ")
		Writer.WriteWord(_RSC.SegmentListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("SegmentList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _RSC.SegmentListQ
			Segment_Write(_RSC.SegmentList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
		'FreqList
		Writer.WriteWord("FreqListQ")
		Writer.WriteWord(_RSC.FreqListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("FreqList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _RSC.FreqListQ
			FreqSet_Write(_RSC.FreqList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
		'Effects
		Effects_Write(_RSC.Effects)
		'TempoList
		Writer.WriteWord("TempoListQ")
		Writer.WriteWord(_RSC.TempoListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("TempoList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _RSC.TempoListQ
			TempoSet_Write(_RSC.TempoList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
		'BeatList
		Writer.WriteWord("BeatListQ")
		Writer.WriteWord(_RSC.BeatListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("BeatList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _RSC.BeatListQ
			BeatSet_Write(_RSC.BeatList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
		'InteractionSave
		Interaction_Write(_RSC.InteractionSave)
		
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub Segment_Write(ByRef _Segment As Segment)
		Writer.WriteWord("Segment")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("Position")
		Writer.WriteWord(_Segment.Position)
		Writer.NewLine()
		
		Writer.WriteWord("Duration")
		Writer.WriteWord(_Segment.Duration)
		Writer.NewLine()
		
		Writer.WriteWord("Lyric")
		Writer.WriteWord(_Segment.Lyric)
		Writer.NewLine()
		
		SegmentEffects_Write(_Segment.Effects)
		
		Writer.WriteWord("StartFreq")
		Writer.WriteWord(_Segment.StartFreq)
		Writer.NewLine()
		
		Writer.WriteWord("EndFreq")
		Writer.WriteWord(_Segment.EndFreq)
		Writer.NewLine()
		
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub FreqSet_Write(ByRef _FreqSet As FreqSet)
		Writer.WriteWord("FreqSet")
		
		Writer.WriteWord("Position")
		Writer.WriteWord(_FreqSet.Position)
		
		Writer.WriteWord("Freq")
		Writer.WriteWord(_FreqSet.Freq)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub Effects_Write(ByRef _Effects As EffectsStruct)
		Dim i As Integer
		Writer.WriteWord("Effects")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("EnvelopeListQ")
		Writer.WriteWord(_Effects.EnvelopeListQ + 1)
		Writer.NewLine()
		
		Writer.WriteWord("EnvelopeList")
		Writer.IndentPush()
		Writer.NewLine()
		For i = 0 To _Effects.EnvelopeListQ
			EnvelopeSet_Write(_Effects.EnvelopeList(i))
		Next
		Writer.IndentPop()
		Writer.WriteWord("End")
		
		Writer.IndentPop()
		Writer.NewLine()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub TempoSet_Write(ByRef _TempoSet As TempoSet)
		Writer.WriteWord("TempoSet")
		
		Writer.WriteWord("Position")
		Writer.WriteWord(_TempoSet.Position)
		
		Writer.WriteWord("Tempo")
		Writer.WriteWord(_TempoSet.Tempo)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub BeatSet_Write(ByRef _BeatSet As BeatSet)
		Writer.WriteWord("BeatSet")
		
		Writer.WriteWord("BarPosition")
		Writer.WriteWord(_BeatSet.BarPosition)
		
		Writer.WriteWord("Factor")
		Writer.WriteWord(_BeatSet.Beat_Factor)
		
		Writer.WriteWord("Denominator")
		Writer.WriteWord(_BeatSet.Beat_Denominator)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub Interaction_Write(ByRef _Interaction As UserInteraction)
		Writer.WriteWord("InteractionSave")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("LastUserPosition")
		Writer.WriteWord(_Interaction.LastUserPosition)
		Writer.NewLine()
		
		Writer.WriteWord("LastUserScale")
		Writer.WriteWord(_Interaction.LastUserScale)
		Writer.NewLine()
		
		Writer.WriteWord("ViewType")
		Writer.WriteViewType(_Interaction.ViewType)
		
		Writer.IndentPop()
		Writer.NewLine()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub SegmentEffects_Write(ByRef _Effects As SegmentEffects)
		Writer.WriteWord("Effects")
		Writer.IndentPush()
		Writer.NewLine()
		
		Writer.WriteWord("PElopeEnabled")
		Writer.WriteWord(_Effects.PElopeEnabled)
		Writer.NewLine()
		
		If _Effects.PElopeEnabled Then
			
			Writer.WriteWord("PresetedEnvelope")
			Writer.WritePresetedEnvelope(_Effects.PresetedEnvelope)
			Writer.NewLine()
			
			Select Case _Effects.PresetedEnvelope
				Case CVSCommon.Envelopes.ADSR
					ADSR_Write(_Effects.ADSR)
			End Select
		
		End If
		
		Writer.IndentPop()
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub

	Public Sub ADSR_Write(ByRef _ADSR As CVSCommon.ADSREnvelope)
		Writer.WriteWord("ADSR")
		
		Writer.WriteWord("Amplitude")
		Writer.WriteWord(_ADSR.Amplitude)
		Writer.WriteWord("Attack")
		Writer.WriteWord(_ADSR.Attack)
		Writer.WriteWord("Decline")
		Writer.WriteWord(_ADSR.Decline)
		Writer.WriteWord("Release")
		Writer.WriteWord(_ADSR.Release)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
	
	Public Sub EnvelopeSet_Write(ByRef _ESet As EnvelopeSet)
		Writer.WriteWord("EnvelopeSet")
		
		Writer.WriteWord("Position")
		Writer.WriteWord(_ESet.Position)
		Writer.WriteWord("Magnitude")
		Writer.WriteWord(_ESet.Amplitude)
		
		Writer.WriteWord("End")
		Writer.NewLine()
	End Sub
End Module
'Template
'
'	Public Sub RSC_Write(ByRef _RSC As RSC)
'		Dim i As Integer
'		Writer.WriteWord("RSC")
'		Writer.IndentPush()
'		Writer.NewLine()
'		
'		
'		
'		Writer.IndentPop()
'		Writer.NewLine()
'		Writer.WriteWord("End")
'		Writer.NewLine()
'	End Sub

'		Writer.WriteWord("SegmentList")
'		Writer.IndentPush()
'		Writer.NewLine()
'		For i = 0 To _CVS.SegmentListQ
'			Segment_Write(_CVS.SegmentList(i))
'		Next
'		Writer.IndentPop()
'		Writer.WriteWord("End")