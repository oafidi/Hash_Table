#ifndef HASH_TABLE_H
# define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Case
{
    char *key;
    char *value;
    struct Case *next;
}   Case;

#endif