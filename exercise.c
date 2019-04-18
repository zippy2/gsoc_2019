#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "exercise.h"
#include "filemap.h"

#define ERROR(...) \
    do { \
        fprintf(stderr, "ERROR %s:%d : ", __func__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while (0)

#define ANSI_COLOR_RED     "\x1b[91m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void
efree(void *ptrptr)
{
    int savedErrno = errno;

    free(*(void **)ptrptr);
    *(void **)ptrptr = NULL;

    errno = savedErrno;
}

typedef enum {
    DATA,
    HOLE
} testOperation;


typedef struct {
    int op;
    off_t off;
    off_t len;
} test_op;


static int
do_test_ops(off_t size,
            const char *expectedMap,
            test_op *ops[])
{
    FileMap *map = NULL;
    AUTOFREE(char *) errStr = NULL;
    AUTOFREE(char *) actualMap = NULL;
    size_t i;
    int ret = -1;

    if (!(map = FileMapInit(size))) {
        ERROR("Failed to init file map");
        return -1;
    }

    for (i = 0; ops[i]; i++) {
        test_op *o = ops[i];

        switch ((testOperation) o->op) {
        case DATA:
            FileMapData(map, o->off, o->len);
            break;
        case HOLE:
            FileMapHole(map, o->off, o->len);
            break;

         default:
            ERROR("Uknown operation %d", o->op);
            abort();
        }
    }

    FileMapCheckError(map, &errStr);
    if (errStr) {
        ERROR("FileMapCheckError returned: %s", errStr);
        goto cleanup;
    }

    if (FileMapGetMap(map, &actualMap) < 0) {
        ERROR("FileMapGetMap returned error");
        goto cleanup;
    }

    if (!actualMap ||
        strcmp(actualMap, expectedMap) != 0) {
        ERROR("Expected map: '%s'\nActual map: '%s'", expectedMap, actualMap);
        goto cleanup;
    }

    ret = 0;
 cleanup:
    FileMapFree(map);
    return ret;
}


int main(int argc, char *argv[])
{
    int ret = EXIT_FAILURE;
    unsigned long testcnt = 1;

#define DO_TEST(size, map, ...) \
    do { \
        test_op *ops[] = {__VA_ARGS__, NULL}; \
        int rc; \
\
        rc = do_test_ops(size, map, ops); \
        printf("Test %lu: %s\n", testcnt, \
               rc == 0 ? ANSI_COLOR_GREEN "Success" ANSI_COLOR_RESET: \
                         ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET); \
\
        if (rc < 0) \
            ret = EXIT_FAILURE; \
\
        testcnt++; \
    } while (0)

#define HOLE(offset, length) \
    &(test_op) {.op = HOLE, .off = offset, .len = length }

#define DATA(offset, length) \
    &(test_op) {.op = DATA, .off = offset, .len = length }

    DO_TEST(10, "hole: 10\n", NULL);
    DO_TEST(10, "data: 10\n", DATA(0, 10));
    DO_TEST(20, "hole: 10\n"
                "data: 10\n", DATA(10, 10));
    DO_TEST(50, "data: 10\n"
                "hole: 10\n"
                "data: 10\n"
                "hole: 10\n"
                "data: 10\n", DATA(0, 50), HOLE(10, 10), HOLE(30, 10));

    return ret;
}
