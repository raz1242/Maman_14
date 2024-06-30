#ifndef ASSEMBLER_STAGE_0_H
#define ASSEMBLER_STAGE_0_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MIN_LENGTH_OF_MACRO_BODY 1
#define MAX_LENGTH_OF_MACRO_BODY 100
#define MAX_LENGTH_OF_MACRO_HEADER 30

const char* reserved_words[] = {
    "mov", "cmp", "add", "sub", "lea", "not", "clr", "inc",
    "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop",
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
};

typedef struct {
    char *name;
    char *content;
} macro;

typedef struct {
    macro *array;
    int rep;
    int length;
} macro_array;

enum {
    HEADER,
    BODY,
    END,
    REGULAR
};


char* firstNonSpaceCharacter(char* s);
int macroLocation(const char *str, int flag, int cmd_length);
void process_assembly_file(char line[]);
void macroArrayAllocator(macro_array *arr, int size);
int macroArrayAdd(macro_array *arr, const char* name, const char* body);
int firstWordLengthCounter(const char *str);
int isEndOfStr(char *str);
int isReservedWord(char* word, int length);

#endif //ASSEMBLER_STAGE_0_H