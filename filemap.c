/**
 * filemap.c: Implementation
 */

#include <stdlib.h>
#include <string.h>

#include "filemap.h"
#include "exercise.h"

struct _FileMap {
    /* TODO: Put something useful here and remove 'dummy' */
    unsigned int dummy;
};


/**
 * FileMapInit:
 * @size: number of blocks
 *
 * Returns an allocated and initialized FileMap. By default, any
 * empty file map is considered having one hole throughout the
 * whole file.
 *
 * Returns: allocated map on success, or
 *          NULL on failure.
 */
FileMap *
FileMapInit(off_t size)
{
    return NULL;
}


/**
 * FileMapFree:
 * @map: a file map
 *
 * Free a perviously allocated file map.
 * This is a NO-OP if @map is NULL.
 */
void
FileMapFree(FileMap *map)
{
}


/**
 * FileMapData:
 * @map: a file map
 * @off: offset since the begging of @map
 * @len: length of data section
 *
 * Marks a data section in a file map. The section starts at
 * offset @off from the beginning of the file (and thus the file
 * @map too) and is @len units long. It is considered an error if
 * @off or @off + @len falls out of file (as specified in
 * FileMapInit).
 */
void
FileMapData(FileMap *map, off_t off, off_t len)
{
}


/**
 * FileMapHole:
 * @map: a file map
 * @off: offset since the beggining of @map
 * @len: length of hole section
 *
 * Marks a hole in a file map. The hole starts at offset @off and
 * is @len units long. It is considered an error if @off or @off
 * + @len falls out of file (as specified in FileMapInit).
 */
void
FileMapHole(FileMap *map, off_t off, off_t len)
{
}


/**
 * FileMapCheckError:
 * @map: a file map
 * @errStr: error message
 *
 * Returns any error that might have ocurred earlier.
 * If there was none errStr is set to NULL.
 * It's a caller's responsibility to free the returned string
 * once no longer needed.
 */
void
FileMapCheckError(FileMap *map, char **errStr)
{
}


/**
 * FileMapGetMap:
 * @map: a file map
 * @mapStr: string representation of the @map
 *
 * Creates a string representation of @map and saves it into
 * @mapStr. The string has the following form:
 *
 *   $section: $length\n
 *
 * where $section is "data" for a data section, or "hole" for a
 * hole section. The $length is then computed $length of
 * $section. The line repeats for every section in the map.
 *
 * Caller is responsible for freeing @mapStr.
 *
 * Returns: 0 on success,
 *         -1 otherwise.
 */
int
FileMapGetMap(FileMap *map, char **mapStr)
{
    return -1;
}
