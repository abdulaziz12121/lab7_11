#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input_fp, *output_fp;
    char input_filename[] = "bitstream(3).bit";
    char output_filename[] = "bitstream.hex";
    char bit;
    int byte = 0;
    int bit_count = 0;

    // Open the input and output files
    input_fp = fopen(input_filename, "r");
    if (input_fp == NULL) {
        perror("Error opening input file");
        return 1;
    }

    output_fp = fopen(output_filename, "w");
    if (output_fp == NULL) {
        perror("Error opening output file");
        fclose(input_fp);
        return 1;
    }

    // Read bits and group them into bytes
    while ((bit = fgetc(input_fp)) != EOF) {
        if (bit == '0' || bit == '1') {
            // Shift the byte left and add the new bit
            byte |= (bit - '0') << bit_count;
            bit_count++;

            // When we have 8 bits, write the byte in hexadecimal and reset
            if (bit_count == 8) {
                fprintf(output_fp, "%02X\n", byte);
                byte = 0;
                bit_count = 0;
            }
        }
    }

    // If there are remaining bits, pad with zeros
    if (bit_count > 0) {
        fprintf(output_fp, "%02X\n", byte);
    }

    // Close the files
    fclose(input_fp);
    fclose(output_fp);

    printf("Conversion complete. Check the output file '%s'.\n", output_filename);

    return 0;
}

