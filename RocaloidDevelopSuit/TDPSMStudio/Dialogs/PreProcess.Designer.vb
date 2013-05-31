'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class PreProcess
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
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.MA_Extra = New System.Windows.Forms.CheckBox()
		Me.MA_Twice = New System.Windows.Forms.CheckBox()
		Me.MA_23 = New System.Windows.Forms.RadioButton()
		Me.MA_Enabled = New System.Windows.Forms.CheckBox()
		Me.MA_13 = New System.Windows.Forms.RadioButton()
		Me.MA_12 = New System.Windows.Forms.RadioButton()
		Me.MA_14 = New System.Windows.Forms.RadioButton()
		Me.groupBox2 = New System.Windows.Forms.GroupBox()
		Me.EM_4 = New System.Windows.Forms.RadioButton()
		Me.EM_2 = New System.Windows.Forms.RadioButton()
		Me.EM_1 = New System.Windows.Forms.RadioButton()
		Me.label1 = New System.Windows.Forms.Label()
		Me.groupBox3 = New System.Windows.Forms.GroupBox()
		Me.SP_Delayed = New System.Windows.Forms.RadioButton()
		Me.SP_Fixed = New System.Windows.Forms.RadioButton()
		Me.label3 = New System.Windows.Forms.Label()
		Me.SP_Time = New System.Windows.Forms.TextBox()
		Me.Button_Apply = New System.Windows.Forms.Button()
		Me.groupBox1.SuspendLayout
		Me.groupBox2.SuspendLayout
		Me.groupBox3.SuspendLayout
		Me.SuspendLayout
		'
		'groupBox1
		'
		Me.groupBox1.Controls.Add(Me.MA_Extra)
		Me.groupBox1.Controls.Add(Me.MA_Twice)
		Me.groupBox1.Controls.Add(Me.MA_23)
		Me.groupBox1.Controls.Add(Me.MA_Enabled)
		Me.groupBox1.Controls.Add(Me.MA_13)
		Me.groupBox1.Controls.Add(Me.MA_12)
		Me.groupBox1.Controls.Add(Me.MA_14)
		Me.groupBox1.Location = New System.Drawing.Point(12, 12)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(404, 74)
		Me.groupBox1.TabIndex = 0
		Me.groupBox1.TabStop = false
		Me.groupBox1.Text = "Moving Average"
		'
		'MA_Extra
		'
		Me.MA_Extra.Location = New System.Drawing.Point(206, 20)
		Me.MA_Extra.Name = "MA_Extra"
		Me.MA_Extra.Size = New System.Drawing.Size(91, 20)
		Me.MA_Extra.TabIndex = 4
		Me.MA_Extra.Text = "Extra"
		Me.MA_Extra.UseVisualStyleBackColor = true
		'
		'MA_Twice
		'
		Me.MA_Twice.Checked = true
		Me.MA_Twice.CheckState = System.Windows.Forms.CheckState.Checked
		Me.MA_Twice.Location = New System.Drawing.Point(109, 20)
		Me.MA_Twice.Name = "MA_Twice"
		Me.MA_Twice.Size = New System.Drawing.Size(91, 20)
		Me.MA_Twice.TabIndex = 3
		Me.MA_Twice.Text = "Twice"
		Me.MA_Twice.UseVisualStyleBackColor = true
		AddHandler Me.MA_Twice.CheckedChanged, AddressOf Me.MA_TwiceCheckedChanged
		'
		'MA_23
		'
		Me.MA_23.Location = New System.Drawing.Point(12, 46)
		Me.MA_23.Name = "MA_23"
		Me.MA_23.Size = New System.Drawing.Size(91, 20)
		Me.MA_23.TabIndex = 2
		Me.MA_23.Text = "2/3 Periods"
		Me.MA_23.UseVisualStyleBackColor = true
		'
		'MA_Enabled
		'
		Me.MA_Enabled.Checked = true
		Me.MA_Enabled.CheckState = System.Windows.Forms.CheckState.Checked
		Me.MA_Enabled.Location = New System.Drawing.Point(12, 20)
		Me.MA_Enabled.Name = "MA_Enabled"
		Me.MA_Enabled.Size = New System.Drawing.Size(105, 20)
		Me.MA_Enabled.TabIndex = 0
		Me.MA_Enabled.Text = "Enabled"
		Me.MA_Enabled.UseVisualStyleBackColor = true
		'
		'MA_13
		'
		Me.MA_13.Checked = true
		Me.MA_13.Location = New System.Drawing.Point(206, 45)
		Me.MA_13.Name = "MA_13"
		Me.MA_13.Size = New System.Drawing.Size(91, 20)
		Me.MA_13.TabIndex = 2
		Me.MA_13.TabStop = true
		Me.MA_13.Text = "1/3 Periods"
		Me.MA_13.UseVisualStyleBackColor = true
		'
		'MA_12
		'
		Me.MA_12.Location = New System.Drawing.Point(109, 46)
		Me.MA_12.Name = "MA_12"
		Me.MA_12.Size = New System.Drawing.Size(91, 20)
		Me.MA_12.TabIndex = 1
		Me.MA_12.Text = "1/2 Periods"
		Me.MA_12.UseVisualStyleBackColor = true
		'
		'MA_14
		'
		Me.MA_14.Location = New System.Drawing.Point(303, 46)
		Me.MA_14.Name = "MA_14"
		Me.MA_14.Size = New System.Drawing.Size(91, 20)
		Me.MA_14.TabIndex = 2
		Me.MA_14.Text = "1/4 Periods"
		Me.MA_14.UseVisualStyleBackColor = true
		'
		'groupBox2
		'
		Me.groupBox2.Controls.Add(Me.EM_4)
		Me.groupBox2.Controls.Add(Me.EM_2)
		Me.groupBox2.Controls.Add(Me.EM_1)
		Me.groupBox2.Controls.Add(Me.label1)
		Me.groupBox2.Location = New System.Drawing.Point(12, 98)
		Me.groupBox2.Name = "groupBox2"
		Me.groupBox2.Size = New System.Drawing.Size(404, 42)
		Me.groupBox2.TabIndex = 1
		Me.groupBox2.TabStop = false
		Me.groupBox2.Text = "Envelope Mapping"
		'
		'EM_4
		'
		Me.EM_4.Location = New System.Drawing.Point(303, 14)
		Me.EM_4.Name = "EM_4"
		Me.EM_4.Size = New System.Drawing.Size(84, 19)
		Me.EM_4.TabIndex = 3
		Me.EM_4.Text = "4 Periods"
		Me.EM_4.UseVisualStyleBackColor = true
		'
		'EM_2
		'
		Me.EM_2.Checked = true
		Me.EM_2.Location = New System.Drawing.Point(206, 14)
		Me.EM_2.Name = "EM_2"
		Me.EM_2.Size = New System.Drawing.Size(84, 19)
		Me.EM_2.TabIndex = 2
		Me.EM_2.TabStop = true
		Me.EM_2.Text = "2 Periods"
		Me.EM_2.UseVisualStyleBackColor = true
		'
		'EM_1
		'
		Me.EM_1.Location = New System.Drawing.Point(109, 14)
		Me.EM_1.Name = "EM_1"
		Me.EM_1.Size = New System.Drawing.Size(74, 19)
		Me.EM_1.TabIndex = 1
		Me.EM_1.Text = "1 Period"
		Me.EM_1.UseVisualStyleBackColor = true
		'
		'label1
		'
		Me.label1.Location = New System.Drawing.Point(12, 17)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(78, 19)
		Me.label1.TabIndex = 0
		Me.label1.Text = "Precision:"
		'
		'groupBox3
		'
		Me.groupBox3.Controls.Add(Me.SP_Delayed)
		Me.groupBox3.Controls.Add(Me.SP_Fixed)
		Me.groupBox3.Controls.Add(Me.label3)
		Me.groupBox3.Controls.Add(Me.SP_Time)
		Me.groupBox3.Location = New System.Drawing.Point(12, 146)
		Me.groupBox3.Name = "groupBox3"
		Me.groupBox3.Size = New System.Drawing.Size(404, 77)
		Me.groupBox3.TabIndex = 2
		Me.groupBox3.TabStop = false
		Me.groupBox3.Text = "Start Position"
		'
		'SP_Delayed
		'
		Me.SP_Delayed.Checked = true
		Me.SP_Delayed.Location = New System.Drawing.Point(109, 20)
		Me.SP_Delayed.Name = "SP_Delayed"
		Me.SP_Delayed.Size = New System.Drawing.Size(74, 19)
		Me.SP_Delayed.TabIndex = 4
		Me.SP_Delayed.TabStop = true
		Me.SP_Delayed.Text = "Delayed"
		Me.SP_Delayed.UseVisualStyleBackColor = true
		'
		'SP_Fixed
		'
		Me.SP_Fixed.Location = New System.Drawing.Point(12, 20)
		Me.SP_Fixed.Name = "SP_Fixed"
		Me.SP_Fixed.Size = New System.Drawing.Size(74, 19)
		Me.SP_Fixed.TabIndex = 3
		Me.SP_Fixed.Text = "Fixed"
		Me.SP_Fixed.UseVisualStyleBackColor = true
		'
		'label3
		'
		Me.label3.Location = New System.Drawing.Point(94, 49)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(32, 17)
		Me.label3.TabIndex = 2
		Me.label3.Text = "s."
		'
		'SP_Time
		'
		Me.SP_Time.Location = New System.Drawing.Point(12, 45)
		Me.SP_Time.Name = "SP_Time"
		Me.SP_Time.Size = New System.Drawing.Size(76, 21)
		Me.SP_Time.TabIndex = 1
		Me.SP_Time.Text = "0.1"
		Me.SP_Time.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'Button_Apply
		'
		Me.Button_Apply.Location = New System.Drawing.Point(315, 229)
		Me.Button_Apply.Name = "Button_Apply"
		Me.Button_Apply.Size = New System.Drawing.Size(100, 28)
		Me.Button_Apply.TabIndex = 3
		Me.Button_Apply.Text = "Apply"
		Me.Button_Apply.UseVisualStyleBackColor = true
		AddHandler Me.Button_Apply.Click, AddressOf Me.Button_Apply_Click
		'
		'PreProcess
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(428, 261)
		Me.Controls.Add(Me.Button_Apply)
		Me.Controls.Add(Me.groupBox3)
		Me.Controls.Add(Me.groupBox2)
		Me.Controls.Add(Me.groupBox1)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
		Me.MaximizeBox = false
		Me.MinimizeBox = false
		Me.Name = "PreProcess"
		Me.ShowInTaskbar = false
		Me.Text = "Preprocess"
		Me.TopMost = true
		AddHandler Load, AddressOf Me.PreProcessLoad
		Me.groupBox1.ResumeLayout(false)
		Me.groupBox2.ResumeLayout(false)
		Me.groupBox3.ResumeLayout(false)
		Me.groupBox3.PerformLayout
		Me.ResumeLayout(false)
	End Sub
	Private MA_Extra As System.Windows.Forms.CheckBox
	Private Button_Apply As System.Windows.Forms.Button
	Private SP_Fixed As System.Windows.Forms.RadioButton
	Private SP_Delayed As System.Windows.Forms.RadioButton
	Private label3 As System.Windows.Forms.Label
	Private SP_Time As System.Windows.Forms.TextBox
	Private groupBox3 As System.Windows.Forms.GroupBox
	Private label1 As System.Windows.Forms.Label
	Private EM_1 As System.Windows.Forms.RadioButton
	Private EM_2 As System.Windows.Forms.RadioButton
	Private EM_4 As System.Windows.Forms.RadioButton
	Private groupBox2 As System.Windows.Forms.GroupBox
	Private MA_14 As System.Windows.Forms.RadioButton
	Private MA_12 As System.Windows.Forms.RadioButton
	Private MA_13 As System.Windows.Forms.RadioButton
	Private MA_Enabled As System.Windows.Forms.CheckBox
	Private MA_23 As System.Windows.Forms.RadioButton
	Private MA_Twice As System.Windows.Forms.CheckBox
	Private groupBox1 As System.Windows.Forms.GroupBox
End Class
