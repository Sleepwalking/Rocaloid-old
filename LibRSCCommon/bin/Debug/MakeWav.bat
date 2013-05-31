@echo The name of the Vocaloid3 Project file:
@Set /P filename=
RSCCommon.exe -vsqx %filename% -cvsqx -format Z:\formated.rsc -cdt HMCHNDICT.cdt -cvs x.cvs -q
copy x.cvs ..\..\..\..\CVE1.6\CybervoiceEngine\bin\Debug\x.cvs
cd E:\DSync\Dropbox\RocaBeautiful\CVE1.6\CybervoiceEngine\bin\Debug\
Call make.bat
pause