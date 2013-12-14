#ifndef FILEUTIL_H
#define FILEUTIL_H

#include "../Structure/String.h"
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C"{
#endif

extern int GetFileExistence(String* Path);
extern time_t GetLastModifyTime(String* Path);
extern int64_t GetFileLength(String* Path);

extern int64_t LoadFileAll(void* Dest, String* Path);
extern int64_t LoadFileRange(void* Dest, String* Path, int64_t Start, int64_t End);
extern int WriteFileAll(String* Path, void* Src, int64_t size);

extern int LoadWaveAll(float* Dest, String* Path);
extern int WriteWaveAll(String* Dest, float* Src, int Size, int SampleRate);

#ifdef __cplusplus
}
#endif
#endif
