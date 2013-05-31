'    常用的抽象函数
'    Useful abstract functions.
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

Public Module Util
	Public Sub ListInsert(Of T)(ByRef List() As T, ByRef ListQ As Integer, ByRef Data As T)
		Dim UBound As Integer = List.GetUpperBound(0)
		If ListQ + 1 > UBound Then
			Array.Resize(List, UBound + 1000)
		End If
		List(ListQ) = Data
		ListQ += 1
	End Sub
End Module
