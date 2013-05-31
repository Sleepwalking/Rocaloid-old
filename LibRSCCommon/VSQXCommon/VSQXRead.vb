'    把vsqx载入RSC
'    Loads vsqx into RSC.
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
Public Module VSQXRead
	Friend Reader As VSQ3Reader
	Private Resolution As Integer
	Private MusicalPartStartPos As Double
	
	Public Sub Reader_Open(ByVal File As String)
		Reader = New VSQ3Reader(File)
	End Sub
	
	Public Sub Reader_Close()
		Reader.Close()
	End Sub
	
	Public Sub VSQX_Read(ByRef _RSC As RSC)
		Reader.ReadUntil("<masterTrack>")
		Reader.ReadUntil("<resolution>")
		Resolution = CInt(Reader.ReadNextValue("resolution")) * 2
		ReadTempos(_RSC, "</masterTrack>")
		ReadMusicalPart(_RSC)
	End Sub
	
	Public Sub ReadTempos(ByRef _RSC As RSC, ByVal EndTag As String)
		ReDim _RSC.TempoList(1000)
		_RSC.TempoListQ = 0
		Dim EndPos As Integer = Reader.FindLastPos("</tempo>", Reader.FindNextPos(EndTag))
		Dim TempoSet_ As TempoSet
		While Reader.Pointer < EndPos
			TempoSet_ = New TempoSet()
			TempoSet_.Position = CInt(Reader.ReadNextValue("posTick")) / Resolution
			TempoSet_.Tempo = CInt(Reader.ReadNextValue("bpm")) / 100
			Util.ListInsert(_RSC.TempoList, _RSC.TempoListQ, TempoSet_)
			Reader.ReadUntil("</tempo>")
		End While
		TempoSet_ = New TempoSet()
		TempoSet_.Position = 99999
		TempoSet_.Tempo = 120
		Util.ListInsert(_RSC.TempoList, _RSC.TempoListQ, TempoSet_)
		_RSC.TempoListQ -= 1
	End Sub
	
	Public Sub ReadMusicalPart(ByRef _RSC As RSC)
		ReDim _RSC.SegmentList(1000)
		_RSC.SegmentListQ = 0
		Reader.ReadUntil("<posTick>")
		MusicalPartStartPos = CInt(Reader.ReadNextValue("posTick")) / Resolution
		Reader.ReadUntil("<note>")
		Dim EndPos As Integer = Reader.FindLastPos("</note>", Reader.FindNextPos("</musicalPart>"))
		Dim Segment_ As Segment
		Dim Pitch As Integer
		Dim EachADSR As CVSCommon.ADSREnvelope
		EachADSR.Amplitude = 1
		EachADSR.Attack = 0.05
		EachADSR.Decline = 0.1
		EachADSR.Release = 0.1
		While Reader.Pointer < EndPos
			Segment_ = New Segment()
			Segment_.Position = CInt(Reader.ReadNextValue("posTick")) / Resolution + MusicalPartStartPos
			Segment_.Duration = CInt(Reader.ReadNextValue("durTick")) / Resolution
			Pitch = CInt(Reader.ReadNextValue("noteNum")) - 36
			Segment_.StartFreq = FreqList(Pitch)
			Segment_.EndFreq = FreqList(Pitch)
			Segment_.Lyric = Reader.ReadCDATA(Reader.ReadNextValue("lyric"))
			With Segment_
				.StartAmplitude = 1
				.EndAmplitude = 1
				.Effects.PElopeEnabled = True
				.Effects.PresetedEnvelope = CVSCommon.Envelopes.ADSR
				.Effects.ADSR = EachADSR
				.Effects.Breath.Magnitude = 0
			End With
			Util.ListInsert(_RSC.SegmentList, _RSC.SegmentListQ, Segment_)
			Reader.ReadUntil("</note>")
		End While
		_RSC.SegmentListQ -= 1
		ReDim _RSC.Effects.EnvelopeList(1)
		_RSC.Effects.EnvelopeListQ = 0
		_RSC.Effects.EnvelopeList(0).Amplitude = 1
		_RSC.Effects.EnvelopeList(0).Position = 0
		ReDim _RSC.FreqList(1)
		_RSC.FreqListQ = 0
		_RSC.FreqList(0).Freq = 270
		_RSC.FreqList(0).Position = 0
		ReDim _RSC.BeatList(1)
		_RSC.BeatListQ = 0
		_RSC.BeatList(0).BarPosition = 0
		_RSC.BeatList(0).Beat_Denominator = 4
		_RSC.BeatList(0).Beat_Factor = 4
		_RSC.Version = "2.0"
		_RSC.Author = "Sleepwalking"
		_RSC.InteractionSave.LastUserScale = 1
	End Sub
End Module
