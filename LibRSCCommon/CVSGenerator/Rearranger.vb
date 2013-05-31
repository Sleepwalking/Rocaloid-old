'    根据CDT中的语音学数据修改RSC
'    Make adaptions to RSC with phonetic datas in CDT.
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

Public Module Rearranger
	Public Sub Rearrange(ByVal _RSC As RSC, ByRef RSCOrg As RSC, ByRef _CDT As CDTCommon.CDT)
		Dim i As Integer
		Dim Phonetic As CDTCommon.PhoneticData
		Dim AdjustedPhonetic As CDTCommon.PhoneticData
		Dim ThisStartTime As Double, LastStartTime As Double, ThisDurTime As Double, LastEndTime As Double, IntervalTime As Double
		Dim ThisFirstPhone As String, ThisPitch As String
		Dim ThisDEF As CDTCommon.DEF
		Dim ThisDB As CDTCommon.DBSet
		Dim ThisPhoneSet As CDTCommon.PhoneSet
		Dim DBVOT As Double
		LastStartTime = -100
		
		For i = 0 To RSCOrg.SegmentListQ
			ThisStartTime = RSCOrg.SegmentList(i).StartTime
			ThisDurTime = RSCOrg.SegmentList(i).DurTime
			If i > 0 Then
				LastStartTime = _RSC.SegmentList(i - 1).StartTime
				LastEndTime = _RSC.SegmentList(i - 1).DurTime + LastStartTime - _RSC.SegmentList(i - 1).CutTime
			End If
			IntervalTime = ThisStartTime - LastStartTime
			
			ThisDEF = CDTCommon.CreateDEFCopy(_CDT.DEFList(CDTCommon.FindDEFNum(_CDT, RSCOrg.SegmentList(i))))
			CDTCommon.ReplaceDEF(ThisDEF, CDTCommon.ToSingleNotation(RSCOrg.SegmentList(i).Lyric))
			
			ThisFirstPhone = ThisDEF.TList(0).TFrom
			ThisPitch = GetPitchByFreq(RSCOrg.SegmentList(i).StartFreq)
			ThisDB = CDTCommon.GetDBSet(_CDT, ThisFirstPhone, ThisPitch)
			ThisPhoneSet = CDTCommon.GetPhoneSet(_CDT, ThisFirstPhone)
			DBVOT = CDbl(ThisDB.VOT) / 96000
						
			If ThisPhoneSet.Type = CDTCommon.PhoneType.Vowel Then
				Phonetic.ForwardOffset = 0.07
				Phonetic.LastEnd = 0
				Phonetic.VOT = 0
			Else
				Phonetic = CDTCommon.GetData(LastEndTime - LastStartTime, ThisPhoneSet)
			End If
			
			AdjustedPhonetic.ForwardOffset = Math.Min(DBVOT, Phonetic.ForwardOffset)
			AdjustedPhonetic.LastEnd = Phonetic.LastEnd - (Phonetic.ForwardOffset - AdjustedPhonetic.ForwardOffset)
			AdjustedPhonetic.VOT = Math.Min(DBVOT, Phonetic.VOT)
			
			If ThisPhoneSet.PType = CDTCommon.PEnvelopeType.PLO Then
				AdjustedPhonetic.VOT = DBVOT / 5 * 4
			End If
			
			If i > 0 Then 
				LastEndTime = Math.Min(LastEndTime, ThisStartTime - AdjustedPhonetic.LastEnd)
				_RSC.SegmentList(i - 1).DurTime = LastEndTime - _RSC.SegmentList(i - 1).StartTime
			End If
			
			With _RSC.SegmentList(i)
				.StartTime -= AdjustedPhonetic.ForwardOffset
				.CutTime = DBVOT - AdjustedPhonetic.VOT
				.DurTime += .CutTime + AdjustedPhonetic.ForwardOffset
				If i > 0 Then
					If ThisPhoneSet.Type = CDTCommon.PhoneType.Vowel OrElse ThisPhoneSet.Type = CDTCommon.PhoneType.Semi Then
						_RSC.SegmentList(i - 1).DurTime += 0.03
						.StartTime -= 0.02
						.DurTime += 0.02
					End If
					If _RSC.SegmentList(i - 1).DurTime < 0.15 AndAlso .StartTime > _RSC.SegmentList(i - 1).DurTime + LastStartTime Then
						'_RSC.SegmentList(i - 1).DurTime = 0.5 * (.StartTime + _RSC.SegmentList(i - 1).DurTime + LastStartTime)
					End If
				End If
			End With
			
		Next
	End Sub
End Module
