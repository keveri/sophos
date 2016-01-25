#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>

typedef struct options { uint32_t port; FILE *input; } options;

static void help_and_exit() {
    printf("See man page for help.\n");
    exit(1);
}

static FILE * choose_input(int argc, char **argv) {
    FILE *input;
    if (argc > 3) {
        char *fname = argv[3];
        input = fopen(fname, "r");
        if (input == 0) {
            fprintf(stderr, "Failed to open file %s\n", fname);
            help_and_exit();
        }
    }
    else {
        input = stdin;
    }
    return input;
}

options parse_options(int argc, char **argv) {
    int32_t c;
    uint32_t port = 0;
    while ((c = getopt(argc, argv, "p:")) != -1) {
        switch (c) {
        case 'p':
            sscanf (optarg, "%u", &port);
            break;
        }
    }
    if (port < 1) help_and_exit();
    FILE *input = choose_input(argc, argv);
    struct options o = { port, input };
    return o;
}
