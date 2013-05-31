'    提供CDT读取函数
'    Provides CDT reading functions.
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

Namespace CDTCommon
	Public Module RDLIOExtend
		Public Function TestIfIsCaseParameter(ByVal _String As String) As CaseParameter
			Select Case _String
				Case "Time"
					Return CaseParameter.Time
				Case Else
					Throw New Exception(_String & " is not a valid Case Parameter!")
			End Select
			Return CaseParameter.None
		End Function
		Public Function TestIfIsCaseComparison(ByVal _String As String) As CaseComparison
			Select Case _String
				Case ">"
					Return CaseComparison.More
				Case "<"
					Return CaseComparison.Less
				Case "="
					Return CaseComparison.Equal
				Case ">="
					Return CaseComparison.MoreOrEqual
				Case "<="
					Return CaseComparison.LessOrEqual
				Case Else
					Throw New Exception(_String & " is not a valid Case Comparison!")
			End Select
			Return CaseComparison.None
		End Function
		Public Function TestIfIsDEFType(ByVal _String As String) As DEFType
			Select Case _String
				Case "V"
					Return DEFType.V
				Case "VV"
					Return DEFType.VV
				Case "VVV"
					Return DEFType.VVV
				Case "CV"
					Return DEFType.CV
				Case "CVV"
					Return DEFType.CVV
				Case "CAV"
					Return DEFType.CAV
				Case "CAVV"
					Return DEFType.CAVV
				Case Else
					Throw New Exception(_String & " is not a valid Case Comparison!")
			End Select
			Return DEFType.V
		End Function
	End Module
	
	Public Module CDTRead
		Private Reader As RDLReader
		
		Public Sub Reader_Open(ByVal File As String)
			Reader = New RDLReader(File)
		End Sub
		
		Public Sub Reader_Close()
			Reader.Close()
		End Sub
		
		Public Sub CDT_Read(ByRef _CDT As CDT)
			If Reader.Read() <> "#CDT" Then
				'Not Cybervoice Dictionary
				Throw New Exception("The file is not a Rocaloid Script !")
			End If
			_CDT.CDTVersion = Reader.Read()
			Select Case _CDT.CDTVersion
				Case "2.33"
				Case "2.41"
				Case Else
					Throw New Exception("Wrong CDT version.")
			End Select
			Dim StrBuff As String
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "Version"
						StrBuff = Reader.Read()
						_CDT.Version = StrBuff
					Case "Language"
						StrBuff = Reader.Read()
						_CDT.Language = StrBuff
					Case "DEFList"
						If _CDT.CDTVersion = "2.33" Then DEFList_0233_Read(_CDT)
						If _CDT.CDTVersion = "2.41" Then DEFList_Read(_CDT)
					Case "PhoneticInfo"
						PhoneticInfo_Read(_CDT.Phonetic)
					Case "DBInfo"
						DBInfo_Read(_CDT.DB)
					Case Else
						'Throw New Exception("Invalid identifier as " & StrBuff & ".")
				End Select
			Loop While StrBuff <> "End"
		End Sub
		
		Public Sub DEFList_Read(ByRef _CDT As CDT)
			Dim StrBuff As String
			Dim Count As Integer = 0
			ReDim _CDT.DEFList(5000)
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "DEF"
						DEF_Read(_CDT.DEFList(Count))
						Count += 1
				End Select
			Loop While StrBuff <> "End"
			_CDT.DEFListQ = Count - 1
		End Sub
		
		Public Sub DEFList_0233_Read(ByRef _CDT As CDT)
			Dim StrBuff As String
			Dim Count As Integer = 0
			ReDim _CDT.DEFList_0233(5000)
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "#DEF"
						DEF_0233_Read(_CDT.DEFList_0233(Count))
						Count += 1
				End Select
			Loop While StrBuff <> "End"
			_CDT.DEFListQ = Count - 1
		End Sub
		
		Public Sub DEF_Read(ByRef _DEF As DEF)
			Dim StrBuff As String
			Dim i As Integer
			StrBuff = Reader.Read()
			_DEF.Name = StrBuff
			_DEF.Extended = False
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "Type"
						StrBuff = Reader.Read()
						_DEF.Type = TestIfIsDEFType(StrBuff)
					Case "TRatio"
						StrBuff = Reader.Read()
						_DEF.TRatio = TestIfIsDoubleNotNegative(StrBuff)
					Case "TList"
						ReDim _DEF.TList(10)
						i = 0
						While True
							StrBuff = Reader.Read()
							If StrBuff = "T" Then
								_DEF.TList(i).TFrom = Reader.Read()
								_DEF.TList(i).TTo = Reader.Read()
							Else
								'End
								_DEF.TListQ = i - 1
								StrBuff = "-"
								Exit While
							End If
							i += 1
						End While
					Case "Extended"
						StrBuff = Reader.Read()
						_DEF.Extended = TestIfIsBoolean(StrBuff)
				End Select
			Loop While StrBuff <> "End"
		End Sub
		
		Public Sub DEF_0233_Read(ByRef _DEF As DEF_0233)
			Dim StrBuff As String
			StrBuff = Reader.Read()
			_DEF.Name = StrBuff
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "Case"
						_DEF.CaseEnabled = True
						StrBuff = Reader.Read()
						_DEF.CaseParaType = TestIfIsCaseParameter(StrBuff)
						StrBuff = Reader.Read()
						_DEF.CaseCmp = TestIfIsCaseComparison(StrBuff)
						StrBuff = Reader.Read()
						_DEF.CasePara = TestIfIsDouble(StrBuff)
					Case "TransitionRatio"
						StrBuff = Reader.Read()
						_DEF.TransitionRatio = TestIfIsDoubleNotNegative(StrBuff)
					Case "TPhoneList"
						TPhoneList_Read(_DEF)
				End Select
			Loop While StrBuff <> "#EDEF"
		End Sub
		
		Public Sub TPhoneList_Read(ByRef _DEF As DEF_0233)
			Dim StrBuff As String = ""
			Dim Count As Integer = 0
			ReDim _DEF.TPhoneList(10)
			StrBuff = Reader.Read()
			While StrBuff <> "End"
				_DEF.TPhoneList(Count) = StrBuff
				Count += 1
				StrBuff = Reader.Read()
			End While
			_DEF.TPhoneListQ = Count - 1
		End Sub
		
		Public Sub PhoneticInfo_Read(ByRef _PhoneticInfo As PhoneticInfo)
			Dim StrBuff As String = ""
			Dim i As Integer
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "OpennessListQ"
						StrBuff = Reader.Read()
						_PhoneticInfo.OpennessListQ = TestIfIsIntNotNegative(StrBuff) - 1
						ReDim _PhoneticInfo.OpennessList(_PhoneticInfo.OpennessListQ)
					Case "OpennessList"
						For i = 0 To _PhoneticInfo.OpennessListQ
							StrBuff = Reader.Read()
							_PhoneticInfo.OpennessList(i).Phone = StrBuff
							StrBuff = Reader.Read()
							_PhoneticInfo.OpennessList(i).Ope = TestIfIsDoubleNotNegative(StrBuff)
						Next
					Case "PhoneListQ"
						StrBuff = Reader.Read()
						_PhoneticInfo.PhoneListQ = TestIfIsIntNotNegative(StrBuff) - 1
						ReDim _PhoneticInfo.PhoneList(_PhoneticInfo.PhoneListQ + 1)
					Case "PhoneList"
						For i = 0 To _PhoneticInfo.PhoneListQ
							PhoneSet_Read(_PhoneticInfo.PhoneList(i))
						Next
						Reader.Read()
				End Select
			Loop While StrBuff <> "End"
		End Sub
		
		Public Sub PhoneSet_Read(ByRef _PhoneSet As PhoneSet)
			Dim StrBuff As String = ""
			Dim i As Integer, j As Integer
			Dim Offset() As Double = {0, 0, 0, 0}
			Dim Multiple() As Double = {0, 1, 1, 1}
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "Phone"
						StrBuff = Reader.Read()
						_PhoneSet.Phone = StrBuff
					Case "Type"
						StrBuff = Reader.Read()
						_PhoneSet.Type = TestIfIsPhoneType(StrBuff)
					Case "PType"
						StrBuff = Reader.Read()
						_PhoneSet.PType = TestIfIsPType(StrBuff)
					Case "#DataOffset"
						StrBuff = Reader.Read()
						Offset(1) = TestIfIsDouble(StrBuff)
						StrBuff = Reader.Read()
						Offset(2) = TestIfIsDouble(StrBuff)
						StrBuff = Reader.Read()
						Offset(3) = TestIfIsDouble(StrBuff)
					Case "#DataMultiple"
						StrBuff = Reader.Read()
						Multiple(1) = TestIfIsDouble(StrBuff)
						StrBuff = Reader.Read()
						Multiple(2) = TestIfIsDouble(StrBuff)
						StrBuff = Reader.Read()
						Multiple(3) = TestIfIsDouble(StrBuff)
					Case "DataPointQ"
						StrBuff = Reader.Read()
						_PhoneSet.DataPointQ = TestIfIsIntNotNegative(StrBuff) - 1
						ReDim _PhoneSet.DataPoint(_PhoneSet.DataPointQ + 1, 4)
					Case "DataPoint"
						For i = 0 To _PhoneSet.DataPointQ
							_PhoneSet.DataPoint(i, 0) = (_PhoneSet.DataPointQ + 1 - i) * 0.025
							For j = 1 To 3
								_PhoneSet.DataPoint(i, j) = TestIfIsDouble(Reader.Read()) * Multiple(j) + Offset(j)
							Next
						Next
				End Select
			Loop While StrBuff <> "End"
		End Sub
		
		Public Sub DBInfo_Read(ByRef _DBInfo As DBInfo)
			Dim StrBuff As String = ""
			Dim i As Integer
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "DBListQ"
						StrBuff = Reader.Read()
						_DBInfo.DBListQ = TestIfIsIntNotNegative(StrBuff) - 1
						ReDim _DBInfo.DBList(_DBInfo.DBListQ + 1)
					Case "DBList"
						For i = 0 To _DBInfo.DBListQ
							DBSet_Read(_DBInfo.DBList(i))
						Next
						If Reader.Read() <> "End" Then
							Throw New Exception("List without an End.")
						End If
				End Select
			Loop While StrBuff <> "End"
		End Sub
		
		Public Sub DBSet_Read(ByRef _DBSet As DBSet)
			Dim StrBuff As String = ""
			Do
				StrBuff = Reader.Read()
				Select Case StrBuff
					Case "Pho"
						StrBuff = Reader.Read()
						_DBSet.Phone = StrBuff
				    Case "Pit"
				    	StrBuff = Reader.Read()
				    	_DBSet.Pitch = StrBuff
				    Case "VOT"
				    	StrBuff = Reader.Read()
				    	_DBSet.VOT = TestIfIsIntNotNegative(StrBuff)
				    Case "PSnk"
				    	StrBuff = Reader.Read()
				    	_DBSet.PreShrink = TestIfIsIntNotNegative(StrBuff)
				End Select
			Loop While  StrBuff <> "End"
		End Sub
	End Module
End Namespace
