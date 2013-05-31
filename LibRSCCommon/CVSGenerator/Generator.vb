'    使用CDT从RSC生成CVS
'    Generating RSC from CVS using CDT.
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

Friend Module Generator
	Public Function GenerateCVS(ByVal _RSC As RSC, ByRef _CDT As CDTCommon.CDT) As CVSCommon.CVS
		Dim _CVS As CVSCommon.CVS
		Dim _RSC2 As RSC = New RSC()
		Dim i As Integer
		Dim DEF_0233 As CDTCommon.DEF_0233
		Dim DEF As CDTCommon.DEF
		
		Dim PhoneSet As CDTCommon.PhoneSet
		Dim DBSet As CDTCommon.DBSet
		Dim FirstPhone As String
		
		_RSC.TimeBake()
		_RSC.VolumeBake()
		_RSC.CopyTo(_RSC2)
		Rearrange(_RSC, _RSC2, _CDT)
		
		ReDim _CVS.SegmentList(_RSC.SegmentListQ)
		_CVS.SegmentListQ = _RSC.SegmentListQ
		For i = 0 To _RSC.SegmentListQ
			'DEF_0233 = _CDT.DEFList_0233(CDTCommon.FindDEFNum_0233(_CDT, _RSC.SegmentList(i)))
			DEF = CDTCommon.CreateDEFCopy(_CDT.DEFList(CDTCommon.FindDEFNum(_CDT, _RSC.SegmentList(i))))
			CDTCommon.ReplaceDEF(DEF, CDTCommon.ToSingleNotation(_RSC.SegmentList(i).Lyric))
			
			FirstPhone = DEF.TList(0).TFrom
			PhoneSet = CDTCommon.GetPhoneSet(_CDT, FirstPhone)
			DBSet = CDTCommon.GetDBSet(_CDT, FirstPhone, GetPitchByFreq(_RSC.SegmentList(i).StartFreq))
			
			With _CVS.SegmentList(i)
				.StartTime = _RSC.SegmentList(i).StartTime
				.Effects.ElistEnabled = True
				If _RSC.SegmentList(i).Effects.PElopeEnabled Then
					.Effects.PElopeEnabled = True
					.Effects.PresetedEnvelope = _RSC.SegmentList(i).Effects.PresetedEnvelope
					GeneratePElope(_RSC, _CVS, PhoneSet, i)
					'.Effects.ADSR = _RSC.SegmentList(i).Effects.ADSR
				End If
				.Effects.Breath = _RSC.SegmentList(i).Effects.Breath
				'.Effects.Vibration = _RSC.SegmentList(i).Effects.Virbration
			End With
			GenerateTPhone(_CVS, _RSC, DEF, i)
			GenerateTransition(_CVS, _RSC, PhoneSet, DBSet, DEF, i)
			GenerateOpeList(_CVS, _RSC, _CDT, i)
			GenerateEnvelope(_CVS, _RSC, i)
			GenerateFreq(_CVS, _RSC, i)
		Next
		Return _CVS
	End Function
	
	Private Sub GenerateTPhone(ByRef _CVS As CVSCommon.CVS, _
								 ByVal _RSC As RSC, _
								 ByRef _CDT As CDTCommon.CDT, _
								 ByVal Num As Integer)
		Dim RSCSegment As Segment = _RSC.SegmentList(Num)
		Dim CDTNum As Integer = CDTCommon.FindDEFNum_0233(_CDT, RSCSegment)
		Dim CDTDEF As CDTCommon.DEF_0233 = _CDT.DEFList_0233(CDTNum)
		GenerateTPhone(_CVS, _RSC, CDTDEF, Num)
	End Sub
	
	Private Sub GenerateTPhone(ByRef _CVS As CVSCommon.CVS, _
								 ByVal _RSC As RSC, _
								 ByRef _DEF As CDTCommon.DEF, _
								 ByVal Num As Integer)
		Dim RSCSegment As Segment = _RSC.SegmentList(Num)
		Dim i As Integer
		ReDim _CVS.SegmentList(Num).TPhoneList(_DEF.TListQ)
		_CVS.SegmentList(Num).TPhoneListQ = _DEF.TListQ
		For i = 0 To _DEF.TListQ
			With _CVS.SegmentList(Num).TPhoneList(i)
				If _DEF.TList(i).TFrom = "p1" Then
					.Start.Preserved = 1
					.Start.Type = False
				ElseIf _DEF.TList(i).TFrom = "p2" Then
					.Start.Preserved = 2
					.Start.Type = False
				Else
					.Start.Symbol = _DEF.TList(i).TFrom
					.Start.Type = True
				End If
				If _DEF.TList(i).TTo = "p2" Then
					.Dest.Preserved = 2
					.Dest.Type = False
				ElseIf _DEF.TList(i).TTo = "p1" Then
					.Dest.Preserved = 1
					.Dest.Type = False
				Else
					.Dest.Symbol = _DEF.TList(i).TTo
					.Dest.Type = True
				End If
			End With
		Next
		With _CVS.SegmentList(Num)
			Select Case _DEF.Type
				Case CDTCommon.DEFType.V
					.TPhoneList(0).Transition.StartRatio		= 1
					.TPhoneList(0).Transition.EndRatio		= 1
				Case CDTCommon.DEFType.VV
					.TPhoneList(0).Transition.StartRatio		= 0
					.TPhoneList(0).Transition.EndRatio		= _DEF.TRatio
					.TPhoneList(1).Transition.StartRatio		= _DEF.TRatio
					.TPhoneList(1).Transition.EndRatio		= _DEF.TRatio
					If _DEF.TListQ = 2 Then
						.TPhoneList(2).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.EndRatio	= 1
					End If
				Case CDTCommon.DEFType.VVV
					.TPhoneList(0).Transition.StartRatio		= 0
					.TPhoneList(0).Transition.EndRatio		= 1
					.TPhoneList(1).Transition.StartRatio		= 0
					.TPhoneList(1).Transition.EndRatio		= _DEF.TRatio
					.TPhoneList(2).Transition.StartRatio		= _DEF.TRatio
					.TPhoneList(2).Transition.EndRatio		= _DEF.TRatio
					.TPhoneList(3).Transition.StartRatio		= _DEF.TRatio
					.TPhoneList(3).Transition.EndRatio		= 1
				Case CDTCommon.DEFType.CV
					.TPhoneList(0).Transition.StartRatio		= 0
					.TPhoneList(0).Transition.EndRatio		= 1
					.TPhoneList(1).Transition.StartRatio		= 1
					.TPhoneList(1).Transition.EndRatio		= 1
				Case CDTCommon.DEFType.CVV
					If _DEF.TListQ = 2 Then
						.TPhoneList(0).Transition.StartRatio	= 0
						.TPhoneList(0).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(1).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(1).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.EndRatio	= 1
					End If
					If _DEF.TListQ = 3 Then
						.TPhoneList(0).Transition.StartRatio	= 0
						.TPhoneList(0).Transition.EndRatio	= 1
						.TPhoneList(1).Transition.StartRatio	= 0
						.TPhoneList(1).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(3).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(3).Transition.EndRatio	= 1
					End If
				Case CDTCommon.DEFType.CAV
					If _DEF.TListQ = 1 Then
						.TPhoneList(0).Transition.StartRatio	= 0
						.TPhoneList(0).Transition.EndRatio	= 1
						.TPhoneList(1).Transition.StartRatio	= 1
						.TPhoneList(1).Transition.EndRatio	= 1
					End If
					If _DEF.TListQ = 2 Then
						.TPhoneList(0).Transition.StartRatio	= 0
						.TPhoneList(0).Transition.EndRatio	= 1
						.TPhoneList(1).Transition.StartRatio	= 0
						.TPhoneList(1).Transition.EndRatio	= 1
						.TPhoneList(2).Transition.StartRatio	= 1
						.TPhoneList(2).Transition.EndRatio	= 1
					End If
				Case CDTCommon.DEFType.CAVV
					.TPhoneList(0).Transition.StartRatio		= 0
					.TPhoneList(0).Transition.EndRatio		= 1
					If _DEF.TListQ = 3 Then
						.TPhoneList(1).Transition.StartRatio	= 0
						.TPhoneList(1).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(2).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(3).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(3).Transition.EndRatio	= 1
					End If
					If _DEF.TListQ = 4 Then
						.TPhoneList(1).Transition.StartRatio	= 0
						.TPhoneList(1).Transition.EndRatio	= 1
						.TPhoneList(2).Transition.StartRatio	= 0
						.TPhoneList(2).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(3).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(3).Transition.EndRatio	= _DEF.TRatio
						.TPhoneList(4).Transition.StartRatio	= _DEF.TRatio
						.TPhoneList(4).Transition.EndRatio	= 1
					End If
			End Select
		End With
	End Sub
	
	Private Sub GenerateTPhone(ByRef _CVS As CVSCommon.CVS, _
								 ByVal _RSC As RSC, _
								 ByRef _DEF As CDTCommon.DEF_0233, _
								 ByVal Num As Integer)
		Dim RSCSegment As Segment = _RSC.SegmentList(Num)
		Dim i As Integer
		ReDim _CVS.SegmentList(Num).TPhoneList(_DEF.TPhoneListQ + 1)
		_CVS.SegmentList(Num).TPhoneListQ = _DEF.TPhoneListQ
		Select Case _DEF.TPhoneListQ
			Case 0
				With _CVS.SegmentList(Num).TPhoneList(0)
					.Start.Type = True
					.Start.Symbol = _DEF.TPhoneList(0)
					.Dest.Type = True
					.Dest.Symbol = _DEF.TPhoneList(0)
					.Transition.StartRatio = 0
					.Transition.EndRatio = 0
				End With
			Case 1
				With _CVS.SegmentList(Num).TPhoneList(0)
					.Start.Type = True
					.Start.Symbol = _DEF.TPhoneList(0)
					.Dest.Type = True
					.Dest.Symbol = _DEF.TPhoneList(1)
					.Transition.StartRatio = 0
					.Transition.EndRatio = _DEF.TransitionRatio
				End With
				With _CVS.SegmentList(Num).TPhoneList(1)
					.Start.Type = False
					.Start.Preserved = 1
					.Dest.Type = False
					.Dest.Preserved = 2
					.Transition.StartRatio = _DEF.TransitionRatio
					.Transition.EndRatio = _DEF.TransitionRatio
				End With
			Case > 1
				With _CVS.SegmentList(Num).TPhoneList(0)
					.Start.Type = True
					.Start.Symbol = _DEF.TPhoneList(0)
					.Dest.Type = True
					.Dest.Symbol = _DEF.TPhoneList(1)
					.Transition.StartRatio = 0
					.Transition.EndRatio = 1
				End With
				For i = 1 To _DEF.TPhoneListQ - 1
					With _CVS.SegmentList(Num).TPhoneList(i)
						.Start.Type = False
						.Start.Preserved = 2
						.Dest.Type = True
						.Dest.Symbol = _DEF.TPhoneList(i + 1)
						.Transition.StartRatio = 0
						If i = _DEF.TPhoneListQ - 1 Then
							'Last Transition with New symbol
							'Use TR in DEF
							.Transition.EndRatio = _DEF.TransitionRatio
						Else
							.Transition.EndRatio = 1
						End If
					End With
				Next
				With _CVS.SegmentList(Num).TPhoneList(_DEF.TPhoneListQ)
					.Start.Type = False
					.Start.Preserved = 1
					.Dest.Type = False
					.Dest.Preserved = 2
					.Transition.StartRatio = _DEF.TransitionRatio
					.Transition.EndRatio = _DEF.TransitionRatio
				End With
		End Select
	End Sub
	
	'Must be used after GenerateTPhone!
	Private Sub GenerateFreq(ByRef _CVS As CVSCommon.CVS, ByVal _RSC As RSC, ByVal Num As Integer)
		Dim i As Integer
		Dim _FreqSet As FreqSet
		Dim StartPos As Double, EndPos As Double, DurPos As Double
		Dim StartTime As Double, DurTime As Double, SaveTime As Double, FirstSegTime As Double
		With _RSC.SegmentList(Num)
			StartPos = .Position
			DurPos = .Duration
			EndPos = StartPos + DurPos
			StartTime = .StartTime
			DurTime = .DurTime
		End With
		FirstSegTime = _CVS.SegmentList(Num).TPhoneList(0).Transition.Time
		ReDim _CVS.SegmentList(Num).FreqList(1000)
		_CVS.SegmentList(Num).FreqList(0).Time = 0
		_CVS.SegmentList(Num).FreqList(0).Freq = _RSC.SegmentList(Num).StartFreq
		i = 1
		For Each _FreqSet In _RSC.FreqList
			If _FreqSet.Position > StartPos Then
				If _FreqSet.Position > EndPos Then
					Exit For
				End If
				SaveTime = (_FreqSet.Position - StartPos) / DurPos * DurTime
				If SaveTime > FirstSegTime AndAlso _
				   _CVS.SegmentList(Num).FreqList(i - 1).Time < FirstSegTime Then
					_CVS.SegmentList(Num).FreqList(i).Time = FirstSegTime
					_CVS.SegmentList(Num).FreqList(i).Freq = _RSC.SegmentList(Num).StartFreq
					i += 1
				End If
				_CVS.SegmentList(Num).FreqList(i).Time = SaveTime
				_CVS.SegmentList(Num).FreqList(i).Freq = _FreqSet.Freq
				With _CVS.SegmentList(Num)
					If CVSCommon.IsConsonant(.TPhoneList(0).Start.Symbol) Then
						'Consonant Starting
						'Pitch change before entering real transformation may cause errors.
						If .FreqList(i).Time < .TPhoneList(0).Transition.Time Then
							.FreqList(0).Freq = _FreqSet.Freq
							i -= 1
						End If
					End If
				End With
				i += 1
			End If
		Next
		If DurTime > FirstSegTime AndAlso _
		   _CVS.SegmentList(Num).FreqList(i - 1).Time < FirstSegTime Then
			_CVS.SegmentList(Num).FreqList(i).Time = FirstSegTime
			_CVS.SegmentList(Num).FreqList(i).Freq = _RSC.SegmentList(Num).StartFreq
			i += 1
		End If
		_CVS.SegmentList(Num).FreqList(i).Time = DurTime
		_CVS.SegmentList(Num).FreqList(i).Freq = _RSC.SegmentList(Num).EndFreq
		_CVS.SegmentList(Num).FreqListQ = i
		Array.Resize(_CVS.SegmentList(Num).FreqList, i + 1)
	End Sub
	
	Private Sub GenerateEnvelope(ByRef _CVS As CVSCommon.CVS, ByVal _RSC As RSC, ByVal Num As Integer)
		Dim i As Integer
		Dim _EnvelopeSet As EnvelopeSet
		Dim StartPos As Double, EndPos As Double, DurPos As Double
		Dim StartTime As Double, DurTime As Double
		With _RSC.SegmentList(Num)
			StartPos = .Position
			DurPos = .Duration
			EndPos = StartPos + DurPos
			StartTime = .StartTime
			DurTime = .DurTime
		End With
		ReDim _CVS.SegmentList(Num).Effects.EnvelopeList(1000)
		_CVS.SegmentList(Num).Effects.EnvelopeList(0).Time = 0
		_CVS.SegmentList(Num).Effects.EnvelopeList(0).Amplitude = _RSC.SegmentList(Num).StartAmplitude
		i = 1
		For Each _EnvelopeSet In _RSC.Effects.EnvelopeList
			If _EnvelopeSet.Position > StartPos Then
				If _EnvelopeSet.Position > EndPos Then
					Exit For
				End If
				With _CVS.SegmentList(Num).Effects.EnvelopeList(i)
					.Time = (_EnvelopeSet.Position - StartPos) / DurPos * DurTime
					.Amplitude = _EnvelopeSet.Amplitude
				End With
				i += 1
			End If
		Next
		_CVS.SegmentList(Num).Effects.EnvelopeList(i).Time = DurTime
		_CVS.SegmentList(Num).Effects.EnvelopeList(i).Amplitude = _RSC.SegmentList(Num).EndAmplitude
		_CVS.SegmentList(Num).Effects.EnvelopeListQ = i
		Array.Resize(_CVS.SegmentList(Num).Effects.EnvelopeList, i + 1)
	End Sub
End Module
