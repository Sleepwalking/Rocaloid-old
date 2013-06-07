'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class MainForm
	Inherits System.Windows.Forms.Form
	
	''' <summary>
	''' Designer variable used to keep track of non-visual components.
	''' </summary>
	Private components As System.ComponentModel.IContainer
	
	''' <summary>
	''' Disposes resources used by the form.
	''' </summary>
	''' <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
	Protected Overrides Sub Dispose(ByVal disposing As Boolean)
		If disposing Then
			If components IsNot Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(disposing)
	End Sub
	
	''' <summary>
	''' This method is required for Windows Forms designer support.
	''' Do not change the method contents inside the source code editor. The Forms designer might
	''' not be able to load this method if it was changed manually.
	''' </summary>
	Private Sub InitializeComponent()
		Me.components = New System.ComponentModel.Container()
		Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainForm))
		Me.MainMenuStrip = New System.Windows.Forms.MenuStrip()
		Me.fileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.Menu_Open = New System.Windows.Forms.ToolStripMenuItem()
		Me.Menu_Save = New System.Windows.Forms.ToolStripMenuItem()
		Me.Menu_SaveAs = New System.Windows.Forms.ToolStripMenuItem()
		Me.toolStripSeparator2 = New System.Windows.Forms.ToolStripSeparator()
		Me.Menu_Synthesis = New System.Windows.Forms.ToolStripMenuItem()
		Me.Menu_Console = New System.Windows.Forms.ToolStripMenuItem()
		Me.MainToolStrip = New System.Windows.Forms.ToolStrip()
		Me.SynthesisAndPlay = New System.Windows.Forms.ToolStripButton()
		Me.SynthesisSegment = New System.Windows.Forms.ToolStripButton()
		Me.SynthesisStop = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator1 = New System.Windows.Forms.ToolStripSeparator()
		Me.SaveCVS = New System.Windows.Forms.ToolStripButton()
		Me.MainNoteBox = New CEditor.NoteBox()
		Me.NBoxScrollBar = New System.Windows.Forms.HScrollBar()
		Me.HorizontalScale = New System.Windows.Forms.TrackBar()
		Me.MainSBox = New CEditor.SingleNoteBox()
		Me.SBoxScrollBar = New System.Windows.Forms.HScrollBar()
		Me.BarUpdateTimer = New System.Windows.Forms.Timer(Me.components)
		Me.Dialog_OpenFile = New System.Windows.Forms.OpenFileDialog()
		Me.Dialog_SaveFile = New System.Windows.Forms.SaveFileDialog()
		Me.radioButton1 = New System.Windows.Forms.RadioButton()
		Me.radioButton2 = New System.Windows.Forms.RadioButton()
		Me.ADSR_Box = New System.Windows.Forms.GroupBox()
		Me.ADSR_Amplitude = New System.Windows.Forms.Label()
		Me.ADSR_AmplitudeBar = New System.Windows.Forms.TrackBar()
		Me.ADSR_Release = New System.Windows.Forms.Label()
		Me.ADSR_ReleaseBar = New System.Windows.Forms.TrackBar()
		Me.ADSR_Decline = New System.Windows.Forms.Label()
		Me.ADSR_DeclineBar = New System.Windows.Forms.TrackBar()
		Me.ADSR_Attack = New System.Windows.Forms.Label()
		Me.ADSR_AttackBar = New System.Windows.Forms.TrackBar()
		Me.ADSR_Enabled = New System.Windows.Forms.CheckBox()
		Me.Dialog_SynthesisWav = New System.Windows.Forms.SaveFileDialog()
		Me.radioButton3 = New System.Windows.Forms.RadioButton()
		Me.Shrink_Box = New System.Windows.Forms.GroupBox()
		Me.Shrink_Shrink = New System.Windows.Forms.Label()
		Me.Shrink_ShrinkBar = New System.Windows.Forms.TrackBar()
		Me.Shrink_Cut = New System.Windows.Forms.Label()
		Me.Shrink_CutBar = New System.Windows.Forms.TrackBar()
		Me.MainMenuStrip.SuspendLayout
		Me.MainToolStrip.SuspendLayout
		CType(Me.MainNoteBox,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.HorizontalScale,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.MainSBox,System.ComponentModel.ISupportInitialize).BeginInit
		Me.ADSR_Box.SuspendLayout
		CType(Me.ADSR_AmplitudeBar,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.ADSR_ReleaseBar,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.ADSR_DeclineBar,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.ADSR_AttackBar,System.ComponentModel.ISupportInitialize).BeginInit
		Me.Shrink_Box.SuspendLayout
		CType(Me.Shrink_ShrinkBar,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.Shrink_CutBar,System.ComponentModel.ISupportInitialize).BeginInit
		Me.SuspendLayout
		'
		'MainMenuStrip
		'
		Me.MainMenuStrip.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.fileToolStripMenuItem, Me.Menu_Console})
		Me.MainMenuStrip.Location = New System.Drawing.Point(0, 0)
		Me.MainMenuStrip.Name = "MainMenuStrip"
		Me.MainMenuStrip.Size = New System.Drawing.Size(731, 24)
		Me.MainMenuStrip.TabIndex = 0
		Me.MainMenuStrip.Text = "menuStrip1"
		'
		'fileToolStripMenuItem
		'
		Me.fileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Menu_Open, Me.Menu_Save, Me.Menu_SaveAs, Me.toolStripSeparator2, Me.Menu_Synthesis})
		Me.fileToolStripMenuItem.Name = "fileToolStripMenuItem"
		Me.fileToolStripMenuItem.Size = New System.Drawing.Size(35, 20)
		Me.fileToolStripMenuItem.Text = "File"
		'
		'Menu_Open
		'
		Me.Menu_Open.Name = "Menu_Open"
		Me.Menu_Open.Size = New System.Drawing.Size(120, 22)
		Me.Menu_Open.Text = "Open"
		AddHandler Me.Menu_Open.Click, AddressOf Me.Menu_OpenClick
		'
		'Menu_Save
		'
		Me.Menu_Save.Name = "Menu_Save"
		Me.Menu_Save.Size = New System.Drawing.Size(120, 22)
		Me.Menu_Save.Text = "Save"
		AddHandler Me.Menu_Save.Click, AddressOf Me.Menu_SaveClick
		'
		'Menu_SaveAs
		'
		Me.Menu_SaveAs.Name = "Menu_SaveAs"
		Me.Menu_SaveAs.Size = New System.Drawing.Size(120, 22)
		Me.Menu_SaveAs.Text = "Save As"
		AddHandler Me.Menu_SaveAs.Click, AddressOf Me.Menu_SaveAsClick
		'
		'toolStripSeparator2
		'
		Me.toolStripSeparator2.Name = "toolStripSeparator2"
		Me.toolStripSeparator2.Size = New System.Drawing.Size(117, 6)
		'
		'Menu_Synthesis
		'
		Me.Menu_Synthesis.Name = "Menu_Synthesis"
		Me.Menu_Synthesis.Size = New System.Drawing.Size(120, 22)
		Me.Menu_Synthesis.Text = "Synthesis"
		AddHandler Me.Menu_Synthesis.Click, AddressOf Me.Menu_SynthesisClick
		'
		'Menu_Console
		'
		Me.Menu_Console.Name = "Menu_Console"
		Me.Menu_Console.Size = New System.Drawing.Size(57, 20)
		Me.Menu_Console.Text = "Console"
		AddHandler Me.Menu_Console.Click, AddressOf Me.ConsoleToolStripMenuItemClick
		'
		'MainToolStrip
		'
		Me.MainToolStrip.BackColor = System.Drawing.Color.Transparent
		Me.MainToolStrip.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.SynthesisAndPlay, Me.SynthesisSegment, Me.SynthesisStop, Me.toolStripSeparator1, Me.SaveCVS})
		Me.MainToolStrip.Location = New System.Drawing.Point(0, 24)
		Me.MainToolStrip.Name = "MainToolStrip"
		Me.MainToolStrip.Size = New System.Drawing.Size(731, 25)
		Me.MainToolStrip.TabIndex = 1
		Me.MainToolStrip.Text = "toolStrip1"
		'
		'SynthesisAndPlay
		'
		Me.SynthesisAndPlay.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SynthesisAndPlay.Image = CType(resources.GetObject("SynthesisAndPlay.Image"),System.Drawing.Image)
		Me.SynthesisAndPlay.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SynthesisAndPlay.Name = "SynthesisAndPlay"
		Me.SynthesisAndPlay.Size = New System.Drawing.Size(23, 22)
		Me.SynthesisAndPlay.Text = "Play"
		AddHandler Me.SynthesisAndPlay.Click, AddressOf Me.SynthesisAndPlayClick
		'
		'SynthesisSegment
		'
		Me.SynthesisSegment.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SynthesisSegment.Image = CType(resources.GetObject("SynthesisSegment.Image"),System.Drawing.Image)
		Me.SynthesisSegment.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SynthesisSegment.Name = "SynthesisSegment"
		Me.SynthesisSegment.Size = New System.Drawing.Size(23, 22)
		Me.SynthesisSegment.Text = "Play Segment"
		AddHandler Me.SynthesisSegment.Click, AddressOf Me.ToolStripButton1Click
		'
		'SynthesisStop
		'
		Me.SynthesisStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SynthesisStop.Image = CType(resources.GetObject("SynthesisStop.Image"),System.Drawing.Image)
		Me.SynthesisStop.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SynthesisStop.Name = "SynthesisStop"
		Me.SynthesisStop.Size = New System.Drawing.Size(23, 22)
		Me.SynthesisStop.Text = "Stop"
		AddHandler Me.SynthesisStop.Click, AddressOf Me.SynthesisStopClick
		'
		'toolStripSeparator1
		'
		Me.toolStripSeparator1.Name = "toolStripSeparator1"
		Me.toolStripSeparator1.Size = New System.Drawing.Size(6, 25)
		'
		'SaveCVS
		'
		Me.SaveCVS.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SaveCVS.Image = CType(resources.GetObject("SaveCVS.Image"),System.Drawing.Image)
		Me.SaveCVS.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SaveCVS.Name = "SaveCVS"
		Me.SaveCVS.Size = New System.Drawing.Size(23, 22)
		Me.SaveCVS.Text = "Save"
		AddHandler Me.SaveCVS.Click, AddressOf Me.SaveCVSClick
		'
		'MainNoteBox
		'
		Me.MainNoteBox.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.MainNoteBox.Location = New System.Drawing.Point(0, 52)
		Me.MainNoteBox.Name = "MainNoteBox"
		Me.MainNoteBox.ScrollBar = Nothing
		Me.MainNoteBox.Size = New System.Drawing.Size(731, 65)
		Me.MainNoteBox.SNoteBox = Nothing
		Me.MainNoteBox.TabIndex = 2
		Me.MainNoteBox.TabStop = false
		'
		'NBoxScrollBar
		'
		Me.NBoxScrollBar.CausesValidation = false
		Me.NBoxScrollBar.Location = New System.Drawing.Point(0, 119)
		Me.NBoxScrollBar.Name = "NBoxScrollBar"
		Me.NBoxScrollBar.Size = New System.Drawing.Size(731, 21)
		Me.NBoxScrollBar.TabIndex = 3
		'
		'HorizontalScale
		'
		Me.HorizontalScale.LargeChange = 20
		Me.HorizontalScale.Location = New System.Drawing.Point(598, 143)
		Me.HorizontalScale.Maximum = 50
		Me.HorizontalScale.Minimum = 1
		Me.HorizontalScale.Name = "HorizontalScale"
		Me.HorizontalScale.Size = New System.Drawing.Size(133, 42)
		Me.HorizontalScale.TabIndex = 4
		Me.HorizontalScale.TickFrequency = 5
		Me.HorizontalScale.Value = 6
		AddHandler Me.HorizontalScale.Scroll, AddressOf Me.VerticalScaleScroll
		'
		'MainSBox
		'
		Me.MainSBox.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.MainSBox.Location = New System.Drawing.Point(0, 180)
		Me.MainSBox.Name = "MainSBox"
		Me.MainSBox.ScrollBar = Nothing
		Me.MainSBox.Size = New System.Drawing.Size(731, 32)
		Me.MainSBox.SNoteBox = Nothing
		Me.MainSBox.TabIndex = 5
		Me.MainSBox.TabStop = false
		'
		'SBoxScrollBar
		'
		Me.SBoxScrollBar.CausesValidation = false
		Me.SBoxScrollBar.Location = New System.Drawing.Point(0, 215)
		Me.SBoxScrollBar.Name = "SBoxScrollBar"
		Me.SBoxScrollBar.Size = New System.Drawing.Size(731, 21)
		Me.SBoxScrollBar.TabIndex = 6
		'
		'BarUpdateTimer
		'
		Me.BarUpdateTimer.Enabled = true
		Me.BarUpdateTimer.Interval = 50
		AddHandler Me.BarUpdateTimer.Tick, AddressOf Me.Timer1Tick
		'
		'Dialog_OpenFile
		'
		Me.Dialog_OpenFile.Filter = "Cybervoice Script (*.cvs)|*.cvs"
		'
		'Dialog_SaveFile
		'
		Me.Dialog_SaveFile.Filter = "Cybervoice Script (*.cvs)|*.cvs"
		'
		'radioButton1
		'
		Me.radioButton1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.radioButton1.Location = New System.Drawing.Point(422, 143)
		Me.radioButton1.Name = "radioButton1"
		Me.radioButton1.Size = New System.Drawing.Size(95, 32)
		Me.radioButton1.TabIndex = 7
		Me.radioButton1.Text = "View-Shrink"
		Me.radioButton1.UseVisualStyleBackColor = true
		AddHandler Me.radioButton1.CheckedChanged, AddressOf Me.RadioButton1CheckedChanged
		'
		'radioButton2
		'
		Me.radioButton2.ForeColor = System.Drawing.SystemColors.ControlText
		Me.radioButton2.Location = New System.Drawing.Point(515, 143)
		Me.radioButton2.Name = "radioButton2"
		Me.radioButton2.Size = New System.Drawing.Size(93, 32)
		Me.radioButton2.TabIndex = 8
		Me.radioButton2.Text = "View-ADSR"
		Me.radioButton2.UseVisualStyleBackColor = true
		AddHandler Me.radioButton2.CheckedChanged, AddressOf Me.RadioButton2CheckedChanged
		'
		'ADSR_Box
		'
		Me.ADSR_Box.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink
		Me.ADSR_Box.Controls.Add(Me.ADSR_Amplitude)
		Me.ADSR_Box.Controls.Add(Me.ADSR_AmplitudeBar)
		Me.ADSR_Box.Controls.Add(Me.ADSR_Release)
		Me.ADSR_Box.Controls.Add(Me.ADSR_ReleaseBar)
		Me.ADSR_Box.Controls.Add(Me.ADSR_Decline)
		Me.ADSR_Box.Controls.Add(Me.ADSR_DeclineBar)
		Me.ADSR_Box.Controls.Add(Me.ADSR_Attack)
		Me.ADSR_Box.Controls.Add(Me.ADSR_AttackBar)
		Me.ADSR_Box.Controls.Add(Me.ADSR_Enabled)
		Me.ADSR_Box.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Box.Location = New System.Drawing.Point(0, 241)
		Me.ADSR_Box.Name = "ADSR_Box"
		Me.ADSR_Box.Size = New System.Drawing.Size(731, 87)
		Me.ADSR_Box.TabIndex = 9
		Me.ADSR_Box.TabStop = false
		Me.ADSR_Box.Text = "ADSR Envelope"
		'
		'ADSR_Amplitude
		'
		Me.ADSR_Amplitude.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Amplitude.Location = New System.Drawing.Point(631, 52)
		Me.ADSR_Amplitude.Name = "ADSR_Amplitude"
		Me.ADSR_Amplitude.Size = New System.Drawing.Size(94, 18)
		Me.ADSR_Amplitude.TabIndex = 8
		Me.ADSR_Amplitude.Text = "Amplitude"
		'
		'ADSR_AmplitudeBar
		'
		Me.ADSR_AmplitudeBar.Location = New System.Drawing.Point(619, 20)
		Me.ADSR_AmplitudeBar.Maximum = 100
		Me.ADSR_AmplitudeBar.Name = "ADSR_AmplitudeBar"
		Me.ADSR_AmplitudeBar.Size = New System.Drawing.Size(100, 42)
		Me.ADSR_AmplitudeBar.TabIndex = 7
		Me.ADSR_AmplitudeBar.TickFrequency = 10
		AddHandler Me.ADSR_AmplitudeBar.Scroll, AddressOf Me.ADSR_AmplitudeBarScroll
		'
		'ADSR_Release
		'
		Me.ADSR_Release.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Release.Location = New System.Drawing.Point(496, 52)
		Me.ADSR_Release.Name = "ADSR_Release"
		Me.ADSR_Release.Size = New System.Drawing.Size(88, 18)
		Me.ADSR_Release.TabIndex = 6
		Me.ADSR_Release.Text = "Release"
		'
		'ADSR_ReleaseBar
		'
		Me.ADSR_ReleaseBar.Location = New System.Drawing.Point(484, 20)
		Me.ADSR_ReleaseBar.Maximum = 50
		Me.ADSR_ReleaseBar.Name = "ADSR_ReleaseBar"
		Me.ADSR_ReleaseBar.Size = New System.Drawing.Size(100, 42)
		Me.ADSR_ReleaseBar.TabIndex = 5
		Me.ADSR_ReleaseBar.TickFrequency = 5
		AddHandler Me.ADSR_ReleaseBar.Scroll, AddressOf Me.ADSR_ReleaseBarScroll
		'
		'ADSR_Decline
		'
		Me.ADSR_Decline.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Decline.Location = New System.Drawing.Point(354, 52)
		Me.ADSR_Decline.Name = "ADSR_Decline"
		Me.ADSR_Decline.Size = New System.Drawing.Size(88, 18)
		Me.ADSR_Decline.TabIndex = 4
		Me.ADSR_Decline.Text = "Decline"
		'
		'ADSR_DeclineBar
		'
		Me.ADSR_DeclineBar.Location = New System.Drawing.Point(342, 20)
		Me.ADSR_DeclineBar.Maximum = 50
		Me.ADSR_DeclineBar.Name = "ADSR_DeclineBar"
		Me.ADSR_DeclineBar.Size = New System.Drawing.Size(100, 42)
		Me.ADSR_DeclineBar.TabIndex = 3
		Me.ADSR_DeclineBar.TickFrequency = 5
		AddHandler Me.ADSR_DeclineBar.Scroll, AddressOf Me.ADSR_DeclineBarScroll
		'
		'ADSR_Attack
		'
		Me.ADSR_Attack.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Attack.Location = New System.Drawing.Point(210, 52)
		Me.ADSR_Attack.Name = "ADSR_Attack"
		Me.ADSR_Attack.Size = New System.Drawing.Size(88, 18)
		Me.ADSR_Attack.TabIndex = 2
		Me.ADSR_Attack.Text = "Attack"
		'
		'ADSR_AttackBar
		'
		Me.ADSR_AttackBar.Location = New System.Drawing.Point(198, 20)
		Me.ADSR_AttackBar.Maximum = 50
		Me.ADSR_AttackBar.Name = "ADSR_AttackBar"
		Me.ADSR_AttackBar.Size = New System.Drawing.Size(100, 42)
		Me.ADSR_AttackBar.TabIndex = 1
		Me.ADSR_AttackBar.TickFrequency = 5
		AddHandler Me.ADSR_AttackBar.Scroll, AddressOf Me.ADSR_AttackBarScroll
		'
		'ADSR_Enabled
		'
		Me.ADSR_Enabled.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Enabled.Location = New System.Drawing.Point(6, 20)
		Me.ADSR_Enabled.Name = "ADSR_Enabled"
		Me.ADSR_Enabled.Size = New System.Drawing.Size(128, 20)
		Me.ADSR_Enabled.TabIndex = 0
		Me.ADSR_Enabled.Text = "Use ADSR Envelope"
		Me.ADSR_Enabled.UseVisualStyleBackColor = true
		AddHandler Me.ADSR_Enabled.CheckedChanged, AddressOf Me.ADSR_EnabledCheckedChanged
		'
		'Dialog_SynthesisWav
		'
		Me.Dialog_SynthesisWav.Filter = "Wave (*.wav) | *.wav"
		'
		'radioButton3
		'
		Me.radioButton3.Checked = true
		Me.radioButton3.ForeColor = System.Drawing.SystemColors.ControlText
		Me.radioButton3.Location = New System.Drawing.Point(329, 143)
		Me.radioButton3.Name = "radioButton3"
		Me.radioButton3.Size = New System.Drawing.Size(87, 32)
		Me.radioButton3.TabIndex = 10
		Me.radioButton3.TabStop = true
		Me.radioButton3.Text = "View-Non"
		Me.radioButton3.UseVisualStyleBackColor = true
		AddHandler Me.radioButton3.CheckedChanged, AddressOf Me.RadioButton3CheckedChanged
		'
		'Shrink_Box
		'
		Me.Shrink_Box.Controls.Add(Me.Shrink_Shrink)
		Me.Shrink_Box.Controls.Add(Me.Shrink_ShrinkBar)
		Me.Shrink_Box.Controls.Add(Me.Shrink_Cut)
		Me.Shrink_Box.Controls.Add(Me.Shrink_CutBar)
		Me.Shrink_Box.Location = New System.Drawing.Point(0, 330)
		Me.Shrink_Box.Name = "Shrink_Box"
		Me.Shrink_Box.Size = New System.Drawing.Size(731, 69)
		Me.Shrink_Box.TabIndex = 11
		Me.Shrink_Box.TabStop = false
		Me.Shrink_Box.Text = "Shrinkage"
		'
		'Shrink_Shrink
		'
		Me.Shrink_Shrink.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Shrink_Shrink.Location = New System.Drawing.Point(124, 49)
		Me.Shrink_Shrink.Name = "Shrink_Shrink"
		Me.Shrink_Shrink.Size = New System.Drawing.Size(110, 18)
		Me.Shrink_Shrink.TabIndex = 6
		Me.Shrink_Shrink.Text = "Shrink"
		'
		'Shrink_ShrinkBar
		'
		Me.Shrink_ShrinkBar.Location = New System.Drawing.Point(112, 17)
		Me.Shrink_ShrinkBar.Maximum = 20
		Me.Shrink_ShrinkBar.Name = "Shrink_ShrinkBar"
		Me.Shrink_ShrinkBar.Size = New System.Drawing.Size(100, 42)
		Me.Shrink_ShrinkBar.TabIndex = 5
		Me.Shrink_ShrinkBar.TickFrequency = 5
		AddHandler Me.Shrink_ShrinkBar.Scroll, AddressOf Me.Shrink_ShrinkBarScroll
		'
		'Shrink_Cut
		'
		Me.Shrink_Cut.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Shrink_Cut.Location = New System.Drawing.Point(18, 49)
		Me.Shrink_Cut.Name = "Shrink_Cut"
		Me.Shrink_Cut.Size = New System.Drawing.Size(88, 18)
		Me.Shrink_Cut.TabIndex = 4
		Me.Shrink_Cut.Text = "Cut"
		'
		'Shrink_CutBar
		'
		Me.Shrink_CutBar.Location = New System.Drawing.Point(6, 17)
		Me.Shrink_CutBar.Maximum = 20
		Me.Shrink_CutBar.Name = "Shrink_CutBar"
		Me.Shrink_CutBar.Size = New System.Drawing.Size(100, 42)
		Me.Shrink_CutBar.TabIndex = 3
		Me.Shrink_CutBar.TickFrequency = 5
		AddHandler Me.Shrink_CutBar.Scroll, AddressOf Me.Shrink_CutBarScroll
		'
		'MainForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.ClientSize = New System.Drawing.Size(731, 411)
		Me.Controls.Add(Me.Shrink_Box)
		Me.Controls.Add(Me.radioButton3)
		Me.Controls.Add(Me.ADSR_Box)
		Me.Controls.Add(Me.radioButton2)
		Me.Controls.Add(Me.radioButton1)
		Me.Controls.Add(Me.SBoxScrollBar)
		Me.Controls.Add(Me.MainSBox)
		Me.Controls.Add(Me.HorizontalScale)
		Me.Controls.Add(Me.NBoxScrollBar)
		Me.Controls.Add(Me.MainNoteBox)
		Me.Controls.Add(Me.MainToolStrip)
		Me.Controls.Add(Me.MainMenuStrip)
		Me.KeyPreview = true
		Me.Name = "MainForm"
		Me.Text = "Rocaloid CVS Editor"
		AddHandler FormClosing, AddressOf Me.MainFormFormClosing
		AddHandler Load, AddressOf Me.MainFormLoad
		AddHandler KeyDown, AddressOf Me.MainFormKeyDown
		AddHandler Resize, AddressOf Me.MainFormResize
		Me.MainMenuStrip.ResumeLayout(false)
		Me.MainMenuStrip.PerformLayout
		Me.MainToolStrip.ResumeLayout(false)
		Me.MainToolStrip.PerformLayout
		CType(Me.MainNoteBox,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.HorizontalScale,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.MainSBox,System.ComponentModel.ISupportInitialize).EndInit
		Me.ADSR_Box.ResumeLayout(false)
		Me.ADSR_Box.PerformLayout
		CType(Me.ADSR_AmplitudeBar,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.ADSR_ReleaseBar,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.ADSR_DeclineBar,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.ADSR_AttackBar,System.ComponentModel.ISupportInitialize).EndInit
		Me.Shrink_Box.ResumeLayout(false)
		Me.Shrink_Box.PerformLayout
		CType(Me.Shrink_ShrinkBar,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.Shrink_CutBar,System.ComponentModel.ISupportInitialize).EndInit
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private SynthesisSegment As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator2 As System.Windows.Forms.ToolStripSeparator
	Private Shrink_CutBar As System.Windows.Forms.TrackBar
	Private Shrink_Cut As System.Windows.Forms.Label
	Private Shrink_ShrinkBar As System.Windows.Forms.TrackBar
	Private Shrink_Shrink As System.Windows.Forms.Label
	Private Shrink_Box As System.Windows.Forms.GroupBox
	Private radioButton3 As System.Windows.Forms.RadioButton
	Private Dialog_SynthesisWav As System.Windows.Forms.SaveFileDialog
	Private ADSR_AttackBar As System.Windows.Forms.TrackBar
	Private ADSR_Attack As System.Windows.Forms.Label
	Private ADSR_DeclineBar As System.Windows.Forms.TrackBar
	Private ADSR_Decline As System.Windows.Forms.Label
	Private ADSR_ReleaseBar As System.Windows.Forms.TrackBar
	Private ADSR_Release As System.Windows.Forms.Label
	Private ADSR_AmplitudeBar As System.Windows.Forms.TrackBar
	Private ADSR_Amplitude As System.Windows.Forms.Label
	Private ADSR_Enabled As System.Windows.Forms.CheckBox
	Private ADSR_Box As System.Windows.Forms.GroupBox
	Private radioButton2 As System.Windows.Forms.RadioButton
	Private radioButton1 As System.Windows.Forms.RadioButton
	Private Dialog_SaveFile As System.Windows.Forms.SaveFileDialog
	Private Dialog_OpenFile As System.Windows.Forms.OpenFileDialog
	Private Menu_Synthesis As System.Windows.Forms.ToolStripMenuItem
	Private Menu_SaveAs As System.Windows.Forms.ToolStripMenuItem
	Private Menu_Save As System.Windows.Forms.ToolStripMenuItem
	Private Menu_Open As System.Windows.Forms.ToolStripMenuItem
	Private Menu_Console As System.Windows.Forms.ToolStripMenuItem
	Private BarUpdateTimer As System.Windows.Forms.Timer
	Private SaveCVS As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator1 As System.Windows.Forms.ToolStripSeparator
	Private SynthesisStop As System.Windows.Forms.ToolStripButton
	Private SynthesisAndPlay As System.Windows.Forms.ToolStripButton
	Private SBoxScrollBar As System.Windows.Forms.HScrollBar
	Private MainSBox As CEditor.SingleNoteBox
	Private HorizontalScale As System.Windows.Forms.TrackBar
	Friend NBoxScrollBar As System.Windows.Forms.HScrollBar
	Friend MainNoteBox As CEditor.NoteBox
	Private MainToolStrip As System.Windows.Forms.ToolStrip
	Private fileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private MainMenuStrip As System.Windows.Forms.MenuStrip
	
End Class
