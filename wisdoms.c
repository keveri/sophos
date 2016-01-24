#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Struct for holding wisdom array pointer and the item count. */
typedef struct warray { char **items; uint16_t count; } warray;

static void free_array_and_exit(char **array, uint16_t size) {
    for (uint16_t i = 0; i < size; i++)
        free(array[i]);
    free(array);
    exit(1);
}

static void free_and_exit(char *buff) {
    free(buff);
    exit(1);
}

/* Read wisdoms from given file and return wisdom struct. */
/* TODO: increase line_buff if long lines appear */
warray read_wisdoms(const char *fname) {
    FILE *fp = fopen(fname, "r");
    if (fp == 0) {
        fprintf(stderr, "Failed to open file %s\n", fname);
        exit(1);
    }

    uint16_t max_lines = 36;
    uint16_t buff_size = 512;

    char *line_buff = malloc(buff_size);
    if (line_buff == NULL) free_and_exit(line_buff);

    char **items = malloc(sizeof(char *) * max_lines);
    if (items == NULL) free_array_and_exit(items, 0);

    uint16_t count = 0;
    while (fgets(line_buff, buff_size, fp)) {
        /* grow the array dynamically */
        if (count == max_lines) {
            max_lines *= 2;
            char **newitems = realloc(items, sizeof(char *) * max_lines);
            if (newitems == NULL) free_array_and_exit(items, count);
            items = newitems;
        }
        items[count] = malloc(strlen(line_buff) + 1);
        strcpy(items[count], line_buff);
        count++;
    }
    fclose(fp);
    free(line_buff);

    /* shrink the array to match line count */
    char **newitems = realloc(items, sizeof(char* ) * count);
    if (newitems == NULL) free_array_and_exit(items, count);
    items = newitems;

    struct warray wisdoms = { items, count };
    return wisdoms;
}

/* Free allocated memory used by wisdoms. */
void clean_wisdoms(warray wisdoms) {
    for (uint16_t i = 0; i < wisdoms.count; i++)
        free(wisdoms.items[i]);
    free(wisdoms.items);
}

/* Pick random wisdom from the array. */
char * pick_a_wisdom(warray wisdoms) {
    int x = rand() % (wisdoms.count);
    return wisdoms.items[x];
}
