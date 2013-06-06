'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class MainForm
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Public Shared Sub UpdateScrollBar(ByVal Position As Integer)
		MainForm.NBoxScrollBar.Value = Position
	End Sub
	
	Sub MainFormLoad(sender As Object, e As EventArgs)
		Operation.LoadCVS("default.cvs")
		MainNoteBox.ScrollBar = NBoxScrollBar
		MainNoteBox.SNoteBox = MainSBox
		MainNoteBox.LoadCVS(Operation.MainCVS)
		
		MainNoteBox.Init()
		MainNoteBox.Resize(Width - 8)
		
		MainSBox.ScrollBar = SBoxScrollBar
		MainSBox.Init()
		
		Operation.SynthesizerInit()
		Operation.SoundInit()
	End Sub
	
	Sub MainFormResize(sender As Object, e As EventArgs)
		MainNoteBox.Resize(Width - 8)
		MainSBox.Resize(Width - 8)
		HorizontalScale.Left = Width - 141
		RadioButton2.Left = HorizontalScale.Left - 83
		RadioButton1.Left = radioButton2.Left - 93
		ADSR_Box.Width = Me.Width - 8
	End Sub
	
	Sub VerticalScaleScroll(sender As Object, e As EventArgs)
		MainNoteBox.Scale(HorizontalScale.Value / 2)
		MainNoteBox.Redraw()
	End Sub
	
	
	Sub SynthesisAndPlayClick(sender As Object, e As EventArgs)
		Operation.StartSynthesis(MainNoteBox.SelectBar)
	End Sub
	
	Sub SynthesisStopClick(sender As Object, e As EventArgs)
		Operation.StopSynthesis()
	End Sub
	
	Sub Timer1Tick(sender As Object, e As EventArgs)
		Dim CurrentNoteNum As Integer
		If Operation.SoundIsPlaying Then
			'This seems to be a bug of ScrollBar, that you need to change the value twice, the first time should be a lower level, and then it will be updated.
			NBoxScrollBar.Value = 0
			NBoxScrollBar.Value = CInt(Operation.MainNoteBox.LBound * 100)
			CurrentNoteNum = CVSOperation.GetSegment(Operation.MainCVS, MainNoteBox.SelectBar)
			If CurrentNoteNum <> MainNoteBox.DragNoteNum Then
				MainNoteBox.DragNoteNum = CurrentNoteNum
				MainNoteBox.SNoteBox.LoadSegment(Operation.MainCVS.SegmentList(CurrentNoteNum))
				MainNoteBox.SNoteBox.Redraw()
			End If
		End If
	End Sub
	
	Sub ConsoleToolStripMenuItemClick(sender As Object, e As EventArgs)
		My.Forms.Console.Show()
	End Sub
	
	Sub Menu_OpenClick(sender As Object, e As EventArgs)
		Dim FileAddr As String
		Dialog_OpenFile.ShowDialog()
		FileAddr = Dialog_OpenFile.FileName
		If FileAddr = "" Then Exit Sub
		If System.IO.File.Exists(FileAddr) Then
			Operation.Editor_CVSFile = FileAddr
			Operation.LoadCVS(FileAddr)
			MainNoteBox.LoadCVS(Operation.MainCVS)
			MainSBox.LoadSegment(Operation.MainCVS.SegmentList(0))
			MainNoteBox.Redraw()
		Else
			MsgBox("Invalid file path!", , "CVS Editor")
		End If
	End Sub
	
	Sub Menu_SaveClick(sender As Object, e As EventArgs)
		Dim DoSave As Boolean = CBool(MsgBox("Are you sure to overwrite?", MsgBoxStyle.YesNo, "CVS Editor"))
		If DoSave Then
			Operation.SaveCVS(Operation.Editor_CVSFile)
		End If
	End Sub
	
	Sub Menu_SaveAsClick(sender As Object, e As EventArgs)
		Dim FileAddr As String
		Dialog_SaveFile.ShowDialog()
		FileAddr = Dialog_SaveFile.FileName
		If FileAddr = "" Then
			Exit Sub
		End If
		Operation.Editor_CVSFile = FileAddr
		Operation.SaveCVS(FileAddr)		
	End Sub
	
	Sub SaveCVSClick(sender As Object, e As EventArgs)
		If Operation.Editor_CVSFile = "" Then
			Dim FileAddr As String
			Dialog_SaveFile.ShowDialog()
			FileAddr = Dialog_SaveFile.FileName
			If FileAddr = "" Then
				Exit Sub
			End If
			Operation.Editor_CVSFile = FileAddr
		End If
		
		Dim DoSave As Boolean = True
		If System.IO.File.Exists(Operation.Editor_CVSFile) Then DoSave = CBool(MsgBox("Are you sure to overwrite?", MsgBoxStyle.YesNo, "CVS Editor"))
		If DoSave Then
			Operation.SaveCVS(Operation.Editor_CVSFile)
		End If
	End Sub
	
	Sub RadioButton1CheckedChanged(sender As Object, e As EventArgs)
		MainSBox.Mode = SBoxMode.Non
		MainSBox.Redraw()
	End Sub
	
	Sub RadioButton2CheckedChanged(sender As Object, e As EventArgs)
		MainSBox.Mode = SBoxMode.ADSR
		MainSBox.Redraw()
	End Sub
	
	Sub MainFormFormClosing(sender As Object, e As FormClosingEventArgs)
		Operation.StopSynthesis()
	End Sub
	
End Class
