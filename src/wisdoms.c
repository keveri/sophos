#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Struct for holding wisdom array pointer and the item count. */
typedef struct warray { char **items; uint32_t count; } warray;

static void free_array_and_exit(char **array, uint32_t size) {
    for (uint32_t i = 0; i < size; i++)
        free(array[i]);
    free(array);
    exit(1);
}

static char ** array_calloc(uint32_t size) {
    char **ptr = calloc(size, sizeof(char *));
    if (ptr == NULL) free_array_and_exit(ptr, 0);
    return ptr;
}

static char ** array_realloc(char **array, uint32_t size) {
    char **new_array = realloc(array, sizeof(char *) * size);
    if (new_array == NULL) free_array_and_exit(new_array, size);
    return new_array;
}

static char * str_calloc(uint32_t size) {
    char *str = calloc(size, sizeof(char));
    if (str == NULL) {
        free(str);
        exit(1);
    }
    return str;
}

/* Read wisdoms from given file and return wisdom struct. */
/* TODO: increase line_buff if long lines appear */
warray read_wisdoms(const char *fname) {
    FILE *fp = fopen(fname, "r");
    if (fp == 0) {
        fprintf(stderr, "Failed to open file %s\n", fname);
        exit(1);
    }

    uint32_t count     = 0;
    uint32_t max_lines = 36;
    uint32_t buff_size = 512;
    char **items       = array_calloc(max_lines);
    char *line_buff    = str_calloc(buff_size);

    while (fgets(line_buff, buff_size, fp)) {
        /* grow the array dynamically */
        if (count == max_lines) {
            max_lines *= 2;
            items = array_realloc(items, max_lines);
        }
        items[count] = str_calloc(strlen(line_buff) + 1);
        strcpy(items[count], line_buff);
        count++;
    }
    fclose(fp);
    free(line_buff);
    /* shrink the array to match line count */
    items = array_realloc(items, count);

    struct warray wisdoms = { items, count };
    return wisdoms;
}

/* Free allocated memory used by wisdoms. */
void clean_wisdoms(warray wisdoms) {
    for (uint32_t i = 0; i < wisdoms.count; i++)
        free(wisdoms.items[i]);
    free(wisdoms.items);
}

/* Pick random wisdom from the array. */
char * pick_a_wisdom(warray wisdoms) {
    uint32_t x = rand() % (wisdoms.count);
    return wisdoms.items[x];
}
