'    将语音信号分割成语音帧
'    Cutting voice wave into frames.
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

Public Class SearchFrame
	Public Shared Function ForwardSearch(ByRef ForwardLength() As Integer, ByRef Wave As WaveBuffer, _
										 ByVal StartPosition As Integer, ByVal BasePeriod As Integer, _
										 ByVal Length As Integer) As SearchResult
		Dim i As Integer, position As Integer, lastposition As Integer
		Dim EstimatedPeriod As Integer
		Dim ret As SearchResult
		position = StartPosition
		EstimatedPeriod = BasePeriod
		i = 0
		While Math.Abs(BasePeriod - EstimatedPeriod) < BasePeriod * Setting_AllowingError AndAlso position < StartPosition + Length 
			lastposition = position
			position = ZeroPass_FindNext(Wave, position, EstimatedPeriod)
			EstimatedPeriod = position - lastposition
			ForwardLength(i) = EstimatedPeriod
			i += 1
		End While
		ret.Num = i - 2
		ret.Position = lastposition
		Return ret
	End Function
	Public Shared Function BackwardSearch(ByRef BackwardLength() As Integer, ByRef Wave As WaveBuffer, _
										  ByVal StartPosition As Integer, ByVal BasePeriod As Integer) As SearchResult
		Dim i As Integer, position As Integer, lastposition As Integer
		Dim EstimatedPeriod As Integer
		Dim ret As SearchResult
		position = StartPosition
		EstimatedPeriod = BasePeriod
		i = 0
		While Math.Abs(BasePeriod - EstimatedPeriod) < BasePeriod * Setting_AllowingError
			lastposition = position
			position = ZeroPass_FindBack(Wave, position, EstimatedPeriod)
			EstimatedPeriod = lastposition - position
			BackwardLength(i) = EstimatedPeriod
			i += 1
			If Wave.GetMax(position - BasePeriod, position) - Wave.GetMin(position - BasePeriod, position) < 0.005 Then
				Exit While
			End If
		End While
		ret.Num = i - 2
		ret.Position = lastposition
		Return ret
	End Function
	Public Shared Function BackwardFill(ByRef Wave As WaveBuffer, _
										ByVal StartPosition As Integer, _
										ByVal BasePeriod As Integer) As SearchResult
		Dim i As Integer = 0
		Dim position As Integer = StartPosition
		Dim ret As SearchResult
		Dim SilenceBreakPos As Integer = FindSilenceBreakPos(Wave)
		While position > SilenceBreakPos
			position -= BasePeriod
			i += 1
		End While
		If position < 0 Then position = 0
		ret.Num = i
		ret.Position = position
		Return ret
	End Function
	Public Shared Function ZeroPass_FindNext(ByRef Wave As WaveBuffer, _
										   	 ByVal StartPosition As Integer, _
										   	 ByVal BasePeriod As Integer) As Integer
		Dim i As Integer
		Dim score As Double
		Dim record As Double = -999
		Dim position As Integer
		Dim fromi As Integer, toi As Integer
		fromi = StartPosition + CInt(BasePeriod * Setting_SearchWindow_Low)
		toi = StartPosition + CInt(BasePeriod * Setting_SearchWindow_High)
		For i = fromi To toi
			If (Wave.Data(i - 1) > 0 AndAlso Wave.Data(i) < 0) OrElse _
			   (Wave.Data(i) > 0 AndAlso Wave.Data(i - 1) < 0) Then
				If Setting_Algorism = Algorism.Correlation Then _
					score = Analysis.SelfCorrelation(Wave, StartPosition, i - StartPosition, BasePeriod)
				If Setting_Algorism = Algorism.Difference Then _
					score = - Analysis.SelfDifference(Wave, StartPosition, i - StartPosition, BasePeriod)
				If score > record Then
					record = score
					position = i
				End If
			End If
		Next
		Return position
	End Function
	Public Shared Function FindNext(ByRef Wave As WaveBuffer, _
									ByVal StartPosition As Integer, _
									ByVal BasePeriod As Integer) As Integer
		Dim i As Integer
		Dim score As Double
		Dim record As Double = -999
		Dim position As Integer
		Dim fromi As Integer, toi As Integer
		fromi = StartPosition + CInt(BasePeriod * Setting_SearchWindow_Low)
		toi = StartPosition + CInt(BasePeriod * Setting_SearchWindow_High)
		For i = fromi To toi
			If Setting_Algorism = Algorism.Correlation Then _
				score = Analysis.SelfCorrelation(Wave, StartPosition, i - StartPosition, BasePeriod)
			If Setting_Algorism = Algorism.Difference Then _
				score = - Analysis.SelfDifference(Wave, StartPosition, i - StartPosition, BasePeriod)
			If score > record Then
				record = score
				position = i
			End If
		Next
		Return position
	End Function
	Public Shared Function ZeroPass_FindBack(ByRef Wave As WaveBuffer, _
										   	 ByVal StartPosition As Integer, _
										   	 ByVal BasePeriod As Integer) As Integer
		Dim i As Integer
		Dim score As Double
		Dim record As Double = -999
		Dim position As Integer
		Dim fromi As Integer, toi As Integer
		fromi = StartPosition - CInt(BasePeriod * Setting_SearchWindow_Low)
		toi = StartPosition - CInt(BasePeriod * Setting_SearchWindow_High)
		If fromi < 1 Then fromi = 1
		If toi < 1 Then toi = 1
		For i = toi To fromi
			If (Wave.Data(i - 1) > 0 AndAlso Wave.Data(i) < 0) OrElse _
			   (Wave.Data(i) > 0 AndAlso Wave.Data(i - 1) < 0) Then
				If Setting_Algorism = Algorism.Correlation Then _
					score = Analysis.SelfCorrelation(Wave, i, StartPosition - i, BasePeriod)
				If Setting_Algorism = Algorism.Difference Then _
					score = - Analysis.SelfDifference(Wave, i, StartPosition - i, BasePeriod)
				If score > record Then
					record = score
					position = i
				End If
			End If
		Next
		Return position
	End Function
	Public Shared Function FindBack(ByRef Wave As WaveBuffer, _
									ByVal StartPosition As Integer, _
									ByVal BasePeriod As Integer) As Integer
		Dim i As Integer
		Dim score As Double
		Dim record As Double = -999
		Dim position As Integer
		Dim fromi As Integer, toi As Integer
		fromi = StartPosition - CInt(BasePeriod * Setting_SearchWindow_Low)
		toi = StartPosition - CInt(BasePeriod * Setting_SearchWindow_High)
		For i = toi To fromi
			If Setting_Algorism = Algorism.Correlation Then _
				score = Analysis.SelfCorrelation(Wave, i, StartPosition - i, BasePeriod)
			If Setting_Algorism = Algorism.Difference Then _
				score = - Analysis.SelfDifference(Wave, i, StartPosition - i, BasePeriod)
			If score > record Then
				record = score
				position = i
			End If
		Next
		Return position
	End Function
	Public Shared Function FindVOT(ByRef Wave As WaveBuffer, _
								   ByVal StartPosition As Integer, _
								   ByVal BasePeriod As Integer) As Integer
		Dim SearchRsut As SearchResult
		Dim Frames(800) As Integer
		SearchRsut = BackwardSearch(Frames, Wave, StartPosition, BasePeriod)
		Return SearchRsut.Position
	End Function
	Public Shared Function FindStart(ByRef Wave As WaveBuffer, _
									 ByVal VOTPosition As Integer, _
									 ByVal BasePeriod As Integer) As Integer
		Dim SearchRsut As SearchResult
		SearchRsut = BackwardFill(Wave, VOTPosition, BasePeriod)
		Return SearchRsut.Position
	End Function
End Class
