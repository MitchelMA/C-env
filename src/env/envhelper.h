#ifndef __IOHELP_H__
#define __IOHELP_H__

#include <stddef.h>

/**
 * @brief Safely read file content into a buffer
 * @param name Name of the File
 * @param buffer The string buffer the content gets read into
 * @param buffer_size The size of the buffer
*/
int readff(const char *name, char buffer[], size_t buffer_size);

/**
 * @brief Handles an env string to put into the environment variables
 * @param env_str The env string
 * @param size The length of the env string
*/
int env_str_hndlr(const char* env_str);


#endif // __IOHELP_H__
