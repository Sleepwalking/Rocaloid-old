'    一些结构定义
'    Some structure definitions.
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

Public Class PointList
	Public PointQ As Integer
	Public Points() As PointF
	Public Style As WaveStyle
End Class

Public Class BarList
	Public BarQ As Integer
	Public Bars() As Integer
	Public Style As WaveStyle
End Class

Public Structure SelectedSet
	Public SelectFrom As Integer
	Public SelectTo As Integer
	Public Style As WaveStyle
End Structure

Public Structure WaveStyle
	Public Show As Boolean
	Public Color As Color
End Structure

Public Structure SearchResult
	Public Num As Integer
	Public Position As Integer
End Structure

Public Structure LoadResult
	Public BasePeriod As Integer
	Public StartPosition As Integer
End Structure

Public Structure AnalysisInfo
	Public Symbol As String
	Public Pitch As String
End Structure

Public Enum EditMode
	WavEditor = 0	
	WavAnalysis = 1
	CVQC = 2
End Enum

Public Enum Algorism
	Correlation = 0
	Difference = 1
End Enum