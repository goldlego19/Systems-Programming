#include <stdio.h>



int count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1; // Error opening file
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    fclose(file);
    return count;
}

int main() {
    int lines = count_lines("number.bin");
    if (lines == -1) {
        printf("Error opening file.\n");
    } else {
        printf("Number of lines: %d\n", lines);
    }
    return 0;
}