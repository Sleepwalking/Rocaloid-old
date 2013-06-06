'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Imports CVSCommon
Public Class SingleNoteBox
	Inherits NoteBox
	Public InnerSegment As Segment
	Public Event SegmentUpdate()
	Private OriginalTime As Double
	
	Public Sub New()
		MyBase.New()
		Duration = 0.5
		LNoteNum = -1
		RNoteNum = -1
		Loaded = False
		SelectBarEnabled = False
	End Sub
	
	Public Sub LoadSegment(ByRef Segment_ As Segment)
		InnerSegment = Segment_
		ScrollBar.Maximum = CInt(GetDuration(Segment_) * 100)
		ScrollBar.LargeChange = CInt(Duration * 100)
		ReDim NoteList(Segment_.TPhoneListQ)
		Loaded = True
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
		Dim CurrentPen As New Pen(Color.DimGray)
		
		StartTime = 0
		LNoteNum = -1
		RNoteNum = -1
		
		With InnerSegment
			For i = 0 To .TPhoneListQ
				EndTime = StartTime + .TPhoneList(i).Transition.Time
				If EndTime > LBound And StartTime < RBound Then
					If LNoteNum = -1 Then LNoteNum = i
					RNoteNum = i
					
					xbound = AbsoluteToRelative(StartTime)
					xdur = CInt((EndTime - StartTime) / Duration * Width)
					
					NoteList(i).StartPos = xbound
					NoteList(i).Duration = xdur
					SDSymbol = GetTSymbol(InnerSegment, i)
					
					GraphicControl.FillRectangle(CurrentBrush, xbound, 0, xdur, 31)
					GraphicControl.DrawRectangle(CurrentPen, xbound, 0, xdur, 31)
					GraphicControl.DrawString(SDSymbol.Start & "->" & SDSymbol.Dest, New Font("Arial", 12), TextBrush, xbound + 3, 7)
					GraphicControl.DrawLine(CurrentPen, _
						xbound, CSng(31 - 31 * InnerSegment.TPhoneList(i).Transition.StartRatio), _
						xbound + xdur, CSng(31 - 31 * InnerSegment.TPhoneList(i).Transition.EndRatio))
				End If
				StartTime = EndTime
			Next
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
End Class
