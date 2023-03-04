#include "envhelper.h"

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// LOCAL PROTOTYPES

char **_envstr_to_evnvars(const char *env_str, size_t *varcount);
size_t _str_getlinecnt(const char *str);

// IMPLEMENTATIONS

int readff(const char *name, char buffer[], size_t buffer_size)
{
    if(buffer == NULL)
    {
        return 0;
    }

    FILE *fp = fopen(name, "rb");
    if(!fp)
    {
        return 0;
    }

    // Getting the size of the file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Making sure the buffer_size is great enough for null-terminator
    if(size >= buffer_size)
    {
        fclose(fp);
        return 0;
    }

    size_t count = fread(buffer, sizeof(char), buffer_size, fp);
    if(count != size)
    {
        fclose(fp);
        return 0;
    }
    buffer[count] = '\0';

    fclose(fp);
    return 1;
}

int env_str_hndlr(const char *env_str)
{
    size_t count;
    char **vars = _envstr_to_evnvars(env_str, &count);
    if(count == 0)
        return 0;

    for(size_t i = 0; i < count; i++)
    {
        putenv(vars[i]);
    }
    free(vars);

    return 1;
}
            
// LOCAL IMPLEMENTATIONS
char **_envstr_to_evnvars(const char *env_str, size_t *varcount)
{
    size_t len = strlen(env_str);
    size_t lines = 0;
    if(len == 0)
    {
        *varcount = 0;
        return NULL;
    }
    if(env_str[0] == '\n') 
    {
        *varcount = 0;
        return NULL;
    }

    lines = _str_getlinecnt(env_str);
    if(lines == 0) 
    {
        *varcount = 0;
        return NULL;
    }

    // lexing the env strings
    char buffer[256] = {0};
    int buff_index = 0;
    int str_index = 0;
    size_t counted_lines = 0;
    size_t cur_var_index = 0;
    char **env_vars = malloc(sizeof(char*) * lines);
    while(str_index < len+1)
    {
        if(counted_lines >= lines)
            break;

        if(env_str[str_index] == '\n' || env_str[str_index] == '\0')
        {
            buffer[buff_index++] = '\0';
            buff_index = 0;

            env_vars[cur_var_index] = calloc(strlen(buffer)+1, 1);
            strncpy(env_vars[cur_var_index++], buffer, strlen(buffer));

            counted_lines++;
            str_index++;
        }

        buffer[buff_index++] = env_str[str_index++];
    }

    *varcount = lines;
    return env_vars;
}

size_t _str_getlinecnt(const char *str)
{
    size_t len = strlen(str);
    size_t lines = 0;
    if(len == 0)
        return 0;

    lines++;
    for(size_t i = 0; i <= len; i++)
    {
        int cur = str[i];
        if(i > 0)
        {
            char prev = str[i-1];
            if(
                (prev == '\n' && cur == '\n') || 
                (prev == '\n' && cur == '\0'))
            {
                lines--;
                break;
            }
        }

        if(cur == '\n') lines++;
    }
    
    return lines;
}
