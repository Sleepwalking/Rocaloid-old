'    RSC数据结构和一些乐理的计算。
'    Data structure of RSC and some musical calculations.
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
Public Class RSC
	Public Version As String
	Public Author As String
	Public Information As String
	Public SegmentListQ As Integer
	Public SegmentList() As Segment
	Public FreqListQ As Integer
	Public FreqList() As FreqSet
	Public Effects As EffectsStruct
	Public TempoListQ As Integer
	Public TempoList() As TempoSet
	Public BeatListQ As Integer
	Public BeatList() As BeatSet
	Public InteractionSave As UserInteraction
	Private NextChunk_Coincidence As Boolean = False
	Private NextChunk_Chunk As PositionChunk
	
	Public Sub New()
	End Sub
	
	Public Sub CopyTo(ByVal Target As RSC)
		Dim i As Integer
		With Target
			.Version = Version
			.Author = Author
			.Information = Information
			.SegmentListQ = SegmentListQ
			ReDim .SegmentList(SegmentListQ + 1)
			.InitSegmentList(0, SegmentListQ)
			.FreqListQ = FreqListQ
			ReDim .FreqList(FreqListQ + 1)
			.Effects = Effects
			.TempoListQ = TempoListQ
			ReDim .TempoList(TempoListQ)
			.BeatListQ = BeatListQ
			ReDim .BeatList(BeatListQ)
			.InteractionSave = InteractionSave
		End With
		For i = 0 To Target.SegmentListQ
			SegmentList(i).CopyTo(Target.SegmentList(i))
		Next
		For i = 0 To Target.FreqListQ
			Target.FreqList(i) = FreqList(i)
		Next
		For i = 0 To Target.TempoListQ
			Target.TempoList(i) = TempoList(i)
		Next
		For i = 0 To BeatListQ
			Target.BeatList(i) = BeatList(i)
		Next
	End Sub
	
	Public Sub InitSegmentList(ByVal LIndex As Integer, ByVal HIndex As Integer)
		Dim i As Integer
		For i = LIndex To HIndex
			SegmentList(i) = New Segment()
		Next
	End Sub
	
	Public Sub TimeBake()
		Dim i As Double = -1
		Dim NextChunk As PositionChunk
		Dim LastChunk As PositionChunk
		Dim LastTempo_Time As Double = 0
		Dim LastTempo As TempoSet
		Dim LastSegmentIndex As Integer = 0
		Dim EndTime As Double = 0
		LastTempo.Position = 0
		LastTempo.Tempo = 120
		
		While i < SegmentList(SegmentListQ).Position _
				+ SegmentList(SegmentListQ).Duration
			If LastChunk.Type = PositionChunkType.SegmentEnd Then
				NextChunk = GetNextPositionChunk(i - 0.0001, LastChunk.Index + 1)
			Else
				NextChunk = GetNextPositionChunk(i + 0.0001, 0)
			End If
			i = NextChunk.Position
			Select Case NextChunk.Type
				Case PositionChunkType.SegmentStart
					LastSegmentIndex = NextChunk.Index
					SegmentList(LastSegmentIndex).StartTime = PositionToTime(NextChunk.Position _
															- LastTempo.Position, LastTempo.Tempo) _
															+ LastTempo_Time
				Case PositionChunkType.SegmentEnd
					EndTime = PositionToTime(NextChunk.Position _
							- LastTempo.Position, LastTempo.Tempo) _
							+ LastTempo_Time
					SegmentList(LastSegmentIndex).DurTime = EndTime _
														  - SegmentList(LastSegmentIndex).StartTime
				Case PositionChunkType.TempoStart
					LastTempo_Time += PositionToTime(NextChunk.Position - LastTempo.Position, _
													 LastTempo.Tempo)
					LastTempo = TempoList(NextChunk.Index)
			End Select
			If NextChunk.Type = PositionChunkType.SegmentEnd _
				AndAlso NextChunk.Index = SegmentListQ Then
				Exit While
			End If
			LastChunk = NextChunk
		End While
	End Sub
	
	Public Sub PositionBake()
		Dim i As Integer = 0
		Dim LastBeat As BeatSet
		LastBeat.BarPosition = 0
		LastBeat.Beat_Denominator = 4
		LastBeat.Beat_Factor = 4
		LastBeat.Position = 0
		For i = 0 To BeatListQ
			BeatList(i).Position = (BeatList(i).BarPosition _
									- LastBeat.BarPosition) _
									* GetBarLength(LastBeat) + LastBeat.Position
			LastBeat = BeatList(i)
		Next
	End Sub
	
	Public Sub VolumeBake()
		Dim i As Integer = 0
		For i = 0 To SegmentListQ
			With SegmentList(i)
				.StartAmplitude = GetVolumeAt(.Position )
				.EndAmplitude = GetVolumeAt(.Position + .Duration)
			End With
		Next
	End Sub
	
	Private Function GetVolumeAt(ByVal Position As Double) As Double
		Dim i As Integer
		Dim pos1 As Double, pos2 As Double, ratio As Double
		Dim found As Boolean = False
		GetVolumeAt = 1
		For i = 0 To Effects.EnvelopeListQ
			If Effects.EnvelopeList(i).Position >= Position Then
				found = True
				If i = 0 Then
					GetVolumeAt = Effects.EnvelopeList(0).Amplitude
					Exit For
				End If
				pos1 = Effects.EnvelopeList(i - 1).Position
				pos2 = Effects.EnvelopeList(i).Position
				ratio = (Position - pos1) / (pos2 - pos1)
				GetVolumeAt = Effects.EnvelopeList(i - 1).Amplitude * (1 - ratio) + _
							  Effects.EnvelopeList(i).Amplitude * ratio
				Exit For				
			End If
		Next
		If Not found Then
			GetVolumeAt = Effects.EnvelopeList(Effects.EnvelopeListQ).Amplitude
		End If
		Return GetVolumeAt
	End Function
	
	Private Function GetBarLength(ByRef _BeatSet As BeatSet) As Double
		Return _BeatSet.Beat_Factor / _BeatSet.Beat_Denominator * 2
	End Function
	
	Private Function PositionToTime(ByVal Position As Double, ByVal Tempo As Double) As Double
		Return Position * 2 * 60 / Tempo
	End Function
	
	Private Function GetNextPositionChunk(ByVal Position As Double, ByVal Optional SegmentNum As Integer = 0) As PositionChunk
		Dim PChunk As PositionChunk, PChunk2 As PositionChunk
		Dim i As Integer
		i = 0
		If NextChunk_Coincidence Then
			NextChunk_Coincidence = False
			Return NextChunk_Chunk
		End If
		For i = SegmentNum To SegmentListQ
			If SegmentList(i).Position > Position Then
				PChunk.Type = PositionChunkType.SegmentStart
				PChunk.Position = SegmentList(i).Position
				PChunk.Index = i
				Exit For
			End If
			If SegmentList(i).Position + SegmentList(i).Duration > Position Then
				PChunk.Type = PositionChunkType.SegmentEnd
				PChunk.Position = SegmentList(i).Position + SegmentList(i).Duration
				PChunk.Index = i				
				Exit For
			End If
		Next
		For i = 0 To TempoListQ
			If TempoList(i).Position > Position Then
				PChunk2.Type = PositionChunkType.TempoStart
				PChunk2.Position = TempoList(i).Position
				PChunk2.Index = i
				Exit For
			End If
		Next
		If PChunk.Position < PChunk2.Position Then
			Return PChunk
		Else
			If PChunk.Position = PChunk2.Position Then
				NextChunk_Coincidence = True
				NextChunk_Chunk = PChunk
			End If
			Return PChunk2
		End If
	End Function
End Class

Friend Structure PositionChunk
	Dim Type As PositionChunkType
	Dim Position As Double
	Dim Index As Integer
End Structure

Friend Enum PositionChunkType
	SegmentStart
	SegmentEnd
	TempoStart
End Enum

Public Class Segment
	Public Position As Double
	Public Lyric As String
	Public Duration As Double
	Public StartTime As Double
	Public DurTime As Double
	Public Effects As SegmentEffects
	Public StartFreq As Double
	Public EndFreq As Double
	Friend StartAmplitude As Double
	Friend EndAmplitude As Double
	Friend CutTime As Double = 0
	
	Public Sub CopyTo(ByVal Target As Segment)
		With Target
			.Position = Position
			.Lyric = Lyric
			.Duration = Duration
			.StartTime = StartTime
			.DurTime = DurTime
			.Effects = Effects
			.StartFreq = StartFreq
			.EndFreq = EndFreq
			.StartAmplitude = StartAmplitude
			.EndAmplitude = EndAmplitude
			.CutTime = CutTime
		End With
	End Sub
	
	Public Function IsConnectedTo(ByRef _Segment As Segment) As Boolean
		If Math.Abs(Position + Duration - _Segment.Position) < 0.01 Then
			Return True
		Else
			Return False
		End If
	End Function
End Class

Public Structure SegmentEffects
	'Dim Vibration As VibrationStruct
	Dim PElopeEnabled As Boolean
	Dim PresetedEnvelope As CVSCommon.Envelopes
	Dim ADSR As CVSCommon.ADSREnvelope
	Dim Breath As CVSCommon.BreathStruct
End Structure

Public Structure EffectsStruct
	Dim EnvelopeListQ As Integer
	Dim EnvelopeList() As EnvelopeSet
End Structure

Public Structure TempoSet
	Dim Position As Double
	Dim Tempo As Double
End Structure

Public Structure BeatSet
	Dim Position As Double
	Dim BarPosition As Integer
	Dim Beat_Factor As Integer
	Dim Beat_Denominator As Integer
End Structure

Public Structure EnvelopeSet
	Dim Position As Double
	Dim Amplitude As Double
End Structure

Public Structure UserInteraction
	Dim LastUserPosition As Double
	Dim LastUserScale As Double
	Dim ViewType As ViewTypes
End Structure

Public Structure FreqSet
	Dim Position As Double
	Dim Freq As Double
End Structure

Public Enum ViewTypes
	NotesEditor = 0
	FreqEditor = 1
	EnvelopeEditor = 2
	BreathEditor = 3
	Other = -INFINITY
End Enum