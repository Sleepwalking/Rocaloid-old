'    提供CVS结构的常用计算。
'    Provides useful calculations of CVS structure.
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

Imports CVSCommon
Public Structure TSymbol
	Public Start As String
	Public Dest As String
End Structure
Public Module CVSOperation
	Public Function GetDuration(ByRef Segment_ As Segment) As Double
		Dim i As Integer
		Dim ret As Double = 0
		For i = 0 To Segment_.TPhoneListQ
			ret += Segment_.TPhoneList(i).Transition.Time
		Next
		Return ret - Segment_.Effects.Shrink - Segment_.Effects.ForwardCut
	End Function
	Public Function GetEndTime(ByRef Segment_ As Segment) As Double
		Return GetDuration(Segment_) + Segment_.StartTime
	End Function
	Public Function GetCVSLength(ByRef CVS_ As CVS) As Double
		Return GetEndTime(CVS_.SegmentList(CVS_.SegmentListQ))
	End Function
	Public Function GetSegment(ByRef CVS_ As CVS, ByVal Time As Double) As Integer
		Dim i As Integer
		Dim ret As Integer
		For i = 0 To CVS_.SegmentListQ
			If Time > CVS_.SegmentList(i).StartTime Then
				ret = i
			End If
		Next
		Return ret
	End Function
	Public Function GetTimeSinceSegment(ByRef Segment_ As Segment, ByVal Time As Double) As Double
		Return Time - Segment_.StartTime
	End Function
	Public Function GetTSymbol(ByRef Segment_ As Segment, ByVal Index As Integer) As TSymbol
		Dim p1 As String, p2 As String
		Dim i As Integer
		Dim ret As New TSymbol
		p1 = "" : p2 = ""
		For i = 0 To Segment_.TPhoneListQ
			With Segment_.TPhoneList(i)
				If .Start.Type = True Then
					'new
					p1 = .Start.Symbol
				Else
					'psvd
					If .Start.Preserved = 1 Then
						p1 = p1
					Else
						p1 = p2
					End If
				End If
				If .Dest.Type = True Then
					'new
					p2 = .Dest.Symbol
				Else
					'psvd
					If .Dest.Preserved = 1 Then
						p2 = p1
					Else
						p2 = p2
					End If
				End If
				If i = Index Then
					ret.Start = p1
					ret.Dest = p2
				End If
			End With
		Next
		Return ret
	End Function
	Public Sub Arrange(ByRef CVS_ As CVS, ByVal Arrangement() As Boolean)
		Dim i As Integer
		For i = 0 To CVS_.SegmentListQ
			If i Mod 2 = 0 Then
				Arrangement(i) = False
			Else
				Arrangement(i) = True
			End If
		Next
	End Sub
End Module
