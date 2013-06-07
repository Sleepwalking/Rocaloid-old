'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class MainForm
	Public Sub New()
		Me.InitializeComponent()
		AddHandler MainNoteBox.Selected, AddressOf MainNoteBoxSelected
	End Sub
	
	Public Shared Sub UpdateScrollBar(ByVal Position As Integer)
		MainForm.NBoxScrollBar.Value = Position
	End Sub
	
	Private Sub ShowEffects(ByRef Effect As CVSCommon.EffectCollection)
		If Effect.PElopeEnabled And Effect.PresetedEnvelope = CVSCommon.Envelopes.ADSR Then
			ADSR_Enabled.Checked = True
		End If
		With Effect.ADSR
			ADSR_AmplitudeBar.Value = CInt(.Amplitude * 50)
			ADSR_Amplitude.Text = "Amplitude " & .Amplitude
			ADSR_ReleaseBar.Value = CInt(.Release * 100)
			ADSR_Release.Text = "Release " & .Release
			ADSR_DeclineBar.Value = CInt(.Decline * 100)
			ADSR_Decline.Text = "Decline " & .Decline
			ADSR_AttackBar.Value = CInt(.Attack * 100)
			ADSR_Attack.Text = "Attack " & .Attack
		End With
		With Effect
			Shrink_CutBar.Value = CInt(.ForwardCut * 400)
			Shrink_Cut.Text = "Cut " & CSng(CInt(.ForwardCut * 400) / 400)
			Shrink_ShrinkBar.Value = CInt(.Shrink * 400)
			Shrink_Shrink.Text = "Shrink " & CSng(CInt(.Shrink * 400) / 400)
		End With
	End Sub
	
	Private Sub MainNoteBoxSelected(ByVal SegmentIndex As Integer)
		ShowEffects(Operation.MainCVS.SegmentList(SegmentIndex).Effects)
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
		RadioButton3.Left = radioButton1.Left - 113
		
		ADSR_Box.Width = Me.Width - 8
		ADSR_AmplitudeBar.Left = ADSR_Box.Width - 112
		ADSR_Amplitude.Left = ADSR_AmplitudeBar.Left + 12
		ADSR_ReleaseBar.Left = ADSR_Box.Width - 247
		ADSR_Release.Left = ADSR_ReleaseBar.Left + 12
		ADSR_DeclineBar.Left = ADSR_Box.Width - 389
		ADSR_Decline.Left = ADSR_DeclineBar.Left + 12
		ADSR_AttackBar.Left = ADSR_Box.Width - 533
		ADSR_Attack.Left = ADSR_AttackBar.Left + 12
		
		Shrink_Box.Width = Me.Width - 8
	End Sub
	
	Sub VerticalScaleScroll(sender As Object, e As EventArgs)
		MainNoteBox.Scale(HorizontalScale.Value / 2)
		MainNoteBox.Redraw()
	End Sub
	
	Sub SynthesisAndPlayClick(sender As Object, e As EventArgs)
		Operation.StartSynthesis(MainNoteBox.SelectBar)
	End Sub
	
	Sub ToolStripButton1Click(sender As Object, e As EventArgs)
		MainNoteBox.SelectBar = Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).StartTime + 0.01
		Operation.StartSegmentSynthesis(MainNoteBox.SelectBar)
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
			If Not Operation.SynthesizingSegment AndAlso CurrentNoteNum <> MainNoteBox.DragNoteNum Then
				MainNoteBox.DragNoteNum = CurrentNoteNum
				MainNoteBox.SNoteBox.LoadSegment(Operation.MainCVS.SegmentList(CurrentNoteNum))
				ShowEffects(Operation.MainCVS.SegmentList(CurrentNoteNum).Effects)
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
		MainSBox.Mode = SBoxMode.Shrink
		MainSBox.Redraw()
	End Sub
	
	Sub RadioButton2CheckedChanged(sender As Object, e As EventArgs)
		MainSBox.Mode = SBoxMode.ADSR
		MainSBox.Redraw()
	End Sub
	
	Sub RadioButton3CheckedChanged(sender As Object, e As EventArgs)
		MainSBox.Mode = SBoxMode.Non
		MainSBox.Redraw()
	End Sub
	
	Sub MainFormFormClosing(sender As Object, e As FormClosingEventArgs)
		Operation.StopSynthesis()
	End Sub
	
	Sub ADSR_AttackBarScroll(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.ADSR.Attack = ADSR_AttackBar.Value / 100
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
	End Sub
	
	Sub ADSR_DeclineBarScroll(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.ADSR.Decline = ADSR_DeclineBar.Value / 100
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
	End Sub
	
	Sub ADSR_ReleaseBarScroll(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.ADSR.Release = ADSR_ReleaseBar.Value / 100
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
	End Sub
	
	Sub ADSR_AmplitudeBarScroll(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.ADSR.Amplitude = ADSR_AmplitudeBar.Value / 50
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
	End Sub
	
	Sub ADSR_EnabledCheckedChanged(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.PElopeEnabled = ADSR_Enabled.Checked
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
	End Sub
	
	Sub Shrink_CutBarScroll(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.ForwardCut = Shrink_CutBar.Value / 400
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
		MainNoteBox.Redraw()
	End Sub
	
	Sub Shrink_ShrinkBarScroll(sender As Object, e As EventArgs)
		If Not MainNoteBox.EditEnabled Then Exit Sub
		Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects.Shrink = Shrink_ShrinkBar.Value / 400
		MainSBox.ReloadSegment(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
		ShowEffects(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).Effects)
		MainNoteBox.Redraw()
	End Sub
	
	Sub Menu_SynthesisClick(sender As Object, e As EventArgs)
		Dim FileAddr As String
		Dialog_SynthesisWav.ShowDialog()
		FileAddr = Dialog_SynthesisWav.FileName
		If FileAddr = "" Then
			Exit Sub
		End If
		Operation.CVESynthesis(FileAddr)			
	End Sub
	
	Sub MainFormKeyDown(sender As Object, e As KeyEventArgs)
		Select Case e.KeyCode
			Case Keys.ShiftKey
				ToolStripButton1Click(New Object, New EventArgs)
			Case Keys.Space
				If Operation.SoundIsPlaying Then
					Operation.StopSynthesis()
				Else
					SynthesisAndPlayClick(New Object, New EventArgs)
				End If
			Case Keys.D
				MainNoteBox.Focus()
				If MainNoteBox.DragNoteNum < Operation.MainCVS.SegmentListQ Then MainNoteBox.DragNoteNum += 1
				If MainNoteBox.RBound < CVSOperation.GetEndTime(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum)) Then
					MainNoteBox.LBound += CVSOperation.GetDuration(Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum))
				End If
				MainNoteBox.Scale(MainNoteBox.Duration)
				MainNoteBox.Redraw()
			Case Keys.A
				MainNoteBox.Focus()
				If MainNoteBox.DragNoteNum > 0 Then MainNoteBox.DragNoteNum -= 1
				If MainNoteBox.LBound > Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).StartTime Then
					MainNoteBox.LBound = Operation.MainCVS.SegmentList(MainNoteBox.DragNoteNum).StartTime
				End If
				MainNoteBox.Scale(MainNoteBox.Duration)
				MainNoteBox.Redraw()
		End Select
	End Sub
End Class
