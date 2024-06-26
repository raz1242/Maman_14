#ifndef CPU_H
#define CPU_H

#endif //CPU_H
/********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/*
typedef struct FileCount {
    char *filename;
    int count;
    struct FileCount *next;
} FileCount;


typedef struct {
    FileCount *heads[MAX_VALUE + 1];
} HashTable;
*/
typedef uint16_t reg15_t;

typedef struct {
    reg15_t r0 : 15;
    reg15_t r1 : 15;
    reg15_t r2 : 15;
    reg15_t r3 : 15;
    reg15_t r4 : 15;
    reg15_t r5 : 15;
    reg15_t r6 : 15;
    reg15_t r7 : 15;
} RegisterArray;

typedef struct {

}PSW;