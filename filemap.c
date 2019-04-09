/**
 * filemap.c: Implementation
 */

#include <stdlib.h>
#include <string.h>

#include "filemap.h"
#include "exercise.h"

/**************************************************************
 *
 *            ====== What are sparse files? ======
 *
 * The FileMap module exists for keeping map of allocated blocks
 * of a file. Under Linux a file doesn't have to be fully
 * allocated, there can be some 'holes' within. For instance, if
 * a file has apparent size of 100 units and only first 10 store
 * actual data the file would look like this (not to scale):
 *
 *   0      10                                                99
 *   +------+-------------------------------------------------+
 *   | data |                       hole                      |
 *   +------+-------------------------------------------------+
 *
 * Note that offsets start from zero and thus offset 0 is a valid
 * offset. 9th block belongs to data section and hole starts at
 * 10th block.
 *
 * If an application opens the file and reads from 'hole' it
 * would read all zeroes. An attempt to write inside a hole
 * splits this into two and creates a data section. In our
 * example, if an application would write 25 blocks at offset 50
 * the file would look like this:
 *
 *   0      10               50               75              99
 *   +------+----------------+----------------+---------------+
 *   | data |      hole      |      data      |     hole      |
 *   +------+----------------+----------------+---------------+
 *
 * Writing into a data section doesn't create any new section.
 * However, there is a syscall for so called 'hole punching'. If
 * a data section (or a part of it) is no longer needed, punching
 * a hole creates a hole section. In our example, if an
 * application would punch a hole of size 5 at offset 60 then the
 * file would look like this:
 *
 *   0      10             50     60     65     75             99
 *   +------+--------------+------+------+------+--------------+
 *   | data |     hole     | data | hole | data |     hole     |
 *   +------+--------------+------+------+------+--------------+
 *
 * Please note that if there are two or more consecutive sections
 * of the same type they are joined together. For instance,
 * writing 5 block at offset 60 would turn the hole in the middle
 * into a data section, leaving us with three consecutive data
 * sections. These are then joined into one and the resulting map
 * would look like in the previous picture.
 *
 * Typical use case of sparse files are disks for virtual
 * machines. A file that represents a virtual machine disk can be
 * allocated sparsly and as OS in the VM writes and erases blocks
 * data sections or holes are created.
 *
 * Point of FileMap module is to keep track of the file map so
 * that any application can get the current map of the file. This
 * can be useful for backup software because it can backup only
 * data sections and not holes so it manages space on backup
 * medium better.
 *
 *
 *          ====== What to implement? =====
 *
 * There are several APIs for you to implement. Each API (except
 * for FileMapInit() is given the FileMap structure as the first
 * argument. You can use it to store data and change it on API
 * calls accordingly.
 *
 * Typical use case is as follows:
 *
 *  FileMap *map;
 *  char *errStr = NULL;
 *
 *  if (!(map = FileMapInit(100)))
 *      error();
 *
 *  FileMapData(map, 0, 10);
 *  FileMapHole(map, 10, 40);
 *  FileMapData(map, 50, 10);
 *  FileMapHole(map, 60, 5);
 *  FileMapData(map, 65, 10);
 *
 *  FileMapCheckError(map, &errStr);
 *  if (errStr)
 *      error(errStr);
 *
 *  if (FileMapGetMap(map, &actualMap) < 0)
 *      error();
 *
 *  FileMapFree(map);
 *
 *
 * Calling FileMapInit() creates a new instance of given size. By
 * default, right after initialization the map is considered
 * empty and therefore has nothing but one hole section filling
 * up the whole file.
 *
 * This can be followed by calling FileMapData() or FileMapHole()
 * to create or update corresponding sections in the map. Just
 * like described in previous section. Hence, strictly speaking
 * those FileMapHole() calls above are not necessary and if
 * removed the map would still look the same.
 *
 * Note that neither of FileMapData() nor FileMapHole() APIs can
 * return an error. Should any error occur in them it has to be
 * saved into FileMap structure and reported only when
 * FileMapCheckError() or FileMapGetMap() is called.
 *
 * As advertised, FileMapCheckError() sets passed pointer to
 * stringified error (caller is responsible for freeing the
 * string later). It's okay if your implementation doesn't need
 * this. Just set the pointer to NULL to indicate there's no
 * error and carry on.
 *
 * And finally. FileMapGetMap() returns stringified
 * representation of the current state of the map. Note that it
 * can be called several times and there can be more FileMap*()
 * calls in between each run. The stringified representation
 * consists of the following line repeating for each section in
 * the map:
 *
 *   $section: $length\n
 *
 * where $section is one of "data" or "hole", and $length then
 * tells how long the section is. Note that because of joining
 * sections of the same type as described above there can never
 * be two sections of the same type followed one by the other,
 * i.e. two data sections or two holes next to each other.
 */

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
