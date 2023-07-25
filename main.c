/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char** lines;
    int size;
    int head;
    int count;
} CircularBuffer;

// Function to initialize the circular buffer
void initBuffer(CircularBuffer* buffer, int size) {
    buffer->lines = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; ++i) {
        buffer->lines[i] = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    }
    buffer->size = size;
    buffer->head = 0;
    buffer->count = 0;
}

// Function to add a line to the circular buffer
void addLine(CircularBuffer* buffer, const char* line) {
    int len = strlen(line) + 1; // +1 to include the null-terminator
    strncpy(buffer->lines[buffer->head], line, MAX_LINE_LENGTH - 1);
    buffer->lines[buffer->head][MAX_LINE_LENGTH - 1] = '\0'; // Ensure null-termination

    buffer->head = (buffer->head + 1) % buffer->size;
    if (buffer->count < buffer->size) {
        buffer->count++;
    }
}

// Function to print the last n lines from the circular buffer
void printLastLines(CircularBuffer* buffer, int n) {
    int i = buffer->head;
    for (int j = 0; j < n && j < buffer->count; ++j) {
        printf("%s", buffer->lines[i]);
        i = (i + 1) % buffer->size;
    }
}

// Function to free memory used by the circular buffer
void freeBuffer(CircularBuffer* buffer) {
    for (int i = 0; i < buffer->size; ++i) {
        free(buffer->lines[i]);
    }
    free(buffer->lines);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Error: n must be a positive integer.\n");
        return 1;
    }

    CircularBuffer buffer;
    initBuffer(&buffer, n);

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        addLine(&buffer, line);
    }

    printLastLines(&buffer, n);
    freeBuffer(&buffer);

    return 0;
}

