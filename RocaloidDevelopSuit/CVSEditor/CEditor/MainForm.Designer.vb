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
		Me.Menu_Synthesis = New System.Windows.Forms.ToolStripMenuItem()
		Me.Menu_Console = New System.Windows.Forms.ToolStripMenuItem()
		Me.MainToolStrip = New System.Windows.Forms.ToolStrip()
		Me.SynthesisAndPlay = New System.Windows.Forms.ToolStripButton()
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
		Me.label3 = New System.Windows.Forms.Label()
		Me.trackBar3 = New System.Windows.Forms.TrackBar()
		Me.label2 = New System.Windows.Forms.Label()
		Me.trackBar2 = New System.Windows.Forms.TrackBar()
		Me.label1 = New System.Windows.Forms.Label()
		Me.trackBar1 = New System.Windows.Forms.TrackBar()
		Me.ADSR_Attack = New System.Windows.Forms.Label()
		Me.ADSR_AttackBar = New System.Windows.Forms.TrackBar()
		Me.checkBox1 = New System.Windows.Forms.CheckBox()
		Me.MainMenuStrip.SuspendLayout
		Me.MainToolStrip.SuspendLayout
		CType(Me.MainNoteBox,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.HorizontalScale,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.MainSBox,System.ComponentModel.ISupportInitialize).BeginInit
		Me.ADSR_Box.SuspendLayout
		CType(Me.trackBar3,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.trackBar2,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.trackBar1,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.ADSR_AttackBar,System.ComponentModel.ISupportInitialize).BeginInit
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
		Me.fileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Menu_Open, Me.Menu_Save, Me.Menu_SaveAs, Me.Menu_Synthesis})
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
		'Menu_Synthesis
		'
		Me.Menu_Synthesis.Name = "Menu_Synthesis"
		Me.Menu_Synthesis.Size = New System.Drawing.Size(120, 22)
		Me.Menu_Synthesis.Text = "Synthesis"
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
		Me.MainToolStrip.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.SynthesisAndPlay, Me.SynthesisStop, Me.toolStripSeparator1, Me.SaveCVS})
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
		Me.Dialog_OpenFile.Filter = "Cybervoice Script|*.cvs"
		'
		'Dialog_SaveFile
		'
		Me.Dialog_SaveFile.Filter = "Cybervoice Script|*.cvs"
		'
		'radioButton1
		'
		Me.radioButton1.Checked = true
		Me.radioButton1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.radioButton1.Location = New System.Drawing.Point(422, 143)
		Me.radioButton1.Name = "radioButton1"
		Me.radioButton1.Size = New System.Drawing.Size(87, 32)
		Me.radioButton1.TabIndex = 7
		Me.radioButton1.TabStop = true
		Me.radioButton1.Text = "View : Non"
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
		Me.radioButton2.TabStop = true
		Me.radioButton2.Text = "View : ADSR"
		Me.radioButton2.UseVisualStyleBackColor = true
		AddHandler Me.radioButton2.CheckedChanged, AddressOf Me.RadioButton2CheckedChanged
		'
		'ADSR_Box
		'
		Me.ADSR_Box.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink
		Me.ADSR_Box.Controls.Add(Me.label3)
		Me.ADSR_Box.Controls.Add(Me.trackBar3)
		Me.ADSR_Box.Controls.Add(Me.label2)
		Me.ADSR_Box.Controls.Add(Me.trackBar2)
		Me.ADSR_Box.Controls.Add(Me.label1)
		Me.ADSR_Box.Controls.Add(Me.trackBar1)
		Me.ADSR_Box.Controls.Add(Me.ADSR_Attack)
		Me.ADSR_Box.Controls.Add(Me.ADSR_AttackBar)
		Me.ADSR_Box.Controls.Add(Me.checkBox1)
		Me.ADSR_Box.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ADSR_Box.Location = New System.Drawing.Point(0, 241)
		Me.ADSR_Box.Name = "ADSR_Box"
		Me.ADSR_Box.Size = New System.Drawing.Size(731, 87)
		Me.ADSR_Box.TabIndex = 9
		Me.ADSR_Box.TabStop = false
		Me.ADSR_Box.Text = "ADSR Envelope"
		'
		'label3
		'
		Me.label3.ForeColor = System.Drawing.SystemColors.ControlText
		Me.label3.Location = New System.Drawing.Point(631, 52)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(88, 18)
		Me.label3.TabIndex = 8
		Me.label3.Text = "Amplitude"
		'
		'trackBar3
		'
		Me.trackBar3.Location = New System.Drawing.Point(619, 20)
		Me.trackBar3.Name = "trackBar3"
		Me.trackBar3.Size = New System.Drawing.Size(100, 42)
		Me.trackBar3.TabIndex = 7
		'
		'label2
		'
		Me.label2.ForeColor = System.Drawing.SystemColors.ControlText
		Me.label2.Location = New System.Drawing.Point(496, 52)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(88, 18)
		Me.label2.TabIndex = 6
		Me.label2.Text = "Release"
		'
		'trackBar2
		'
		Me.trackBar2.Location = New System.Drawing.Point(484, 20)
		Me.trackBar2.Name = "trackBar2"
		Me.trackBar2.Size = New System.Drawing.Size(100, 42)
		Me.trackBar2.TabIndex = 5
		'
		'label1
		'
		Me.label1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.label1.Location = New System.Drawing.Point(354, 52)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(88, 18)
		Me.label1.TabIndex = 4
		Me.label1.Text = "Decline"
		'
		'trackBar1
		'
		Me.trackBar1.Location = New System.Drawing.Point(342, 20)
		Me.trackBar1.Name = "trackBar1"
		Me.trackBar1.Size = New System.Drawing.Size(100, 42)
		Me.trackBar1.TabIndex = 3
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
		Me.ADSR_AttackBar.Name = "ADSR_AttackBar"
		Me.ADSR_AttackBar.Size = New System.Drawing.Size(100, 42)
		Me.ADSR_AttackBar.TabIndex = 1
		'
		'checkBox1
		'
		Me.checkBox1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.checkBox1.Location = New System.Drawing.Point(6, 20)
		Me.checkBox1.Name = "checkBox1"
		Me.checkBox1.Size = New System.Drawing.Size(128, 20)
		Me.checkBox1.TabIndex = 0
		Me.checkBox1.Text = "Use ADSR Envelope"
		Me.checkBox1.UseVisualStyleBackColor = true
		'
		'MainForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.ClientSize = New System.Drawing.Size(731, 326)
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
		Me.Name = "MainForm"
		Me.Text = "CEditor"
		AddHandler FormClosing, AddressOf Me.MainFormFormClosing
		AddHandler Load, AddressOf Me.MainFormLoad
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
		CType(Me.trackBar3,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.trackBar2,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.trackBar1,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.ADSR_AttackBar,System.ComponentModel.ISupportInitialize).EndInit
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private ADSR_AttackBar As System.Windows.Forms.TrackBar
	Private ADSR_Attack As System.Windows.Forms.Label
	Private trackBar1 As System.Windows.Forms.TrackBar
	Private label1 As System.Windows.Forms.Label
	Private trackBar2 As System.Windows.Forms.TrackBar
	Private label2 As System.Windows.Forms.Label
	Private trackBar3 As System.Windows.Forms.TrackBar
	Private label3 As System.Windows.Forms.Label
	Private checkBox1 As System.Windows.Forms.CheckBox
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
