'    一个特殊的NoteBox，用于装载一个段中的过渡音素。
'    A special NoteBox which is used to contain the TPhones in a segment.
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
Public Enum SBoxMode As Integer
	Non = 0
	ADSR = 1
	Shrink = 2
End Enum
Public Class SingleNoteBox
	Inherits NoteBox
	Public InnerSegment As Segment
	Public Event SegmentUpdate()
	Public Event ParentNoteBoxUpdate()
	Private OriginalTime As Double
	Public Mode As SBoxMode
	
	Public Sub New()
		MyBase.New()
		Duration = 0.5
		LNoteNum = -1
		RNoteNum = -1
		Loaded = False
		SelectBarEnabled = False
		Mode = SBoxMode.Non
	End Sub
	
	Public Sub LoadSegment(ByRef Segment_ As Segment)
		InnerSegment = Segment_
		ScrollBar.Value = 0
		LBound = 0
		ScrollBar.Maximum = CInt(GetDuration(Segment_) * 100)
		ScrollBar.LargeChange = CInt(Duration * 100)
		ReDim NoteList(Segment_.TPhoneListQ)
		Loaded = True
		Redraw()
	End Sub
	
	Public Sub ReloadSegment(ByRef Segment_ As Segment)
		InnerSegment = Segment_
		ReDim NoteList(Segment_.TPhoneListQ)
		Loaded = True
		Redraw()
	End Sub
	
	Public Overrides Sub Redraw()
		GraphicControl.Clear(Color.White)
		If Not Loaded Then Exit Sub
		DrawBars()
		Invalidate()
	End Sub
	
	Public Overrides Sub DrawBars()
		Dim i As Integer
		Dim StartTime As Double, EndTime As Double
		Dim xbound As Integer
		Dim xdur As Integer
		Dim SDSymbol As TSymbol
		Dim CurrentBrush As New SolidBrush(Color.Pink)
		Dim TextBrush As New SolidBrush(Color.Black)
		Dim BorderPen As New Pen(Color.DimGray)
		Dim TransitionPen As New Pen(Color.Red)
		Dim EnvelopePen As New Pen(Color.Green)
		Dim CutPen As New Pen(Color.Blue)
		
		StartTime = 0
		LNoteNum = -1
		RNoteNum = -1
		
		With InnerSegment
			For i = 0 To .TPhoneListQ
				EndTime = StartTime + .TPhoneList(i).Transition.Time
				If EndTime > LBound And StartTime < RBound Then
					If LNoteNum = -1 Then LNoteNum = i
					RNoteNum = i
					
					'Draw Note
					xbound = AbsoluteToRelative(StartTime)
					xdur = CInt((EndTime - StartTime) / Duration * Width)
					
					NoteList(i).StartPos = xbound
					NoteList(i).Duration = xdur
					SDSymbol = GetTSymbol(InnerSegment, i)
					
					GraphicControl.FillRectangle(CurrentBrush, xbound, 0, xdur, Height - 1)
					GraphicControl.DrawRectangle(BorderPen, xbound, 0, xdur, Height - 1)
					GraphicControl.DrawString(SDSymbol.Start & "->" & SDSymbol.Dest, New Font("Arial", 12), TextBrush, xbound + 3, 7)
					
					'Draw Transition
					GraphicControl.DrawLine(TransitionPen, _
						xbound, CSng(Height - 1 - Height * InnerSegment.TPhoneList(i).Transition.StartRatio), _
						xbound + xdur, CSng(Height - 1 - Height * InnerSegment.TPhoneList(i).Transition.EndRatio))
				End If
				StartTime = EndTime
			Next
			'Draw ADSR
			If Mode = SBoxMode.ADSR Then
				With InnerSegment.Effects.ADSR
					Dim ADSRAmplitudex As Integer, ADSRAmplitudey As Integer, ADSRSustainx As Integer, ADSRReleasex As Integer, ADSRTotalx As Integer
					Dim TotalLength As Double = CVSOperation.GetDuration(InnerSegment) + InnerSegment.Effects.Shrink + InnerSegment.Effects.ForwardCut
					ADSRAmplitudex = CInt(AbsoluteToRelative(.Attack))
					ADSRAmplitudey = Height - 1 - CInt(.Amplitude * Height * 0.5)
					ADSRSustainx = ADSRAmplitudex + CInt(AbsoluteToRelative(.Decline))
					ADSRTotalx = CInt(AbsoluteToRelative(TotalLength))
					ADSRReleasex = CInt(AbsoluteToRelative(TotalLength - .Release))
					GraphicControl.DrawLine(EnvelopePen, CInt(AbsoluteToRelative(0)), Height - 1, ADSRAmplitudex, ADSRAmplitudey)
					GraphicControl.DrawLine(EnvelopePen, ADSRAmplitudex, ADSRAmplitudey, ADSRSustainx, CInt(Height * 0.5))
					GraphicControl.DrawLine(EnvelopePen, ADSRSustainx, CInt(Height * 0.5), ADSRReleasex, CInt(Height * 0.5))
					GraphicControl.DrawLine(EnvelopePen, ADSRReleasex, CInt(Height * 0.5), ADSRTotalx, Height)
				End With
			End If
			
			'Draw Shrinkage
			If Mode = SBoxMode.Shrink Then
				With InnerSegment.Effects
					Dim ForwardCutx As Integer, Shrinkx As Integer
					ForwardCutx = CInt(AbsoluteToRelative(.ForwardCut))
					Shrinkx = CInt(AbsoluteToRelative(.ForwardCut + .Shrink))
					GraphicControl.DrawLine(CutPen, ForwardCutx, 0, ForwardCutx, Height - 1)
					GraphicControl.DrawLine(EnvelopePen, Shrinkx, 0, Shrinkx, Height - 1)
				End With
			End If
			
		End With
	End Sub
	Public Sub NBoxMouseScroll(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseWheel
		MouseX = e.X
		Dim i As Integer
		If LNoteNum < 0 Then Exit Sub
		For i = LNoteNum To RNoteNum
			If NoteList(i).StartPos < MouseX And NoteList(i).EndPos > MouseX Then
				InnerSegment.TPhoneList(i).Transition.EndRatio += e.Delta / 1800
				If InnerSegment.TPhoneList(i).Transition.EndRatio < 0 Then InnerSegment.TPhoneList(i).Transition.EndRatio = 0
				If InnerSegment.TPhoneList(i).Transition.EndRatio > 1 Then InnerSegment.TPhoneList(i).Transition.EndRatio = 1
				If i < InnerSegment.TPhoneListQ AndAlso InnerSegment.TPhoneList(i + 1).Start.Type = False AndAlso InnerSegment.TPhoneList(i + 1).Start.Preserved = 1 Then
					InnerSegment.TPhoneList(i + 1).Transition.StartRatio = InnerSegment.TPhoneList(i).Transition.EndRatio 
				End If
				Redraw()
			End If
		Next
	End Sub
	Public Overrides Sub NBoxMouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseMove
		Focus()
		If Not EditEnabled Then Exit Sub
		MouseX = e.X
		If IsMouseDown Then
			'Drag
			If IsDragging Then
				InnerSegment.TPhoneList(DragNoteNum).Transition.Time = OriginalTime + (MouseX - MouseDownX) / Width * Duration
				If InnerSegment.TPhoneList(DragNoteNum).Transition.Time < 0.005 Then
					InnerSegment.TPhoneList(DragNoteNum).Transition.Time = 0.005
				End If
				Redraw()
				RaiseEvent SegmentUpdate()
			End If
		End If
	End Sub
	Public Overrides Sub NBoxMouseDown(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseDown
		If Not EditEnabled Then Exit Sub
		MouseDownX = e.X
		IsMouseDown = True
		Dim i As Integer
		If LNoteNum < 0 Then Exit Sub
		For i = LNoteNum To RNoteNum
			If NoteList(i).StartPos < e.X And NoteList(i).EndPos > e.X Then
				DragNoteNum = i
				IsDragging = True
				OriginalTime = InnerSegment.TPhoneList(i).Transition.Time
				Redraw()
				Exit For
			End If
		Next
	End Sub
	Public Overrides Sub NBoxMouseUp(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseUp
		If Not EditEnabled Then Exit Sub
		IsMouseDown = False
		IsDragging = False
		MouseX = e.X
		SelectBar = RelativeToAbsolute(MouseX)
		ScrollBar.Maximum = CInt(GetDuration(InnerSegment) * 100)
		RaiseEvent ParentNoteBoxUpdate()
		Redraw()
	End Sub
End Class
