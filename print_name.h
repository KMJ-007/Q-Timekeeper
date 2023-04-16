#include <stdio.h>
#include <string.h>

void print_name(char *algorithm_name) {

    // Calculate the length of the algorithm name
    int name_length = strlen(algorithm_name);

    // Calculate the width of the box
    int box_width = name_length + 4;

    // Print the top of the box
    printf("+");
    for (int i = 0; i < box_width; i++) {
        printf("-");
    }
    printf("+\n");

    // Print the sides of the box
    printf("|  ");
    printf("%s", algorithm_name);
    printf("  |\n");

    // Print the bottom of the box
    printf("+");
    for (int i = 0; i < box_width; i++) {
        printf("-");
    }
    printf("+\n");

}
