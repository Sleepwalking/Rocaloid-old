'    一个显示波形的线程安全PictureBox
'    A SecurePictureBox that shows a wave.
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

Public Class WaveBox
	Inherits SecurePictureBox
	Private InnerWave() As WaveBuffer
	Private WaveStyle() As WaveStyle
	Private InnerWaveQ As Integer
	Private InnerLineQ As Integer
	Private InnerLine() As PointList
	Private InnerBarQ As Integer
	Private InnerBar() As BarList
	Public InnerClickBar As Integer
	Public InnerClickBar_Show As Boolean
	Public InnerClickBar_Lock As Boolean
	Public SelectedArea As SelectedSet
	Public LeftPosition As Integer
	Public WindowSize As Integer
	Private Amplitude As Double
	Private Mousex As Integer
	Public Event WindowSizeChange()
	
	Public ShowZeroBar As Boolean
	
	Public Sub New()
		InnerWaveQ = -1
		Amplitude = 1
		ShowZeroBar = True
		InnerLineQ = -1
		InnerBarQ = -1
		InnerClickBar = 0
		InnerClickBar_Show = False
		InnerClickBar_Lock = False
		InitSelection()
		ReDim InnerBar(3)
		ReDim InnerLine(3)
		ReDim InnerWave(3)
		ReDim WaveStyle(3)
	End Sub
	
	Public Sub InitSelection()
		SelectedArea.SelectFrom = 0
		SelectedArea.SelectTo = 0
		SelectedArea.Style.Show = False
		SelectedArea.Style.Color = Color.DimGray
	End Sub
	
	Public Overloads Sub Add(ByRef Bar As BarList, ByVal _Color As Color)
		InnerBarQ += 1
		If InnerBarQ > InnerBar.GetUpperBound(0) Then
			Array.Resize(InnerBar, InnerBar.GetUpperBound(0) + 3)
		End If
		InnerBar(InnerBarQ) = Bar
		InnerBar(InnerBarQ).Style.Show = True
		InnerBar(InnerBarQ).Style.Color = _Color
	End Sub
	
	Public Overloads Sub Add(ByRef Line As PointList, ByVal _Color As Color)
		InnerLineQ += 1
		If InnerLineQ > InnerLine.GetUpperBound(0) Then
			Array.Resize(InnerLine, InnerLine.GetUpperBound(0) + 3)
		End If
		InnerLine(InnerLineQ) = Line
		InnerLine(InnerLineQ).Style.Show = True
		InnerLine(InnerLineQ).Style.Color = _Color
	End Sub
	
	Public Overloads Sub Add(ByRef Wave As WaveBuffer, ByVal _Color As Color)
		InnerWaveQ += 1
		If InnerWaveQ > InnerWave.GetUpperBound(0) Then
			Array.Resize(InnerWave, InnerWave.GetUpperBound(0) + 3)
			Array.Resize(WaveStyle, WaveStyle.GetUpperBound(0) + 3)
		End If
		InnerWave(InnerWaveQ) = Wave
		WaveStyle(InnerWaveQ).Show = True
		WaveStyle(InnerWaveQ).Color = _Color
	End Sub
	
	Public Overloads Sub Add(ByRef Wave As WaveBuffer)
		Add(Wave, Color.Red)
	End Sub
	
	Public Shadows Sub Show(ByVal Num As Integer)
		WaveStyle(Num).Show = True
	End Sub
	
	Public Shadows Sub Hide(ByVal Num As Integer)
		WaveStyle(Num).Show = False
	End Sub
	
	Public Shadows Sub Refresh()
		SyncLock Me
			Clear(Color.LightSlateGray)
			If GetAbsolutePos(Width) > MaximumPointer Then
				WindowSize = MaximumPointer - LeftPosition
			End If
			If SelectedArea.Style.Show Then
				DrawSelection(SelectedArea)
			End If
			If ShowZeroBar Then
				GraphicControl.DrawLine(New Pen(Color.DarkGray), 0, CInt(Height / 2), _
															 Width, CInt(Height / 2))
			End If
			Dim i As Integer
			For i = 0 To InnerBarQ
				If InnerBar(i).Style.Show Then DrawBar(InnerBar(i), InnerBar(i).Style.Color)
			Next
			For i = 0 To InnerWaveQ
				If WaveStyle(i).Show Then DrawWave(InnerWave(i), WaveStyle(i).Color)
			Next
			For i = 0 To InnerLineQ
				If InnerLine(i).Style.Show Then DrawLine(InnerLine(i), InnerLine(i).Style.Color)
			Next
			If InnerClickBar_Show Then DrawClickBar()
			Invalidate()
		End SyncLock
	End Sub
	
	#Region "Draw"
	Public Shadows Sub Resize(ByVal _x As Integer, ByVal _y As Integer)
		Width = _x
		Height = _y
		Init()
		Refresh()
	End Sub
	
	Private Sub DrawClickBar()
		If WindowSize <> 0 AndAlso GetRelativePos(InnerClickBar) > 0 Then
			GraphicControl.DrawLine(New Pen(Color.OrangeRed), GetRelativePos(InnerClickBar), 0, _
															  GetRelativePos(InnerClickBar), Height)
		End If
	End Sub
	
	Private Sub DrawBar(ByRef Bar As BarList, ByVal _Color As Color)
		Dim i As Integer
		Dim nextx As Integer
		Dim _pen As Pen = New Pen(_Color)
		For i = 0 To Bar.BarQ
			nextx = CInt(Bar.Bars(i))
			If GetRelativePos(nextx) > 0 Then
				GraphicControl.DrawLine(_pen, GetRelativePos(nextx), 0, _
											  GetRelativePos(nextx), Height)
			End If
		Next
	End Sub
	
	Private Sub DrawSelection(ByRef Selection As SelectedSet)
		If WindowSize = 0 Then Exit Sub
		Dim FromX As Integer =  GetRelativePos(Selection.SelectFrom)
		Dim ToX As Integer =  GetRelativePos(Selection.SelectTo)
		If FromX = -1 Then FromX = Width
		If FromX = -2 Then FromX = 0
		If ToX = -1 Then ToX = Width
		If ToX = -2 Then ToX = 0
		GraphicControl.FillRectangle(New SolidBrush(Selection.Style.Color), _
									 FromX, 0, ToX - FromX, Height)
		GraphicControl.DrawLine(New Pen(Color.OrangeRed), FromX, 0, _
														  FromX, Height)
		GraphicControl.DrawLine(New Pen(Color.OrangeRed), ToX, 0, _
														  ToX, Height)
	End Sub
	
	Private Sub DrawLine(ByRef Line As PointList, ByVal _Color As Color)
		Dim i As Integer
		Dim lastx As Integer = 0
		Dim lasty As Single = 0
		Dim nextx As Integer, nexty As Single
		Dim _pen As Pen = New Pen(_Color)
		For i = 0 To Line.PointQ - 1
			nextx = CInt(Line.Points(i).X)
			nexty = Line.Points(i).Y
			If GetRelativePos(nextx) > 0 OrElse GetRelativePos(lastx) > 0 Then
				GraphicControl.DrawLine(_pen, GetRelativePosWithoutBound(lastx), _
											  CInt((1 - lasty * Amplitude / 2) / 2 * Height), _
											  GetRelativePosWithoutBound(nextx), _
											  CInt((1 - nexty * Amplitude / 2) / 2 * Height))
				GraphicControl.DrawLine(_pen, GetRelativePosWithoutBound(lastx), _
											  CInt((1 + lasty * Amplitude / 2) / 2 * Height), _
											  GetRelativePosWithoutBound(nextx), _
											  CInt((1 + nexty * Amplitude / 2) / 2 * Height))
			End If
			lastx = nextx
			lasty = nexty
		Next
	End Sub
	
	Private Sub DrawWave(ByRef Wave As WaveBuffer, ByVal _Color As Color)
		Dim i As Integer
		Dim lastx As Integer = LeftPosition
		Dim nextx As Integer
		Dim max As Double, min As Double
		Dim up As Integer, down As Integer
		Dim _pen As Pen = New Pen(_Color)
		For i = 0 To Width
			nextx = GetAbsolutePos(i)
			If nextx > Wave.Size Or nextx > Wave.Pointer + Wave.Offset Then
				Exit Sub
			End If
			
			If lastx - Wave.Offset >= 0 Then
				max = Wave.GetMax(lastx - Wave.Offset, nextx - Wave.Offset)
				min = Wave.GetMin(lastx - Wave.Offset, nextx - Wave.Offset)
			End If			
			
			up = CInt((1 - max * Amplitude) / 2 * Height)
			down = CInt((1 - min * Amplitude) / 2 * Height)
			
			If up = down Then
				up += 1
			End If
			
			GraphicControl.DrawLine(_pen, i, up, i, down)
			
			lastx = nextx
		Next
	End Sub
	#End Region
	
	#Region "Control"
	Public Sub SetAmplitude(ByVal _Amplitdue As Double)
		Amplitude = _Amplitdue
		Refresh()
	End Sub
	
	Public Sub SetWindow(ByVal AbsoluteCenterPos As Integer, ByVal Factor As Double)
		Dim AdjustedLBound, AdjustedRBound, AdjustedCenter As Integer
		Dim maxp As Integer = MaximumPointer
		AdjustedLBound=CInt(AbsoluteCenterPos - (AbsoluteCenterPos - LeftBound) * Factor)
		AdjustedRBound=CInt(AbsoluteCenterPos + (RightBound - AbsoluteCenterPos) * Factor)
		If AdjustedLBound < 0 Then
			AdjustedLBound = 0
		End If
		If AdjustedRBound > maxp Then
			AdjustedRBound = maxp
		End If
		AdjustedCenter = CInt((AdjustedLBound - AdjustedRBound) / 2)
		LeftPosition = AdjustedLBound
		WindowSize = AdjustedRBound - AdjustedLBound
		RaiseEvent WindowSizeChange
	End Sub
	
	Private Shadows Sub OnMouseWheel(ByVal sender As Object, e As MouseEventArgs) Handles Me.MouseWheel
		Dim MousePos As Integer
		MousePos=e.X
		If e.Delta>0 Then
			If WindowSize>10 Then
				SetWindow(GetAbsolutePos(MousePos), 0.6667)
			End If
		Else
			SetWindow(GetAbsolutePos(MousePos), 1.5)	
		End If
		Refresh()
	End Sub
	
	Private Shadows Sub OnClick(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseClick
		Me.Focus()
		If e.Button = MouseButtons.Left Then
			If Not InnerClickBar_Lock Then InnerClickBar = GetAbsolutePos(e.X)
			If GetAbsolutePos(e.X) < SelectedArea.SelectTo Then
				SelectedArea.SelectFrom = GetAbsolutePos(e.X)
			Else
				SelectedArea.SelectFrom = SelectedArea.SelectTo - 1
			End If
		End If
		If e.Button = MouseButtons.Right Then
			If GetAbsolutePos(e.X) > SelectedArea.SelectFrom Then
				SelectedArea.SelectTo = GetAbsolutePos(e.X)
			Else
				SelectedArea.SelectTo = SelectedArea.SelectFrom + 1
			End If
		End If
		Refresh()
	End Sub
	
	
	Private Shadows Sub OnMouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseMove
		Mousex = e.X
	End Sub
	
	Public Sub SyncToBar(ByRef Bar As HScrollBar)
		If InnerWaveQ = -1 Then
			Exit Sub
		End If
		Dim maxp As Integer = MaximumPointer
		LeftPosition = CInt(Bar.Value / Bar.Maximum * maxp)
		If LeftPosition < 0 Then
			LeftPosition = 0
		End If
		If LeftPosition > maxp Then
			LeftPosition = maxp
		End If
		Refresh
	End Sub
	
	Public ReadOnly Property MaximumPointer() As Integer
		Get
			Dim i As Integer
			Dim max As Integer = 0
			For i = 0 To InnerWaveQ
				If InnerWave(i).Pointer > max And WaveStyle(i).Show Then max = InnerWave(i).Pointer
			Next
			Return max
		End Get
	End Property
	
	Public ReadOnly Property LeftBound() As Integer
		Get
			Return LeftPosition
		End Get
	End Property
	
	Public ReadOnly Property RightBound() As Integer
		Get
			Return LeftPosition + WindowSize
		End Get
	End Property
	
	Public ReadOnly Property CenterPosition() As Integer
		Get
			Return CInt(LeftPosition + WindowSize / 2)
		End Get
	End Property
	
	Public Function GetAbsolutePos(ByVal RelativePos As Integer) As Integer
		Return CInt(LeftPosition + RelativePos / Width * WindowSize)
	End Function
	
	Public Function GetRelativePos(ByVal AbsolutePos As Integer) As Integer
		If AbsolutePos > RightBound Then
			Return -1
		End If
		If AbsolutePos < LeftBound Then
			Return -2
		End If
		Return CInt((AbsolutePos - LeftPosition) / WindowSize * Width)
	End Function
	
	Public Function GetRelativePosWithoutBound(ByVal AbsolutePos As Integer) As Integer
		Return CInt((AbsolutePos - LeftPosition) / WindowSize * Width)
	End Function
	#End Region
End Class
