'    CVS文件结构定义
'    Contains numerous CVS data structure definitions.
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
	Public Function GetSegmentTime(ByRef _Segment As Segment) As Double
		Dim i As Integer
		Dim acc As Double = 0
		For i = 0 To _Segment.SyllableListQ
			acc += _Segment.SyllableList(i).Transition.Time
		Next
		Return acc
	End Function
	Public Function IsConsonant(ByVal Symbol As String) As Boolean
		If Symbol.Length = 1 Then
			Return False
		Else
			Select Case Symbol
				Case "e-"
					Return False
				Case "NN"
					Return False
				Case "NG"
					Return False
				Case Else
					Return True						
			End Select
		End If
	End Function
End Module
'Here, Q represents "Quantity".
Public Structure CVS
	Dim SegmentList() As Segment
	Dim SegmentListQ As Integer
End Structure
Public Structure Segment
	Dim SyllableList() As Syllable
	Dim FreqList() As FreqSet
	Dim SyllableListQ As Integer
	Dim FreqListQ As Integer
	Dim Effects As EffectCollection
	Dim StartTime As Double
End Structure
Public Structure Syllable
	Dim Start As SyllableStart
	Dim Dest As SyllableDest 'Avoided using keyword End.
	Dim Transition As SyllableTransition
End Structure
Public Structure FreqSet
	Dim Time As Double
	Dim Freq As Double
End Structure
Public Structure SyllableStart
	Dim Type As Boolean 'True : New, False : Preserved
	Dim Symbol As String
	Dim Preserved As Integer
End Structure
Public Structure SyllableDest
	Dim Type As Boolean 'True : New, False : Preserved
	Dim Symbol As String
	Dim Preserved As Integer
End Structure
Public Structure SyllableTransition
	Dim StartRatio As Double
	Dim EndRatio As Double
	Dim Time As Double
End Structure
Public Structure EffectCollection
	Dim Shrink As Double	
	Dim ForwardCut As Double
	Dim EnvelopeList() As EnvelopeSet
	Dim EnvelopeListQ As Integer
	Dim ElistEnabled As Boolean
	Dim PElopeEnabled As Boolean
	Dim PresetedEnvelope As Integer
	Dim ADSR As ADSREnvelope
	Dim OpennessList() As Double
	Dim Vibration As VibrationStruct
	Dim Breath As BreathStruct
End Structure
Public Structure EnvelopeSet
	Dim Time As Double
	Dim Amplitude As Double
End Structure
Public Structure BreathStruct
	Dim Magnitude As Double
End Structure
Public Structure VibrationStruct
	Dim StartTime As Double
	Dim Interval As Double
	Dim FreqChange As Double
End Structure
Public Structure ADSREnvelope
	Dim Amplitude As Double
	Dim Attack As Double
	Dim Decline As Double
	Dim Release As Double
End Structure
Public Enum Envelopes As Integer
	ADSR = 0
End Enum