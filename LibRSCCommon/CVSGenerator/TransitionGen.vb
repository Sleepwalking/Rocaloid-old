'    生成音节中过渡的时间长度。
'    Generates time of transitions in a TPhone.
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

Imports RSCCommon.CDTCommon
Friend Module TransitionGen
	Public Sub GenerateTransition(ByRef _CVS As CVSCommon.CVS, _
								  ByVal _RSC As RSC, _
								  ByRef _CDT As CDTCommon.CDT, _
								  ByVal Num As Integer)
		Dim FirstPhone As String = _CVS.SegmentList(Num).TPhoneList(0).Start.Symbol
		Dim PhoneSet_ As CDTCommon.PhoneSet = CDTCommon.GetPhoneSet(_CDT, FirstPhone)
		Dim DBSet_ As CDTCommon.DBSet = CDTCommon.GetDBSet(_CDT, FirstPhone, GetPitchByFreq(_RSC.SegmentList(Num).StartFreq))
		GenerateTransition(_CVS, _RSC, PhoneSet_, DBSet_, Num)
	End Sub
	
	Public Sub GenerateTransition(ByRef _CVS As CVSCommon.CVS, _
								  ByVal _RSC As RSC, _
								  ByRef _PhoneSet As CDTCommon.PhoneSet, _
								  ByRef _DBSet As CDTCommon.DBSet, _
								  ByVal Num As Integer)
		'This is the obsoleted Generator.
		Dim DurTime As Double
		Dim StartTimeLimit As Double
		Dim p1 As Double, p2 As Double, p3 As Double
		Dim i As Integer
		Dim p1Limit As Double = _DBSet.VOT / 96000
		Dim PreShrink As Double = _DBSet.PreShrink / 96000 / 2
		
		If p1Limit = 0 Then p1Limit = 0.11 Else p1Limit = Math.Max(0.11, p1Limit + 0.05)
		
		p1 = 0.15
		p2 = 0.1
		p3 = 0.2
		
		With _RSC.SegmentList(Num)
			_CVS.SegmentList(Num).Effects.Shrink = .CutTime + PreShrink
			If .DurTime < 0.25 Then
				If .StartTime < 0 Then .StartTime = 0
				If Num > 1 Then
					StartTimeLimit = _RSC.SegmentList(Num - 2).StartTime + _RSC.SegmentList(Num - 2).DurTime
					If StartTimeLimit > .StartTime Then
						'Over - Overlapped
						_CVS.SegmentList(Num).Effects.ForwardCut = StartTimeLimit - .StartTime
						.StartTime = StartTimeLimit
					End If
				End If
			End If
		End With
		With _CVS.SegmentList(Num)
			.StartTime = _RSC.SegmentList(Num).StartTime
			DurTime = _RSC.SegmentList(Num).DurTime
			Select Case .TPhoneListQ
				Case 0
					.TPhoneList(0).Transition.Time = DurTime
				Case 1
					If DurTime < 0.3 Then
						p1 = 0.5 * DurTime
						If p1 < p1Limit Then p1 = p1Limit
					End If
					.TPhoneList(0).Transition.Time = p1 + PreShrink
					.TPhoneList(1).Transition.Time = DurTime - p1
				Case 2
					If DurTime < 0.3 Then
						p1 = 0.4 * DurTime
						p2 = 0.3 * DurTime
						If p1 < p1Limit Then
							p1 = p1Limit
							p2 = (DurTime - p1) / 2
						End If
					End If
					.TPhoneList(0).Transition.Time = p1 + PreShrink
					.TPhoneList(1).Transition.Time = p2
					.TPhoneList(2).Transition.Time = DurTime - p1 - p2
				Case 3
					If DurTime < 0.4 Then
						p1 = 0.4 * DurTime
						p2 = 0.1 * DurTime
						p3 = 0.2 * DurTime
						If p1 < p1Limit Then
							p1 = p1Limit
							p2 = (DurTime - p1) * 0.167
							p3 = (DurTime - p1) * 0.333
						End If
					End If
					.TPhoneList(0).Transition.Time = p1 + PreShrink
					.TPhoneList(1).Transition.Time = p2
					.TPhoneList(2).Transition.Time = p3
					.TPhoneList(3).Transition.Time = DurTime - p1 - p2 - p3
			End Select
			For i = 0 To .TPhoneListQ
				If .TPhoneList(i).Transition.Time <= 0 Then .TPhoneList(i).Transition.Time = 0.0001
			Next
		End With
	End Sub
	
	Public Sub GenerateTransition(ByRef _CVS As CVSCommon.CVS, _
								  ByVal _RSC As RSC, _
								  ByRef _PhoneSet As CDTCommon.PhoneSet, _
								  ByRef _DBSet As CDTCommon.DBSet, _
								  ByRef DEF As CDTCommon.DEF, _
								  ByVal Num As Integer)
		Dim TotalTime As Double = _RSC.SegmentList(Num).DurTime
		Dim PreShrink As Double = _DBSet.PreShrink / 96000 / 2
		Dim ConsonantTime As Double = _DBSet.VOT / 96000 + 0.02 + PreShrink
		Dim t0, t1, t2, t3, t4 As Double
		With _CVS.SegmentList(Num)
			.Effects.Shrink = (PreShrink + _RSC.SegmentList(Num).CutTime)/2
			.Effects.ForwardCut = (PreShrink + _RSC.SegmentList(Num).CutTime)/2
			Select Case DEF.Type
				Case DEFType.V
					t0 = TotalTime
				Case DEFType.VV
					If DEF.TListQ = 2 Then
						t0 = 0.13
						If TotalTime < 0.4 Then
							t0 = 0.13 * TotalTime / 0.4
						End If
						t2 = 0.13
						If TotalTime < 0.4 Then
							t2 = TotalTime * 0.13 / 0.4
						End If
						t1 = TotalTime - t0 - t2
					End If
					If DEF.TListQ = 1 Then
						t0 = 0.2
						If TotalTime < 0.3 Then
							t0 = TotalTime * 2 / 3
						End If
						t1 = TotalTime - t0
					End If
				Case DEFType.VVV
					t0 = 0.15
					t1 = 0.1
					t3 = 0.15
					If TotalTime < 0.8 Then
						t3 = 0.15 * TotalTime / 0.8
					End If
					If TotalTime < 0.4 Then
						t0 = 0.15 * TotalTime / 0.4
						t1 = 0.1 * TotalTime / 0.4
					End If
					t2 = TotalTime - t0 - t1 - t3
				Case DEFType.CV
					TotalTime -= ConsonantTime
					t0 = 0.08
					If TotalTime < 0.3 Then
						t0 = 0.08 * TotalTime / 0.3
					End If
					t0 += ConsonantTime
					t1 = TotalTime + ConsonantTime - t0
				Case DEFType.CVV
					TotalTime -= ConsonantTime
					If DEF.TListQ = 2 Then
						t0 = 0.1
						t2 = 0.15
						If TotalTime < 0.6 Then
							t2 = 0.15 * TotalTime / 0.6
						End If
						If TotalTime < 0.3 Then
							t0 = 0.1 * TotalTime / 0.3
						End If
						t0 += ConsonantTime
						t1 = TotalTime + ConsonantTime - t0 - t2
					End If
					If DEF.TListQ = 3 Then
						t0 = 0.10
						t1 = 0.10
						t3 = 0.15
						If TotalTime < 0.6 Then
							t3 = 0.15 * TotalTime / 0.6
						End If
						If TotalTime < 0.5 Then
							t0 = 0.10 * TotalTime / 0.5
							t1 = 0.10 * TotalTime / 0.5
						End If
						t0 += ConsonantTime
						t2 = TotalTime + ConsonantTime - t0 - t1 - t3
					End If
				Case DEFType.CAV
					TotalTime -= ConsonantTime
					If DEF.TListQ = 1 Then
						t0 = 0.12
						If TotalTime < 0.5 Then
							t0 = 0.14 * TotalTime / 0.5
						End If
						t0 += ConsonantTime
						t1 = TotalTime + ConsonantTime - t0
					End If
					If DEF.TListQ = 2 Then
						t0 = 0.12
						t1 = 0.11
						If TotalTime < 0.5 Then
							t0 = 0.12 * TotalTime / 0.5
							t1 = 0.11 * TotalTime / 0.5
						End If
						t0 += ConsonantTime
						t2 = TotalTime + ConsonantTime - t0 - t1
					End If
				Case DEFType.CAVV
					TotalTime -= ConsonantTime
					If DEF.TListQ = 3 Then
						t0 = 0.12
						t1 = 0.11
						t3 = 0.15
						If TotalTime < 0.6 Then
							t3 = 0.15 * TotalTime / 0.6
						End If
						If TotalTime < 0.5 Then
							t0 = 0.12 * TotalTime / 0.5
							t1 = 0.11 * TotalTime / 0.5
						End If
						t0 += ConsonantTime
						t2 = TotalTime + ConsonantTime - t0 - t1 - t3
					End If
					If DEF.TListQ = 4 Then
						t0 = 0.12
						t1 = 0.11
						t2 = 0.08
						t4 = 0.15
						If TotalTime < 0.6 Then
							t4 = 0.15 * TotalTime / 0.6
						End If
						If TotalTime < 0.5 Then
							t0 = 0.12 * TotalTime / 0.5
							t1 = 0.11 * TotalTime / 0.5
							t2 = 0.08 * TotalTime / 0.5
						End If
						t0 += ConsonantTime
						t3 = TotalTime + ConsonantTime - t0 - t1 - t2 - t4
					End If
			End Select
			.TPhoneList(0).Transition.Time = t0
			If t1 <= 0 Then t1 = 0.0001
			If t2 <= 0 Then t2 = 0.0001
			If t3 <= 0 Then t3 = 0.0001
			If t4 <= 0 Then t4 = 0.0001
			If DEF.TListQ > 0 Then .TPhoneList(1).Transition.Time = t1
			If DEF.TListQ > 1 Then .TPhoneList(2).Transition.Time = t2
			If DEF.TListQ > 2 Then .TPhoneList(3).Transition.Time = t3
			If DEF.TListQ > 3 Then .TPhoneList(4).Transition.Time = t4
		End With
	End Sub
End Module
