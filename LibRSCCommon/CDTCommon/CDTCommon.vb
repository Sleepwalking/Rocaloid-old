'    CDT数据结构
'    Data Structure of CDT files
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
Namespace CDTCommon
	Public Module CDTOperation
		Public Function GetOpe(ByRef _CDT As CDT, ByVal Phone As String) As Double
			Dim i As Integer
			For i = 0 To _CDT.Phonetic.OpennessListQ
				If _CDT.Phonetic.OpennessList(i).Phone = Phone Then
					Return _CDT.Phonetic.OpennessList(i).Ope
				End If
			Next
			Return 1
		End Function
		Public Function CreateDEFCopy(ByRef _DEF As DEF) As DEF
			Dim Ret As New DEF
			Dim i As Integer
			Ret.TListQ = _DEF.TListQ
			ReDim Ret.TList(Ret.TListQ)
			For i = 0 To Ret.TListQ
				Ret.TList(i).TFrom	= _DEF.TList(i).TFrom
				Ret.TList(i).TTo	= _DEF.TList(i).TTo
			Next
			Ret.Extended = _DEF.Extended
			Ret.TRatio = _DEF.TRatio
			Ret.Type = _DEF.Type
			Ret.Name = _DEF.Name
			Return Ret
		End Function
		Public Sub ReplaceDEF(ByRef _DEF As DEF, ByVal Name As String)
			If GetChar(_DEF.Name, 1) <> "/" Then Exit Sub
			
			Dim i As Integer
			Dim SPhone As Char = GetChar(Name, 1)
			For i = 0 To _DEF.TListQ
				If GetChar(_DEF.TList(i).TFrom, 1) = "/" Then _
					_DEF.TList(i).TFrom	= SPhone & Mid(_DEF.TList(i).TFrom, 2)
				If GetChar(_DEF.TList(i).TTo, 1) = "/" Then _
					_DEF.TList(i).TTo	= SPhone & Mid(_DEF.TList(i).TTo, 2)
			Next
		End Sub
		Public Function FindDEFNum(ByRef _CDT As CDT, ByVal Name As String) As Integer
			Dim i As Integer
			For i = 0 To _CDT.DEFListQ
				If _CDT.DEFList(i).Name = Name Then
					Return i
				End If
				If GetChar(_CDT.DEFList(i).Name, 1) = CChar("/") AndAlso _
				   Mid(_CDT.DEFList(i).Name, 2) = Mid(Name, 2) Then
					Return i
				End If
			Next
			Return -1
		End Function
		Public Function FindDEFNum(ByRef _CDT As CDT, ByVal _Segment As Segment) As Integer
			Dim i As Integer
			Dim SingleNotation As String = ToSingleNotation(_Segment.Lyric)
			If GetChar(SingleNotation, 1) = "&" Then
				i = i
			End If
			For i = 0 To _CDT.DEFListQ
				If (GetChar(_CDT.DEFList(i).Name, 1) = CChar("/") AndAlso _
					Mid(_CDT.DEFList(i).Name, 2) = Mid(SingleNotation, 2)) OrElse _
				   _CDT.DEFList(i).Name = SingleNotation Then
					If _CDT.DEFList(i).Extended = True Then
						If _Segment.DurTime > 0.3 Then Return i
					Else
						Return i
					End If
				End If
			Next
			Return -1
		End Function
		Public Function FindDEFNum_0233(ByRef _CDT As CDT, ByVal Name As String) As Integer
			'Obsoleted
			Dim i As Integer
			For i = 0 To _CDT.DEFListQ
				If _CDT.DEFList_0233(i).Name = Name Then
					Return i
				End If
			Next
			Return -1
		End Function
		Public Function FindDEFNum_0233(ByRef _CDT As CDT, ByVal _Segment As Segment) As Integer
			'Obsoleted Overload
			Dim i As Integer
			For i = 0 To _CDT.DEFListQ
				If _CDT.DEFList_0233(i).Name = _Segment.Lyric Then
					If _CDT.DEFList_0233(i).CaseEnabled Then
						If CaseMatch(_CDT.DEFList_0233(i), _Segment) Then Return i
					Else
						Return i
					End If
				End If
			Next
			Return -1
		End Function
		Public Function ToSingleNotation(ByVal Str As String) As String
			If Left(Str, 2) = "zh" Then
				Return "%" & Mid(Str, 3)
			End If
			If Left(Str, 2) = "ch" Then
				Return "^" & Mid(Str, 3)
			End If
			If Left(Str, 2) = "sh" Then
				Return "&" & Mid(Str, 3)
			End If
			Return Str
		End Function
		Private Function CaseMatch(ByRef _DEF As DEF_0233, ByVal _Segment As Segment) As Boolean
			'Obsoleted Matching
			Select Case _DEF.CaseParaType
				Case CaseParameter.Time
					Select Case _DEF.CaseCmp
						Case CaseComparison.More
							Return _Segment.DurTime > _DEF.CasePara
						Case CaseComparison.Less
							Return _Segment.DurTime < _DEF.CasePara
						Case CaseComparison.Equal
							Return _Segment.DurTime = _DEF.CasePara
						Case CaseComparison.MoreOrEqual
							Return _Segment.DurTime >= _DEF.CasePara
						Case CaseComparison.LessOrEqual
							Return _Segment.DurTime <= _DEF.CasePara
					End Select
			End Select
			Return False
		End Function
		Private Sub JoinDEF(ByRef DEFTo As DEF_0233, ByRef DEFFrom As DEF_0233)
			'Obsoleted Joining
			Dim i As Integer
			For i = 0 To DEFFrom.TPhoneListQ
				DEFTo.TPhoneList(DEFTo.TPhoneListQ + i + 1) = DEFFrom.TPhoneList(i)
			Next
			DEFTo.TPhoneListQ += DEFFrom.TPhoneListQ + 1
		End Sub
		Private Sub InsertDEF(ByRef DEFTo As DEF_0233, ByRef DEFFrom As DEF_0233, ByVal Index As Integer)
			'Obsoleted Inserting
			Dim i As Integer
			RightShiftDEF(DEFTo, Index, DEFFrom.TPhoneListQ + 1)
			For i = 0 To DEFFrom.TPhoneListQ
				DEFTo.TPhoneList(Index + i) = DEFFrom.TPhoneList(i)
			Next
		End Sub
		Private Sub RightShiftDEF(ByRef _DEF As DEF_0233, ByVal Start As Integer, ByVal Num As Integer)
			'Obsoleted Shifting
			Dim i As Integer
			_DEF.TPhoneListQ += Num
			For i = _DEF.TPhoneListQ To Num + Start Step - 1
				_DEF.TPhoneList(i) = _DEF.TPhoneList(i - Num)
			Next
		End Sub
		Private Sub LeftCutDEF(ByRef _DEF As DEF_0233, ByRef Start As Integer, ByVal Num As Integer)
			'Obsoleted Cutting
			Dim i As Integer
			_DEF.TPhoneListQ -= Num
			For i = Start To _DEF.TPhoneListQ
				_DEF.TPhoneList(i) = _DEF.TPhoneList(i + Num)
			Next
		End Sub
		Private Sub DEFCpy(ByRef DEFTo As DEF_0233, ByRef DEFFrom As DEF_0233, ByVal Index As Integer)
			'Obsoleted Copying
			InsertDEF(DEFTo, DEFFrom, Index)
			DEFTo.TransitionRatio = DEFFrom.TransitionRatio
		End Sub
		Public Sub Compile(ByRef _CDT As CDT)
			'Obsoleted Compiling
			Dim i As Integer, j As Integer
			Dim Identifier As String
			Dim UseName As String
			For i = 0 To _CDT.DEFListQ
				For j = 0 To _CDT.DEFList_0233(i).TPhoneListQ
					Identifier =  _CDT.DEFList_0233(i).TPhoneList(j)
					If _CDT.DEFList_0233(i).Name = "ran" Then
						i = i
					End If
					If Identifier = "#USE" OrElse Identifier = "#CUSE" Then
						UseName = _CDT.DEFList_0233(i).TPhoneList(j + 1)
						LeftCutDEF(_CDT.DEFList_0233(i), j, 2)
						DEFCpy(
								  _CDT.DEFList_0233(i), _
								  _CDT.DEFList_0233(
								  				FindDEFNum_0233(
								  							_CDT, _
								  						    UseName
								  						  )
								  			  ), _
								  j
							   )
					End If
					If Identifier = "#CUSE" Then
						LeftCutDEF(_CDT.DEFList_0233(i), j, 1)
					End If
				Next
			Next
		End Sub
		Public Function GetDBSet(ByRef _CDT As CDT, ByVal Phone As String, ByVal Pitch As String) As DBSet
			For Each DBSet_ As DBSet In _CDT.DB.DBList
				If DBSet_.Phone = Phone AndAlso DBSet_.Pitch = Pitch Then
					Return DBSet_
				End If
			Next
			Dim Ret As New DBSet
			Ret.VOT = 0
			Return Ret
		End Function
		Public Function GetPhoneSet(ByRef _CDT As CDT, ByVal Phone As String) As PhoneSet
			Return GetPhoneSet(_CDT, GetChar(Phone, 1))
		End Function
		Public Function GetPhoneSet(ByRef _CDT As CDT, ByVal PhoneChar As Char) As PhoneSet
			For Each PhoneSet_ As PhoneSet In _CDT.Phonetic.PhoneList
				If PhoneSet_.Phone = PhoneChar Then
					Return PhoneSet_
				End If
			Next
			Dim Ret As New PhoneSet
			Ret.Type = PhoneType.Vowel
			Return Ret
		End Function
	End Module
	Public Structure CDT
		Dim Version As String
		Dim CDTVersion As String
		Dim Language As String
		Dim DEFListQ As Integer
		Dim DEFList_0233() As DEF_0233 'Obsoleted
		Dim DEFList() As DEF
		Dim Phonetic As PhoneticInfo
		Dim DB As DBInfo
	End Structure
	
	Public Structure DEF
		Dim Name As String
		Dim Type As DEFType
		Dim TRatio As Double
		Dim TListQ As Integer
		Dim TList() As PTransition
		Dim Extended As Boolean
	End Structure
	
	Public Structure DEF_0233
		'Obsoleted DEF Structure
		Dim Name As String
		Dim TransitionRatio As Double
		Dim TPhoneListQ As Integer
		Dim TPhoneList() As String
		Dim CaseEnabled As Boolean
		Dim CaseParaType As CaseParameter
		Dim CaseCmp As CaseComparison
		Dim CasePara As Double
	End Structure
	
	Public Structure PTransition
		Dim TFrom As String
		Dim TTo As String
	End Structure
	
	Public Enum DEFType As Integer
		V	= 0
		VV	= 1
		VVV	= 2
		CV	= 3
		CVV	= 4
		CAV	= 5
		CAVV= 6
	End Enum
	
	Public Structure PhoneticInfo
		Dim OpennessListQ As Integer
		Dim OpennessList() As OpennessSet
		Dim PhoneListQ As Integer
		Dim PhoneList() As PhoneSet
	End Structure
	
	Public Structure OpennessSet
		Dim Phone As String
		Dim Ope As Double
	End Structure
	
	Public Structure PhoneSet
		Dim Phone As String
		Dim Type As PhoneType
		Dim PType As PEnvelopeType
		Dim DataPointQ As Integer
		Dim DataPoint(,) As Double
	End Structure
	
	Public Structure DBInfo
		Dim DBListQ As Integer
		Dim DBList() As DBSet
	End Structure
	
	Public Structure DBSet
		Dim Phone As String
		Dim Pitch As String
		Dim VOT As Integer
		Dim PreShrink As Integer
	End Structure
	
 	Public Enum CaseComparison As Integer
		None = 0
		Less = 1
		More = 2
		Equal = 3
		LessOrEqual = 4
		MoreOrEqual = 5
	End Enum
	
	Public Enum CaseParameter As Integer
		None = 0
		Time = 1
	End Enum
	
	Public Enum PhoneType As Integer
		Consonant = 0
		Vowel = 1
		Semi = 2
	End Enum
	
	Public Enum PEnvelopeType As Integer
		PLO = 0
		FRC = 1
		SEM = 2
		VOW = 3
	End Enum
End Namespace
