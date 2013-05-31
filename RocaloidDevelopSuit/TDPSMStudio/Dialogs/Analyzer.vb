'    拆帧器的设定对话框
'    Setting Dialog for frame analyzer.
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

Public Partial Class Analyzer
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Sub Button_ApplyClick(sender As Object, e As EventArgs)
		Setting_SilentThreshold = CDbl(TextBox_Silence.Text)
		Setting_AllowingError = CDbl(TextBox_AllowingError.Text)
		If Alg_SelfCorrelation.Checked Then
			Setting_Algorism = Algorism.Correlation
		Else
			Setting_Algorism = Algorism.Difference
		End If
		Setting_SearchWindow_Low = CDbl(Alg_Window_From.Text)
		Setting_SearchWindow_High = CDbl(Alg_Window_To.Text)
	End Sub
	
	Sub AnalyzerLoad(sender As Object, e As EventArgs)
		TextBox_Silence.Text = CStr(Setting_SilentThreshold)
		TextBox_AllowingError.Text = CStr(Setting_AllowingError)
		Alg_SelfCorrelation.Checked = False
		Alg_SelfDifference.Checked = False
		If Setting_Algorism = Algorism.Correlation Then
			Alg_SelfCorrelation.Checked = True
		End If
		If Setting_Algorism = Algorism.Difference Then
			Alg_SelfDifference.Checked = True
		End If
		Alg_Window_From.Text = CStr(Setting_SearchWindow_Low)
		Alg_Window_To.Text = CStr(Setting_SearchWindow_High)
	End Sub
End Class
