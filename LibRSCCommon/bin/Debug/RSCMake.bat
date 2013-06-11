@echo The name of the RSC file:
@Set /P filename=
RSCCommon.exe -rsc %filename% -format Z:\formated.rsc -cdt HMCHNDICT.cdt -cvs x.cvs -q
copy x.cvs ..\..\..\LibCVE\bin\Debug\x.cvs
pause