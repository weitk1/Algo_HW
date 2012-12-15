#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: \n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[128];
    if (NULL == fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Error reading file %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    int num_vertices = 0, num_edges = 0;
    int parse_ret = sscanf(line, "%d %d", &num_vertices, &num_edges);
    if (parse_ret != 2) {
        fprintf(stderr, "Error parsing line '%s'\n", line);
        exit(EXIT_FAILURE);
    }
    printf("Num of vertices: %d, Num of edges: %d\n", num_vertices, num_edges);
    
    int p_1, p_2, weight;
    while (!feof(fp)) {
        fgets(line, sizeof(line), fp);
        int parse_ret = sscanf(line, "%d %d %d", &p_1, &p_2, &weight);
        if (parse_ret != 3) {
            fprintf(stderr, "Error parsing line '%s'\n", line);
            exit(EXIT_FAILURE);
        }
        printf("%d, %d, %d\n", p_1, p_2, weight);
    }

    fclose(fp);
}
