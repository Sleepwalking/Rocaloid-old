#include "structure/array.h"
#include "structure/string.h"
#include "misc/listopr.h"
#include "misc/converter.h"
#include "misc/memopr.h"
#include "io/fileStream.h"
#include "io/stringStream.h"
#include "io/memoryStream.h"
#include "io/terminal.h"
#include "defs.h"
using namespace converter;
int main()
{
	void* membuffer = mem_malloc(655360);
	textStream fs;
	fs.open("/tmp/HMCHNDICT.cdt", READONLY);
	fs.readBuffer(membuffer, 1000);
	
	stringStream ss(membuffer);
	ss.setPosition(0);
	
	lfor(i, 20, wr(ss.readWord() + CStr("]")););
	
	mem_free(membuffer);
	fs.close();
	
	return 0;
}
