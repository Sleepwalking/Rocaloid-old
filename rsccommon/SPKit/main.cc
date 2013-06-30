#include "structure/array.h"
#include "structure/string.h"
#include "misc/listopr.h"
#include "defs.h"
#include "io/fileStream.h"
#include "io/memoryStream.h"
#include "io/terminal.h"
#include "misc/converter.h"

using namespace converter;
int main()
{
	void* membuffer = malloc(65536);
	memoryStream mem(membuffer);

	mem.setPosition(0);
	mem.write(CStr("blah blah blah"));
	mem.write(CStr("blah blah blah"));
	mem.write('a');
	mem.write('a');
	mem.write('a');
	mem.write('a');
	mem.write('a');
	mem.write('a');
	mem.write(CByte(0));
	mem.writeChars("Bloody blah~");

	mem.setPosition(5);
	wLine(mem.readString());
	wLine(mem.readString());
	wLine(mem.readString());
	wLine(mem.readString());
	wLine(mem.readString());
	
	free(membuffer);
	return 0;
}
