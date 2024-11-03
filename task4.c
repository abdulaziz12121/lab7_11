#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 3

void encrypt(char *text, char *result) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            result[i] = ((ch - 'A' + (26 - SHIFT)) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            result[i] = ((ch - 'a' + (26 - SHIFT)) % 26) + 'a';
        } else {
            result[i] = ch;  
        }
    }
    result[i] = '\0';
}

void decrypt(char *text, char *result) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            result[i] = ((ch - 'A' + SHIFT) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            result[i] = ((ch - 'a' + SHIFT) % 26) + 'a';
        } else {
            result[i] = ch;  
        }
    }
    result[i] = '\0';
}

void encrypt_file(const char *input_filename, const char *output_filename) {
    FILE *input_fp = fopen(input_filename, "r");
    FILE *output_fp = fopen(output_filename, "w");

    if (input_fp == NULL || output_fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[256];
    char result[256];
    while (fgets(buffer, sizeof(buffer), input_fp) != NULL) {
        encrypt(buffer, result);
        fprintf(output_fp, "%s", result);
    }

    fclose(input_fp);
    fclose(output_fp);
}

void decrypt_file(const char *input_filename, const char *output_filename) {
    FILE *input_fp = fopen(input_filename, "r");
    FILE *output_fp = fopen(output_filename, "w");

    if (input_fp == NULL || output_fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[256];
    char result[256];
    while (fgets(buffer, sizeof(buffer), input_fp) != NULL) {
        decrypt(buffer, result);
        fprintf(output_fp, "%s", result);
    }

    fclose(input_fp);
    fclose(output_fp);
}

int main() {
    char choice;
    printf("Welcome to the Caesar Cipher Program!\n");
    printf("Do you want to perform (E)ncryption or (D)ecryption?\n> ");
    scanf(" %c", &choice);

    if (choice == 'E' || choice == 'e') {
        char method;
        printf("Do you want to encrypt data from a (F)ile or enter a (S)tring?\n> ");
        scanf(" %c", &method);

        if (method == 'F' || method == 'f') {
            char input_filename[100], output_filename[100];
            printf("Enter the input file name:\n> ");
            scanf("%s", input_filename);
            printf("Enter the output file name:\n> ");
            scanf("%s", output_filename);
            encrypt_file(input_filename, output_filename);

        } else if (method == 'S' || method == 's') {
            char text[256];
            char encrypted_text[256];
            printf("Please enter the string to encrypt:\n> ");
            getchar();
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0';
            encrypt(text, encrypted_text);
            printf("Encrypted string: %s\n", encrypted_text);
        }

    } else if (choice == 'D' || choice == 'd') {
        char method;
        printf("Do you want to decrypt data from a (F)ile or enter a (S)tring?\n> ");
        scanf(" %c", &method);

        if (method == 'F' || method == 'f') {
            char input_filename[100], output_filename[100];
            printf("Enter the input file name:\n> ");
            scanf("%s", input_filename);
            printf("Enter the output file name:\n> ");
            scanf("%s", output_filename);
            decrypt_file(input_filename, output_filename);

        } else if (method == 'S' || method == 's') {
            char text[256];
            char decrypted_text[256];
            printf("Please enter the string to decrypt:\n> ");
            getchar();
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0';
            decrypt(text, decrypted_text);
            printf("Decrypted string: %s\n", decrypted_text);
        }
    }

    return 0;
}

