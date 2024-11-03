#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[100];
    int word = 0;
    int characters = 0;
    int lines = 0;

    fp = fopen("task2test.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1; 
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        lines++; 

        characters += strlen(buffer);
        if (buffer[strlen(buffer) - 1] == '\n') {
            characters--; 
        }

        char *token = strtok(buffer, " \n\t"); 
        while (token != NULL) {
            word++; 
            token = strtok(NULL, " \n\t");
        }
    }

    fclose(fp); 

   
    printf("Words: %d\n", word);
    printf("Characters: %d\n", characters);
    printf("Lines: %d\n", lines);

    return 0;
}

