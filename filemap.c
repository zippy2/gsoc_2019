/**
 * filemap.c: Implementation
 */

#include <stdlib.h>
#include <string.h>

#include "filemap.h"
#include "exercise.h"

struct _FileMap {
    unsigned int dummy;
};


FileMap *
FileMapInit(off_t size)
{
    return NULL;
}


void
FileMapFree(FileMap *map)
{
}


void
FileMapData(FileMap *map, off_t off, off_t len)
{
}


void
FileMapHole(FileMap *map, off_t off, off_t len)
{
}


void
FileMapCheckError(FileMap *map, char **errStr)
{
}


int
FileMapGetMap(FileMap *map, char **mapStr)
{
    return -1;
}
