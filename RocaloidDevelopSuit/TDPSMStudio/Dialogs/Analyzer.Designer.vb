'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class Analyzer
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
		Me.label1 = New System.Windows.Forms.Label()
		Me.TextBox_Silence = New System.Windows.Forms.TextBox()
		Me.Button_Apply = New System.Windows.Forms.Button()
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.label4 = New System.Windows.Forms.Label()
		Me.Alg_Window_To = New System.Windows.Forms.TextBox()
		Me.label3 = New System.Windows.Forms.Label()
		Me.Alg_Window_From = New System.Windows.Forms.TextBox()
		Me.label2 = New System.Windows.Forms.Label()
		Me.Alg_SelfDifference = New System.Windows.Forms.RadioButton()
		Me.Alg_SelfCorrelation = New System.Windows.Forms.RadioButton()
		Me.label5 = New System.Windows.Forms.Label()
		Me.TextBox_AllowingError = New System.Windows.Forms.TextBox()
		Me.groupBox1.SuspendLayout
		Me.SuspendLayout
		'
		'label1
		'
		Me.label1.Location = New System.Drawing.Point(12, 12)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(115, 13)
		Me.label1.TabIndex = 0
		Me.label1.Text = "Silence Threshold:"
		'
		'TextBox_Silence
		'
		Me.TextBox_Silence.Location = New System.Drawing.Point(170, 9)
		Me.TextBox_Silence.Name = "TextBox_Silence"
		Me.TextBox_Silence.Size = New System.Drawing.Size(110, 21)
		Me.TextBox_Silence.TabIndex = 1
		Me.TextBox_Silence.Text = "0.025"
		Me.TextBox_Silence.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'Button_Apply
		'
		Me.Button_Apply.Location = New System.Drawing.Point(185, 195)
		Me.Button_Apply.Name = "Button_Apply"
		Me.Button_Apply.Size = New System.Drawing.Size(95, 28)
		Me.Button_Apply.TabIndex = 2
		Me.Button_Apply.Text = "Apply"
		Me.Button_Apply.UseVisualStyleBackColor = true
		AddHandler Me.Button_Apply.Click, AddressOf Me.Button_ApplyClick
		'
		'groupBox1
		'
		Me.groupBox1.Controls.Add(Me.label4)
		Me.groupBox1.Controls.Add(Me.Alg_Window_To)
		Me.groupBox1.Controls.Add(Me.label3)
		Me.groupBox1.Controls.Add(Me.Alg_Window_From)
		Me.groupBox1.Controls.Add(Me.label2)
		Me.groupBox1.Controls.Add(Me.Alg_SelfDifference)
		Me.groupBox1.Controls.Add(Me.Alg_SelfCorrelation)
		Me.groupBox1.Location = New System.Drawing.Point(12, 59)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(268, 130)
		Me.groupBox1.TabIndex = 3
		Me.groupBox1.TabStop = false
		Me.groupBox1.Text = "Algorism"
		'
		'label4
		'
		Me.label4.Location = New System.Drawing.Point(207, 95)
		Me.label4.Name = "label4"
		Me.label4.Size = New System.Drawing.Size(54, 19)
		Me.label4.TabIndex = 6
		Me.label4.Text = "periods."
		'
		'Alg_Window_To
		'
		Me.Alg_Window_To.Location = New System.Drawing.Point(124, 93)
		Me.Alg_Window_To.Name = "Alg_Window_To"
		Me.Alg_Window_To.Size = New System.Drawing.Size(77, 21)
		Me.Alg_Window_To.TabIndex = 5
		Me.Alg_Window_To.Text = "1.5"
		Me.Alg_Window_To.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'label3
		'
		Me.label3.Location = New System.Drawing.Point(98, 96)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(34, 19)
		Me.label3.TabIndex = 4
		Me.label3.Text = "to"
		'
		'Alg_Window_From
		'
		Me.Alg_Window_From.Location = New System.Drawing.Point(15, 93)
		Me.Alg_Window_From.Name = "Alg_Window_From"
		Me.Alg_Window_From.Size = New System.Drawing.Size(77, 21)
		Me.Alg_Window_From.TabIndex = 3
		Me.Alg_Window_From.Text = "0.5"
		Me.Alg_Window_From.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'label2
		'
		Me.label2.Location = New System.Drawing.Point(15, 75)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(99, 15)
		Me.label2.TabIndex = 2
		Me.label2.Text = "Search Window:"
		'
		'Alg_SelfDifference
		'
		Me.Alg_SelfDifference.Location = New System.Drawing.Point(15, 49)
		Me.Alg_SelfDifference.Name = "Alg_SelfDifference"
		Me.Alg_SelfDifference.Size = New System.Drawing.Size(144, 23)
		Me.Alg_SelfDifference.TabIndex = 1
		Me.Alg_SelfDifference.Text = "Self Difference"
		Me.Alg_SelfDifference.UseVisualStyleBackColor = true
		'
		'Alg_SelfCorrelation
		'
		Me.Alg_SelfCorrelation.Checked = true
		Me.Alg_SelfCorrelation.Location = New System.Drawing.Point(15, 20)
		Me.Alg_SelfCorrelation.Name = "Alg_SelfCorrelation"
		Me.Alg_SelfCorrelation.Size = New System.Drawing.Size(144, 23)
		Me.Alg_SelfCorrelation.TabIndex = 0
		Me.Alg_SelfCorrelation.TabStop = true
		Me.Alg_SelfCorrelation.Text = "Self Correlation"
		Me.Alg_SelfCorrelation.UseVisualStyleBackColor = true
		'
		'label5
		'
		Me.label5.Location = New System.Drawing.Point(12, 40)
		Me.label5.Name = "label5"
		Me.label5.Size = New System.Drawing.Size(127, 16)
		Me.label5.TabIndex = 4
		Me.label5.Text = "Allowing Error:"
		'
		'TextBox_AllowingError
		'
		Me.TextBox_AllowingError.Location = New System.Drawing.Point(170, 37)
		Me.TextBox_AllowingError.Name = "TextBox_AllowingError"
		Me.TextBox_AllowingError.Size = New System.Drawing.Size(110, 21)
		Me.TextBox_AllowingError.TabIndex = 5
		Me.TextBox_AllowingError.Text = "0.25"
		Me.TextBox_AllowingError.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'Analyzer
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(292, 234)
		Me.Controls.Add(Me.TextBox_AllowingError)
		Me.Controls.Add(Me.label5)
		Me.Controls.Add(Me.groupBox1)
		Me.Controls.Add(Me.Button_Apply)
		Me.Controls.Add(Me.TextBox_Silence)
		Me.Controls.Add(Me.label1)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
		Me.MaximizeBox = false
		Me.MinimizeBox = false
		Me.Name = "Analyzer"
		Me.ShowInTaskbar = false
		Me.Text = "Analyzer"
		Me.TopMost = true
		AddHandler Load, AddressOf Me.AnalyzerLoad
		Me.groupBox1.ResumeLayout(false)
		Me.groupBox1.PerformLayout
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private TextBox_AllowingError As System.Windows.Forms.TextBox
	Private label5 As System.Windows.Forms.Label
	Private label2 As System.Windows.Forms.Label
	Private Alg_Window_From As System.Windows.Forms.TextBox
	Private label3 As System.Windows.Forms.Label
	Private Alg_Window_To As System.Windows.Forms.TextBox
	Private label4 As System.Windows.Forms.Label
	Private Alg_SelfCorrelation As System.Windows.Forms.RadioButton
	Private Alg_SelfDifference As System.Windows.Forms.RadioButton
	Private groupBox1 As System.Windows.Forms.GroupBox
	Private Button_Apply As System.Windows.Forms.Button
	Private TextBox_Silence As System.Windows.Forms.TextBox
	Private label1 As System.Windows.Forms.Label
End Class
