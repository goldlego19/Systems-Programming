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

void display_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
	printf("-");
    }
    fclose(file);
}

int main() {
    int lines = count_lines("number.bin");
    if (lines == -1) {
        printf("Error opening file.\n");
    } else {
        printf("Number of lines: %d\n", lines);
    }

    display_file_content("number.bin");
}
