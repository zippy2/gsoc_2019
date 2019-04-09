/*
 * exercise.h: Some useful exports
 */

#pragma once

/**
 * efree:
 * @ptrptr: pointer to pointer for address of memory to be freed
 *
 * Release the chunk of memory in the pointer pointed to by
 * the 'ptrptr' variable. After release, 'ptrptr' will be
 * updated to point to NULL.
 */
void efree(void *ptrptr);

#define EFREE(ptr) efree(&ptr)

/**
 * AUTOFREE:
 * @type: type of the variable to be freed automatically
 *
 * Macro to automatically free the memory allocated to
 * the variable declared with it by calling efree
 * when the variable goes out of scope.
 */
#define AUTOFREE(type) __attribute__((cleanup(efree))) type
