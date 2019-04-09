/*
 * filemap.h: Exported API
 */

#pragma once

#include <sys/types.h>

typedef struct _FileMap FileMap;

FileMap *FileMapInit(off_t size);

void FileMapFree(FileMap *map);

void FileMapData(FileMap *map, off_t off, off_t len);
void FileMapHole(FileMap *map, off_t off, off_t len);
void FileMapCheckError(FileMap *map, char **errStr);
int FileMapGetMap(FileMap *map, char **mapStr);
