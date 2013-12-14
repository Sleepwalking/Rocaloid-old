#ifndef FILEPATH_H
#define FILEPATH_H

#include "../Structure/String.h"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

extern void GetFileName(String* Dest, String* Path);
extern void GetFileDir(String* Dest, String* Path);

#endif
