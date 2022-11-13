# Env Variables Helper
Een kleine helper om een bestand uit te lezen met env variables, om deze vervolgens in geheugen te schrijven.

## Gebruik
Stel je voor, je hebt een `.env` bestand met env variables. Kans is groot dat je deze wilt inlezen voor runtime. Daar is dit precies voor:

```C
...
#include "env/envhelper.h"
#define BUF_SIZE 1024
...
...

char buffer[BUF_SIZE] = {0};
/* 
    Read the content of the ".env" file
    into buffer "buffer" with a length of
    "BUF_SIZE". 
*/
if(!readff(".env", buffer, BUF_SIZE))
    return
/* Put the content-string into the env variables. */
if(!env_str_hndlr(buffer))
    return;

/* Do what you need to do with the env's */
...
```  

## Allocation Info
De `env_str_hndlr()` maakt wel gebruik van heap-allocation. Ik heb zoveel mogelijk geprobeerd alles op de `stack` te houden, alleen is de hoeveelheid env-vars die toegevoegd gaan worden onbekend. Gelukkig hoef je niet zelf om te gaan met dit geheugen, want als je naar de implementation gaat kijken, doet deze dit voor je.