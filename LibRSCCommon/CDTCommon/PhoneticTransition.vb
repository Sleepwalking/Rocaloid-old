'    PhoneSet中的过渡计算
'    Calculations of Transitions in PhoneSet.
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
	Public  Structure Transition
		Dim StartNum As Integer
		Dim EndNum As Integer
		Dim Ratio As Double
	End Structure
	Public Structure PhoneticData
		Dim LastEnd As Double
		Dim ForwardOffset As Double
		Dim VOT As Double
	End Structure
	Public Module PhoneticTransition
		Public Function GetTransitionRate(ByVal Time As Double, ByRef _PhoneSet As PhoneSet) As Transition
			Dim i As Integer
			Dim ret As Transition
			For i = _PhoneSet.DataPointQ To 0 Step - 1
				If Time >= _PhoneSet.DataPoint(i, 0) AndAlso Time < _PhoneSet.DataPoint(i + 1, 0) Then
					ret.Ratio = (Time - _PhoneSet.DataPoint(i, 0)) / (_PhoneSet.DataPoint(i + 1, 0) - _PhoneSet.DataPoint(i, 0))
					ret.StartNum = i
					ret.EndNum = i + 1
					Return ret
				End If
			Next
			If Time < _PhoneSet.DataPoint(_PhoneSet.DataPointQ, 0) Then
				ret.StartNum = _PhoneSet.DataPointQ - 1
				ret.EndNum = _PhoneSet.DataPointQ
				ret.Ratio = 1
				Return ret
			End If
			If Time >= _PhoneSet.DataPoint(0, 0) Then
				ret.StartNum = 0
				ret.EndNum = 1
				ret.Ratio = 0
			End If
			Return ret
		End Function
		Public Function GetData(ByVal _Transition As Transition, ByRef _PhoneSet As PhoneSet) As PhoneticData
			Dim ret As PhoneticData
			ret.LastEnd = _PhoneSet.DataPoint(_Transition.StartNum, 1) * (1 - _Transition.Ratio) + _PhoneSet.DataPoint(_Transition.EndNum, 1) * _Transition.Ratio
			ret.ForwardOffset = _PhoneSet.DataPoint(_Transition.StartNum, 2) * (1 - _Transition.Ratio) + _PhoneSet.DataPoint(_Transition.EndNum, 2) * _Transition.Ratio
			ret.VOT = _PhoneSet.DataPoint(_Transition.StartNum, 3) * (1 - _Transition.Ratio) + _PhoneSet.DataPoint(_Transition.EndNum, 3) * _Transition.Ratio
			Return ret
		End Function
		Public Function GetData(ByVal Time As Double, ByRef _PhoneSet As PhoneSet) As PhoneticData
			Return GetData(GetTransitionRate(Time, _PhoneSet), _PhoneSet)
		End Function
	End Module
End Namespace