#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "env/envhelper.h"

#define ENV_FILE_NAME "./src/.env"
#define BUFFER_SIZE 1024

int main(void)
{
    // environment buffer
    char envstr[BUFFER_SIZE] = {0};
    
    // read the ".env" file into the buffer
    if(!readff(ENV_FILE_NAME, envstr, BUFFER_SIZE))
    {

        fprintf(stderr, "Something went wrong handling the \"%s\" file\n", ENV_FILE_NAME);
        return EXIT_FAILURE;
    }

    printf("buffer: \n%s\n\n", envstr);
    env_str_hndlr(envstr);
    char *exmp = getenv("EXAMPLE");
    char *key = getenv("KEY");
    printf("EXAMPLE=%s\n", exmp);
    printf("KEY=%s\n", key);

    return EXIT_SUCCESS;
}
