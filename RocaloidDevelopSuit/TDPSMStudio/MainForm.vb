'    用户界面
'    User Interface
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

Imports System.Threading
Public Partial Class MainForm
	
	Public Sub New()
		Me.InitializeComponent()
		MyBase.KeyPreview = True
		AddHandler Me.Resize, AddressOf MainFormSizeChange
	End Sub
	
	Protected Overrides Sub OnKeyDown(ByVal e As KeyEventArgs)
		If e.Control Then
			Select Case e.KeyCode
				Case Keys.S
					Button_Open_Click(New Object(), New EventArgs())
				Case Keys.D
					Button_Next_Click(New Object(), New EventArgs())
				Case Keys.A
					Button_Prev_Click(New Object(), New EventArgs())
				Case Keys.F
					If Setting_Mode = EditMode.WavAnalysis Or _
					   Setting_Mode = EditMode.CVQC Then
						Button_AddFrame_Click(New Object(), New EventArgs())
					End If
				Case Keys.C
					If Setting_Mode = EditMode.CVQC Then
						LoadedCVDB.Header.StartPosition = MainBox.InnerClickBar
						LoadedCVDB.Save(Directory & CurrentSymbol & "_" & CurrentPitch & ".cbv")
						Status.Text = "Saved."
					End If
					If Setting_Mode = EditMode.WavEditor Then
						Operation.SaveWave(Directory & CurrentSymbol & "_" & CurrentPitch & ".wav")
						Status.Text = "Saved."
					End If
			End Select
		End If
	End Sub
	
	Public Sub LoadWave(ByVal FileName As String)
		If Not System.IO.File.Exists(Directory & FileName) Then
			Status.Text = "File doesn't exist."
			Exit Sub
		End If
		If LoadThread.ThreadState <> ThreadState.Running Then
			LoadThread = New Thread(AddressOf Operation.LoadWave)
			LoadThread.Start(FileName)
			Status.Text = "Loading..."
		End If
	End Sub
	
	Public Sub LoadCVDB(ByVal FileName As String)
		If Not System.IO.File.Exists(Directory & FileName) Then
			Status.Text = "File doesn't exist."
			Exit Sub
		End If
		If LoadThread.ThreadState <> ThreadState.Running Then
			LoadThread = New Thread(AddressOf Operation.LoadCVDB)
			LoadThread.Start(FileName)
			Status.Text = "Loading..."
		End If
	End Sub
	
	Public Sub TryLoad()
		CurrentPitch = Textbox_Pitch.Text
		CurrentSymbol = Textbox_Symbol.Text
		If CurrentSymbol <> "" And CurrentPitch <> "" Then
			If Setting_Mode <> EditMode.CVQC Then
				LoadWave(CurrentSymbol & "_" & CurrentPitch & ".wav")
			Else
				LoadCVDB(CurrentSymbol & "_" & CurrentPitch & ".cbv")
			End If
		End If
	End Sub
	
	Public Sub MainFormLoad(sender As Object, e As EventArgs)		
		StatusBox = Status
		PBar = ProgressBar_Completeness
		ProgressBar_Completeness.CheckForIllegalCrossThreadCalls = False
		
		SoundFormat = New Microsoft.DirectX.DirectSound.WaveFormat()
		SoundFormat.AverageBytesPerSecond = 192000
		SoundFormat.BitsPerSample = 16
		SoundFormat.BlockAlign = 2
		SoundFormat.Channels = 1
		SoundFormat.FormatTag = Microsoft.DirectX.DirectSound.WaveFormatTag.Pcm
		SoundFormat.SamplesPerSecond = 96000
		
		SoundDesc = New Microsoft.DirectX.DirectSound.BufferDescription(SoundFormat)
		SoundDesc.ControlFrequency = True
		SoundDesc.ControlPan = True
		SoundDesc.ControlVolume = True
		SoundDesc.GlobalFocus = True
		
		SoundDevice = New Microsoft.DirectX.DirectSound.Device()
		SoundDevice.SetCooperativeLevel(Me, Microsoft.DirectX.DirectSound.CooperativeLevel.Normal)
		
		SoundTimer = New System.Timers.Timer()
		SoundTimer.Interval = 50
		
		MainWave = New WaveBuffer(10.0)
		MainWave_Smooth = New WaveBuffer(10.0)
		CopyWave = New WaveBuffer(10.0)
		MainEnvelope = New PointList()
		MainEnvelope.PointQ = -1
		MainRecognization = New PointList()
		MainRecognization.PointQ = -1
		MainPeriod = New PointList()
		MainRecognization.PointQ = -1
		MainBar = New BarList()
		MainBar.BarQ = -1
		ReDim MainBar.Bars(4000)
		ReDim MainPeriod.Points(4000)
		
		MainBox = New WaveBox()
		MainContainer.Panel1.Controls.Add(MainBox)
		MainBox.Location = New System.Drawing.Point(0, 0)
		MainBox.Size = New System.Drawing.Size(MainContainer.Panel1.Width, _
											   MainContainer.Panel1.Height)
		MainBox.Init()
		MainBox.Add(MainWave, Color.LightBlue)
		MainBox.Add(MainWave_Smooth, Color.LightGreen)
		MainBox.Add(CopyWave, Color.LightGreen)
		MainBox.Add(MainEnvelope, Color.Red)
		MainBox.Add(MainRecognization, Color.Black)
		MainBox.Add(MainBar, Color.LightPink)
		MainBox.Add(MainPeriod, Color.White)
		MainBox.Hide(2)
		MainPeriod.Style.Show = False
		MainBox.WindowSize = MainBox.MaximumPointer
		MainBox.LeftPosition = 0
		MainBox.Refresh()
		
		AddHandler SoundTimer.Elapsed, AddressOf OnSoundTimer
		AddHandler MainContainer.Panel1.Resize, AddressOf Panel1SizeChange
		AddHandler MainContainer.Panel1.MouseWheel, AddressOf MainBoxFocus
		AddHandler MainContainer.MouseWheel, AddressOf MainBoxFocus
		AddHandler MainBox.MouseDown, AddressOf MainBox_MouseMidButton
	End Sub
	
	Sub Panel1SizeChange(sender As Object, e As EventArgs)
		MainBox.Resize(MainContainer.Panel1.Width, MainContainer.Panel1.Height)
		ProgressBar_Completeness.Width = MainContainer.Panel1.Width - 89
		groupBox1.Width = MainContainer.Panel1.Width - 89
	End Sub
	
	Sub MainFormSizeChange(sender As Object, e As EventArgs)
		MainContainer.Width = Me.Width - 32
		MainContainer.Height = Me.Height - 98
	End Sub
	
	Sub MainBoxFocus(sender As Object, e As EventArgs)
		MainBox.Focus()
	End Sub
	
	Sub AmplitudeControllerScroll(sender As Object, e As EventArgs)
		MainBox.SetAmplitude(AmplitudeController.Value / 10)		
	End Sub
	
	Sub Button_Open_Click(sender As Object, e As EventArgs)
		CurrentPitch = Textbox_Pitch.Text
		CurrentSymbol = Textbox_Symbol.Text
		If CurrentSymbol <> "" And CurrentPitch <> "" Then
			If Setting_Mode <> EditMode.CVQC Then
				LoadWave(CurrentSymbol & "_" & CurrentPitch & ".wav")
			Else
				LoadCVDB(CurrentSymbol & "_" & CurrentPitch & ".cbv")
			End If
		Else
			MsgBox("Symbol or pitch cannot be empty!")
		End If
	End Sub
	
	Sub Button_Next_Click(sender As Object, e As EventArgs)
		'Next
		Try
			Dim PitchNum As Integer
			PitchNum = GetNumByPitch(CurrentPitch)
			If PitchNum = Pitch_C5 Then
				CurrentPitch = PitchList(Pitch_C2)
			Else
				CurrentPitch = PitchList(PitchNum + 1)
			End If
			If Setting_Mode <> EditMode.CVQC Then
				LoadWave(CurrentSymbol & "_" & CurrentPitch & ".wav")
			Else
				LoadCVDB(CurrentSymbol & "_" & CurrentPitch & ".cbv")
			End If
			Textbox_Pitch.text = CurrentPitch
		Catch
			MsgBox("Wrong pitch or symbol!")
		End Try
	End Sub
	
	Sub Button_Prev_Click(sender As Object, e As EventArgs)
		'Prev
		Try
			Dim PitchNum As Integer
			PitchNum = GetNumByPitch(CurrentPitch)
			If PitchNum = Pitch_C2 Then
				CurrentPitch = PitchList(Pitch_C5)
			Else
				CurrentPitch = PitchList(PitchNum - 1)
			End If
			If Setting_Mode <> EditMode.CVQC Then
				LoadWave(CurrentSymbol & "_" & CurrentPitch & ".wav")
			Else
				LoadCVDB(CurrentSymbol & "_" & CurrentPitch & ".cbv")
			End If
			Textbox_Pitch.text = CurrentPitch
		Catch
			MsgBox("Wrong pitch or symbol!")
		End Try
	End Sub
	
	Sub Button_AddFrame_Click(sender As Object, e As EventArgs)
		Dim _CVDB As CVDB
		Setting_Multithread = False
		UpdateSettings()
		_CVDB = AddFrame(MainWave, MainWave_Smooth, CurrentBasePeriod, MainWave_StartPosition)
		_CVDB.Save(Directory & CurrentSymbol & "_" & CurrentPitch & ".cbv")
	End Sub
	
	Sub Button_AnalysisAll_Click(sender As Object, e As EventArgs)
		Setting_Multithread = True
		UpdateSettings()
		Operation.AnalysisAll()
	End Sub
	
	Sub Button_AdjustAll_Click(sender As Object, e As EventArgs)
		BatchAdjust.Show()
	End Sub
	
	#Region "ModeSwitch"
	Sub ModeSwitch_UncheckAll()
		cbvQualityControlToolStripMenuItem.Checked = False
		waveEditorToolStripMenuItem.Checked = False
		wavCbvToolStripMenuItem.Checked = False
	End Sub
	
	Sub ModeSwitch_WavEditor(sender As Object, e As EventArgs)
		Setting_Mode = EditMode.WavEditor
		Button_AnalyzeAll.Enabled = False
		Button_Analyze.Enabled = False
		Button_AdjustToAll.Enabled = True
		MainPeriod.Style.Show = False
		MainPeriod.PointQ = -1
		MainBox.InnerClickBar_Show = True
		MainBox.InnerClickBar_Lock = True
		MainBar.Style.Show = False
		MainBox.InitSelection()
		MainBox.SelectedArea.Style.Show = True
		MainBox.Hide(1)
		State_MixEnabled = False
		CopyWave.Pointer = 0
		MainBox.Refresh()
		TryLoad()
		EditorToolStrip.Enabled = True
		ModeSwitch_UncheckAll()
		waveEditorToolStripMenuItem.Checked = True
		WBox_SelectAll.Enabled = True
		WBox_SelectView.Enabled = True
		Me.Text = "TDPSMStudio 1.05 (Wave Editor Mode)"
	End Sub
	
	Sub ModeSwitch_WavAnalysis(sender As Object, e As EventArgs)
		Setting_Mode = EditMode.WavAnalysis
		Button_AnalyzeAll.Enabled = True
		Button_Analyze.Enabled = True
		Button_AdjustToAll.Enabled = False
		MainPeriod.Style.Show = False
		MainPeriod.PointQ = -1
		MainBox.InnerClickBar_Show = True
		MainBox.InnerClickBar_Lock = False
		MainBar.Style.Show = True
		MainBox.SelectedArea.Style.Show = False
		MainBox.Show(1)
		State_MixEnabled = False
		CopyWave.Pointer = 0
		MainBox.Refresh()
		TryLoad()
		EditorToolStrip.Enabled = False
		ModeSwitch_UncheckAll()
		wavCbvToolStripMenuItem.Checked = True
		WBox_SelectAll.Enabled = False
		WBox_SelectView.Enabled = False
		Me.Text = "TDPSMStudio 1.05 (Wave Analyzer Mode)"
	End Sub
	
	Sub ModeSwitch_CVQC(sender As Object, e As EventArgs)
		Setting_Mode = EditMode.CVQC
		Button_AnalyzeAll.Enabled = False
		Button_Analyze.Enabled = True
		Button_AdjustToAll.Enabled = False
		MainPeriod.Style.Show = True
		MainPeriod.PointQ = -1
		MainBox.InnerClickBar_Show = True
		MainBox.InnerClickBar_Lock = False
		MainBar.Style.Show = True
		MainBox.SelectedArea.Style.Show = False
		MainBox.Show(1)
		State_MixEnabled = False
		CopyWave.Pointer = 0
		MainBox.Refresh()
		TryLoad()
		EditorToolStrip.Enabled = False
		ModeSwitch_UncheckAll()
		cbvQualityControlToolStripMenuItem.Checked = True
		WBox_SelectAll.Enabled = False
		WBox_SelectView.Enabled = False
		Me.Text = "TDPSMStudio 1.05 (CVQC Mode)"
	End Sub
	#End Region
	
	Sub Button_AboutClick(sender As Object, e As EventArgs)
		About.Show()
	End Sub
	
	Sub PreprocessToolStripMenuItemClick(sender As Object, e As EventArgs)
		PreProcess.Show()
	End Sub
	
	Sub AnalyzerToolStripMenuItemClick(sender As Object, e As EventArgs)
		Analyzer.Show()
	End Sub
	
	Sub Button_ViewAllClick(sender As Object, e As EventArgs)
		State_Viewing = True
	End Sub
	
	Sub Button_StopViewClick(sender As Object, e As EventArgs)
		State_Viewing = False
	End Sub
	
	Sub Timer1Tick(sender As Object, e As EventArgs)
		If State_Viewing Then
			Button_Next_Click(New Object(), New EventArgs())
		End If
	End Sub
	
	
	Sub Tool_PlayClick(sender As Object, e As EventArgs)
		PlaySound()
	End Sub
	
	Sub Tool_StopClick(sender As Object, e As EventArgs)
		If Setting_Mode <> EditMode.WavEditor Then Exit Sub
		Try
			StopSound()
		Catch
		End Try
		MainBox.Refresh()
	End Sub
	
	Sub Tool_CopyClick(sender As Object, e As EventArgs)
		CopySound(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		MainBox.Hide(2)
		State_MixEnabled = False
		MainBox.Refresh()
	End Sub
	
	Sub Tool_CutClick(sender As Object, e As EventArgs)
		CutSound(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()
	End Sub
	
	Sub Tool_MixClick(sender As Object, e As EventArgs)
		MixSound(MainBox.SelectedArea.SelectFrom)
		State_MixEnabled = True
		MainBox.Refresh()
	End Sub
	
	Sub Tool_ChangeVolumeClick(sender As Object, e As EventArgs)
		Operation.ChangeVolume(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()
	End Sub
	
	Sub Tool_SmoothenClick(sender As Object, e As EventArgs)
		Operation.Smoothen(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()
	End Sub
	
	Sub Tool_NormalizeClick(sender As Object, e As EventArgs)
		Operation.Normalize(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()
	End Sub
	
	Sub Tool_SilenceClick(sender As Object, e As EventArgs)
		Operation.Silence(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()
	End Sub
	
	Sub Tool_ShrinkClick(sender As Object, e As EventArgs)
		Operation.Shrink(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()		
	End Sub
		
	Sub Tool_AdjustClick(sender As Object, e As EventArgs)
		Operation.Adjust(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
		UpdateLists()
		MainBox.Refresh()
	End Sub
	
	Sub Tool_WeakenMouseUp(sender As Object, e As MouseEventArgs)
		If e.Button = MouseButtons.Left Then
			Operation.Weaken(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
			UpdateLists()
			MainBox.Refresh()
		Else
			Strip_WeakenSettings.Show(MousePosition)
		End If
	End Sub
	
	#Region "Strip_WeakenSettings"
	Sub Strip_WeakenSettings_UncheckAll()
		Weaken_00.Checked = False
		Weaken_01.Checked = False
		Weaken_02.Checked = False
		Weaken_03.Checked = False
		Weaken_04.Checked = False
		Weaken_05.Checked = False
		Weaken_06.Checked = False
		Weaken_07.Checked = False
		Weaken_08.Checked = False
		Weaken_09.Checked = False
	End Sub
	Sub Weaken_09Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_09.Checked = True
		Setting_Editor_WeakenStrength = 0.9
	End Sub
	Sub Weaken_08Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_08.Checked = True
		Setting_Editor_WeakenStrength = 0.8
	End Sub
	Sub Weaken_07Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_07.Checked = True
		Setting_Editor_WeakenStrength = 0.7
	End Sub
	Sub Weaken_06Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_06.Checked = True
		Setting_Editor_WeakenStrength = 0.6
	End Sub
	Sub Weaken_05Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_05.Checked = True
		Setting_Editor_WeakenStrength = 0.5
	End Sub
	Sub Weaken_04Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_04.Checked = True
		Setting_Editor_WeakenStrength = 0.4
	End Sub
	Sub Weaken_03Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_03.Checked = True
		Setting_Editor_WeakenStrength = 0.3
	End Sub
	Sub Weaken_02Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_02.Checked = True
		Setting_Editor_WeakenStrength = 0.2
	End Sub
	Sub Weaken_01Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_01.Checked = True
		Setting_Editor_WeakenStrength = 0.1
	End Sub
	Sub Weaken_00Click(sender As Object, e As EventArgs)
		Strip_WeakenSettings_UncheckAll()
		Weaken_00.Checked = True
		Setting_Editor_WeakenStrength = 0
	End Sub
	#End Region
	
	Sub Tool_FadeInMouseUp(sender As Object, e As MouseEventArgs)
		If e.Button = MouseButtons.Left Then
			Operation.FadeIn(MainBox.SelectedArea.SelectFrom, MainBox.SelectedArea.SelectTo)
			UpdateLists()
			MainBox.Refresh()
		Else
			Strip_FadeLowSettings.Show(MousePosition)
		End If
	End Sub
	
	#Region "Strip_FadeLowSettings"
	Sub Strip_FadeLow_UncheckAll()
		FadeLow_00.Checked = False
		FadeLow_01.Checked = False
		FadeLow_02.Checked = False
		FadeLow_03.Checked = False
		FadeLow_04.Checked = False
		FadeLow_05.Checked = False
	End Sub
	Sub FadeLow_05Click(sender As Object, e As EventArgs)
		Strip_FadeLow_UncheckAll()
		FadeLow_05.Checked = True
		Setting_Editor_FadeLowerEnd = 0.5
	End Sub
	Sub FadeLow_04Click(sender As Object, e As EventArgs)
		Strip_FadeLow_UncheckAll()
		FadeLow_04.Checked = True
		Setting_Editor_FadeLowerEnd = 0.4
	End Sub
	Sub FadeLow_03Click(sender As Object, e As EventArgs)
		Strip_FadeLow_UncheckAll()
		FadeLow_03.Checked = True
		Setting_Editor_FadeLowerEnd = 0.3
	End Sub
	Sub FadeLow_02Click(sender As Object, e As EventArgs)
		Strip_FadeLow_UncheckAll()
		FadeLow_02.Checked = True
		Setting_Editor_FadeLowerEnd = 0.2
	End Sub
	Sub FadeLow_01Click(sender As Object, e As EventArgs)
		Strip_FadeLow_UncheckAll()
		FadeLow_01.Checked = True
		Setting_Editor_FadeLowerEnd = 0.1
	End Sub
	Sub FadeLow_00Click(sender As Object, e As EventArgs)
		Strip_FadeLow_UncheckAll()
		FadeLow_00.Checked = True
		Setting_Editor_FadeLowerEnd = 0
	End Sub
	#End Region
	
	Sub MainBox_MouseMidButton(sender As Object, e As MouseEventArgs)
		If e.Button = MouseButtons.Middle Then
			Strip_WaveBoxClick.Show(MousePosition)
		End If
	End Sub
	
	Sub WBox_SelectAllClick(sender As Object, e As EventArgs)
		MainBox.SelectedArea.SelectFrom = 0
		MainBox.SelectedArea.SelectTo = MainBox.MaximumPointer
		MainBox.Refresh()
	End Sub
	
	Sub WBox_SelectViewClick(sender As Object, e As EventArgs)
		MainBox.SelectedArea.SelectFrom = MainBox.LeftPosition
		MainBox.SelectedArea.SelectTo = MainBox.LeftPosition + MainBox.WindowSize
		MainBox.Refresh()
	End Sub
	
	Sub WBox_ViewAllClick(sender As Object, e As EventArgs)
		MainBox.LeftPosition = 0
		MainBox.WindowSize = MainBox.MaximumPointer
		MainBox.Refresh()
	End Sub
	
	
	Sub CheckBox_BalanceCheckedChanged(sender As Object, e As EventArgs)
		If CheckBox_Balance.Checked Then
			Setting_Balance = True
		Else
			Setting_Balance = False
		End If
	End Sub
End Class
