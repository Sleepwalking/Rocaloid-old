'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class Console
	Public Shared Log As String = ""
	Public Shared LogLen As Integer = 100000
	Public Sub Send(ByVal String_ As String)
		If Log.Length > LogLen Then
			Log = ""
		End If
		Log = Log & String_ & Chr(13) & Chr(10)
	End Sub
	Public Sub SendInput(ByVal String_ As String)
		Send("> " & String_)
		String_ = String_.ToLower()
		If Mid(String_, 1, 4) = "setl" Then
			LogLen = CInt(Mid(String_, 6, 100))
			Send("  Buffer length was set to " & LogLen & ".")
			Exit Sub
		End If
		Select Case String_
			Case "clear"
				Log = "  Log Cleared."
			Case Else
				Send("  Undefined Instruction.")
		End Select
	End Sub
	Public Sub New()
		Me.InitializeComponent()
	End Sub
	
	Sub ConsoleLoad(sender As Object, e As EventArgs)
		ConsoleBox.Text = Log
	End Sub
	
	Sub Button_SendClick(sender As Object, e As EventArgs)
		SendInput(ConsoleInput.Text)
		ConsoleInput.Text = ""
	End Sub
	
	Sub ConsoleUITimerTick(sender As Object, e As EventArgs)
		Try
			ConsoleBox.Text = Log
		Catch
		End Try
	End Sub
End Class
