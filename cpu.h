#ifndef CPU_H
#define CPU_H

#endif //CPU_H
/********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define COMMANDS_TABLE_SIZE 16

typedef uint16_t reg15_t;

typedef struct Command {
    char *key;
    int value;
    struct Command *next;
} Command;

typedef struct {
    Command **entries;
} HashTable;