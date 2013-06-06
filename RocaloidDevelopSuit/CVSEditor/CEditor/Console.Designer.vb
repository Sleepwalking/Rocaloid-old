'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class Console
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
		Me.ConsoleBox = New System.Windows.Forms.TextBox()
		Me.ConsoleInput = New System.Windows.Forms.TextBox()
		Me.Button_Send = New System.Windows.Forms.Button()
		Me.ConsoleUITimer = New System.Windows.Forms.Timer(Me.components)
		Me.SuspendLayout
		'
		'ConsoleBox
		'
		Me.ConsoleBox.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.ConsoleBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
		Me.ConsoleBox.CausesValidation = false
		Me.ConsoleBox.Location = New System.Drawing.Point(12, 12)
		Me.ConsoleBox.Multiline = true
		Me.ConsoleBox.Name = "ConsoleBox"
		Me.ConsoleBox.ReadOnly = true
		Me.ConsoleBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
		Me.ConsoleBox.ShortcutsEnabled = false
		Me.ConsoleBox.Size = New System.Drawing.Size(433, 254)
		Me.ConsoleBox.TabIndex = 1
		Me.ConsoleBox.TabStop = false
		'
		'ConsoleInput
		'
		Me.ConsoleInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
		Me.ConsoleInput.Location = New System.Drawing.Point(12, 272)
		Me.ConsoleInput.Name = "ConsoleInput"
		Me.ConsoleInput.Size = New System.Drawing.Size(386, 21)
		Me.ConsoleInput.TabIndex = 0
		'
		'Button_Send
		'
		Me.Button_Send.FlatStyle = System.Windows.Forms.FlatStyle.Flat
		Me.Button_Send.Location = New System.Drawing.Point(403, 272)
		Me.Button_Send.Name = "Button_Send"
		Me.Button_Send.Size = New System.Drawing.Size(42, 21)
		Me.Button_Send.TabIndex = 2
		Me.Button_Send.Text = "Send"
		Me.Button_Send.UseVisualStyleBackColor = true
		AddHandler Me.Button_Send.Click, AddressOf Me.Button_SendClick
		'
		'ConsoleUITimer
		'
		Me.ConsoleUITimer.Enabled = true
		AddHandler Me.ConsoleUITimer.Tick, AddressOf Me.ConsoleUITimerTick
		'
		'Console
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(457, 303)
		Me.Controls.Add(Me.Button_Send)
		Me.Controls.Add(Me.ConsoleInput)
		Me.Controls.Add(Me.ConsoleBox)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow
		Me.Name = "Console"
		Me.Text = "Console"
		AddHandler Load, AddressOf Me.ConsoleLoad
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private ConsoleUITimer As System.Windows.Forms.Timer
	Private Button_Send As System.Windows.Forms.Button
	Private ConsoleInput As System.Windows.Forms.TextBox
	Private ConsoleBox As System.Windows.Forms.TextBox
End Class
