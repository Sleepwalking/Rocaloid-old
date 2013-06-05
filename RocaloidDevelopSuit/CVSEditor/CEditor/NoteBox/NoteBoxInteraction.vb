'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class NoteBox
	Protected MouseDownX As Integer
	Protected MouseDownOffset As Integer
	Protected MouseX As Integer
	Protected IsMouseDown As Boolean = False
	Protected IsDragging As Boolean = False
	Protected Friend DragNoteNum As Integer
	
	Public Overridable Sub NBoxMouseDown(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseDown
		If Not EditEnabled Then Exit Sub
		MouseDownX = e.X
		IsMouseDown = True
		Dim i As Integer
		If LNoteNum < 0 Then Exit Sub
		For i = LNoteNum To RNoteNum
			If NoteList(i).StartPos < e.X And NoteList(i).EndPos > e.X Then
				If (Arrangement(i) And e.Y > 32) Or (Not Arrangement(i) And e.Y < 32) Then
					DragNoteNum = i
					IsDragging = True
					MouseDownOffset = MouseDownX - AbsoluteToRelative(InnerCVS.SegmentList(i).StartTime)
					SNoteBox.LoadSegment(InnerCVS.SegmentList(i))
					SNoteBox.Redraw()
					Redraw()
					Exit For
				End If
			End If
		Next
	End Sub
	Public Overridable Sub NBoxMouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseMove
		If Not EditEnabled Then Exit Sub
		MouseX = e.X
		If IsMouseDown Then
			'Drag
			If IsDragging Then
				InnerCVS.SegmentList(DragNoteNum).StartTime = RelativeToAbsolute(MouseX - MouseDownOffset)
				Redraw()
			End If
		End If
	End Sub
	Public Overridable Sub NBoxMouseUp(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseUp
		If Not EditEnabled Then Exit Sub
		IsMouseDown = False
		IsDragging = False
		MouseX = e.X
		SelectBar = RelativeToAbsolute(MouseX)
		Redraw()
	End Sub
End Class
