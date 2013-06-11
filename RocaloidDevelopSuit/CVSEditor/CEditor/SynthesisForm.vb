'    点下“Synthesis”后出现的窗口。
'    The dialog that appears after clicking "Synthesis".
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

Public Partial Class SynthesisForm
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Sub UpdateTimerTick(sender As Object, e As EventArgs)
		Synthesis_Bar.Value = Math.Min(100, CInt(100 * (CybervoiceEngine.MixerWriterEffector.WriterCounter / CybervoiceEngine.MixerWriterEffector.TotalCount) + 0.5))
		Synthesis_State.Text = CSng(CybervoiceEngine.MixerWriterEffector.WriterCounter / 96000) & " sec / " & CSng(CybervoiceEngine.MixerWriterEffector.TotalCount / 96000) & " sec."
		If Synthesis_Bar.Value >= 100 Then
			Me.Hide()
		End If
	End Sub
End Class
