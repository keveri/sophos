#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>

typedef struct options { uint32_t port; char *fname; } options;

static void help_and_exit() {
    printf("Example usage: sophos -p 4444 -f wisdoms.txt\n");
    exit(1);
}

options parse_options(int argc, char **argv) {
    if (argc < 3) help_and_exit();
    int32_t c;
    uint32_t port = 0;
    char *fname = "";
    while ((c = getopt(argc, argv, "p:f:")) != -1) {
        switch (c) {
        case 'p':
            sscanf (optarg, "%u", &port);
            break;
        case 'f':
            fname = optarg;
            break;
        }
    }
    if (port < 1 || strlen(fname) < 1) help_and_exit();
    struct options o = { port, fname };
    return o;
}

