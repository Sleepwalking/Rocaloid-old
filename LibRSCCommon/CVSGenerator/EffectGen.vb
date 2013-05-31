'    通过CDT从RSC生成部分效果到CVS
'    Generates some of the Effects from RSC to CVS via CDT.
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
Public Module EffectGenerator
	Public Sub GeneratePElope(ByVal _RSC As RSC, ByRef _CVS As CVSCommon.CVS, ByRef PhoneSet As CDTCommon.PhoneSet, ByVal Num As Integer)
		With _CVS.SegmentList(Num).Effects.ADSR
			If PhoneSet.Type <> CDTCommon.PhoneType.Vowel Then
				Select Case PhoneSet.PType
					Case CDTCommon.PEnvelopeType.PLO
						.Attack = 0
						.Amplitude = 1
						.Decline = 0.1
						.Release = 0.07
					Case CDTCommon.PEnvelopeType.FRC
						.Attack = 0.05
						.Amplitude = 1
						.Decline = 0.1
						.Release = 0.07
					Case CDTCommon.PEnvelopeType.SEM
						.Attack = 0.06
						.Amplitude = 1
						.Decline = 0.1
						.Release = 0.07
					Case Else
						.Attack = 0.07
						.Amplitude = 1
						.Decline = 0.1
						.Release = 0.1
				End Select
			Else
				.Attack = 0.1
				.Amplitude = 1.2
				.Decline = 0.1
				.Release = 0.1
			End If
		End With
	End Sub
	Public Sub GenerateOpeList(ByVal _CVS As CVSCommon.CVS, ByRef _RSC As RSC, ByVal _CDT As CDTCommon.CDT, ByVal Num As Integer)
		Dim i As Integer
		Dim s1 As String, s2 As String
		Dim l1 As String, l2 As String
		l1 = ""
		l2 = ""
		With _CVS.SegmentList(Num)
			ReDim .Effects.OpennessList(.TPhoneListQ + 1)
			.Effects.OpennessList(0) = CDTCommon.GetOpe(_CDT, .TPhoneList(0).Start.Symbol)
			For i = 0 To .TPhoneListQ
				If Not .TPhoneList(i).Start.Type Then
					'Preserved
					If .TPhoneList(i).Start.Preserved = 1 Then
						s1 = l1
					Else
						s1 = l2
					End If
				Else
					'New
					s1 = .TPhoneList(i).Start.Symbol
				End If
				If Not .TPhoneList(i).Dest.Type Then
					'Preserved
					If .TPhoneList(i).Dest.Preserved = 1 Then
						s2 = l1
					Else
						s2 = l2
					End If
				Else
					'New
					s2 = .TPhoneList(i).Dest.Symbol
				End If
				.Effects.OpennessList(i + 1) = CDTCommon.GetOpe(_CDT, s1) * (1 - .TPhoneList(i).Transition.EndRatio) + _
											   CDTCommon.GetOpe(_CDT, s2) * .TPhoneList(i).Transition.EndRatio
				l1 = s1
				l2 = s2
			Next
		End With
	End Sub
End Module
