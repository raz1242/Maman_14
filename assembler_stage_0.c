#include "assembler_stage_0.h"


void process_assembly_file(char line[]) {
    int i, codeLocationFlag = 0, firstWordOfStrLength, lineLocation;
    macro_array array;
    char macro_header[MAX_LENGTH_OF_MACRO_HEADER], macro_body[MAX_LENGTH_OF_MACRO_BODY];
    macro_header[0] = '\0', macro_body[0] = '\0';

    macroArrayAllocator(&array, MIN_LENGTH_OF_MACRO_BODY);

    while (fgets(line, 80, stdin)) {
        char *main_line = firstNonSpaceCharacter(line);
        firstWordOfStrLength = firstWordLengthCounter(line);
        lineLocation = macroLocation(line, codeLocationFlag, firstWordOfStrLength);

        if (lineLocation == HEADER) {
            codeLocationFlag = 1;
            main_line += firstWordOfStrLength;
            firstWordOfStrLength = firstWordLengthCounter(firstNonSpaceCharacter(main_line));
            strncpy(macro_header, main_line, firstWordOfStrLength);
            *(macro_header + firstWordOfStrLength) = '\n';

            if (isReservedWord(macro_header, firstWordOfStrLength)) {
                //PRINT_MESSAGE(ERROR_MSG_TYPE, ERROR_INVALID_MACRO_NAME);
                //free_macro_array(&array);
                return;
            }
        }
        else if (lineLocation == BODY) {
            strncat(macro_body, line, strlen(line) + 1);
        }
        else if (lineLocation == END) {
            macroArrayAdd(&array, macro_header, macro_body);
            macro_body[0] = 0;
            codeLocationFlag = 0;
        }
        /*else {
            replaced_flag = 0;


            for (i = 0; i < array.rep; i++) {
                if (strncmp(main_line, array.array[i].name, firstWordOfStrLength) == 0 &&
                    isEndOfStr(main_line + firstWordOfStrLength)) {
                    replaced_flag = TRUE;
                    fputs(array.array[i].content, am_file);
                    break;
                    }
            }
            if (!replaced_flag)
                fputs(line, am_file);
        }*/
    }
}


/* moves string to the beginning of the code */
char* firstNonSpaceCharacter(char* s) {
    int n;
    for (n = 0; *(s + n) != 0 && (s[n] == ' ' || s[n] == '\t'); n++) {}
    return s + n;
}

void macroArrayAllocator(macro_array *arr, int size) {
    arr->array = malloc(size * sizeof(macro));
    if (arr->array == NULL) {
        //PRINT_MESSAGE(ERROR_MSG_TYPE, ERROR_FAILED_TO_ALLOCATE_MEM);
        free(arr->array);
        exit(1);
    }
    arr->rep = 0;
    arr->length = size;
}


int macroArrayAdd(macro_array* arr, const char* name, const char* body) {
    void *temp;
    if (arr->rep == arr->length) {
        arr->length = (arr->length) * 2;
        temp = realloc(arr->array, arr->length * sizeof(macro));

        if (!temp) {
            //PRINT_MESSAGE(ERROR_MSG_TYPE, ERROR_FAILED_TO_REALLOCATE_MEM);
            exit(EXIT_FAILURE);
        }
        arr->array = (macro*)temp;
    }

    arr->array[arr->rep].name = malloc(strlen(name) + 1);
    arr->array[arr->rep].content = malloc(strlen(body) + 1);
    if (!arr->array[arr->rep].content || !arr->array[arr->rep].name) {
        //PRINT_MESSAGE(ERROR_MSG_TYPE, ERROR_FAILED_TO_ALLOCATE_MEM);
        free(arr->array[arr->rep].name);
        free(arr->array[arr->rep].content);

        exit(EXIT_FAILURE);
    }
    strcpy(arr->array[arr->rep].name, name);
    strcpy(arr->array[arr->rep].content, body);
    arr->rep++;
    return 0;
}


int macroLocation(const char *str, int flag, int cmd_length) {
    if (strncmp(str, "macr", strlen("macr")) == 0 && str[4] && str[4] == ' ')
        return HEADER;
    if (flag && strncmp(str, "endmacr", cmd_length) != 0)
        return BODY;
    if (flag && strncmp(str, "endmacr", cmd_length) == 0)
        return END;
    return REGULAR;
}


int firstWordLengthCounter(const char *str) {
    int counter;

    for (counter = 0; *(str + counter) && !isspace(*(str + counter)); counter++){};
    return counter;
}


int isReservedWord(char* word, const int length) {
    int i, size;

    size = sizeof(reserved_words) / sizeof(reserved_words[0]);
    for (i = 0; i < size; i++) {
        if (strncmp(word, reserved_words[i], length) == 0 && isEndOfStr(word + length)) {
            return 1;
        }
    }
    return 0;
}


int isEndOfStr(char *str) {
    char* new_str = firstNonSpaceCharacter(str);

    if (strncmp(new_str, "\n", 2) || !*new_str)
        return 1;
    else
        return 0;
}